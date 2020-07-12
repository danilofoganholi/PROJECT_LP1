#ifndef __chassi_h__
#define __chassi_h__

typedef struct Chassi
{
	char numSerie[21];
	char modelo[128];
	char color[10];
	struct Chassi *next;
}Chassi;

typedef struct 
{
	Chassi * head, *tail;
}QueueChassi;

void queueInitChassi(QueueChassi *);
void queueInsertChassi (QueueChassi *, Chassi);
int queueRemoveChassi(QueueChassi*,Chassi);
void printQueueChassi(QueueChassi *);
void printChassi(Chassi *);
int countQueueChassi(QueueChassi *);
void escreveChassiInventario(QueueChassi*,char*);

#endif