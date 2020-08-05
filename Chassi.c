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
	//inicializa chassi
	q -> head = NULL;
	q -> tail = NULL;
}

int removeChassi (QueueChassi *q, char *numSerie )
{
	Chassi *t;
		
	//compara para ver se é o primeiro elemento
	if (strncmp(q->head->numSerie,numSerie,20)==0)
	{
		//remove o primeiro elemento da lista

		Chassi *aux = q->head;//salva o primeiro elemento

		q->head=q->head->next;//aponta o head da lista para o segundo elemento

		free(aux);//libera memoria

		return 1;
	}

	//percorre a queue inteira
	for (t = q->head ; t->next!= NULL ; t = t -> next)
	{
		if (strncmp(t->next->numSerie,numSerie,20)==0)//compara os numeros de series
		{
			//remove o t->next avaliado

			Chassi *aux = t->next;//salva o t->next

			t->next = t->next->next;//faz o anterior apontar para o seguinte do t->next

			free(aux);//libera a memoria 

			return 1;
		}
	}
	return 0;
}

void queueInsertChassi (QueueChassi *q, Chassi chassi )
{
	//aloca memoria para chassi
	Chassi *tmp = (Chassi *) malloc(sizeof(Chassi));
	if (tmp == NULL)
		printf(ERR_MEM);

	*tmp=chassi;
	
	tmp->next = NULL;//colocar a null

	if (q->head == NULL)//se for o primeiro elemento da lista
		q->head = tmp;//coloca na primeira posicao
	else
		q->tail->next=tmp;//caso contrario 

	//em ambos os casos arrumar o tail pois a insercao eh no final
	q->tail=tmp;
}

void printQueueChassi(QueueChassi *q)
{
	if (q->head == NULL)//validade se fila não é vazia
		return;

	Chassi *t;

	//percorre fila printando todos os nodes, um em cada linha
	for (t = q->head ; t!= NULL ; t = t -> next)
	{
		printf("Chassis,%s,%s,%s\n",t->numSerie,t->color,t->modelo);
	}
}

void escreveChassiInventario(QueueChassi *q, char* file)
{
	Chassi *t;

	FILE * filepointer= fopen(file, "a");//abre o arquivo

	//percorre a fila escrevendo cada node em uma linha do ficheiro
	for (t = q->head ; t!= NULL ; t = t -> next)
	{
		fprintf(filepointer,"Chassis,%s,%s,%s\n",t->numSerie,t->color,t->modelo);	
	}

	fclose(filepointer);//fecha ficheiro
}

int countQueueChassi(QueueChassi *q)
{
	int count=0;//variavel para contar elementos da queue

	Chassi *t;

	//percorro todos os elementos
	for (t = q->head ; t != NULL ; t = t -> next,count++);

	return count;
}

void bubbleSortChassi(QueueChassi *q)
{
	//inicializa variavel que contem o tamanho da fila 
	int size = countQueueChassi(q); 

	//declara variaveis auxiliares
	int c, d;

	Chassi *t;
	Chassi *z;

	//vai percorrer o array ate ter ordenado toda a lista
	for (c = 0 ; c<size-1; c++) 
	{
		//compara o numSerie dos odis primeiros elementos
		if (strcmp(q->head->numSerie,q->head->next->numSerie)>0)
		{
			//troca eles de lugar

			z = q->head->next;//salva o segundo elemento

			q->head->next=z->next;//faz o primeiro elemento aponta para o tercerio

			z->next=q->head;//faz o segundo apontar para o primeiro elemento

			q->head=z;//faz o segundo elemento ser o topo da lista
		}
		
		//percorre a lista até aonde ainda não esta ordenado
		for (t= q->head, d=0 ;d<(size-c-2) && t->next->next!=NULL; d++, t=t->next) 
		{
			//compara o numSerie dos odis primeiros elementos
			if (strcmp(t->next->numSerie,t->next->next->numSerie)>0) 
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
		{
			q->tail=t;
		}
	}
}

Chassi pegaChassiLista(QueueChassi *listaChassi, char *color,char *modelo)
{
	Chassi *tmp ;

	//valida quais dados devem ser procurados na fila
	if (strcmp(color,"")==0 && strcmp(modelo,"")==0)//nenhum dado especificado
	{
		return *listaChassi->head;//pegar o primeiro

	}else if (strcmp(color,"")==0 && strcmp(modelo,"")!=0)//apenas modelo especificado
	{
		//percorre a lista a procura do modelo especificado
		for (tmp = listaChassi->head ; tmp != NULL ; tmp = tmp -> next)
		{
			if (strcmp(modelo,tmp->modelo)==0)
			{
				return *tmp;//retorna chassi dentro das especificacoes
			}
		}
	}else if (strcmp(color,"")!=0 && strcmp(modelo,"")==0)//apenas cor especificado
	{
		//percorre a lista a procura da cor especificada
		for (tmp = listaChassi->head ; tmp != NULL ; tmp = tmp -> next)
		{
			if (strcmp(color,tmp->color)==0)
			{
				return *tmp;//retorna chassi dentro das especificacoes
			}
		}
	}else//cor e modelo especificados
	{
		//percorre a lista a procura do modelo especificado
		for (tmp = listaChassi->head ; tmp != NULL ; tmp = tmp -> next)
		{
			if (strcmp(color,tmp->color)==0 && strcmp(modelo,tmp->modelo)==0)
			{
				return *tmp;//retorna chassi dentro das especificacoes
			}
		}
	}

	return *tmp;
}
