#ifndef __carro_h__
#define __carro_h__

#include "Motor.h"
#include "Chassi.h"
#include "Jante.h"
#include "Pneu.h"

//declarando estruturas
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

//declarando funcoes para carro
void queueInitCarro(QueueCarro *);
void queueInsertCarro (QueueCarro *, Carro);
void printQueueCarro(QueueCarro *);
void escreveCarroProduzidos(QueueCarro*,char*);

#endif