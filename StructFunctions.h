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

pno AdicionaProdutoAtCoords(pno prod,int IDProduto, int Quantidade, int corredor, int armario)
{
	pno novo, aux;
	novo = malloc(sizeof(produto));

	if(novo == NULL)
	{
		printf("Erro na alocacao de memoria!\n");
		return prod;
	}

	preenche(novo, IDProduto, Quantidade, corredor, armario);

	if(prod == NULL || (novo->corredor && novo->armario) < (prod->armario && prod->corredor))
	{
		novo->proximo = prod;
		prod = novo;
	} else {
		aux = prod;
		while (aux->proximo != NULL && (novo->corredor && novo->armario) > (aux->proximo->corredor &&aux->proximo->armario))  
			aux = aux->proximo;
		novo->proximo = aux->proximo;
		aux->proximo = novo;
	}
	return prod;
}

pno InitializeRetailWarehouse(pno ListaProdutos, FILE *RetailFile)
	{
		int NCorredores, NArmarios, NProdutos_p_Armario, cArmario=1, cCorredor=1;   //vars do armazem
		int i, j, h;																//vars dos for's

		fread(&NArmarios, sizeof(int), 1, RetailFile);   //Obtem numero de armarios
		fread(&NCorredores, sizeof(int), 1, RetailFile); //Obtem numero de corredores
	
		for (i = 0; i < NCorredores; i++) { //5
			for (h = 0; h < NArmarios; h++) { //3
				fread(&NProdutos_p_Armario, sizeof(int), 1, RetailFile);
				for(j = 0; j < NProdutos_p_Armario; j++) { 
					//Guarda dados na struct
					ListaProdutos=AdicionaProduto(ListaProdutos, GetData(RetailFile), GetData(RetailFile), cCorredor, cArmario);
				}
				cArmario++;
				if (cArmario >= 4)
				{
					cArmario = 1;
					cCorredor++;
				}
			}
		}
		return ListaProdutos;
	}

int ObtemCoordsLivres()
{
	int i, j, h, inicial=2, lixo, NCorredores, NArmarios, NProdutos_p_Armario=10, fim=10, cArmario=1, cCorredor=1;
	FILE *file;
	char coords[2];

	file=OpenFile(&file, RETAIL_FILE_NAME, "r");
	
	fread(&NArmarios, sizeof(int), 1, file);
	fread(&NCorredores, sizeof(int), 1, file); 

	for(i = 0; i < NCorredores; i++){
		for(j = 0; j < NArmarios; j++){
			fread(&NProdutos_p_Armario, sizeof(int), 1, file);
			for(h = 0; h < NProdutos_p_Armario; h++) {
				fread(&lixo, sizeof(int), 1, file);
				fread(&lixo, sizeof(int), 1, file);
			}
			cArmario++;
				if (cArmario >= 4)
				{
					cArmario = 1;
					cCorredor++;
				}

			if(fim > NProdutos_p_Armario){
				fim = NProdutos_p_Armario;
				coords[0]=cCorredor;
				coords[1]=cArmario-1;
			}
			
		}
		
	}
	fclose(file);
	fim=concatena(coords[0], coords[1]);
	return fim;
}

/* Mostra na Consola */

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
			printf("\nProduto Encontrado:\n\nCorredor: %d\nArmario: %d\n\n", corredor, armario);
			printf("ID Produto: %d\n",prod->IDProduto);
			printf("Quantidade: %d\n", prod->quantidade);
		}
		prod = prod->proximo;

		if(prod == NULL)
		{
			printf("\nProduto nao encontrado ou lista chegou ao fim!\n");
			return;
		}
	}

}

void MostraProdutobyCorredor(pno prod, int corredor)
{
	while(prod != NULL)
	{
		if(prod->corredor == corredor) {
			printf("\nProduto Encontrado:\n\nCorredor: %d\n\n", corredor);
			printf("ID Produto: %d\n",prod->IDProduto);
			printf("Quantidade: %d\n", prod->quantidade);
		}
		prod = prod->proximo;

		if(prod == NULL)
		{
			printf("\nProduto nao encontrado ou lista chegou ao fim!\n");
			return;
		}
	}
}

void MostraProdutobyArmario(pno prod, int armario)
{
	while(prod != NULL)
	{
		if(prod->armario == armario) {
			printf("\nProduto Encontrado:\n\nArmario: %d\n\n", armario);
			printf("ID Produto: %d\n",prod->IDProduto);
			printf("Quantidade: %d\n", prod->quantidade);
		}
		prod = prod->proximo;

		if(prod == NULL)
		{
			printf("\nProduto nao encontrado ou lista chegou ao fim!\n");
			return;
		}
	}
}

/* Escreve para Ficheiro de Texto */

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
		fprintf(file, "ID: %d\nQuantidade: %d\n", prod->IDProduto, prod->quantidade);
		fprintf(file, "Coordenadas: Corredor->%d    Armario->%d\n\n", prod->corredor, prod->armario);
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

	fprintf(file, "\tResultado da Pesquisa\n\nCorredor: %d\nArmario: %d\n\n", corredor, armario);

	while(prod != NULL)
	{
		if(prod->corredor == corredor && prod->armario == armario) {
			fprintf(file, "ID Produto: %d\n",prod->IDProduto);
			fprintf(file, "Quantidade: %d\n\n", prod->quantidade);
		}
		prod = prod->proximo;

		if(prod == NULL)
		{
			printf("\nProduto nao encontrado ou lista chegou ao fim!\n");
		}
	}

	fprintf(file, "\n\n%s", c_DataActual);

	fclose(file);

	printf("\nFicheiro %s criado com sucesso.\n\n", filename);

}

void GuardaPesquisabyCorredor(pno prod, char *filename, int corredor)
{
	FILE *file;
	time_t DataActual;
	char* c_DataActual;
	char *ext=".txt";

	DataActual = time(NULL);
	c_DataActual = ctime(&DataActual);
	
	strcat(filename, ext);
	
	file = OpenFile(&file, filename, "a+");

	fprintf(file, "\tResultado da Pesquisa\n\nCorredor: %d\n\n", corredor);

	while(prod != NULL)
	{
		if(prod->corredor == corredor) {
			fprintf(file, "ID Produto: %d\n",prod->IDProduto);
			fprintf(file, "Quantidade: %d\n\n", prod->quantidade);
		}
		prod = prod->proximo;

		if(prod == NULL)
		{
			printf("\nProduto nao encontrado ou lista chegou ao fim!\n");
		}
	}

	fprintf(file, "\n\n%s", c_DataActual);

	fclose(file);

	printf("\nFicheiro %s criado com sucesso.\n\n", filename);
}

void GuardaPesquisabyArmario(pno prod, char *filename, int armario)
{
	FILE *file;
	time_t DataActual;
	char* c_DataActual;
	char *ext=".txt";

	DataActual = time(NULL);
	c_DataActual = ctime(&DataActual);
	
	strcat(filename, ext);
	
	file = OpenFile(&file, filename, "a+");

	fprintf(file, "\tResultado da Pesquisa\n\nArmario: %d\n\n", armario);

	while(prod != NULL)
	{
		if(prod->armario == armario) {
			fprintf(file, "ID Produto: %d\n",prod->IDProduto);
			fprintf(file, "Quantidade: %d\n\n", prod->quantidade);
		}
		prod = prod->proximo;

		if(prod == NULL)
		{
			printf("\nProduto nao encontrado ou lista chegou ao fim!\n");
		}
	}

	fprintf(file, "\n\n%s", c_DataActual);

	fclose(file);

	printf("\nFicheiro %s criado com sucesso.\n\n", filename);
}

/* Gestão de Stocks */

pno ReporStocks(pno prod, char *filename)
{
	FILE *file;
	pno novo, aux;
	char *lixo={NULL};
	int id, quantidade, valor, armario, corredor;
	char *ext=".txt";	
	strcat(filename, ext);

	novo=malloc(sizeof(pno));

	file = OpenFile(&file, filename, "r");

	lixo = BufferSpaceAlloc(&file, lixo);
	
	while (!feof(file))
	{

		fscanf(file, "%d%s%d", &id, lixo, &quantidade);
		printf("ID: %d\nQNT: %d\n\n", id, quantidade);

		while (prod != NULL && prod->IDProduto != id)
			prod = prod -> proximo;
		
		if(prod != NULL)
		{
			printf("Existe!\n");
			//prod->quantidade = prod->quantidade + quantidade; //produto existe, adiciona nova quantidade
			//return prod;
		} else {
			printf("Nao Existe!\n");
			valor = ObtemCoordsLivres();
			corredor = valor/10;
			armario = valor%10;

			preenche(novo, id, quantidade, corredor, armario);

			if(verifica_lista(prod))
				prod = novo;
			else {
				aux = prod;
				while(aux->proximo != NULL)
					aux = aux->proximo;
				aux->proximo = novo;
			}
		}
	}
	fclose(file);
	return prod;
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