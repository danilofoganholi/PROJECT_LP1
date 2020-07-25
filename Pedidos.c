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