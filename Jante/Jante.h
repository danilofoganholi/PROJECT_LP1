#ifndef __jante_h__
#define __jante_h__

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

void queueInitJante(QueueJante *);
void queueInsertJante (QueueJante *, Jante);
void queueRemoveJante(QueueJante*,Jante);
void printQueueJante(QueueJante *);
void printJante(Jante *);

#endif