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
int isEmpty(QueueMotor*,QueueChassi*,QueueJante*,QueuePneu*,QueuePedidos*);
void escreverFicheiroInventario(QueueMotor *,QueueChassi *,QueueJante *,QueuePneu *, char* );

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
	QueueCarro listaCarrosNaoProduzidos;

	//inicializando listas
	queueInitMotor(&listaMotores);
	queueInitChassi(&listaChassis);
	queueInitJante(&listaJante);
	queueInitPneu(&listaPneu);
	queueInitPedido(&listaPedidos);
	queueInitCarro(&listaCarrosProduzidos);
	queueInitCarro(&listaCarrosNaoProduzidos);

	if (argv[1]!=NULL && argc!=1)
	{
		leFicheiroInventario(&listaMotores,&listaChassis,&listaJante,&listaPneu,argv[1]);
		leFicheiroPedidos(&listaPedidos,argv[1]);
	}

	do
	{
		printMenu();

		scanf(" %5s", opcao);

		if (strcmp(opcao,"write")==0 || strcmp(opcao,"ro")==0 || strcmp(opcao,"rs")==0)
		{
			scanf(" %39s",file);
			printf("file = /%s/\n",file);
		}

		if (strcmp(opcao,"prod")==0)
		{
			if (isEmpty(&listaMotores,&listaChassis,&listaJante,&listaPneu,&listaPedidos))
			{
				puts(ERR_NO_FILES);
			}else
			{
				iniciarProducao(&listaMotores,&listaChassis,&listaJante,&listaPneu,
				&listaCarrosProduzidos,&listaCarrosNaoProduzidos,listaPedidos);
			}
		}else if (strcmp(opcao,"show")==0)
		{
			mostraInventario(&listaMotores,&listaChassis,&listaJante,&listaPneu);
		}else if (strcmp(opcao,"done")==0)
		{
			if (isEmptyCarro(&listaCarrosProduzidos))
			{
				puts(WARN_NO_PRODUCTION_INIT);
			}else
			{
				printQueueCarro(&listaCarrosProduzidos);
			}		
		}else if (strcmp(opcao,"todo")==0)
		{
			if (isEmptyCarro(&listaCarrosNaoProduzidos))
			{
				puts(WARN_NO_PRODUCTION_INIT);
			}else
			{
				printQueueCarroEspecial(&listaCarrosNaoProduzidos);
			}
		}else if (strcmp(opcao,"write")==0)
		{
			if (countQueueCarro(&listaCarrosProduzidos)>0 || countQueueCarro(&listaCarrosNaoProduzidos)>0)
			{
				escreverFicheiroInventario(&listaMotores,&listaChassis,&listaJante,&listaPneu,file);
				escreveCarroProduzidos(&listaCarrosProduzidos,file);
				escreveCarroNaoProduzidos(&listaCarrosNaoProduzidos,file);
			}else
			{
				puts(WARN_NO_PRODUCTION_INIT);
			}
			
		}else if (strcmp(opcao,"rs")==0)
		{
			leFicheiroInventario(&listaMotores,&listaChassis,&listaJante,&listaPneu,file);		
		}else if (strcmp(opcao,"ro")==0)
		{
			leFicheiroPedidos(&listaPedidos,file);		
		}else if (strcmp(opcao,"sos")==0 || strcmp(opcao,"bye")==0)
		{
			continue;
		}else
		{
			puts(ERR_ARGS);
		}
		
	}while(strcmp(opcao,"bye")!=0);
}

void printMenu ()
{
	printf("**********Autolusofona***********\n");
	printf("prod . Iniciar producao\n");
	printf("show . Mostrar inventario atual\n");
	printf("done . Mostrar pedidos satisfeitos\n");
	printf("todo . Mostrar pedidos insatisfeitos\n");
	printf("write <basename> . Escrever ficheiros atualizados\n");
	printf("rs <basename> . Ler ficheiro de inventario\n");
	printf("ro <basename> . Ler ficheiro de pedidos\n");
	printf("bye . Sair\n");
	printf("sos . Mostrar o menu\n");
	printf("*********************************\n");
}

int isEmpty(QueueMotor *listaMotores,QueueChassi *listaChassi,
QueueJante *listaJante,QueuePneu *listaPneu, QueuePedidos *listaPedidos)
{
	if (listaMotores->head==NULL && listaChassi->head==NULL && listaJante->head==NULL
	&& listaPneu->head==NULL && listaPedidos->head==NULL)
	{
		return 1;
	}
	return 0;
}

void mostraInventario(QueueMotor *listaMotores,QueueChassi *listaChassi,
QueueJante *listaJante,QueuePneu *listaPneu)
{
	// printQueueMotor(listaMotores);
	// printQueueChassi(listaChassi);
	printQueueJante(listaJante);
	// printQueuePneu(listaPneu);
}

void escreverFicheiroInventario(QueueMotor *listaMotores,QueueChassi *listaChassi,
QueueJante *listaJante,QueuePneu *listaPneu, char* file)
{
	char* localFile = strcat(strtok(file,"."),"_out.inventario");
	escreveMotoresInventario(listaMotores,localFile);
	escreveChassiInventario(listaChassi,localFile);
	escreveJanteInventario(listaJante, localFile);
	escrevePneuInventario(listaPneu, localFile);
}

