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
#include "Pneu.h"

void queueInitPneu(QueuePneu *q)
{
	q -> head = NULL;
	q -> tail = NULL;
}

void queueInsertPneu (QueuePneu *q, Pneu pneu )
{
	Pneu *tmp = (Pneu *) malloc(sizeof(Pneu));
	if (tmp == NULL){
		printf(ERR_MEM);
		return;
	}

	*tmp=pneu;
	
	tmp->next = NULL;
	if (q->head == NULL)
		q->head = tmp;
	else
		q->tail->next=tmp;
	q->tail=tmp;
}

int queueRemovePneu (QueuePneu *q, Pneu pneu )
{
	Pneu *t = (Pneu*) malloc(sizeof(Pneu));
	if (t == NULL){
		printf(ERR_MEM);
		return 0;
	}

	if (strcmp(q->head->numSerie,pneu.numSerie)==0)
	{
		Pneu *aux = q->head;
		q->head=q->head->next;
		free(aux);
		return 1;
	}

	for (t = q->head ; t->next != NULL ; t = t -> next)
	{
		if (strncmp(t->next->numSerie,pneu.numSerie,20)==0)
		{
			Pneu *aux = t->next;
			t->next = t->next->next;
			free(aux);
			return 1;
		}
	}
	return 0;
}

void printQueuePneu(QueuePneu *q)
{
	if (q->head == NULL)
		return;
	Pneu *t = (Pneu*) malloc(sizeof(Pneu));
	if (t == NULL){
		printf(ERR_MEM);
		return;
	}
	for (t = q->head ; t->next != NULL ; t = t -> next){
		printf("Pneus,%s,%d,%d,%d\n",t->numSerie,t->diametro,t->largura,t->altura);
	}
	printf("Pneus,%s,%d,%d,%d\n",q->tail->numSerie,q->tail->diametro,q->tail->largura,q->tail->altura);
}

void printPneu(Pneu *pneu)
{
	printf("%s,%d,%d,%d",pneu->numSerie,pneu->diametro,pneu->largura,pneu->altura);
}

int countQueuePneu(QueuePneu *q)
{
	int count=0;
	Pneu *t = (Pneu*) malloc(sizeof(Pneu));
	if (t == NULL)
		printf(ERR_MEM);
	for (t = q->head ; t != NULL ; t = t -> next)
	{
		count++;
	}
	return count;
}

void escrevePneuInventario(QueuePneu *q, char* file)
{
	Pneu *t = (Pneu*) malloc(sizeof(Pneu));
	if (t == NULL)
		printf(ERR_MEM);

	FILE * filepointer= fopen(file, "a");

	for (t = q->head ; t->next != NULL ; t = t -> next)
	{
		fprintf(filepointer,"Pneus,%s,%d,%d,%d\n",t->numSerie,t->diametro,t->largura,t->altura);	
	}

	fprintf(filepointer,"Pneus,%s,%d,%d,%d",q->tail->numSerie,q->tail->diametro,q->tail->largura,q->tail->altura);

	fclose(filepointer);
}