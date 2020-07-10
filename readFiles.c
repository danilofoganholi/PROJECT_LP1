#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define ERR_FOPEN "Error: could not open file."
#define ERR_CORPT "Error: File is corrupted."
#define ERR_ARGS "Error: Invalid argument."
#define ERR_MEM "Error: Couldn't allocate memory."
#define WARN_NO_PRODUCTION_INIT "Warning: No production done initiated yet."
#define ERR_NO_FILES "No files were specified"

#include "./Motor/Motor.h"
#include "./Chassi/Chassi.h"
#include "./Jante/Jante.h"
#include "./Pneu/Pneu.h"
#include "./Carro/Carro.h"
#include "readFiles.h"


Motor* pegaMotor(char* array[5])
{
	Motor *tmp = (Motor *) malloc(sizeof(Motor));
	if (tmp == NULL)
		printf(ERR_MEM);

	strcpy(tmp->numSerie,array[1]);
	tmp->potencia=atoi(array[2]);
	strcpy(tmp->type_of_fuel,array[3]);

	return tmp;
}

Chassi* pegaChassi(char* array[5])
{
	Chassi *tmp = (Chassi *) malloc(sizeof(Chassi));
	if (tmp == NULL)
	{
		printf(ERR_MEM);
	}
	//printf("ANTE = %s | %s | %s",array[1],array[2],array[3]);

	strcpy(tmp->color,array[2]);
	*tmp->modelo = *array[3];
	strcpy(tmp->numSerie,array[1]);
	

	printf("DEPOS = %s | %s | %s\n", tmp->numSerie, tmp->color, tmp->modelo);

	return tmp;
}

Jante* pegaJante(char* array[5])
{
	Jante *tmp = (Jante *) malloc(sizeof(Jante));
	if (tmp == NULL)
		printf(ERR_MEM);

	strcpy(tmp->numSerie,array[1]);
	tmp->diametro=atoi(array[2]);
	tmp->largura=atoi(array[3]);
	strcpy(tmp->color,array[4]);

	return tmp;
}

Pneu* pegaPneu(char* array[5])
{
	Pneu *tmp = (Pneu *) malloc(sizeof(Pneu));
	if (tmp == NULL)
		printf(ERR_MEM);

	strcpy(tmp->numSerie,array[1]);
	tmp->diametro=atoi(array[2]);
	tmp->largura=atoi(array[3]);
	tmp->altura=atoi(array[4]);

	return tmp;
}

void leFicheiroInventario(QueueMotor *listaMotores,QueueChassi *listaChassi,
QueueJante *listaJante,QueuePneu *listaPneu, char* file)
{
	char line[200];
	char *localFile = strcat(file,".inventario");

	FILE *filePointer = fopen(localFile, "r");	

	if (filePointer == NULL)
	{
		printf(ERR_FOPEN);
	}
	while(!feof(filePointer))
	{
		fgets(line,200,filePointer);
		
		int i= 0;
		char * equipamento = strtok(line, ",");
		char* array[5] = {NULL,NULL,NULL,NULL,NULL};
		while(equipamento!=NULL){
			array[i++] = equipamento;
			equipamento = strtok(NULL,",");
		}

		// printf("%s | %s | %s | %s | %s\n",array[0],array[1],array[2],array[3],array[4]);

		if (strcmp(array[0],"Motor")==0)
		{
			struct Motor* aux = pegaMotor(array);
			queueInsertMotor(listaMotores,*aux);
		}
		else if (strcmp(array[0],"Chassis")==0)
		{
			struct Chassi* aux = pegaChassi(array);
			// printChassi(aux);
			queueInsertChassi(listaChassi,*aux);
		}
		else if (strcmp(array[0],"Jantes")==0)
		{
			struct Jante* aux = pegaJante(array);
			queueInsertJante(listaJante,*aux);
		}
		else if (strcmp(array[0],"Pneus")==0)
		{
			struct Pneu* aux = pegaPneu(array);
			queueInsertPneu(listaPneu,*aux);
		}
	}

	fclose(filePointer);
}