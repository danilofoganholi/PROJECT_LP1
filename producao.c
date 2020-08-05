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
QueuePedidos *listaPedidosNaoProduzidos, QueuePedidos listaPedidos)
{
	if (listaMotores->head==NULL || listaChassis->head==NULL || 
	listaJantes->head==NULL || listaPneus->head==NULL)//valida se as lista não são vazias 
	{
		return;
	}
	Pedido *pedido;

	//percorre todos os pedidos da lista
	for (pedido = listaPedidos.head ; pedido != NULL ; pedido = pedido -> next)
	{
		int pussuiMotor = possuiPecaMotor(listaMotores,*pedido);//retorna 1 se tiver motor especidicado
		int possuiChassi = possuiPecaChassi(listaChassis,*pedido);//retorna 1 se tiver chassi especidicado
		int possuiJantes = possuiPecaJantes(listaJantes,*pedido);//retorna 1 se tiver jante especidicado
		int possuiPneu = possuiPecaPneus(listaPneus,*pedido);//retorna 1 se tiver pneu especidicado

		if (pussuiMotor && possuiChassi && possuiJantes  && possuiPneu )//se possuir todos
		{
			//produzir carro
			listaCarroProduzido(listaCarrosProduzidos,pedido,listaMotores,
			listaChassis,listaJantes,listaPneus);
		}else
		{
			//colocar na lista de não produzido
			listaCarroNaoProduzido(listaPedidosNaoProduzidos,*pedido);
		}
	}
}

void listaCarroNaoProduzido(QueuePedidos *q,Pedido pedido)
{
	//monta pedido
	struct Pedido pedidoIncompleto;

	strcpy(pedidoIncompleto.numPedido,pedido.numPedido);
	pedidoIncompleto.next=NULL;

	pedidoIncompleto.Motorpotencia=pedido.Motorpotencia;
	strcpy(pedidoIncompleto.Motor_fuel,pedido.Motor_fuel);

	strcpy(pedidoIncompleto.ChassiModelo,pedido.ChassiModelo);
	strcpy(pedidoIncompleto.ChassiColor,pedido.ChassiColor);

	pedidoIncompleto.JanteDiametro=pedido.JanteDiametro;
	pedidoIncompleto.JanteLargura=pedido.JanteLargura;
	strcpy(pedidoIncompleto.JanteColor,pedido.JanteColor);

	pedidoIncompleto.PneuDiametro=pedido.PneuDiametro;
	pedidoIncompleto.PneuLargura=pedido.PneuLargura;
	pedidoIncompleto.PneuAltura=pedido.PneuAltura;

	//adiciona pedido na lista de pedidos NÃO PRODUZIDOS
	queueInsertPedido(q,pedidoIncompleto);
}

void listaCarroProduzido(QueueCarro *q,Pedido *pedido,QueueMotor *listaMotores,QueueChassi *listaChassis,
QueueJante *listaJantes,QueuePneu *listaPneus)
{
	//monta CARRO
	Carro carroProduzido ;
	
	Motor *motor = (Motor *) malloc(sizeof(Motor));;
	Chassi *chassi= (Chassi *) malloc(sizeof(Chassi));;
	Jante *jante= (Jante *) malloc(sizeof(Jante));;
	Pneu *pneu= (Pneu *) malloc(sizeof(Pneu));;

	strcpy(carroProduzido.numPedido,pedido->numPedido);
	carroProduzido.estado=1;
	carroProduzido.next=NULL;

	//devolve o motor com as especificações pedidas
	*motor = pegaMotorLista(listaMotores,pedido->Motorpotencia,pedido->Motor_fuel);

	//devolve o chassi com as especificações pedidas
	*chassi = pegaChassiLista(listaChassis,pedido->ChassiColor,pedido->ChassiModelo);

	//devolve o jante com as especificações pedidas
	*jante = pegaJanteLista(listaJantes,pedido->JanteDiametro,pedido->JanteLargura,pedido->JanteColor);

	//devolve o pneu com as especificações pedidas
	*pneu = pegaPneuLista(listaPneus,pedido->PneuDiametro,pedido->PneuLargura,pedido->PneuAltura);


	carroProduzido.motor=motor;//atribui o motor ao carro

	carroProduzido.chassi=chassi;//atribui o chassi ao carro

	carroProduzido.jante=jante;//atribui o jante ao carro

	carroProduzido.pneu=pneu;//atribui o pneu ao carro


	queueInsertCarro(q,carroProduzido);//insere o carro na lista de carros produzidos

	removeMotor(listaMotores,motor->numSerie);//remove do stock o motor utilizado
	removeChassi(listaChassis,chassi->numSerie);//remove do stock o chassi utilizado
	removeJante(listaJantes,jante->numSerie);//remove do stock o jante utilizado
	removePneu(listaPneus,pneu->numSerie);//remove do stock o pneu utilizado
}

int possuiPecaMotor(QueueMotor *listaMotores,Pedido t)
{
	if (listaMotores->head==NULL)//varifica se é null
		return 0;
	
	Motor *tmp ;

	if (t.Motorpotencia==0 && strcmp(t.Motor_fuel,"")==0)//nenhum dado especificado
	{
		return 1;
	}else if (t.Motorpotencia!=0 && strcmp(t.Motor_fuel,"")==0)//potencia especificada
	{
		for (tmp = listaMotores->head ; tmp != NULL ; tmp = tmp -> next)
		{
			if (t.Motorpotencia==tmp->potencia)
				return 1;	
		}
	}else if (t.Motorpotencia==0 && strcmp(t.Motor_fuel,"")!=0)//combustivel especificado
	{
		for (tmp = listaMotores->head ; tmp != NULL ; tmp = tmp -> next)
		{
			if (strcmp(t.Motor_fuel,tmp->type_of_fuel)==0)
				return 1;	
		}
	}else //todos especificados
	{
		for (tmp = listaMotores->head ; tmp != NULL ; tmp = tmp -> next)
		{
			if (t.Motorpotencia==tmp->potencia && strcmp(t.Motor_fuel,tmp->type_of_fuel)==0)
				return 1;	
		}
	}

	return 0;	
}

int possuiPecaChassi(QueueChassi *listaChassis,Pedido t)
{
	if (listaChassis->head==NULL)
		return 0;

	Chassi *tmp;

	if (strcmp(t.ChassiColor,"")==0 && strcmp(t.ChassiModelo,"")==0)//nenhum dado especificado
	{
		return 1;
	}else if (strcmp(t.ChassiColor,"")==0 && strcmp(t.ChassiModelo,"")!=0)//apenas modelo especificado
	{
		for (tmp = listaChassis->head ; tmp != NULL ; tmp = tmp -> next)
		{
			if (strcmp(t.ChassiModelo,tmp->modelo)==0)
				return 1;	
		}
	}else if (strcmp(t.ChassiColor,"")!=0 && strcmp(t.ChassiModelo,"")==0)//apenas cor especificado
	{
		for (tmp = listaChassis->head ; tmp != NULL ; tmp = tmp -> next)
		{
			if (strcmp(t.ChassiColor,tmp->color)==0)
				return 1;	
		}
	}else//cor e modelo especificados
	{
		for (tmp = listaChassis->head ; tmp != NULL ; tmp = tmp -> next)
		{
			if (strcmp(t.ChassiColor,tmp->color)==0 && strcmp(t.ChassiModelo,tmp->modelo)==0)
				return 1;	
		}
	}

	return 0;	
}

int possuiPecaJantes(QueueJante *listaJante,Pedido t)
{
	if (listaJante->head==NULL)
		return 0;

	Jante *tmp ;
	
	if (t.JanteDiametro==0 && t.JanteLargura==0 && strcmp(t.JanteColor,"")==0)//nenhum dado especificado
	{
		return 1;
	}else if (t.JanteDiametro==0 && t.JanteLargura==0 && strcmp(t.JanteColor,"")!=0)//cor especificada
	{
		for (tmp = listaJante->head ; tmp!= NULL ; tmp = tmp -> next)
		{
			if (strcmp(t.JanteColor,tmp->color)==0)
				return 1;
		}
	}else if (t.JanteDiametro==0 && t.JanteLargura!=0 && strcmp(t.JanteColor,"")==0)//largura especificada
	{
		for (tmp = listaJante->head ; tmp!= NULL ; tmp = tmp -> next)
		{
			if (t.JanteLargura==tmp->largura)
				return 1;
		}
	}else if (t.JanteDiametro==0 && t.JanteLargura!=0 && strcmp(t.JanteColor,"")!=0)//largura e cor especificada
	{
		for (tmp = listaJante->head ; tmp!= NULL ; tmp = tmp -> next)
		{
			if (t.JanteLargura==tmp->largura &&	strcmp(t.JanteColor,tmp->color)==0)
				return 1;
		}
	}else if (t.JanteDiametro!=0 && t.JanteLargura==0 && strcmp(t.JanteColor,"")==0)//diametro especificada
	{
		for (tmp = listaJante->head ; tmp!= NULL ; tmp = tmp -> next)
		{
			if (t.JanteDiametro==tmp->diametro)
				return 1;
		}
	}else if (t.JanteDiametro!=0 && t.JanteLargura==0 && strcmp(t.JanteColor,"")!=0)//diametro e cor especificada
	{
		for (tmp = listaJante->head ; tmp!= NULL ; tmp = tmp -> next)
		{
			if (t.JanteDiametro==tmp->diametro && strcmp(t.JanteColor,tmp->color)==0)
				return 1;
		}
	}else if (t.JanteDiametro!=0 && t.JanteLargura!=0 && strcmp(t.JanteColor,"")==0)//diametro e largular especificada
	{
		for (tmp = listaJante->head ; tmp!= NULL ; tmp = tmp -> next)
		{
			if (t.JanteDiametro==tmp->diametro && t.JanteLargura==tmp->largura)
				return 1;
		}
	}else //todos especificados
	{
		for (tmp = listaJante->head ; tmp!= NULL ; tmp = tmp -> next)
		{
			if (t.JanteDiametro==tmp->diametro && t.JanteLargura==tmp->largura &&
				strcmp(t.JanteColor,tmp->color)==0)
				return 1;
		}
	}

	return 0;
}	

int possuiPecaPneus(QueuePneu *listaPneu,Pedido t)
{
	if (listaPneu->head==NULL)
	{
		return 0;
	}
	Pneu *tmp;

	if (t.PneuDiametro==0 && t.PneuLargura==0 && t.PneuAltura==0)//nenhum dado especificado
	{
		return 1;
	}else if (t.PneuDiametro==0 && t.PneuLargura==0 && t.PneuAltura!=0)//altura especificada
	{
				for (tmp = listaPneu->head ; tmp != NULL ; tmp = tmp -> next)
		{
			if (t.PneuDiametro==tmp->diametro && t.PneuLargura==tmp->largura && t.PneuAltura == tmp->altura)
				return 1;
		}
	}else if (t.PneuDiametro==0 && t.PneuLargura!=0 && t.PneuAltura==0)//largura especificada
	{
				for (tmp = listaPneu->head ; tmp != NULL ; tmp = tmp -> next)
		{
			if (t.PneuDiametro==tmp->diametro && t.PneuLargura==tmp->largura && t.PneuAltura == tmp->altura)
				return 1;
		}
	}else if (t.PneuDiametro==0 && t.PneuLargura!=0 && t.PneuAltura!=0)//largura e algura especificadas
	{
				for (tmp = listaPneu->head ; tmp != NULL ; tmp = tmp -> next)
		{
			if (t.PneuDiametro==tmp->diametro && t.PneuLargura==tmp->largura && t.PneuAltura == tmp->altura)
				return 1;
		}
	}else if (t.PneuDiametro!=0 && t.PneuLargura==0 && t.PneuAltura==0)//diametro especificado
	{
				for (tmp = listaPneu->head ; tmp != NULL ; tmp = tmp -> next)
		{
			if (t.PneuDiametro==tmp->diametro && t.PneuLargura==tmp->largura && t.PneuAltura == tmp->altura)
				return 1;
		}
	}else if (t.PneuDiametro!=0 && t.PneuLargura==0 && t.PneuAltura!=0)//diametro e altura especificados
	{
				for (tmp = listaPneu->head ; tmp != NULL ; tmp = tmp -> next)
		{
			if (t.PneuDiametro==tmp->diametro && t.PneuLargura==tmp->largura && t.PneuAltura == tmp->altura)
				return 1;
		}
	}else if (t.PneuDiametro!=0 && t.PneuLargura!=0 && t.PneuAltura==0)//diametro e largura especificados
	{
				for (tmp = listaPneu->head ; tmp != NULL ; tmp = tmp -> next)
		{
			if (t.PneuDiametro==tmp->diametro && t.PneuLargura==tmp->largura && t.PneuAltura == tmp->altura)
				return 1;
		}
	}else //todos especificados
	{
				for (tmp = listaPneu->head ; tmp != NULL ; tmp = tmp -> next)
		{
			if (t.PneuDiametro==tmp->diametro && t.PneuLargura==tmp->largura && t.PneuAltura == tmp->altura)
				return 1;
		}
	}

	return 0;	
}