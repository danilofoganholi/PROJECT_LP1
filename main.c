#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Motor.h"
#include "Chassi.h"
#include "Jante.h"
#include "Pneu.h"
#include "Carro.h"
#include "Pedidos.h"
#include "producao.h"
#include "readFiles.h"

#define ERR_FOPEN "Error: could not open file."
#define ERR_CORPT "Error: File is corrupted."
#define ERR_ARGS "Error: Invalid argument."
#define ERR_MEM "Error: Couldn't allocate memory."
#define WARN_NO_PRODUCTION_INIT "Warning: No production done initiated yet."
#define ERR_NO_FILES "No files were specified"

void printMenu ();
void mostraInventario();
void escreverFicheiroInventario(QueueMotor *,QueueChassi *,QueueJante *,QueuePneu *, char* );
void ordenaListas(QueueMotor*,QueueChassi*,QueueJante*,QueuePneu*);

int main(int argc, char **argv)
{
	// declaracao das variaveis
	char opcao[6];
	char file[40];
	QueueMotor listaMotores;
	QueueChassi listaChassis;
	QueueJante listaJante;
	QueuePneu listaPneu;
	QueuePedidos listaPedidos;
	QueueCarro listaCarrosProduzidos;
	QueuePedidos listaPedidosNaoProduzidos;

	//inicializando listas
	queueInitMotor(&listaMotores);
	queueInitChassi(&listaChassis);
	queueInitJante(&listaJante);
	queueInitPneu(&listaPneu);
	queueInitPedido(&listaPedidos);
	queueInitCarro(&listaCarrosProduzidos);
	queueInitPedido(&listaPedidosNaoProduzidos);


	if (argv[1]!=NULL && argc!=1)//caso tenha sido passado parametros
	{
		//le todos os ficheiros e coloca nas devidas lista
		leFicheiroInventario(&listaMotores,&listaChassis,&listaJante,&listaPneu,argv[1]);
		leFicheiroPedidos(&listaPedidos,argv[1]);
		//ja ordena as listas do inventario
		ordenaListas(&listaMotores,&listaChassis,&listaJante,&listaPneu);
	}
	printMenu();
	do
	{
		scanf(" %5s", opcao);//le a opcao desejada

		if (strcmp(opcao,"write")==0 || strcmp(opcao,"show")==0 ||
		 strcmp(opcao,"ro")==0 || strcmp(opcao,"rs")==0)
		{
			//caso seja uma opcao que precise de file pegaremos aqui
			scanf(" %39s",file);
		}

		//usando o comparador de string para definir o que precisa ser feito
		if (strcmp(opcao,"prod")==0)
		{
			iniciarProducao(&listaMotores,&listaChassis,&listaJante,&listaPneu,
			&listaCarrosProduzidos,&listaPedidosNaoProduzidos,listaPedidos);

		}else if (strcmp(opcao,"show")==0)
		{
			ordenaListas(&listaMotores,&listaChassis,&listaJante,&listaPneu);
			if(strcmp(file,"motors")==0)
			{
				printQueueMotor(&listaMotores);
			}else if(strcmp(file,"chassis")==0)
			{
				printQueueChassi(&listaChassis);
			}else if(strcmp(file,"wheels")==0)
			{
				printQueueJante(&listaJante);
			}else if(strcmp(file,"tyres")==0)
			{
				printQueuePneu(&listaPneu);
			}else
			{
				mostraInventario(&listaMotores,&listaChassis,&listaJante,&listaPneu);
			}
		}else if (strcmp(opcao,"done")==0)
		{
			printQueueCarro(&listaCarrosProduzidos);
		}else if (strcmp(opcao,"todo")==0)
		{
			printQueuePedido(&listaPedidosNaoProduzidos);
		}else if (strcmp(opcao,"write")==0)
		{
			escreverFicheiroInventario(&listaMotores,&listaChassis,&listaJante,&listaPneu,file);
			escreveCarroProduzidos(&listaCarrosProduzidos,file);
			escrevePedidoNaoProduzidos(&listaPedidosNaoProduzidos,file);

		}else if (strcmp(opcao,"rs")==0)
		{
			leFicheiroInventario(&listaMotores,&listaChassis,&listaJante,&listaPneu,file);
			ordenaListas(&listaMotores,&listaChassis,&listaJante,&listaPneu);		
		}else if (strcmp(opcao,"ro")==0)
		{
			leFicheiroPedidos(&listaPedidos,file);		
		}else if (strcmp(opcao,"sos")==0)
		{
			printMenu();
		}else if(strcmp(opcao,"bye")==0)
		{
			continue;
		}else
		{
			puts(ERR_ARGS);
		}
	}while(strcmp(opcao,"bye")!=0);

	exit(0);
}

void printMenu ()
{
	printf("**********Autolusofona***********\n");
	printf("prod . Iniciar producao\n");
	printf("show <type> . Mostrar inventario atual\n");
	printf("done . Mostrar pedidos satisfeitos\n");
	printf("todo . Mostrar pedidos insatisfeitos\n");
	printf("write <basename> . Escrever ficheiros atualizados\n");
	printf("rs <basename> . Ler ficheiro de inventario\n");
	printf("ro <basename> . Ler ficheiro de pedidos\n");
	printf("bye . Sair\n");
	printf("sos . Mostrar o menu\n");
	printf("*********************************\n");
}

void ordenaListas(QueueMotor *listaMotores,QueueChassi *listaChassi,
QueueJante *listaJante,QueuePneu *listaPneu)
{
	if ((listaMotores->head==NULL) && (listaChassi->head==NULL) & 
	(listaJante->head==NULL) && (listaPneu->head==NULL))//verifica se nenhuma lista é nula
	{
		return;
	}
	bubbleSortMotor(listaMotores);
	bubbleSortChassi(listaChassi);
	bubbleSortJante(listaJante);
	bubbleSortPneu(listaPneu);
}

void mostraInventario(QueueMotor *listaMotores,QueueChassi *listaChassi,
QueueJante *listaJante,QueuePneu *listaPneu)
{
	if ((listaMotores->head==NULL) && (listaChassi->head==NULL) & 
	(listaJante->head==NULL) && (listaPneu->head==NULL))//verifica se nenhuma lista é nula
	{
		return;
	}
	printQueueMotor(listaMotores);
	printQueueChassi(listaChassi);
	printQueueJante(listaJante);
	printQueuePneu(listaPneu);
}

void escreverFicheiroInventario(QueueMotor *listaMotores,QueueChassi *listaChassi,
QueueJante *listaJante,QueuePneu *listaPneu, char* file)
{
	if ((listaMotores->head==NULL) && (listaChassi->head==NULL) & 
	(listaJante->head==NULL) && (listaPneu->head==NULL))//verifica se nenhuma lista é nula
	{
		return;
	}
	char tmpFile[40];
	strcpy(tmpFile,file);
	char* localFile = strcat(tmpFile,"_out.inventario");//prepara o nome do arquivo

	escreveMotoresInventario(listaMotores,localFile);
	escreveChassiInventario(listaChassi,localFile);
	escreveJanteInventario(listaJante, localFile);
	escrevePneuInventario(listaPneu, localFile);
}

