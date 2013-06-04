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
	if (prod == NULL) //verifica se a lista está vazia
		return 1;
	else
		return 0;
}

void preenche(pno prod, int IDProduto, int Quantidade, int corredor, int armario)
{
	//preenche a varias com dados passados por argumentos
	prod->IDProduto=IDProduto;
	prod->quantidade=Quantidade;
	prod->corredor=corredor;
	prod->armario=armario;
	prod->proximo = NULL;
}

pno AdicionaProduto(pno prod,int IDProduto, int Quantidade, int corredor, int armario)
{
	pno novo, aux;
	novo = malloc(sizeof(produto)); //aloca espaço

	if(novo == NULL) //verifica se alocou o espaço com sucesso
	{
		printf("Erro na alocacao de memoria!\n");
		return prod;
	}

	preenche(novo, IDProduto, Quantidade, corredor, armario); //preenche os campos do nó a ser inserido

	if(verifica_lista(prod)) 
	{
		prod = novo; //se a lista estiver vazia / for nova, entao insere no topo da lista
	}
	else
	{
			//senao insere no fim da lista
			aux = prod;
			while(aux->proximo != NULL)
				aux = aux->proximo;
			aux->proximo = novo;
	}
	return prod;
}

pno AdicionaProdutoBetween(pno prod,int IDProduto, int Quantidade, int corredor, int armario)
{
	pno novo, aux;
	novo = malloc(sizeof(produto)); //aloca espaço

	if(novo == NULL) //verifica se alocou o espaço com sucesso
	{
		printf("Erro na alocacao de memoria!\n");
		return prod;
	}

	preenche(novo, IDProduto, Quantidade, corredor, armario); //preenche os campos do nó a ser inserido

	if(prod == NULL || novo->corredor < prod->corredor) //se a lista estiver vazia OU o corredor do argumento for "menor" que o corredor da lista, insere no inicio
	{
		novo->proximo = prod;
		prod = novo;
	}
	else
	{
		//senao instroduz asseguir ao corredor passado por parametro
		aux = prod;
		while(aux->proximo != NULL && novo->corredor > aux->proximo->corredor)
			aux = aux->proximo;
		novo->proximo = aux->proximo;
		aux->proximo = novo;
	}
	return prod;
}

pno InitializeWarehouse(pno ListaProdutos)
	{
		int NCorredores, NArmarios, NProdutos_p_Armario, cArmario=1, cCorredor=1;   //vars do armazem
		int i, j, h;																//vars dos for's
		FILE *RetailFile;

		RetailFile = OpenFile(&RetailFile, RETAIL_FILE_NAME, "rb"); //abre ficheiro para leitura

		fread(&NArmarios, sizeof(int), 1, RetailFile);   //Obtem numero de armarios
		fread(&NCorredores, sizeof(int), 1, RetailFile); //Obtem numero de corredores
	
		/* Algoritmo para leitura do ficheiro binário */
		for (i = 0; i < NCorredores; i++) { //percorre os corredores
			for (h = 0; h < NArmarios; h++) { //percorre os armarios
				fread(&NProdutos_p_Armario, sizeof(int), 1, RetailFile); //obtem o nº de produtos por armario
				for(j = 0; j < NProdutos_p_Armario; j++) { //percore o nº de produtos por armario
					//Guarda dados na lista
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
		fclose(RetailFile); //fecha o ficheiro
		return ListaProdutos;
	}

int ObtemCoordsLivres()
{
	int i, j, h, inicial=2, lixo, NCorredores, NArmarios, NProdutos_p_Armario=10, fim=10, cArmario=1, cCorredor=1;
	FILE *file;
	char coords[2];

	file=OpenFile(&file, RETAIL_FILE_NAME, "r"); //abre o ficheiro
	
	fread(&NArmarios, sizeof(int), 1, file); //obtem n armarios
	fread(&NCorredores, sizeof(int), 1, file); //obtem n corredores

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
			if(fim > NProdutos_p_Armario){ //compara n_produtos_por_armario com ultima leitura
				fim = NProdutos_p_Armario;
				coords[0]=cCorredor; //armazena "coordenadas"
				coords[1]=cArmario-1; //armazena "coordenadas"
			}
		}
	}
	fclose(file); //fecha ficheiro
	fim=concatena(coords[0], coords[1]); //concatena os 2 ints (coordenadas)
	return fim; //devolve as coordenadas
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
	printf("Corredor: %d\nArmario: %d\n", corredor, armario);
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
			printf("\nProduto nao encontrado ou lista chegou ao fim!\n");
			return;
		}
	}

}

void MostraProdutobyCorredor(pno prod, int corredor)
{
	printf("Corredor: %d\n", corredor);
	while(prod != NULL)
	{
		if(prod->corredor == corredor) {
			printf("\nProduto Encontrado:\n\n");
			printf("ID Produto: %d\n",prod->IDProduto);
			printf("Quantidade: %d\n\n", prod->quantidade);
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
	printf("Armario: %d\n", armario);
	while(prod != NULL)
	{
		if(prod->armario == armario) {
			printf("\nProduto Encontrado:\n\n");
			printf("ID Produto: %d\n",prod->IDProduto);
			printf("Quantidade: %d\n", prod->quantidade);
			printf("Corredor: %d\n\n", prod->corredor);
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

void GuardaPesquisabyQnt(pno prod, char *filename, int Quantidade)
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

void ActualizaStock(pno prod, int id, int quantidade)
{
	int valor, corredor, armario;
	pno lista_inicio = prod;

	while (prod != NULL) //enquanto a lista nao chegar ao fim (estiver nula)
	{
		if(prod->IDProduto == id) //compara os ids com o id passado por parametro
		{
			prod->quantidade = prod->quantidade + quantidade; //produto existe, adiciona nova quantidade
			return;
		}
		prod = prod -> proximo; //passa para o proximo produto da lista
	}
	prod = lista_inicio->proximo; //aponta a lista para o primeiro produto
	valor = ObtemCoordsLivres(); //obtem coordenadas onde alocar novos produtos
	corredor = valor/10; //obtem o corredor
	armario = valor%10; //obtem o armario
	prod = AdicionaProdutoBetween(prod, id, quantidade, corredor, armario); //adiciona o novo produto
}

void ObtemStock(char *filename, pno prod)
{
	FILE *file;
	char *lixo={NULL};
	int id, quantidade, valor, armario, corredor;
	char *ext=".txt";	
	strcat(filename, ext); //concatena o nome do ficheiro passado por parametro com a extensão

	file = OpenFile(&file, filename, "r"); //abre o ficheiro

	lixo = BufferSpaceAlloc(&file, lixo); //aloca o espaço necessario

	while (!feof(file)) //enquanto nao for fim do ficheiro:
	{
		fscanf(file, "%d%s%d", &id, lixo, &quantidade); //obtem id e quantidade do ficheiro || Formato: "ID: QUANTIDADE"
		ActualizaStock(prod, id, quantidade);
	}
	fclose(file); //fecha ficheiro
}

/* Outras Operações */

void GuardaStruct(pno prod)
{
	FILE *RetailFile;

	RetailFile = OpenFile(&RetailFile, "save.bin", "wb");

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