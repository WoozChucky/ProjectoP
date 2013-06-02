#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<string.h>

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

	if(prod == NULL)
	{
		printf("\nProduto nao encontrado!\n");
		return;
	}
		printf("\nProdutos Encontrados:\n\n");
		printf("ID Produto: %d\n",prod->IDProduto);
		printf("Quantidade: %d\n", prod->quantidade);
		printf("Coordenadas: Corredor->%d    Armario->%d\n\n", prod->corredor, prod->armario);
}

void MostraProdutobyCoordenadas(pno prod, int corredor, int armario)
{

	while(prod != NULL)
	{
		if(prod->corredor == corredor && prod->armario == armario) {
			printf("\nProduto Encontrado:\n\n");
			printf("ID Produto: %d\n",prod->IDProduto);
			printf("Quantidade: %d\n", prod->quantidade);
		}
		prod = prod->proximo;

		if(prod == NULL)
		{
			printf("\nProduto nao encontrado!\n");
			return;
		}
	}

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

void GuardaPesquisaTotal(pno prod, char *filename)
{
	FILE *file;
	time_t DataActual;
	char* c_DataActual;
	char *ext=".txt";

	DataActual = time(NULL);
	c_DataActual = ctime(&DataActual);
	
	strcat(filename, ext);
	
	file = OpenFile(&file, filename, "a+");

	fprintf(file, "\tResultado da Pesquisa\n\n");

	while(prod != NULL)
	{
		fprintf(file, "ID: %d\nQuantidade: %d\n\n", prod->IDProduto, prod->quantidade);
		prod = prod->proximo;
	}

	
	fprintf(file, "\n\n%s", c_DataActual);

	fclose(file);

	printf("\nFicheiro %s criado com sucesso.\n\n", filename);
}

void GuardaPesquisabyID(pno prod, char *filename, int Quantidade)
{

	FILE *file;
	time_t DataActual;
	char* c_DataActual;
	char *ext=".txt";

	DataActual = time(NULL);
	c_DataActual = ctime(&DataActual);
	
	strcat(filename, ext);
	
	file = OpenFile(&file, filename, "a+");

	fprintf(file, "\tResultado da Pesquisa\n\n");

	while(prod != NULL && prod->quantidade != Quantidade)
	{
		prod = prod->proximo;
	}

	if(prod == NULL)
	{
		printf("\nProduto nao encontrado!\n");
		return;
	}

	fprintf(file, "ID: %d\nQuantidade: %d\n\n", prod->IDProduto, prod->quantidade);
	fprintf(file, "\n\n%s", c_DataActual);

	fclose(file);

	printf("\nFicheiro %s criado com sucesso.\n\n", filename);
}

void GuardaPesquisabyCoordenadas(pno prod, char *filename, int corredor, int armario)
{
	FILE *file;
	time_t DataActual;
	char* c_DataActual;
	char *ext=".txt";

	DataActual = time(NULL);
	c_DataActual = ctime(&DataActual);
	
	strcat(filename, ext);
	
	file = OpenFile(&file, filename, "a+");

	fprintf(file, "\tResultado da Pesquisa\n\n");

	while(prod != NULL)
	{
		if(prod->corredor == corredor && prod->armario == armario) {
			fprintf(file, "ID Produto: %d\n",prod->IDProduto);
			fprintf(file, "Quantidade: %d\n", prod->quantidade);
		}
		prod = prod->proximo;

		if(prod == NULL)
		{
			printf("\nProduto nao encontrado!\n");
		}
	}

	fprintf(file, "\n\n%s", c_DataActual);

	fclose(file);

	printf("\nFicheiro %s criado com sucesso.\n\n", filename);

}

void GuardaStruct(pno prod)
{
	FILE *RetailFile;

	RetailFile = OpenFile(&RetailFile, RETAIL_FILE_NAME, "rb");

	while(prod != NULL)
	{
		fwrite(prod, sizeof(produto), 1, RetailFile);
		prod = prod->proximo;
	}
	fclose(RetailFile);
}

pno InitializeRetailWarehouse(pno ListaProdutos, FILE *RetailFile)
	{
		int NCorredores, NArmarios, NProdutos_p_Armario, cArmario=1, cCorredor=1;   //vars do armazem
		int i, j, h;																//vars dos for's

		fread(&NArmarios, sizeof(int), 1, RetailFile);   //Obtem numero de armarios
		fread(&NCorredores, sizeof(int), 1, RetailFile); //Obtem numero de corredores
	
		for (i = 0; i < NCorredores; i++) {
			for (h = 0; h < NArmarios; h++) {
				fread(&NProdutos_p_Armario, sizeof(int), 1, RetailFile);
				for(j = 0; j < NProdutos_p_Armario; j++) { 
					//Guarda dados na struct
					ListaProdutos=AdicionaProduto(ListaProdutos, GetData(RetailFile), GetData(RetailFile), cCorredor, cArmario);
				}
				cArmario++;
				if (cArmario >= 4)
				{
					cArmario = 1;
				}
			
			}
			cCorredor++;
		}
		return ListaProdutos;
	}