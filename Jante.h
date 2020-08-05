#ifndef __jante_h__
#define __jante_h__

//declarando estruturas
typedef struct Jante
{
	char numSerie[21];
	int diametro;
	int largura;
	char color[10];
	struct Jante *next;
}Jante;

typedef struct 
{
	Jante * head, *tail;
}QueueJante;

//declarando funcoes para jante
void queueInitJante(QueueJante *);
void queueInsertJante (QueueJante *, Jante);
void printQueueJante(QueueJante *);
void escreveJanteInventario(QueueJante*,char*);
void bubbleSortJante(QueueJante *);
int countQueueJante(QueueJante *);
Jante pegaJanteLista(QueueJante*,int,int,char*);
int removeJante (QueueJante *,char*);


#endif