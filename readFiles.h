#ifndef __readFiles_h__
#define __readFiles_h__
#include "./Motor/Motor.h"
#include "./Chassi/Chassi.h"
#include "./Jante/Jante.h"
#include "./Pneu/Pneu.h"
#include "./Carro/Carro.h"
#include "./Pedidos/Pedidos.h"

Motor* pegaMotor(FILE*);
Chassi* pegaChassi(FILE*);
Jante* pegaJante(FILE*);
Pneu* pegaPneu(FILE*);
void leFicheiroInventario(QueueMotor *,QueueChassi *,QueueJante *,QueuePneu *, char*);
void leFicheiroPedidos(QueuePedidos *,char*) ;

#endif