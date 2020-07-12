#ifndef __producao_h__
#define __producao_h__

#include "./Motor/Motor.h"
#include "./Chassi/Chassi.h"
#include "./Jante/Jante.h"
#include "./Pneu/Pneu.h"
#include "./Carro/Carro.h"
#include "./Pedidos/Pedidos.h"

int possuiPecaMotor(QueueMotor*,Pedido,Carro*);
int possuiPecaChassi(QueueChassi*,Pedido,Carro*);
int possuiPecaJantes(QueueJante*,Pedido,Carro*);
int possuiPecaPneus(QueuePneu*,Pedido,Carro*);
void iniciarProducao(QueueMotor*,QueueChassi*,QueueJante*,QueuePneu*,QueueCarro*,QueueCarro*, QueuePedidos);

#endif