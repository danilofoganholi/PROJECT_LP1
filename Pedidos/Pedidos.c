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
	q -> head = NULL;
	q -> tail = NULL;
}

void queueInsertPedido (QueuePedidos *q, Pedido pedido )
{
	Pedido *tmp = (Pedido *) malloc(sizeof(Pedido));
	if (tmp == NULL)
		printf(ERR_MEM);

	*tmp=pedido;
	
	tmp->next = NULL;
	if (q->head == NULL)
		q->head = tmp;
	else
		q->tail->next=tmp;
	q->tail=tmp;
}

void queueRemovePedido (QueuePedidos *q, Pedido pedido )
{
	Pedido *t = (Pedido*) malloc(sizeof(Pedido));
	if (t == NULL)
		printf(ERR_MEM);
	for (t = q->head ; t->next != NULL ; t = t -> next)
	{
		if (strncmp(t->next->numPedido,pedido.numPedido,20)==0)
		{
			Pedido *aux = t->next;
			t->next = t->next->next;
			free(aux);
		}
	}
}

void printQueuePedido(QueuePedidos *q)
{
	Pedido *t = (Pedido*) malloc(sizeof(Pedido));
	if (t == NULL)
		printf(ERR_MEM);
	for (t = q->head ; t->next != NULL ; t = t -> next)
	{
		printf("%s;%d,%s;%s,%s;%d,%d,%s;%d,%d,%d;\n",
		t->numPedido,t->Motorpotencia,t->Motor_fuel,t->ChassiColor,t->ChassiModelo,t->JanteDiametro,
		t->JanteLargura,t->JanteColor,t->PneuDiametro,t->PneuLargura,t->PneuAltura);
	}
	printf("%s;%d,%s;%s,%s;%d,%d,%s;%d,%d,%d;\n",
		q->tail->numPedido,q->tail->Motorpotencia,q->tail->Motor_fuel,q->tail->ChassiColor,q->tail->ChassiModelo,
		q->tail->JanteDiametro,q->tail->JanteLargura,q->tail->JanteColor,q->tail->PneuDiametro,
		q->tail->PneuLargura,q->tail->PneuAltura);
}

void printPedido(Pedido *q)
{
	printf("%s = {%d,%s} ; {%s,%s} ; {%d,%d,%s} ; {%d,%d,%d}\n",
		q->numPedido,q->Motorpotencia,q->Motor_fuel,q->ChassiColor,q->ChassiModelo,
		q->JanteDiametro,q->JanteLargura,q->JanteColor,q->PneuDiametro,
		q->PneuLargura,q->PneuAltura);
}

int countQueuePedido(QueuePedidos *q)
{
	int count=0;
	Pedido *t = (Pedido*) malloc(sizeof(Pedido));
	if (t == NULL)
		printf(ERR_MEM);
	for (t = q->head ; t != NULL ; t = t -> next)
	{
		count++;
	}
	return count;
}
