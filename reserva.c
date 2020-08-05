void printCarro(Carro *t)
{
	printf("%s;",t->numPedido);
	if (t->motor->potencia!=0)
	{
		printf("%d",t->motor->potencia);
	}
	printf(",%s;%s,%s;",t->motor->type_of_fuel,t->chassi->color,t->chassi->modelo);
	if (t->jante->diametro!=0)
	{
		printf("%d",t->jante->diametro);
	}
	printf(",");
	if (t->jante->largura!=0)
	{
		printf("%d",t->jante->largura);
	}
	printf(",%s;",t->jante->color);
	if (t->pneu->diametro!=0)
	{
		printf("%d",t->pneu->diametro);
	}
	printf(",");
	if (t->pneu->largura!=0)
	{
		printf("%d",t->pneu->largura);
	}
	printf(",");
	if (t->pneu->altura!=0)
	{
		printf("%d",t->pneu->altura);
	}
	printf(";\n");
}

void resetCarro(Carro *t)
{
	strcpy(t->numPedido,"");
	
	strcpy(t->motor->numSerie,"");
	// t->motor->potencia=0;
	// strcpy(t->motor->type_of_fuel,"");

	strcpy(t->chassi->numSerie,"");
	// strcpy(t->chassi->modelo,"");
	// strcpy(t->chassi->color,"");

	strcpy(t->jante->numSerie,"");
	// t->jante->diametro=0;
	// t->jante->largura=0;
	// strcpy(t->jante->color,"");

	strcpy(t->pneu->numSerie,"");
	// t->pneu->diametro=0;
	// t->pneu->largura=0;
	// t->pneu->altura=0;

	// t->estado=0;
}

void printCarroTESTE(Carro *t)
{
	printf("%s;",t->numPedido);
	printMotor(t->motor);
	printf(";");
	printChassi(t->chassi);
	printf(";");
	printJante(t->jante);
	printf(";");
	printPneu(t->pneu);
	printf("\n");
}

int countQueueCarro(QueueCarro *q)
{
	int count=0;
	if (q->head==NULL)
	{
		return 0;
	}
	
	Carro *t;

	for (t = q->head ; t != NULL ; t = t -> next,count++){}


	return count;
}

void printQueueCarro(QueueCarro *q)
{
	if (q->head==NULL)
	{
		return;
	}
	Carro *t = (Carro*) malloc(sizeof(Carro));
	if (t == NULL)
	{
		printf(ERR_MEM);
		free(t);
		return;
	}
		
	for (t = q->head ; t->next != NULL ; t = t -> next)
	{
		printf("%s;",t->numPedido);
		printMotor(t->motor);
		printf(";");
		printChassi(t->chassi);
		printf(";");
		printJante(t->jante);
		printf(";");
		printPneu(t->pneu);
		printf("\n");
	}
	t=NULL;
	free(t);
}

void printQueuePedidoEspecial(QueuePedidos *q)
{
	if (q->head==NULL)
	{
		return;
	}
	Pedido *t = (Pedido*) malloc(sizeof(Pedido));
	if (t == NULL)
	{
		printf(ERR_MEM);
		free(t);
		return;
	}
	for (t = q->head ; t != NULL ; t = t -> next)
	{
		printf("%s;",t->numPedido);
		if (t->Motorpotencia!=0)
		{
			printf("%d",t->Motorpotencia);
		}
		printf(",%s;%s,%s;",t->Motor_fuel,t->ChassiColor,t->ChassiModelo);
		if (t->JanteDiametro!=0)
		{
			printf("%d",t->JanteDiametro);
		}
		printf(",");
		if (t->JanteLargura!=0)
		{
			printf("%d",t->JanteLargura);
		}
		printf(",%s;",t->JanteColor);
		if (t->PneuDiametro!=0)
		{
			printf("%d",t->PneuDiametro);
		}
		printf(",");
		if (t->PneuLargura!=0)
		{
			printf("%d",t->PneuLargura);
		}
		printf(",");
		if (t->PneuAltura!=0)
		{
			printf("%d",t->PneuAltura);
		}
		printf(";\n");
	}
}