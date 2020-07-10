#ifndef __pneu_h__
#define __pneu_h__

typedef struct Pneu
{
	char numSerie[20];
	int diametro;
	int largura;
	int altura;
	struct Pneu *next;
}Pneu;

typedef struct 
{
	Pneu * head, *tail;
}QueuePneu;

void queueInitPneu(QueuePneu *);
void queueInsertPneu (QueuePneu *, Pneu);
void queueRemovePneu(QueuePneu*,Pneu);
void printQueuePneu(QueuePneu *);
void printPneu(Pneu *);

#endif