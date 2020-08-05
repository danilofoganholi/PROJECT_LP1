#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Motor.h"
#include "Chassi.h"
#include "Jante.h"
#include "Pneu.h"
#include "Carro.h"
#include "readFiles.h"

#define ERR_FOPEN "Error: could not open file."
#define ERR_CORPT "Error: File is corrupted."
#define ERR_ARGS "Error: Invalid argument."
#define ERR_MEM "Error: Couldn't allocate memory."
#define WARN_NO_PRODUCTION_INIT "Warning: No production done initiated yet."
#define ERR_NO_FILES "No files were specified"

Motor pegaMotor(FILE* filePointer)
{
	//declara variaveis
	struct Motor motor;

	char numSerie[21];
	char potencia[5];
	char fuel[10];

	fscanf(filePointer, ",%20s,%4s,",numSerie,potencia);//pega variaveis do input
	fscanf(filePointer, " %9[^\n]",fuel);//pega variaveis do input

	//atribui ao motor declarado
	strcpy(motor.numSerie,numSerie);
	motor.potencia=atoi(potencia);//converte pra int
	strcpy(motor.type_of_fuel,fuel);
	motor.next=NULL;

	return motor;//devolve motor montado
}

Chassi pegaChassi(FILE* filePointer)
{
	//declara variaveis
	struct Chassi chassi;

	char rest[4];
	char numSerie[21];
	char color[11];
	char modelo[128];

	fscanf(filePointer, "%2s,%20s,%10[^,]s",rest,numSerie,color);//pega variaveis do input
	fscanf(filePointer, " ,%127[^\n]",modelo);//pega variaveis do input

	//atribui ao motor declarado
	strcpy(chassi.numSerie,numSerie);
	strcpy(chassi.color,color);
	strcpy(chassi.modelo,modelo);
	chassi.next=NULL;

	return chassi;//devolve chassi montado
}

Jante pegaJante(FILE* filePointer)
{
	//declara variaveis
	struct Jante jante;

	char rest[4];
	char numSerie[21];
	char diametro[3];
	char largura[4];
	char color[10];

	fscanf(filePointer, "%1s,%20s,%2s,%3s,",rest,numSerie,diametro,largura);//pega variaveis do input
	fscanf(filePointer, " %9[^\n]",color);//pega variaveis do input

	//atribui ao motor declarado
	strcpy(jante.numSerie,numSerie);
	jante.diametro = atoi(diametro);//converte pra int
	jante.largura = atoi(largura);//converte pra int
	strcpy(jante.color,color);
	jante.next=NULL;

	return jante;//devolve jante montado
}

Pneu pegaPneu(FILE* filePointer)
{
	//declara variaveis
	struct Pneu pneu;

	char numSerie[21];
	char diametro[3];
	char largura[4];
	char altura[3];

	fscanf(filePointer, ",%20s,%2s,%3s,",numSerie,diametro,largura);//pega variaveis do input
	fscanf(filePointer, " %2[^\n]",altura);//pega variaveis do input

	//atribui ao motor declarado
	strcpy(pneu.numSerie,numSerie);
	pneu.diametro=atoi(diametro);//converte pra int
	pneu.largura=atoi(largura);//converte pra int
	pneu.altura=atoi(altura);//converte pra int
	pneu.next=NULL;

	return pneu;//devolve pneu montado
}

void leFicheiroInventario(QueueMotor *listaMotores,QueueChassi *listaChassi,
QueueJante *listaJante,QueuePneu *listaPneu, char* file)
{
	char *localFile = strcat(file,".inventario");//coloca a extensao

	FILE *filePointer = fopen(localFile, "r");//abre arquivo em modo leitura	
	if (filePointer == NULL)//verifica se e null
	{
		puts(ERR_FOPEN);
		return;
	}
	while(!feof(filePointer))//enquanto tiver linha a ser lida
	{
		char type[6]="";//reset type
		
		fscanf(filePointer, "%5s",type);//tipo de peca a ser lida

		if (strcmp(type,"")==0)//se for vazio é pq acabou a leitura
		{
			break;
		}
		
		if (strncmp(type,"Motor",1)==0)//se for motor 
		{
			struct Motor aux = pegaMotor(filePointer);//monta e devolve o motor
			queueInsertMotor(listaMotores,aux);//insere o motor
		}
		else if (strcmp(type,"Chass")==0)//se for chassi
		{
			struct Chassi aux = pegaChassi(filePointer);//monta e devolve o chassi
			queueInsertChassi(listaChassi,aux);//insere o chassi
		}
		else if (strcmp(type,"Jante")==0)//se for jante
		{
			struct Jante aux = pegaJante(filePointer);//monta e devolve o jante
			queueInsertJante(listaJante,aux);//insere o jante
		}
		else if (strcmp(type,"Pneus")==0)//se for pneu
		{
			struct Pneu aux = pegaPneu(filePointer);//monta e devolve o pneu
			queueInsertPneu(listaPneu,aux);//insere o pneu
		}
	}
	fclose(filePointer);//fecha arquivo
}

void leFicheiroPedidos(QueuePedidos *listaPedidos,char* file)
{
	char *localFile = strcat(strtok(file,"."),".pedidos");//coloca a extensao

	FILE *filePointer = fopen(localFile, "r");//abre arquivo em modo leitura
	if (filePointer == NULL)//valida se é null
	{
		puts(ERR_FOPEN);
		return;
	}

	while(!feof(filePointer))//enquanto tiver linha a ser lida
	{
		//reset das variaveis
		char numPedido[21]="";

		char MotorPotencia[5]="";
		char Motor_fuel[9]="";

		char ChassiColor[10]="";
		char ChassiModelo[128]="";

		char JanteDiametro[4]="";
		char JanteLargura[4]="";
		char JanteColor[10]="";

		char PneuDiametro[4]="";
		char PneuLargura[4]="";
		char PneuAltura[4]="";


		//atribuindo valores as variaveis pela linha
		fscanf(filePointer," %20s",numPedido);

		fscanf(filePointer,";%4[^,]s",MotorPotencia);
		fscanf(filePointer,",%8[^;]s",Motor_fuel);

		fscanf(filePointer,";%9[^,]s",ChassiColor);
		fscanf(filePointer,",%127[^;]s",ChassiModelo);

		fscanf(filePointer,";%3[^,]s",JanteDiametro);
		fscanf(filePointer,",%3[^,]s",JanteLargura);
		fscanf(filePointer,",%9[^;]s",JanteColor);

		fscanf(filePointer,";%3[^,]s",PneuDiametro);
		fscanf(filePointer,",%3[^,]s",PneuLargura);
		fscanf(filePointer,",%3[^\n]s",PneuAltura);
		
		if (strcmp(numPedido,"")==0)//se for vazio é pq acabou a leitura
		{
			break;
		}
		
		//variavel para montar pedido
		struct Pedido pedido;

		strcpy(pedido.numPedido, numPedido);//coloca numero de serie

		pedido.Motorpotencia = atoi(MotorPotencia);//passa pra int
		pedido.JanteDiametro = atoi(JanteDiametro);//passa pra int
		pedido.JanteLargura = atoi(JanteLargura);//passa pra int
		pedido.PneuDiametro = atoi(PneuDiametro);//passa pra int
		pedido.PneuLargura = atoi(PneuLargura);//passa pra int
		pedido.PneuAltura = atoi(PneuAltura);//passa pra int

		//verifica o tamanho para saber se é necessario colocar zerar a string
		if (strlen(Motor_fuel)>2)
		{
			strcpy(pedido.Motor_fuel,Motor_fuel);
		}else
		{
			pedido.Motor_fuel[0] = '\0';
		}

		if (strlen(ChassiColor)>2)
		{
			strcpy(pedido.ChassiColor,ChassiColor);
		}else
		{
			pedido.ChassiColor[0] = '\0';
		}

		if (strlen(ChassiModelo)>2)
		{
			strcpy(pedido.ChassiModelo,ChassiModelo);
		}else
		{
			pedido.ChassiModelo[0] = '\0';
		}

		if (strlen(JanteColor)>2)
		{
			strcpy(pedido.JanteColor, JanteColor);
		}else
		{
			pedido.JanteColor[0] = '\0';
		}

		queueInsertPedido(listaPedidos,pedido);//insere pedido
	}
	fclose(filePointer);//fecha arquivo
}