#ifndef __carro_h__
#define __carro_h__

#include "../Motor/Motor.h"
#include "../Chassi/Chassi.h"
#include "../Jante/Jante.h"
#include "../Pneu/Pneu.h"

typedef struct Carro
{
	char numPedido[21];
	struct Motor *motor;
	struct Chassi *chassi;
	struct Jante *jante;
	struct Pneu *pneu;
	enum { PorAvaliar,Produzido,NaoPossivelProduzir}estado;
	struct Carro *next;
}Carro;

typedef struct 
{
	Carro * head, *tail;
}QueueCarro;

void queueInitCarro(QueueCarro *);
void queueInsertCarro (QueueCarro *, Carro);
void queueRemoveCarro(QueueCarro*,Carro);
void printQueueCarro(QueueCarro *);
void printQueueCarro(QueueCarro *);

#endif