#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "producao.h"
#define ERR_FOPEN "Error: could not open file."
#define ERR_CORPT "Error: File is corrupted."
#define ERR_ARGS "Error: Invalid argument."
#define ERR_MEM "Error: Couldn't allocate memory."
#define WARN_NO_PRODUCTION_INIT "Warning: No production done initiated yet."
#define ERR_NO_FILES "No files were specified"

void iniciarProducao (QueueMotor *listaMotores,QueueChassi *listaChassis,
QueueJante *listaJantes,QueuePneu *listaPneus,QueueCarro *listaCarrosProduzidos,
QueueCarro *listaCarrosNaoProduzidos, QueuePedidos listaPedidos)
{
	Pedido *pedido = (Pedido*) malloc(sizeof(Pedido));
	Carro *aux = (Carro*) malloc(sizeof(Carro));
	if (pedido == NULL || aux==NULL)
	{
		printf(ERR_MEM);
		free(pedido);
		free(aux);
		return;
	}
	
	for (pedido = listaPedidos.head ; pedido->next != NULL ; pedido = pedido -> next)
	{
		int pussuiMotor = possuiPecaMotor(listaMotores,*pedido,aux);
		int possuiChassi = possuiPecaChassi(listaChassis,*pedido,aux);
		int possuiJantes = possuiPecaJantes(listaJantes,*pedido,aux);
		int possuiPneu = possuiPecaPneus(listaPneus,*pedido,aux);

		strcpy(aux->numPedido,pedido->numPedido);

		if (pussuiMotor && possuiChassi && possuiJantes  && possuiPneu )
		{
			aux->estado=1;
			queueInsertCarro(listaCarrosProduzidos,*aux);

			if(queueRemoveMotor(listaMotores, *aux->motor)==0)
			{
				//printf("MOTOR  = %s\n",aux->motor->numSerie);
			}
			if(queueRemoveChassi(listaChassis,*aux->chassi)==0)
			{
				//printf("CHASSI = %s\n",aux->chassi->numSerie);
			}
			if(queueRemoveJante(listaJantes,*aux->jante)==0)
			{
				//printf("JANTE  = %s\n",aux->jante->numSerie);
			}
			if(queueRemovePneu(listaPneus, *aux->pneu)==0)
			{
				//printf("PNEU   = %s\n",aux->pneu->numSerie);
			}
		}else
		{
			aux->estado=2;
			if (!pussuiMotor)
			{
				if (pedido->Motorpotencia!=0)
					aux->motor->potencia=pedido->Motorpotencia;
				else
					aux->motor->potencia=0;
				
				if (strcmp(pedido->Motor_fuel,"")!=0)
					strcpy(aux->motor->type_of_fuel,pedido->Motor_fuel);
				else
					strcpy(aux->motor->type_of_fuel,"");
			}else
			{
				aux->motor->potencia=0;
				strcpy(aux->motor->type_of_fuel,"");
			}

			if (!possuiChassi)
			{
				if (strcmp(pedido->ChassiColor,"")!=0)
					strcpy(aux->chassi->color,pedido->ChassiColor);
				else
					strcpy(aux->chassi->color,"");
				
				if (strcmp(pedido->ChassiModelo,"")!=0)
					strcpy(aux->chassi->modelo,pedido->ChassiModelo);
				else
					strcpy(aux->chassi->modelo,"");
			}else
			{
				strcpy(aux->chassi->color,"");
				strcpy(aux->chassi->modelo,"");
			}
			
			if (!possuiJantes)
			{
				if (pedido->JanteDiametro!=0)
					aux->jante->diametro=pedido->JanteDiametro;
				else
					aux->jante->diametro=0;
				
				if (pedido->JanteLargura!=0)
					aux->jante->largura= pedido->JanteLargura;
				else
					aux->jante->largura=0;

				if (strcmp(pedido->JanteColor,"")!=0)
					strcpy(aux->jante->color,pedido->JanteColor);
				else
					strcpy(aux->jante->color,"");
			}else
			{
				aux->jante->diametro=0;
				aux->jante->largura=0;
				strcpy(aux->jante->color,"");
			}
			
			if (!possuiPneu)
			{
				if (pedido->PneuDiametro!=0)
					aux->pneu->diametro=pedido->PneuDiametro;
				else
					aux->pneu->diametro=0;
				
				if (pedido->PneuLargura!=0)
					aux->pneu->largura= pedido->PneuLargura;
				else
					aux->pneu->largura=0;

				if (pedido->PneuAltura!=0)
					aux->pneu->altura=pedido->PneuAltura;
				else
					aux->pneu->altura=0;
			}else
			{
				aux->pneu->diametro=0;
				aux->pneu->largura=0;
				aux->pneu->altura=0;
			}
			
			queueInsertCarro(listaCarrosNaoProduzidos,*aux);
		}
	}
	free(pedido);
	free(aux);
}

int possuiPecaMotor(QueueMotor *listaMotores,Pedido t,Carro*aux)
{
	Motor *tmp = (Motor*) malloc(sizeof(Motor));
	if (tmp == NULL)
		printf(ERR_MEM);
	if (t.Motorpotencia==0 && strcmp(t.Motor_fuel,"")==0)
	{
		Motor *motor = (Motor*) malloc(sizeof(Motor));
		if (motor == NULL)
			printf(ERR_MEM);

		strcpy(motor->numSerie,listaMotores->head->numSerie);
		motor->potencia=listaMotores->head->potencia;
		strcpy(motor->numSerie,listaMotores->head->numSerie);

		aux->motor= motor;
		free(tmp);
		return 1;
	}else{
		for (tmp = listaMotores->head ; tmp->next != NULL ; tmp = tmp -> next)
		{
			if ( (t.Motorpotencia!=0 && strcmp(t.Motor_fuel,"")==0 && t.Motorpotencia==tmp->potencia) ||
			(t.Motorpotencia==0 && strcmp(t.Motor_fuel,"")!=0 && strcmp(t.Motor_fuel,tmp->type_of_fuel)==0) ||
			(t.Motorpotencia!=0 && strcmp(t.Motor_fuel,"")!=0 && 
			t.Motorpotencia==tmp->potencia && strcmp(t.Motor_fuel,tmp->type_of_fuel)==0))
			{
				Motor *motor = (Motor*) malloc(sizeof(Motor));
				if (motor == NULL)
					printf(ERR_MEM);

				strcpy(motor->numSerie,tmp->numSerie);
				motor->potencia=tmp->potencia;
				strcpy(motor->type_of_fuel,tmp->type_of_fuel);

				aux->motor= motor;
				return 1;
			}
		}
	}
	return 0;	
}

int possuiPecaChassi(QueueChassi *listaChassis,Pedido t,Carro*aux)
{
	Chassi *tmp = (Chassi*) malloc(sizeof(Chassi));
	if (tmp == NULL)
		printf(ERR_MEM);

	if (strcmp(t.ChassiColor,"")==0 && strcmp(t.ChassiModelo,"")==0)
	{
		Chassi *chassi = (Chassi*) malloc(sizeof(Chassi));
		if (chassi == NULL)
			printf(ERR_MEM);

		strcpy(chassi->numSerie,listaChassis->head->numSerie);
		strcpy(chassi->color,listaChassis->head->color);
		strcpy(chassi->modelo,listaChassis->head->modelo);

		aux->chassi= chassi;
		free(tmp);
		return 1;

	}else
	{
		for (tmp = listaChassis->head ; tmp->next != NULL ; tmp = tmp -> next)
		{
			if ((strcmp(t.ChassiColor,"")!=0 && strcmp(t.ChassiModelo,"")==0 && strcmp(t.ChassiColor,tmp->color)) || 
			(strcmp(t.ChassiColor,"")==0 && strcmp(t.ChassiModelo,"")!=0 && strcmp(t.ChassiModelo,tmp->modelo)==0) ||
			(strcmp(t.ChassiColor,"")!=0 && strcmp(t.ChassiModelo,"")!=0 && 
			strcmp(t.ChassiColor,tmp->color) && strcmp(t.ChassiModelo,tmp->modelo)==0))
			{
				Chassi *chassi = (Chassi*) malloc(sizeof(Chassi));
				if (chassi == NULL)
					printf(ERR_MEM);

				strcpy(chassi->numSerie,tmp->numSerie);
				strcpy(chassi->color,tmp->color);
				strcpy(chassi->modelo,tmp->modelo);

				aux->chassi= chassi;
				return 1;
			}
		}
	}
	return 0;	
}

int possuiPecaJantes(QueueJante *listaJante,Pedido t,Carro*aux)
{
	Jante *tmp = (Jante*) malloc(sizeof(Jante));
	if (tmp == NULL)
		printf(ERR_MEM);

	if (t.JanteDiametro==0 && t.JanteLargura==0 && strcmp(t.JanteColor,"")==0)
	{
		Jante *jante = (Jante*) malloc(sizeof(Jante));
		if (jante == NULL)
			printf(ERR_MEM);

		strcpy(jante->numSerie,listaJante->head->numSerie);
		jante->diametro=listaJante->head->diametro;
		jante->largura=listaJante->head->largura;
		strcpy(jante->color,listaJante->head->color);

		aux->jante= jante;
		free(tmp);
		return 1;
	}else
	{
		for (tmp = listaJante->head ; tmp->next != NULL ; tmp = tmp -> next)
		{
			if (t.JanteDiametro!=0 && t.JanteLargura!=0 && strcmp(t.JanteColor,"")!=0)
			{
				if (t.JanteDiametro==tmp->diametro && t.JanteLargura==tmp->largura && strcmp(t.JanteColor,tmp->color)==0)
				{
					Jante *jante = (Jante*) malloc(sizeof(Jante));
					if (jante == NULL)
						printf(ERR_MEM);

					strcpy(jante->numSerie,tmp->numSerie);
					jante->diametro=tmp->diametro;
					jante->largura=tmp->largura;
					strcpy(jante->color,tmp->color);

					aux->jante= jante;
					return 1;
				}
			}else if (t.JanteDiametro!=0 && t.JanteLargura==0 && strcmp(t.JanteColor,"")==0)
			{
				if (t.JanteDiametro==tmp->diametro)
				{
					Jante *jante = (Jante*) malloc(sizeof(Jante));
					if (jante == NULL)
						printf(ERR_MEM);

					strcpy(jante->numSerie,tmp->numSerie);
					jante->diametro=tmp->diametro;
					jante->largura=tmp->largura;
					strcpy(jante->color,tmp->color);

					aux->jante= jante;
					return 1;
				}
			}else if (t.JanteDiametro==0 && t.JanteLargura!=0 && strcmp(t.JanteColor,"")==0)
			{
				if (t.JanteLargura==tmp->largura)
				{
					Jante *jante = (Jante*) malloc(sizeof(Jante));
					if (jante == NULL)
						printf(ERR_MEM);

					strcpy(jante->numSerie,tmp->numSerie);
					jante->diametro=tmp->diametro;
					jante->largura=tmp->largura;
					strcpy(jante->color,tmp->color);

					aux->jante= jante;
					return 1;
				}
			}else if (t.JanteDiametro==0 && t.JanteLargura==0 && strcmp(t.JanteColor,"")!=0)
			{
				if (strcmp(t.JanteColor,tmp->color)==0)
				{
					Jante *jante = (Jante*) malloc(sizeof(Jante));
					if (jante == NULL)
						printf(ERR_MEM);

					strcpy(jante->numSerie,tmp->numSerie);
					jante->diametro=tmp->diametro;
					jante->largura=tmp->largura;
					strcpy(jante->color,tmp->color);

					aux->jante= jante;
					return 1;
				}
			}else if (t.JanteDiametro!=0 && t.JanteLargura!=0 && strcmp(t.JanteColor,"")==0)
			{
				if (t.JanteDiametro==tmp->diametro && t.JanteLargura==tmp->largura)
				{
					Jante *jante = (Jante*) malloc(sizeof(Jante));
					if (jante == NULL)
						printf(ERR_MEM);

					strcpy(jante->numSerie,tmp->numSerie);
					jante->diametro=tmp->diametro;
					jante->largura=tmp->largura;
					strcpy(jante->color,tmp->color);

					aux->jante= jante;
					return 1;
				}
			}else if (t.JanteDiametro==0 && t.JanteLargura!=0 && strcmp(t.JanteColor,"")!=0)
			{
				if (t.JanteLargura==tmp->largura && strcmp(t.JanteColor,tmp->color)==0)
				{
					Jante *jante = (Jante*) malloc(sizeof(Jante));
					if (jante == NULL)
						printf(ERR_MEM);

					strcpy(jante->numSerie,tmp->numSerie);
					jante->diametro=tmp->diametro;
					jante->largura=tmp->largura;
					strcpy(jante->color,tmp->color);

					aux->jante= jante;
					return 1;
				}
			}else if (t.JanteDiametro!=0 && t.JanteLargura==0 && strcmp(t.JanteColor,"")!=0)
			{
				if (t.JanteDiametro==tmp->diametro && strcmp(t.JanteColor,tmp->color)==0)
				{
					Jante *jante = (Jante*) malloc(sizeof(Jante));
					if (jante == NULL)
						printf(ERR_MEM);

					strcpy(jante->numSerie,tmp->numSerie);
					jante->diametro=tmp->diametro;
					jante->largura=tmp->largura;
					strcpy(jante->color,tmp->color);

					aux->jante= jante;
					return 1;
				}
			}
		}
	}
	free(tmp);
	return 0;	
}

int possuiPecaPneus(QueuePneu *listaPneu,Pedido t,Carro*aux)
{
	Pneu *tmp = (Pneu*) malloc(sizeof(Pneu));
	if (tmp == NULL)
	{
		printf(ERR_MEM);
		free(tmp);
		return 0;
	}

	if (t.PneuDiametro==0 && t.PneuLargura==0 && t.PneuAltura==0)
	{
		strcpy(tmp->numSerie,listaPneu->head->numSerie);
		tmp->diametro=listaPneu->head->diametro;
		tmp->largura=listaPneu->head->largura;
		tmp->altura=listaPneu->head->altura;

		aux->pneu= tmp;
		return 1;
	}else
	{
		for (tmp = listaPneu->head ; tmp->next != NULL ; tmp = tmp -> next)
		{
			if (t.PneuDiametro!=0 && t.PneuLargura!=0 && t.PneuAltura!=0)
			{
				if (t.PneuDiametro==tmp->diametro && t.PneuLargura==tmp->largura && t.PneuAltura == tmp->altura)
				{
					Pneu *pneu = (Pneu*) malloc(sizeof(Pneu));
					if (pneu == NULL)
						printf(ERR_MEM);

					strcpy(pneu->numSerie,tmp->numSerie);
					pneu->diametro=tmp->diametro;
					pneu->largura=tmp->largura;
					pneu->altura=tmp->altura;

					aux->pneu= pneu;
					return 1;
				}
			}else if (t.PneuDiametro!=0 && t.PneuLargura==0 && t.PneuAltura ==0)
			{
				if (t.PneuDiametro==tmp->diametro)
				{
					Pneu *pneu = (Pneu*) malloc(sizeof(Pneu));
					if (pneu == NULL)
						printf(ERR_MEM);

					strcpy(pneu->numSerie,tmp->numSerie);
					pneu->diametro=tmp->diametro;
					pneu->largura=tmp->largura;
					pneu->altura=tmp->altura;

					aux->pneu= pneu;
					return 1;
				}
			}else if (t.PneuDiametro==0 && t.PneuLargura!=0 && t.PneuAltura ==0)
			{
				if (t.PneuLargura==tmp->largura)
				{
					Pneu *pneu = (Pneu*) malloc(sizeof(Pneu));
					if (pneu == NULL)
						printf(ERR_MEM);

					strcpy(pneu->numSerie,tmp->numSerie);
					pneu->diametro=tmp->diametro;
					pneu->largura=tmp->largura;
					pneu->altura=tmp->altura;

					aux->pneu= pneu;
					return 1;
				}
			}else if (t.PneuDiametro==0 && t.PneuLargura==0 && t.PneuAltura!=0)
			{
				if (t.PneuAltura == tmp->altura)
				{
					Pneu *pneu = (Pneu*) malloc(sizeof(Pneu));
					if (pneu == NULL)
						printf(ERR_MEM);

					strcpy(pneu->numSerie,tmp->numSerie);
					pneu->diametro=tmp->diametro;
					pneu->largura=tmp->largura;
					pneu->altura=tmp->altura;

					aux->pneu= pneu;
					return 1;
				}
			}else if (t.PneuDiametro!=0 && t.PneuLargura!=0 && t.PneuAltura ==0)
			{
				if (t.PneuDiametro==tmp->diametro && t.PneuLargura==tmp->largura)
				{
					Pneu *pneu = (Pneu*) malloc(sizeof(Pneu));
					if (pneu == NULL)
						printf(ERR_MEM);

					strcpy(pneu->numSerie,tmp->numSerie);
					pneu->diametro=tmp->diametro;
					pneu->largura=tmp->largura;
					pneu->altura=tmp->altura;

					aux->pneu= pneu;
					return 1;
				}
			}else if (t.PneuDiametro==0 && t.PneuLargura!=0 && t.PneuAltura!=0)
			{
				if (t.PneuLargura==tmp->largura && t.PneuAltura==tmp->altura)
				{
					Pneu *pneu = (Pneu*) malloc(sizeof(Pneu));
					if (pneu == NULL)
						printf(ERR_MEM);

					strcpy(pneu->numSerie,tmp->numSerie);
					pneu->diametro=tmp->diametro;
					pneu->largura=tmp->largura;
					pneu->altura=tmp->altura;

					aux->pneu= pneu;
					return 1;
				}
			}else if (t.PneuDiametro!=0 && t.PneuLargura==0 && t.PneuAltura!=0)
			{
				if (t.PneuDiametro==tmp->diametro && t.PneuAltura == tmp->altura)
				{
					Pneu *pneu = (Pneu*) malloc(sizeof(Pneu));
					if (pneu == NULL)
						printf(ERR_MEM);

					strcpy(pneu->numSerie,tmp->numSerie);
					pneu->diametro=tmp->diametro;
					pneu->largura=tmp->largura;
					pneu->altura=tmp->altura;

					aux->pneu= pneu;
					return 1;
				}
			}
		}
	}
	free(tmp);
	return 0;	
}