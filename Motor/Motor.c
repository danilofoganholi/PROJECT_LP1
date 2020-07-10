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

void queueRemoveMotor (QueueMotor *q, Motor motor )
{
	Motor *t = (Motor*) malloc(sizeof(Motor));
	if (t == NULL)
		printf(ERR_MEM);
	for (t = q->head ; t->next != NULL ; t = t -> next)
	{
		if (strncmp(t->next->numSerie,motor.numSerie,20)==0)
		{
			Motor *aux = t->next;
			t->next = t->next->next;
			free(aux);
		}
	}
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
		printf("Motor,%s,%d,%s",t->numSerie,t->potencia,t->type_of_fuel);
	}
	printf("Motor,%s,%d,%s",q->tail->numSerie,q->tail->potencia,q->tail->type_of_fuel);
}

void printMotor(Motor *motor)
{
	printf("%s,%d,%s",motor->numSerie,motor->potencia,motor->type_of_fuel);
}
