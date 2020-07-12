#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "./Motor/Motor.h"
#include "./Chassi/Chassi.h"
#include "./Jante/Jante.h"
#include "./Pneu/Pneu.h"
#include "./Carro/Carro.h"
#include "./Pedidos/Pedidos.h"
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
	int opcao=0;
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
		strcpy(file,argv[1]);
	}

	do
	{
		printMenu();
		do//pegando input e validando
		{
			scanf(" %d", &opcao);

			if (opcao == 6 || opcao==7)
			{
				scanf(" %s",file);
			}
			
			if (opcao<1 || opcao>8) printf("Invalid choice.Try again.");

		} while (opcao<1 || opcao>8);

		switch (opcao)
		{
			case 1:
				if (isEmpty(&listaMotores,&listaChassis,&listaJante,&listaPneu,&listaPedidos))
				{
					puts(ERR_NO_FILES);
				}else
				{
					iniciarProducao(&listaMotores,&listaChassis,&listaJante,&listaPneu,
					&listaCarrosProduzidos,&listaCarrosNaoProduzidos,listaPedidos);
				}
				break;
			case 2:
				mostraInventario(&listaMotores,&listaChassis,&listaJante,&listaPneu);
				break;
			case 3:
				if (isEmptyCarro(&listaCarrosProduzidos))
				{
					puts(WARN_NO_PRODUCTION_INIT);
				}else
				{
					printQueueCarro(&listaCarrosProduzidos);
				}
				break;
			case 4:
				if (isEmptyCarro(&listaCarrosNaoProduzidos))
				{
					puts(WARN_NO_PRODUCTION_INIT);
				}else
				{
					printQueueCarroEspecial(&listaCarrosNaoProduzidos);
				}
				break;
			case 5:
				escreverFicheiroInventario(&listaMotores,&listaChassis,&listaJante,&listaPneu,file);
				escreveCarroProduzidos(&listaCarrosProduzidos,file);
				escreveCarroNaoProduzidos(&listaCarrosNaoProduzidos,file);
				break;
			case 6:
				leFicheiroInventario(&listaMotores,&listaChassis,&listaJante,&listaPneu,file);
				break;
			case 7:
				leFicheiroPedidos(&listaPedidos,file);
				break;
			case 8:
				break;
			default:
				puts(ERR_ARGS);
				break;
		}
		
	}while(opcao!=8);
}

void printMenu ()
{
	printf("**********Autolusofona***********\n");
	printf("1. Iniciar producao\n");
	printf("2. Mostrar inventario atual\n");
	printf("3. Mostrar pedidos satisfeitos\n");
	printf("4. Mostrar pedidos insatisfeitos\n");
	printf("5. Escrever ficheiros atualizados\n");
	printf("6. Ler ficheiro de inventario\n");
	printf("7. Ler ficheiro de pedidos\n");
	printf("8. Sair\n");
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
	printQueueMotor(listaMotores);
	printQueueChassi(listaChassi);
	printQueueJante(listaJante);
	printQueuePneu(listaPneu);
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

