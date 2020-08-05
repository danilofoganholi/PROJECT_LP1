#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define ERR_FOPEN "Error: could not open file."
#define ERR_CORPT "Error: File is corrupted."
#define ERR_ARGS "Error: Invalid argument."
#define ERR_MEM "Error: Couldn't allocate memory."
#define WARN_NO_PRODUCTION_INIT "Warning: No production done initiated yet."
#define ERR_NO_FILES "No files were specified"
#include "Pedidos.h"

void queueInitPedido(QueuePedidos *q)
{
	//inicializa pedido
	q -> head = NULL;
	q -> tail = NULL;
}

void queueInsertPedido (QueuePedidos *q, Pedido pedido )
{
	//aloca memoria para pedido
	Pedido *tmp = (Pedido *) malloc(sizeof(Pedido));
	if (tmp == NULL)
		printf(ERR_MEM);

	*tmp=pedido;
	
	tmp->next = NULL;//colocar a null

	if (q->head == NULL)//se for o primeiro elemento da lista
		q->head = tmp;//coloca na primeira posicao
	else
		q->tail->next=tmp;

	//em ambos os casos arrumar o tail pois a insercao eh no final
	q->tail=tmp;
}

void escrevePedidoNaoProduzidos(QueuePedidos *q, char* file)
{
	if (q->head==NULL)//verifica se fila é vazia
	{
		return;
	}
	char tmpFile[40];
	strcpy(tmpFile,file);
	char* localFile = strcat(tmpFile,"_out.naoproduzidos");//arruma nome do arquivo com extensao

	Pedido *t;

	FILE * filepointer= fopen(localFile, "a");//abre o arquivo

	//percorre a fila escrevendo cada node em uma linha do ficheiro
	for (t = q->head ; t!= NULL ; t = t -> next)
	{
		fprintf(filepointer,"%s;",t->numPedido);
		fprintf(filepointer,"%d",t->Motorpotencia);
		fprintf(filepointer,",%s;%s,%s;",t->Motor_fuel,t->ChassiColor,t->ChassiModelo);
		fprintf(filepointer,"%d",t->JanteDiametro);
		fprintf(filepointer,",");
		fprintf(filepointer,"%d",t->JanteLargura);
		fprintf(filepointer,",%s;",t->JanteColor);
		fprintf(filepointer,"%d",t->PneuDiametro);
		fprintf(filepointer,",");
		fprintf(filepointer,"%d",t->PneuLargura);
		fprintf(filepointer,",");
		fprintf(filepointer,"%d",t->PneuAltura);
		fprintf(filepointer,"\n");
	}
	fclose(filepointer);//fecha ficheiro
}

void printQueuePedido(QueuePedidos *q)
{
	if (q->head==NULL)//validade se fila não é vazia
	{
		return;
	}
	Pedido *t;

	//percorre fila printando todos os nodes, um em cada linha
	for (t = q->head ; t != NULL ; t = t -> next)
	{
		printf("%s;",t->numPedido);
		printf("%d",t->Motorpotencia);
		printf(",%s;%s,%s;",t->Motor_fuel,t->ChassiColor,t->ChassiModelo);
		printf("%d",t->JanteDiametro);
		printf(",");
		printf("%d",t->JanteLargura);
		printf(",%s;",t->JanteColor);
		printf("%d",t->PneuDiametro);
		printf(",");
		printf("%d",t->PneuLargura);
		printf(",");
		printf("%d",t->PneuAltura);
		printf("\n");
	}
}