#ifndef __pedidos_h__
#define __pedidos_h__

#include "Motor.h"
#include "Chassi.h"
#include "Jante.h"
#include "Pneu.h"

//declarando estruturas
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

//declarando funcoes para pedidos
void queueInitPedido(QueuePedidos *);
void queueInsertPedido (QueuePedidos *, Pedido);
void escrevePedidoNaoProduzidos(QueuePedidos*,char*);
void printQueuePedido(QueuePedidos *);

#endif