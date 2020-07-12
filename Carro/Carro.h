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

void printCarro(Carro *);
void queueInitCarro(QueueCarro *);
int isEmptyCarro(QueueCarro *);
void queueInsertCarro (QueueCarro *, Carro);
void queueRemoveCarro(QueueCarro*,Carro);
void printQueueCarro(QueueCarro *);
void printQueueCarro(QueueCarro *);
void printQueueCarroEspecial(QueueCarro *);
int countQueueCarro(QueueCarro *);
void escreveCarroProduzidos(QueueCarro*,char*);
void escreveCarroNaoProduzidos(QueueCarro*,char*);

#endif