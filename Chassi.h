#ifndef __chassi_h__
#define __chassi_h__

//declarando estruturas
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

//declarando funcoes para chassi
void queueInitChassi(QueueChassi *);
void queueInsertChassi (QueueChassi *, Chassi);
void printQueueChassi(QueueChassi *);
void escreveChassiInventario(QueueChassi*,char*);
void bubbleSortChassi(QueueChassi *);
int countQueueChassi(QueueChassi *);
Chassi pegaChassiLista(QueueChassi*,char*,char*);
int removeChassi (QueueChassi *,char*);

#endif