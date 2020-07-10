#ifndef __motor_h__
#define __motor_h__

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

void queueInitMotor( QueueMotor *);
void queueInsertMotor ( QueueMotor *, Motor);
void queueRemove(QueueMotor*,Motor);
void printQueueMotor(QueueMotor *);
void printMotor(Motor *);

#endif