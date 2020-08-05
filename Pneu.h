#ifndef __pneu_h__
#define __pneu_h__

//declarando estruturas
typedef struct Pneu
{
	char numSerie[21];
	int diametro;
	int largura;
	int altura;
	struct Pneu *next;
}Pneu;

typedef struct 
{
	Pneu * head, *tail;
}QueuePneu;

//declarando funcoes para pneu
void queueInitPneu(QueuePneu *);
void queueInsertPneu (QueuePneu *, Pneu);
void printQueuePneu(QueuePneu *);
void escrevePneuInventario(QueuePneu*,char*);
void bubbleSortPneu(QueuePneu *);
int countQueuePneu(QueuePneu *);
Pneu pegaPneuLista(QueuePneu*,int,int,int);
int removePneu (QueuePneu *,char*);

#endif