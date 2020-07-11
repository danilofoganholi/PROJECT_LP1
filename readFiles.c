#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "./Motor/Motor.h"
#include "./Chassi/Chassi.h"
#include "./Jante/Jante.h"
#include "./Pneu/Pneu.h"
#include "./Carro/Carro.h"
#include "readFiles.h"

#define ERR_FOPEN "Error: could not open file."
#define ERR_CORPT "Error: File is corrupted."
#define ERR_ARGS "Error: Invalid argument."
#define ERR_MEM "Error: Couldn't allocate memory."
#define WARN_NO_PRODUCTION_INIT "Warning: No production done initiated yet."
#define ERR_NO_FILES "No files were specified"

Motor* pegaMotor(FILE* filePointer)
{
	Motor *tmp = (Motor *) malloc(sizeof(Motor));
	if (tmp == NULL)
		printf(ERR_MEM);

	char numSerie[21];
	char potencia[5];
	char fuel[10];

	fscanf(filePointer, ",%20s,%4s,",numSerie,potencia);
	fscanf(filePointer, " %9[^\n]",fuel);

	strcpy(tmp->numSerie,numSerie);
	tmp->potencia=atoi(potencia);
	strcpy(tmp->type_of_fuel,fuel);

	return tmp;
}

Chassi* pegaChassi(FILE* filePointer)
{
	Chassi *tmp = (Chassi *) malloc(sizeof(Chassi));
	if (tmp == NULL)
		printf(ERR_MEM);

	char rest[4];
	char numSerie[21];
	char color[11];
	char modelo[128];

	fscanf(filePointer, "%2s,%20s,%10[^,]s",rest,numSerie,color);
	fscanf(filePointer, " ,%127[^\n]",modelo);

	strcpy(tmp->numSerie,numSerie);
	strcpy(tmp->color,color);
	strcpy(tmp->modelo,modelo);

	return tmp;
}

Jante* pegaJante(FILE* filePointer)
{
	Jante *tmp = (Jante *) malloc(sizeof(Jante));
	if (tmp == NULL)
		printf(ERR_MEM);

	char rest[4];
	char numSerie[21];
	char diametro[3];
	char largura[4];
	char color[10];

	fscanf(filePointer, "%1s,%20s,%2s,%3s,",rest,numSerie,diametro,largura);
	fscanf(filePointer, " %9[^\n]",color);

	strcpy(tmp->numSerie,numSerie);
	tmp->diametro = atoi(diametro);
	tmp->largura = atoi(largura);
	strcpy(tmp->color,color);

	return tmp;
}

Pneu* pegaPneu(FILE* filePointer)
{
	Pneu *tmp = (Pneu *) malloc(sizeof(Pneu));
	if (tmp == NULL)
		printf(ERR_MEM);

	char numSerie[21];
	char diametro[3];
	char largura[4];
	char altura[3];

	fscanf(filePointer, ",%20s,%2s,%3s,",numSerie,diametro,largura);
	fscanf(filePointer, " %2[^\n]",altura);

	strcpy(tmp->numSerie,numSerie);
	tmp->diametro = atoi(diametro);
	tmp->largura = atoi(largura);
	tmp->altura = atoi(altura);

	return tmp;
}

void leFicheiroInventario(QueueMotor *listaMotores,QueueChassi *listaChassi,
QueueJante *listaJante,QueuePneu *listaPneu, char* file)
{
	char *localFile = strcat(file,".inventario");

	FILE *filePointer = fopen(localFile, "r");	

	if (filePointer == NULL)
	{
		printf(ERR_FOPEN);
		return;
	}

	while(!feof(filePointer))
	{
		char type[6];
		
		fscanf(filePointer, " %5s",type);

		// printf("MOTOR = {%s;%s;%s}\n",numSerie,potencia,fuel);

		if (strcmp(type,"Motor")==0)
		{
			struct Motor* aux = pegaMotor(filePointer);
			queueInsertMotor(listaMotores,*aux);
		}
		else if (strcmp(type,"Chass")==0)
		{
			struct Chassi* aux = pegaChassi(filePointer);
			queueInsertChassi(listaChassi,*aux);
		}
		else if (strcmp(type,"Jante")==0)
		{
			struct Jante* aux = pegaJante(filePointer);
			queueInsertJante(listaJante,*aux);
		}
		else if (strcmp(type,"Pneus")==0)
		{
			struct Pneu* aux = pegaPneu(filePointer);
			queueInsertPneu(listaPneu,*aux);
		}
	}
	fclose(filePointer);
}

void leFicheiroPedidos(QueuePedidos *listaPedidos,char* file)
{
	char *localFile = strcat(strtok(file,"."),".pedidos");

	FILE *filePointer = fopen(localFile, "r");	

	if (filePointer == NULL)
	{
		puts(ERR_FOPEN);
		return;
	}

	while(!feof(filePointer))
	{
		char numPedido[21];

		char MotorPotencia[5];
		char Motor_fuel[9];

		char ChassiColor[10];
		char ChassiModelo[128];

		char JanteDiametro[4];
		char JanteLargura[4];
		char JanteColor[10];

		char PneuDiametro[4];
		char PneuLargura[4];
		char PneuAltura[4];

		fscanf(filePointer,"%20s",numPedido);

		fscanf(filePointer,";%[^,]s",MotorPotencia);
		fscanf(filePointer,",%[^;]s",Motor_fuel);

		fscanf(filePointer,";%[^,]s",ChassiColor);
		fscanf(filePointer,",%[^;]s",ChassiModelo);

		fscanf(filePointer,";%[^,]s",JanteDiametro);
		fscanf(filePointer,",%[^,]s",JanteLargura);
		fscanf(filePointer,",%[^;]s",JanteColor);

		fscanf(filePointer,";%[^,]s",PneuDiametro);
		fscanf(filePointer,",%[^,]s",PneuLargura);
		fscanf(filePointer,",%[^\n]s",PneuAltura);

		Pedido *tmp = (Pedido *) malloc(sizeof(Pedido));
		if (tmp == NULL)
			printf(ERR_MEM);

		// printf("%s = Motor{%s,%s} Chassi={%s,%s} Jantes={%s,%s,%s} Pneus={%s,%s,%s}\n",
		// numPedido,MotorPotencia,Motor_fuel,ChassiColor,ChassiModelo,JanteDiametro,JanteLargura,
		// JanteColor,PneuDiametro,PneuLargura,PneuAltura);

		strcpy(tmp->numPedido, numPedido);

		tmp->Motorpotencia = atoi(MotorPotencia);
		strcpy(tmp->Motor_fuel,Motor_fuel);

		strcpy(tmp->ChassiColor,ChassiColor);
		strcpy(tmp->ChassiModelo,ChassiModelo);

		tmp->JanteDiametro = atoi(JanteDiametro);
		tmp->JanteLargura = atoi(JanteLargura);
		strcpy(tmp->JanteColor, JanteColor);

		tmp->PneuDiametro = atoi(PneuDiametro);
		tmp->PneuLargura = atoi(PneuLargura);
		tmp->PneuAltura = atoi(PneuAltura);

		queueInsertPedido(listaPedidos,*tmp);
	}
	fclose(filePointer);
}