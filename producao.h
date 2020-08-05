#ifndef __producao_h__
#define __producao_h__

#include "Motor.h"
#include "Chassi.h"
#include "Jante.h"
#include "Pneu.h"
#include "Carro.h"
#include "Pedidos.h"

//declarando funcoes para fazer a producao dos carros
int possuiPecaMotor(QueueMotor*,Pedido);
int possuiPecaChassi(QueueChassi*,Pedido);
int possuiPecaJantes(QueueJante*,Pedido);
int possuiPecaPneus(QueuePneu*,Pedido);
void iniciarProducao(QueueMotor*,QueueChassi*,QueueJante*,QueuePneu*,QueueCarro*,QueuePedidos*, QueuePedidos);
void listaCarroNaoProduzido(QueuePedidos*,Pedido);
void listaCarroProduzido(QueueCarro*,Pedido*,QueueMotor*,QueueChassi*,QueueJante*,QueuePneu*);

#endif