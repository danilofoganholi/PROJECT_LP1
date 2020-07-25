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
	if (tmp == NULL)
		printf(ERR_MEM);

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
	if (t == NULL)
	{
		printf(ERR_MEM);
		free(t);
		return 0;
	}

	if (strncmp(q->head->numSerie,pneu.numSerie,20)==0)
	{
		Pneu *aux = q->head;
		q->head=q->head->next;
		free(aux);
		free(t);
		return 1;
	}

	for (t = q->head ; t->next != NULL ; t = t -> next)
	{
		if (strncmp(t->next->numSerie,pneu.numSerie,20)==0)
		{
			Pneu *aux = t->next;
			t->next = t->next->next;
			free(aux);
			t=NULL;
			free(t);
			return 1;
		}
	}
	t=NULL;
	free(t);
	return 0;
}

void printQueuePneu(QueuePneu *q)
{
	if (q->head == NULL)
		return;

	Pneu *t = (Pneu*) malloc(sizeof(Pneu));
	if (t == NULL){
		printf(ERR_MEM);
		free(t);
		return;
	}
	for (t = q->head ; t->next != NULL ; t = t -> next){
		printf("Pneus,%s,%d,%d,%d\n",t->numSerie,t->diametro,t->largura,t->altura);
	}
	printf("Pneus,%s,%d,%d,%d\n",q->tail->numSerie,q->tail->diametro,q->tail->largura,q->tail->altura);
	t=NULL;
	free(t);
}

void printPneu(Pneu *pneu)
{
	printf("%s,%d,%d,%d",pneu->numSerie,pneu->diametro,pneu->largura,pneu->altura);
}

void escrevePneuInventario(QueuePneu *q, char* file)
{
	Pneu *t = (Pneu*) malloc(sizeof(Pneu));
	if (t == NULL){
		printf(ERR_MEM);
		t=NULL;
		free(t);
		return;
	}

	FILE * filepointer= fopen(file, "a");

	for (t = q->head ; t->next != NULL ; t = t -> next)
	{
		fprintf(filepointer,"Pneus,%s,%d,%d,%d\n",t->numSerie,t->diametro,t->largura,t->altura);	
	}

	fprintf(filepointer,"Pneus,%s,%d,%d,%d",q->tail->numSerie,q->tail->diametro,q->tail->largura,q->tail->altura);

	fclose(filepointer);
	t=NULL;
	free(t);
}