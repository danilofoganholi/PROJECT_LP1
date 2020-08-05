#ifndef __motor_h__
#define __motor_h__

//declarando estruturas
typedef struct Motor
{
	char numSerie[21];
	int potencia;
	char type_of_fuel[9];
	struct Motor *next;
}Motor;

typedef struct
{
	Motor * head, *tail;
}QueueMotor;

//declarando funcoes para motores
void queueInitMotor( QueueMotor *);
void queueInsertMotor ( QueueMotor *, Motor);
void printQueueMotor(QueueMotor *);
int countQueueMotor(QueueMotor *);
void escreveMotoresInventario(QueueMotor*, char*);
void bubbleSortMotor(QueueMotor *);
Motor pegaMotorLista(QueueMotor*,int,char*);
int removeMotor(QueueMotor*,char*);
#endif