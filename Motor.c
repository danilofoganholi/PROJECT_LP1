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
	//inicializa motor
	q -> head = NULL;
	q -> tail = NULL;
}

int removeMotor(QueueMotor *q, char *numSerial )
{
	Motor *t ;
	
	//compara para ver se é o primeiro elemento
	if (strncmp(q->head->numSerie,numSerial,20)==0)
	{
		//remove o primeiro elemento da lista

		Motor *aux = q->head;//salva o primeiro elemento

		q->head=q->head->next;//aponta o head da lista para o segundo elemento

		free(aux);//libera memoria

		return 1;
	}

	//percorre a queue inteira
	for (t = q->head ; t->next != NULL ; t = t -> next)
	{
		if (strncmp(t->next->numSerie,numSerial,20)==0)//compara os numeros de series
		{
			//remove o t->next avaliado
			
			Motor *aux = t->next;//salva o t->next

			t->next = t->next->next;//faz o anterior apontar para o seguinte do t->next

			free(aux);//libera a memoria 

			return 1;
		}
	}
	return 0;
}

void queueInsertMotor (QueueMotor *q, Motor motor )
{
	//aloca memoria para motor
	Motor *tmp = (Motor *) malloc(sizeof(Motor));
	if (tmp == NULL)
		printf(ERR_MEM);

	*tmp=motor;
	
	tmp->next = NULL;//colocar a null

	if (q->head == NULL)//se for o primeiro elemento da lista
		q->head = tmp;//coloca na primeira posicao
	else
		q->tail->next=tmp;//caso contrario 

	//em ambos os casos arrumar o tail pois a insercao eh no final
	q->tail=tmp;
}

void printQueueMotor(QueueMotor *q)
{
	if (q->head == NULL)//validade se fila não é vazia
		return;
	
	Motor *t;
	
	//percorre fila printando todos os nodes, um em cada linha
	for (t = q->head ; t!= NULL ; t = t -> next)
	{
		printf("Motor,%s,%d,%s\n",t->numSerie,t->potencia,t->type_of_fuel);
	}
}

void escreveMotoresInventario(QueueMotor *q, char* file)
{
	Motor *t;

	FILE * filepointer= fopen(file, "a");//abre o arquivo

	//percorre a fila escrevendo cada node em uma linha do ficheiro
	for (t = q->head ; t!= NULL ; t = t -> next)
	{
		fprintf(filepointer,"Motor,%s,%d,%s\n",t->numSerie,t->potencia,t->type_of_fuel);	
	}

	fclose(filepointer);//fecha ficheiro
}

int countQueueMotor(QueueMotor *q)
{
	int count=0;//variavel para contar elementos da queue
	Motor *t;

	//percorro todos os elementos
	for (t = q->head ; t != NULL ; t = t -> next,count++);
	
	return count;
}

void bubbleSortMotor(QueueMotor *q)
{
	//inicializa variavel que contem o tamanho da fila 
	int size = countQueueMotor(q); 

	//declara variaveis auxiliares
	int c, d;

	Motor *t;
	Motor *z;

	//vai percorrer o array ate ter ordenado toda a lista
	for (c = 0 ; c<size-1; c++) 
	{
		//compara o numSerie dos odis primeiros elementos
		if (strncmp(q->head->numSerie,q->head->next->numSerie,4)>0)
		{
			//troca eles de lugar

			z = q->head->next;//salva o segundo elemento

			q->head->next=z->next;//faz o primeiro elemento aponta para o tercerio

			z->next=q->head;//faz o segundo apontar para o primeiro elemento

			q->head=z;//faz o segundo elemento ser o topo da lista
		}
		
		for (t= q->head, d=0 ;d<(size-c-2) && t->next->next!=NULL; d++, t=t->next) 
		{
			//compara o numSerie dos odis primeiros elementos
			if (strncmp(t->next->numSerie,t->next->next->numSerie,4)>0) 
			{
				//troca eles de lugar

				z = t->next;//salva o segundo elemento

				t->next=z->next;//faz o primeiro elemento aponta para o tercerio

				z->next=t->next->next;//faz o segundo apontar para o primeiro elemento

				t->next->next=z;//faz o anterior ao primeiro elemento apontar para o segundo 
			}
		}
	}

	//percorrer a lista para arrumar o tail
	for (t = q->head ; t != NULL ; t = t -> next)
	{
		if (t->next==NULL)
			q->tail=t;
	}
}

Motor pegaMotorLista(QueueMotor *listaMotores, int potencia,char *fuel)
{
	Motor *tmp;

	//valida quais dados devem ser procurados na fila
	if (potencia==0 && strcmp(fuel,"")==0)//nenhum dado especificado
	{
		return *listaMotores->head;
	}else if (potencia!=0 && strcmp(fuel,"")==0)//potencia especificada
	{
		for (tmp = listaMotores->head ; tmp != NULL ; tmp = tmp -> next)
		{
			if (potencia==tmp->potencia)
			{
				return *tmp;
			}
		}
	}else if (potencia==0 && strcmp(fuel,"")!=0)//combustivel especificado
	{
		for (tmp = listaMotores->head ; tmp != NULL ; tmp = tmp -> next)
		{
			if (strcmp(fuel,tmp->type_of_fuel)==0)
			{
				return *tmp;
			}
		}
	}else // todos especificados
	{
		for (tmp = listaMotores->head ; tmp != NULL ; tmp = tmp -> next)
		{
			if (potencia==tmp->potencia && strcmp(fuel,tmp->type_of_fuel)==0)
			{
				return *tmp;
			}
		}
	}

	return *tmp;
}