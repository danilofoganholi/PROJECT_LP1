#ifndef __producao_h__
#define __producao_h__

#include "Motor.h"
#include "Chassi.h"
#include "Jante.h"
#include "Pneu.h"
#include "Carro.h"
#include "Pedidos.h"

int possuiPecaMotor(QueueMotor*,Pedido,Carro*);
int possuiPecaChassi(QueueChassi*,Pedido,Carro*);
int possuiPecaJantes(QueueJante*,Pedido,Carro*);
int possuiPecaPneus(QueuePneu*,Pedido,Carro*);
void iniciarProducao(QueueMotor*,QueueChassi*,QueueJante*,QueuePneu*,QueueCarro*,QueueCarro*, QueuePedidos);

#endif