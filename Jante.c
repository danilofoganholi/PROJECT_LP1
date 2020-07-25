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

int queueRemoveJante (QueueJante *q, Jante jante )
{
	Jante *t = (Jante*) malloc(sizeof(Jante));
	if (t == NULL)
	{
		printf(ERR_MEM);
		free(t);
		return 0;
	}

	if (strncmp(q->head->numSerie,jante.numSerie,20)==0)
	{
		Jante *aux = q->head;
		q->head=aux->next;
		free(aux);
		free(t);
		return 1;
	}

	for (t = q->head ; t->next != NULL ; t = t -> next)
	{
		if (strncmp(t->next->numSerie,jante.numSerie,20)==0)
		{
			Jante *aux = t->next;
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

void printQueueJante(QueueJante *q)
{
	if (q->head == NULL)
		return;
	Jante *t = (Jante*) malloc(sizeof(Jante));
	if (t == NULL){
		printf(ERR_MEM);
		free(t);
		return;
	}
		
	for (t = q->head ; t->next != NULL ; t = t -> next)
	{
		printf("Jantes,%s,%d,%d,%s\n",t->numSerie,t->diametro,t->largura,t->color);
	}
	printf("Jantes,%s,%d,%d,%s\n",q->tail->numSerie,q->tail->diametro,q->tail->largura,q->tail->color);
	t=NULL;
	free(t);
}

void printJante(Jante *jante)
{
	printf("%s,%d,%d,%s",jante->numSerie,jante->diametro,jante->largura,jante->color);
}

void escreveJanteInventario(QueueJante *q, char* file)
{
	Jante *t = (Jante*) malloc(sizeof(Jante));
	if (t == NULL)
		printf(ERR_MEM);

	FILE * filepointer= fopen(file, "a");

	for (t = q->head ; t->next != NULL ; t = t -> next)
	{
		fprintf(filepointer,"Jantes,%s,%d,%d,%s\n",t->numSerie,t->diametro,t->largura,t->color);	
	}

	fprintf(filepointer,"Jantes,%s,%d,%d,%s\n",q->tail->numSerie,q->tail->diametro,q->tail->largura,q->tail->color);

	fclose(filepointer);
	t=NULL;
	free(t);
}
