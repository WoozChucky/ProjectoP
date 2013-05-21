/* #define _CRT_SECURE_NO_WARNINGS 1

	

void preenche(pno p)
{
	printf("Nome: ");
	gets(p->nome);
	printf("Urgencia (1-3): ");
	scanf("%d", p->urgencia);
	p->prox = NULL;
}

int verifica_lista(pno p)
{
	if (p == NULL)
		return 1;
	else
		return 0;
}

pno adiciona_final(pno p)
{
	pno novo, aux;

	novo = malloc(sizeof(no));

	if(novo == NULL)
	{
		printf("Erro na alocacao de memoria!\n");
		return p;
	}

	preenche(novo);

	if(verifica_lista(p))
	{
		p = novo;
	}
	else
	{
		if(novo->urgencia >= 3)
		{
			//Restantes Pacientes
			aux = p;
			while(aux->prox != NULL)
				aux = aux->prox;
			aux->prox = novo;
		} else if(novo->urgencia == 2)
		{
			//Idosos e Criancas

		} else if(novo->urgencia <= 1)
		{
			//Gravidas
			novo->prox = p;
			p = novo;
		}
	}
	
	return p;
}

void mostra_lista(pno p)
{
	while(p != NULL)
	{
		printf("%s\n",p->nome);
		p = p->prox;
	}
}

pno atendimento(pno p)
{
	pno actual;
	actual = p;
	p = actual->prox;
	free(actual);
	return p;
}

pno desistencia(pno p)
{

}

int main()
{
	int resp=0;
	pno lista = NULL;
	
	printf("1. Novo Paciente\n");
	printf("2. Atendimento\n");
	printf("3. Visualizar Fila de Espera\n");
	printf("4. Desistencia\n");
	printf("5. Terminar\n");
	printf("Escolha uma opcao (1-5): ");
	scanf("%d", &resp);
	
	switch(resp)
	{
	case 1:
		{
			printf("\nAdicionar Novo Paciente\n\n");
			lista=adiciona_final(lista);
		}
	case 2:
		{
			lista=atendimento(lista);
		}
	case 3:
		{
			mostra_lista(lista);
		}
	case 4:
		{
			lista=desistencia(lista);
		}
	case 5:
		{
			printf("Terminado.\n");
			return 1;
		}
	default:
		{
			printf("Nenhuma Opcao Selecionada.\n");
			return 1;
		}
	}
}
*/