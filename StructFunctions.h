#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct produto produto, *prod_pointer;
	struct produto
	{
		int IDProduto;
		int quantidade;
		int corredor;
		int armario;
		prod_pointer proximo;
	};

int verifica_lista(prod_pointer prod)
{
	if (prod == NULL)
		return 1;
	else
		return 0;
}

void preenche(prod_pointer prod, int IDProduto, int Quantidade, int corredor, int armario)
{
	prod->IDProduto=IDProduto;
	prod->quantidade=Quantidade;
	prod->corredor=corredor;
	prod->armario=armario;
	prod->proximo = NULL;
}

prod_pointer AdicionaProduto(prod_pointer prod,int IDProduto, int Quantidade, int corredor, int armario)
{

	prod_pointer novo, aux;
	novo = malloc(sizeof(produto));

	if(novo == NULL)
	{
		printf("Erro na alocacao de memoria!\n");
		return prod;
	}

	preenche(novo, IDProduto, Quantidade, corredor, armario);

	/*printf("ID Produto: %d\n",novo->IDProduto);
	printf("Quantidade: %d\n", novo->quantidade);
	printf("Coordenadas: %d%d\n", novo->corredor, novo->armario);*/

	if(verifica_lista(prod))
	{
		prod = novo;
		printf("Lista Vazia! 1 Produto inserido com sucesso!\n\n");
	}
	else
	{
			//Introduz no fim da lista
			aux = prod;
			while(aux->proximo != NULL)
				aux = aux->proximo;
			aux->proximo = novo;
			printf("Produto inserido com sucesso no fim da lista!\n\n");
	}
	
	return prod;
}

void MostraProdutos(prod_pointer prod)
{
	while(prod != NULL)
	{
		printf("ID Produto: %d\n",prod->IDProduto);
		printf("Quantidade: %d\n", prod->quantidade);
		printf("Coordenadas: Corredor->%d    Armario->%d\n", prod->corredor, prod->armario);
		prod = prod->proximo;
	}
}

prod_pointer EliminaProd(prod_pointer prod)
{
	prod_pointer actual;
	actual = prod;
	prod = actual->proximo;
	free(actual);
	return prod;
}