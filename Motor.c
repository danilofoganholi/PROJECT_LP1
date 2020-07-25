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
#include "Motor.h"

void queueInitMotor(QueueMotor *q)//inicializa a lista
{
	q -> head = NULL;
	q -> tail = NULL;
}

void queueInsertMotor (QueueMotor *q, Motor motor )
{
	Motor *tmp = (Motor *) malloc(sizeof(Motor));
	if (tmp == NULL)
		printf(ERR_MEM);

	*tmp=motor;
	
	tmp->next = NULL;
	if (q->head == NULL)
		q->head = tmp;
	else
		q->tail->next=tmp;
	q->tail=tmp;
}

int queueRemoveMotor (QueueMotor *q, Motor motor )
{
	Motor *t = (Motor*) malloc(sizeof(Motor));
	if (t == NULL)
	{
		printf(ERR_MEM);
		free(t);
		return 0;
	}
	
	if (strncmp(q->head->numSerie,motor.numSerie,20)==0)
	{
		Motor *aux = q->head;
		q->head=q->head->next;
		free(aux);
		free(t);
		return 1;
	}

	for (t = q->head ; t->next != NULL ; t = t -> next)
	{
		if (strncmp(t->next->numSerie,motor.numSerie,20)==0)
		{
			Motor *aux = t->next;
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

void printQueueMotor(QueueMotor *q)
{
	if (q->head == NULL)
		return;
	
	Motor *t = (Motor*) malloc(sizeof(Motor));
	if (t == NULL)
		printf(ERR_MEM);
	for (t = q->head ; t->next != NULL ; t = t -> next)
	{
		printf("Motor,%s,%d,%s\n",t->numSerie,t->potencia,t->type_of_fuel);
	}
	printf("Motor,%s,%d,%s\n",q->tail->numSerie,q->tail->potencia,q->tail->type_of_fuel);
	t=NULL;
	free(t);
}

void printMotor(Motor *motor)
{
	printf("%s,%d,%s",motor->numSerie,motor->potencia,motor->type_of_fuel);
}

void escreveMotoresInventario(QueueMotor *q, char* file)
{
	Motor *t = (Motor*) malloc(sizeof(Motor));
	if (t == NULL)
		printf(ERR_MEM);

	FILE * filepointer= fopen(file, "a");

	for (t = q->head ; t->next != NULL ; t = t -> next)
	{
		fprintf(filepointer,"Motor,%s,%d,%s\n",t->numSerie,t->potencia,t->type_of_fuel);	
	}

	fprintf(filepointer,"Motor,%s,%d,%s\n",q->tail->numSerie,q->tail->potencia,q->tail->type_of_fuel);

	fclose(filepointer);
	t=NULL;free(t);
}


