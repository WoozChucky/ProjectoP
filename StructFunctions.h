#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct produto produto, *pno;
	struct produto
	{
		int IDProduto;
		int quantidade;
		int corredor;
		int armario;
		pno proximo;
	};

int verifica_lista(pno prod)
{
	if (prod == NULL)
		return 1;
	else
		return 0;
}

void preenche(pno prod, int IDProduto, int Quantidade, int corredor, int armario)
{
	prod->IDProduto=IDProduto;
	prod->quantidade=Quantidade;
	prod->corredor=corredor;
	prod->armario=armario;
	prod->proximo = NULL;
}

pno AdicionaProduto(pno prod,int IDProduto, int Quantidade, int corredor, int armario)
{

	pno novo, aux;
	novo = malloc(sizeof(produto));

	if(novo == NULL)
	{
		printf("Erro na alocacao de memoria!\n");
		return prod;
	}

	preenche(novo, IDProduto, Quantidade, corredor, armario);

	if(verifica_lista(prod))
	{
		prod = novo;
	}
	else
	{
			//Introduz no fim da lista
			aux = prod;
			while(aux->proximo != NULL)
				aux = aux->proximo;
			aux->proximo = novo;
	}
	
	return prod;
}

void MostraProdutos(pno prod)
{
	while(prod != NULL)
	{
		printf("ID Produto: %d\n",prod->IDProduto);
		printf("Quantidade: %d\n", prod->quantidade);
		printf("Coordenadas: Corredor->%d    Armario->%d\n", prod->corredor, prod->armario);
		prod = prod->proximo;
	}
}

void MostraProdutobyQuantidade(pno prod, int Quantidade)
{
	while(prod != NULL && prod->quantidade != Quantidade)
	{
		prod = prod->proximo;
	}
		printf("\nProdutos Encontrados:\n\n");
		printf("ID Produto: %d\n",prod->IDProduto);
		printf("Quantidade: %d\n", prod->quantidade);
		printf("Coordenadas: Corredor->%d    Armario->%d\n\n", prod->corredor, prod->armario);
}

pno EliminaProd(pno prod, int ProdID)
{
	pno actual, anterior = NULL;
	actual = prod;

	while(actual != NULL && actual->IDProduto != ProdID) //percorre toda a lista ate encontrar o ProdID passado por parametro
	{
		anterior = actual;
		actual = actual->proximo;
	}

	if(actual==NULL)
		return prod;
	if(anterior==NULL)
		prod = actual->proximo;
	else
		anterior->proximo = actual->proximo;

	free(actual);
	return prod;
}

void ApagaStruct(pno prod)
{
	pno aux;

	while(prod != NULL)
	{
		aux = prod;
		prod = prod->proximo;
		free(aux);
	}
}

void GuardaStruct(pno prod)
{
	FILE *RetailFile;
	char *buffer={NULL};

	RetailFile = OpenStorageFile(&RetailFile, RETAIL_FILE_NAME);
	buffer = BufferSpaceAlloc(&RetailFile, buffer);

	while(prod != NULL)
	{
		fwrite(prod, sizeof(produto), 1, RetailFile);
		prod = prod->proximo;
	}
	fclose(RetailFile);
}