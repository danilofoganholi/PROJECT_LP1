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
#include "Jante.h"

void queueInitJante(QueueJante *q)//inicializa a lista
{
	q -> head = NULL;
	q -> tail = NULL;
}

void queueInsertJante (QueueJante *q, Jante jante )
{
	Jante *tmp = (Jante *) malloc(sizeof(Jante));
	if (tmp == NULL){
		printf(ERR_MEM);
		return;
	}

	*tmp=jante;
	
	tmp->next = NULL;
	if (q->head == NULL)
		q->head = tmp;
	else
		q->tail->next=tmp;
	q->tail=tmp;
}

void queueRemoveJante (QueueJante *q, Jante jante )
{
	Jante *t = (Jante*) malloc(sizeof(Jante));
	if (t == NULL){
		printf(ERR_MEM);
		return;
	}
	for (t = q->head ; t->next != NULL ; t = t -> next)
	{
		if (strncmp(t->next->numSerie,jante.numSerie,20)==0)
		{
			Jante *aux = t->next;
			t->next = t->next->next;
			free(aux);
		}
	}
}

void printQueueJante(QueueJante *q)
{
	if (q->head == NULL)
		return;
	Jante *t = (Jante*) malloc(sizeof(Jante));
	if (t == NULL){
		printf(ERR_MEM);
		return;
	}
		
	for (t = q->head ; t->next != NULL ; t = t -> next)
	{
		printf("Jantes,%s,%d,%d,%s\n",t->numSerie,t->diametro,t->largura,t->color);
	}
	printf("Jantes,%s,%d,%d,%s\n",q->tail->numSerie,q->tail->diametro,q->tail->largura,q->tail->color);
}

void printJante(Jante *jante)
{
	printf("%s,%d,%d,%s",jante->numSerie,jante->diametro,jante->largura,jante->color);
}
