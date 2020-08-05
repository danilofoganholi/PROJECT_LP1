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

void queueInitJante(QueueJante *q)
{
	//inicializa jante
	q -> head = NULL;
	q -> tail = NULL;
}

int removeJante (QueueJante *q, char *numSerial )
{
	Jante *t;

	//compara para ver se é o primeiro elemento
	if (strncmp(q->head->numSerie,numSerial,20)==0)
	{
		//remove o primeiro elemento da lista

		Jante *aux = q->head;//salva o primeiro elemento

		q->head=aux->next;//aponta o head da lista para o segundo elemento

		free(aux);//libera memoria

		return 1;
	}

	//percorre a queue inteira
	for (t = q->head ; t->next != NULL ; t = t -> next)
	{
		if (strncmp(t->next->numSerie,numSerial,20)==0)//compara os numeros de series
		{
			//remove o t->next avaliado

			Jante *aux = t->next;//salva o t->next

			t->next = t->next->next;//faz o anterior apontar para o seguinte do t->next

			free(aux);//libera a memoria 

			return 1;
		}
	}
	return 0;
}

void queueInsertJante (QueueJante *q, Jante jante )
{
	//aloca memoria para jante
	Jante *tmp = (Jante *) malloc(sizeof(Jante));
	if (tmp == NULL)
	{
		printf(ERR_MEM);
		return;
	}

	*tmp=jante;
	
	tmp->next = NULL;//colocar a null

	if (q->head == NULL)//se for o primeiro elemento da lista
		q->head = tmp;//coloca na primeira posicao
	else
		q->tail->next=tmp;//caso contrario 

	//em ambos os casos arrumar o tail pois a insercao eh no final
	q->tail=tmp;
}

void printQueueJante(QueueJante *q)
{
	if (q->head == NULL)//validade se fila não é vazia
		return;

	Jante *t ;

	//percorre fila printando todos os nodes, um em cada linha
	for (t = q->head ; t != NULL ; t = t -> next)
	{
		printf("Jantes,%s,%d,%d,%s\n",t->numSerie,t->diametro,t->largura,t->color);
	}
}

void escreveJanteInventario(QueueJante *q, char* file)
{
	Jante *t;

	FILE * filepointer= fopen(file, "a");//abre o arquivo

	//percorre a fila escrevendo cada node em uma linha do ficheiro
	for (t = q->head ; t != NULL ; t = t -> next)
	{
		fprintf(filepointer,"Jantes,%s,%d,%d,%s\n",t->numSerie,t->diametro,t->largura,t->color);	
	}
	fclose(filepointer);//fecha ficheiro
}

int countQueueJante(QueueJante *q)
{
	int count=0;//variavel para contar elementos da queue
	Jante *t;

	//percorro todos os elementos
	for (t = q->head ; t != NULL ; t = t -> next,count++);
	
	return count;
}

void bubbleSortJante(QueueJante *q)
{
	//inicializa variavel que contem o tamanho da fila 
	int size = countQueueJante(q); 

	//declara variaveis auxiliares
	int c, d;

	Jante *t;
	Jante *z;

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

Jante pegaJanteLista(QueueJante *listaJante, int diametro,int largura,char *color)
{
	Jante *tmp ;

	//valida quais dados devem ser procurados na fila
	if (diametro==0 && largura==0 && strcmp(color,"")==0)//nenhum dado especificado
	{
		return *listaJante->head;
	}else if (diametro==0 && largura==0 && strcmp(color,"")!=0)//cor especificada
	{
		for (tmp = listaJante->head ; tmp != NULL ; tmp = tmp -> next)
		{
			if (strcmp(color,tmp->color)==0)
			{
				return *tmp;
			}
		}
	}else if (diametro==0 && largura!=0 && strcmp(color,"")==0)//largura especificada
	{
		for (tmp = listaJante->head ; tmp != NULL ; tmp = tmp -> next)
		{
			if (largura==tmp->largura)
			{
				return *tmp;
			}
		}
	}else if (diametro==0 && largura!=0 && strcmp(color,"")!=0)//largura e cor especificada
	{
		for (tmp = listaJante->head ; tmp != NULL ; tmp = tmp -> next)
		{
			if (largura==tmp->largura && strcmp(color,tmp->color)==0)
			{
				return *tmp;
			}
		}
	}else if (diametro!=0 && largura==0 && strcmp(color,"")==0)//diametro especificada
	{
		for (tmp = listaJante->head ; tmp != NULL ; tmp = tmp -> next)
		{
			if (diametro==tmp->diametro)
			{
				return *tmp;
			}
		}
	}else if (diametro!=0 && largura==0 && strcmp(color,"")!=0)//diametro e cor especificada
	{
		for (tmp = listaJante->head ; tmp != NULL ; tmp = tmp -> next)
		{
			if (diametro==tmp->diametro && strcmp(color,tmp->color)==0)
			{
				return *tmp;
			}
		}
	}else if (diametro!=0 && largura!=0 && strcmp(color,"")==0)//diametro e largular especificada
	{
		for (tmp = listaJante->head ; tmp != NULL ; tmp = tmp -> next)
		{
			if (diametro==tmp->diametro && largura==tmp->largura)
			{
				return *tmp;
			}
		}
	}else //todos especificados
	{
		for (tmp = listaJante->head ; tmp != NULL ; tmp = tmp -> next)
		{
			if (diametro==tmp->diametro && largura==tmp->largura && strcmp(color,tmp->color)==0)
			{
				return *tmp;
			}
		}
	}

	return *tmp;
}
