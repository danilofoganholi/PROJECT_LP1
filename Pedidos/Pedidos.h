#ifndef __pedidos_h__
#define __pedidos_h__

#include "../Motor/Motor.h"
#include "../Chassi/Chassi.h"
#include "../Jante/Jante.h"
#include "../Pneu/Pneu.h"

typedef struct Pedido
{
	char numPedido[21];

	int Motorpotencia;
	char Motor_fuel[9];

	char ChassiColor[10];
	char ChassiModelo[128];

	int JanteDiametro;
	int JanteLargura;
	char JanteColor[10];

	int PneuDiametro;
	int PneuLargura;
	int PneuAltura;

	struct Pedido *next;
	
	
}Pedido;

typedef struct 
{
	Pedido * head, *tail;
}QueuePedidos;

void queueInitPedido(QueuePedidos *);
void queueInsertPedido (QueuePedidos *, Pedido);
void queueRemovePedido(QueuePedidos*,Pedido);
void printQueuePedido(QueuePedidos *);
void printQueuePedido(QueuePedidos *);

#endif