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
#include "Carro.h"

void queueInitCarro(QueueCarro *q)
{
	q -> head = NULL;
	q -> tail = NULL;
}

void queueInsertCarro (QueueCarro *q, Carro carro )
{
	Carro *tmp = (Carro *) malloc(sizeof(Carro));
	if (tmp == NULL)
		printf(ERR_MEM);

	*tmp=carro;
	
	tmp->next = NULL;
	if (q->head == NULL)
		q->head = tmp;
	else
		q->tail->next=tmp;
	q->tail=tmp;
}

void queueRemoveCarro (QueueCarro *q, Carro carro )
{
	Carro *t = (Carro*) malloc(sizeof(Carro));
	if (t == NULL)
		printf(ERR_MEM);
	for (t = q->head ; t->next != NULL ; t = t -> next)
	{
		if (strncmp(t->next->numPedido,carro.numPedido,20)==0)
		{
			Carro *aux = t->next;
			t->next = t->next->next;
			free(aux);
		}
	}
}

void printQueueCarro(QueueCarro *q)
{
	Carro *t = (Carro*) malloc(sizeof(Carro));
	if (t == NULL)
		printf(ERR_MEM);
	for (t = q->head ; t->next != NULL ; t = t -> next)
	{
		printf("%s;",t->numPedido);
		printMotor(t->motor);
		printf(";");
		printChassi(t->chassi);
		printf(";");
		printJante(t->jante);
		printf(";");
		printPneu(t->pneu);
		printf("\n");
	}
}
