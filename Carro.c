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
	//inicializa carro
	q -> head = NULL;
	q -> tail = NULL;
}

void queueInsertCarro (QueueCarro *q, Carro carro )
{
	//aloca memoria para carro
	Carro *tmp = (Carro *) malloc(sizeof(Carro));
	if (tmp == NULL)
	{
		printf(ERR_MEM);
		free(tmp);
		return;
	}

	*tmp=carro;
	
	tmp->next = NULL;//colocar a null

	if (q->head == NULL)//se for o primeiro elemento da lista
		q->head = tmp;//coloca na primeira posicao
	else
		q->tail->next=tmp;//caso contrario 
	
	//em ambos os casos arrumar o tail pois a insercao eh no final
	q->tail=tmp;
}

void escreveCarroProduzidos(QueueCarro *q, char* file)
{
	if (q->head==NULL)//verifica se a fila passada não é vazia
	{
		return;
	}
	
	char tmpFile[40];
	strcpy(tmpFile,file);//copia o nome do arquivo
	char* localFile = strcat(tmpFile,"_out.produzidos");//concatena com a extencao desejada
	
	Carro *t;

	FILE * filepointer= fopen(localFile, "a");//abre o arquivo

	//percorre a fila escrevendo cada node em uma linha do ficheiro
	for (t = q->head ; t!= NULL ; t = t -> next)
	{
		fprintf(filepointer,"%s;%s,%d,%s;%s,%s,%s;%s,%d,%d,%s;%s,%d,%d,%d\n",t->numPedido,t->motor->numSerie,t->motor->potencia,
		t->motor->type_of_fuel,t->chassi->numSerie,t->chassi->color,t->chassi->modelo,t->jante->numSerie,t->jante->diametro,
		t->jante->largura,t->jante->color,t->pneu->numSerie,t->pneu->diametro,t->pneu->largura,t->pneu->altura);
	}
	fclose(filepointer);//fecha ficheiro
}

void printQueueCarro(QueueCarro *q)
{
	if (q->head==NULL)//validade se fila não é vazia
	{
		return;
	}
	Carro *t;
		
	//percorre fila printando todos os nodes, um em cada linha
	for (t = q->head ; t != NULL ; t = t -> next)
	{
		printf("%s;%d,%s;%s,%s;%d,%d,%s;%d,%d,%d\n",t->numPedido,t->motor->potencia,
		t->motor->type_of_fuel,t->chassi->color,t->chassi->modelo,t->jante->diametro,
		t->jante->largura,t->jante->color,t->pneu->diametro,t->pneu->largura,t->pneu->altura);
	}
}