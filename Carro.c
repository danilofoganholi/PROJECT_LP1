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

int isEmptyCarro(QueueCarro *q)
{
	return (q->head==NULL);
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

void printQueueCarro(QueueCarro *q)
{
	Carro *t = (Carro*) malloc(sizeof(Carro));
	if (t == NULL)
		printf(ERR_MEM);
	for (t = q->head ; t != NULL ; t = t -> next)
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

void printQueueCarroEspecial(QueueCarro *q)
{
	Carro *t = (Carro*) malloc(sizeof(Carro));
	if (t == NULL)
		printf(ERR_MEM);
	for (t = q->head ; t != NULL ; t = t -> next)
	{
		printf("%s;",t->numPedido);
		if (t->motor->potencia!=0)
		{
			printf("%d",t->motor->potencia);
		}
		printf(",%s;%s,%s;",t->motor->type_of_fuel,t->chassi->color,t->chassi->modelo);
		if (t->jante->diametro!=0)
		{
			printf("%d",t->jante->diametro);
		}
		printf(",");
		if (t->jante->largura!=0)
		{
			printf("%d",t->jante->largura);
		}
		printf(",%s;",t->jante->color);
		if (t->pneu->diametro!=0)
		{
			printf("%d",t->pneu->diametro);
		}
		printf(",");
		if (t->pneu->largura!=0)
		{
			printf("%d",t->pneu->largura);
		}
		printf(",");
		if (t->pneu->altura!=0)
		{
			printf("%d",t->pneu->altura);
		}
		printf(";\n");
	}
}

int countQueueCarro(QueueCarro *q)
{
	int count=0;
	Carro *t = (Carro*) malloc(sizeof(Carro));
	if (t == NULL)
		printf(ERR_MEM);
	for (t = q->head ; t != NULL ; t = t -> next)
	{
		count++;
	}
	return count;
}

void escreveCarroProduzidos(QueueCarro *q, char* file)
{
	char* localFile = strcat(strtok(file,"_"),"_out.produzidos");

	Carro *t = (Carro*) malloc(sizeof(Carro));
	if (t == NULL)
		printf(ERR_MEM);

	FILE * filepointer= fopen(localFile, "a");

	for (t = q->head ; t->next != NULL ; t = t -> next)
	{
		fprintf(filepointer,"%s;%s,%d,%s;%s,%s,%s;%s,%d,%d,%s;%s,%d,%d,%d\n",t->numPedido,t->motor->numSerie,t->motor->potencia,
		t->motor->type_of_fuel,t->chassi->numSerie,t->chassi->color,t->chassi->modelo,t->jante->numSerie,t->jante->diametro,
		t->jante->largura,t->jante->color,t->pneu->numSerie,t->pneu->diametro,t->pneu->largura,t->pneu->altura);
	}

    fprintf(filepointer,"%s;%s,%d,%s;%s,%s,%s;%s,%d,%d,%s;%s,%d,%d,%d",q->tail->numPedido,q->tail->motor->numSerie,q->tail->motor->potencia,
		q->tail->motor->type_of_fuel,q->tail->chassi->numSerie,q->tail->chassi->color,q->tail->chassi->modelo,q->tail->jante->numSerie,q->tail->jante->diametro,
		q->tail->jante->largura,q->tail->jante->color,q->tail->pneu->numSerie,q->tail->pneu->diametro,q->tail->pneu->largura,q->tail->pneu->altura);

	fclose(filepointer);
}

void escreveCarroNaoProduzidos(QueueCarro *q, char* file)
{
	char* localFile = strcat(strtok(file,"_"),"_out.naoproduzidos");

	Carro *t = (Carro*) malloc(sizeof(Carro));
	if (t == NULL)
		printf(ERR_MEM);

	FILE * filepointer= fopen(localFile, "a");

	for (t = q->head ; t->next != NULL ; t = t -> next)
	{
		fprintf(filepointer,"%s;",t->numPedido);
		if (t->motor->potencia!=0)
		{
			fprintf(filepointer,"%d",t->motor->potencia);
		}
		fprintf(filepointer,",%s;%s,%s;",t->motor->type_of_fuel,t->chassi->color,t->chassi->modelo);
		if (t->jante->diametro!=0)
		{
			fprintf(filepointer,"%d",t->jante->diametro);
		}
		fprintf(filepointer,",");
		if (t->jante->largura!=0)
		{
			fprintf(filepointer,"%d",t->jante->largura);
		}
		fprintf(filepointer,",%s;",t->jante->color);
		if (t->pneu->diametro!=0)
		{
			fprintf(filepointer,"%d",t->pneu->diametro);
		}
		fprintf(filepointer,",");
		if (t->pneu->largura!=0)
		{
			fprintf(filepointer,"%d",t->pneu->largura);
		}
		fprintf(filepointer,",");
		if (t->pneu->altura!=0)
		{
			fprintf(filepointer,"%d",t->pneu->altura);
		}
		fprintf(filepointer,";\n");
	}

	fprintf(filepointer,"%s;",q->tail->numPedido);
		if (q->tail->motor->potencia!=0)
		{
			fprintf(filepointer,"%d",q->tail->motor->potencia);
		}
		fprintf(filepointer,",%s;%s,%s;",q->tail->motor->type_of_fuel,q->tail->chassi->color,q->tail->chassi->modelo);
		if (q->tail->jante->diametro!=0)
		{
			fprintf(filepointer,"%d",q->tail->jante->diametro);
		}
		fprintf(filepointer,",");
		if (q->tail->jante->largura!=0)
		{
			fprintf(filepointer,"%d",q->tail->jante->largura);
		}
		fprintf(filepointer,",%s;",q->tail->jante->color);
		if (q->tail->pneu->diametro!=0)
		{
			fprintf(filepointer,"%d",q->tail->pneu->diametro);
		}
		fprintf(filepointer,",");
		if (q->tail->pneu->largura!=0)
		{
			fprintf(filepointer,"%d",q->tail->pneu->largura);
		}
		fprintf(filepointer,",");
		if (q->tail->pneu->altura!=0)
		{
			fprintf(filepointer,"%d",q->tail->pneu->altura);
		}
		fprintf(filepointer,";");

	fclose(filepointer);

	free(localFile);
}