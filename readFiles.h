#ifndef __readFiles_h__
#define __readFiles_h__
#include "./Motor/Motor.h"
#include "./Chassi/Chassi.h"
#include "./Jante/Jante.h"
#include "./Pneu/Pneu.h"
#include "./Carro/Carro.h"

Motor* pegaMotor(char* array[5]);
void leFicheiroInventario(QueueMotor *,QueueChassi *,QueueJante *,QueuePneu *, char*);

#endif