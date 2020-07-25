#ifndef __readFiles_h__
#define __readFiles_h__
#include "Motor.h"
#include "Chassi.h"
#include "Jante.h"
#include "Pneu.h"
#include "Carro.h"
#include "Pedidos.h"

Motor* pegaMotor(FILE*);
Chassi* pegaChassi(FILE*);
Jante* pegaJante(FILE*);
Pneu* pegaPneu(FILE*);
void leFicheiroInventario(QueueMotor *,QueueChassi *,QueueJante *,QueuePneu *, char*);
void leFicheiroPedidos(QueuePedidos *,char*) ;

#endif