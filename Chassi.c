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
#include "Chassi.h"

void queueInitChassi(QueueChassi *q)//inicializa a lista
{
	q -> head = NULL;
	q -> tail = NULL;
}

void queueInsertChassi (QueueChassi *q, Chassi chassi )
{
	Chassi *tmp = (Chassi *) malloc(sizeof(Chassi));
	if (tmp == NULL)
		printf(ERR_MEM);

	*tmp=chassi;
	
	tmp->next = NULL;
	if (q->head == NULL)
		q->head = tmp;
	else
		q->tail->next=tmp;
	q->tail=tmp;
}

int queueRemoveChassi (QueueChassi *q, Chassi chassi )
{
	Chassi *t = (Chassi*) malloc(sizeof(Chassi));
	if (t == NULL)
	{
		printf(ERR_MEM);
		free(t);
		return 0;
	}
		
	if (strncmp(q->head->numSerie,chassi.numSerie,20)==0)
	{
		Chassi *aux = q->head;
		q->head=q->head->next;
		free(aux);
		free(t);
		return 1;
	}

	for (t = q->head ; t->next != NULL ; t = t -> next)
	{
		if (strncmp(t->next->numSerie,chassi.numSerie,20)==0)
		{
			Chassi *aux = t->next;
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

void printQueueChassi(QueueChassi *q)
{
	if (q->head == NULL)
		return;
	Chassi *t = (Chassi*) malloc(sizeof(Chassi));
	if (t == NULL)
		printf(ERR_MEM);
	for (t = q->head ; t->next != NULL ; t = t -> next)
	{
		printf("Chassis,%s,%s,%s\n",t->numSerie,t->color,t->modelo);
	}
	printf("Chassis,%s,%s,%s\n",q->tail->numSerie,q->tail->color,q->tail->modelo);
	t=NULL;
	free(t);
}

void printChassi(Chassi *chassi)
{
	printf("%s,%s,%s",chassi->numSerie,chassi->color,chassi->modelo);
}

void escreveChassiInventario(QueueChassi *q, char* file)
{
	Chassi *t = (Chassi*) malloc(sizeof(Chassi));
	if (t == NULL)
		printf(ERR_MEM);

	FILE * filepointer= fopen(file, "a");

	for (t = q->head ; t->next != NULL ; t = t -> next)
	{
		fprintf(filepointer,"Chassis,%s,%s,%s\n",t->numSerie,t->color,t->modelo);	
	}

	fprintf(filepointer,"Chassis,%s,%s,%s\n",q->tail->numSerie,q->tail->color,q->tail->modelo);

	fclose(filepointer);
	t=NULL;free(t);
}