/*
structfunctions.h

Vale das Flores Retail
DEIS @ ISEC 2013

Fábio Fonseca - 21210424
Nuno Silva - 21220170

Fcheiro header com funções das listas ligadas e definição da struct / lista ligadas
*/
typedef struct produto produto, *pno;
struct produto
{
    int IDProduto;
    int quantidade;
    int corredor;
    int armario;
    pno proximo;
};

/* Inicializações & Inserções */

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
    for (i = 0; i < NCorredores; i++)   //percorre os corredores
        {
            for (h = 0; h < NArmarios; h++)   //percorre os armarios
                {
                    fread(&NProdutos_p_Armario, sizeof(int), 1, RetailFile); //obtem o nº de produtos por armario
                    for(j = 0; j < NProdutos_p_Armario; j++)   //percore o nº de produtos por armario
                        {
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

    for(i = 0; i < NCorredores; i++)
        {
            for(j = 0; j < NArmarios; j++)
                {
                    fread(&NProdutos_p_Armario, sizeof(int), 1, file);
                    for(h = 0; h < NProdutos_p_Armario; h++)
                        {
                            fread(&lixo, sizeof(int), 1, file);
                            fread(&lixo, sizeof(int), 1, file);
                        }
                    cArmario++;
                    if (cArmario >= 4)
                        {
                            cArmario = 1;
                            cCorredor++;
                        }
                    if(fim > NProdutos_p_Armario)  //compara n_produtos_por_armario com ultima leitura
                        {
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
    while(prod != NULL) //enquanto a lista nao chegar ao fim
        {
            printf("ID Produto: %d\n",prod->IDProduto);
            printf("Quantidade: %d\n", prod->quantidade);
            printf("Coordenadas: Corredor->%d    Armario->%d\n", prod->corredor, prod->armario);
            prod = prod->proximo;
        }
}

void MostraProdutobyQuantidade(pno prod, int Quantidade)
{
    printf("Quantidade: %d\n", Quantidade);
    while(prod != NULL) //enquanto a lista nao chegar ao fim
        {
            if(prod->quantidade == Quantidade)
                {
                    printf("\nProduto Encontrado:\n\n"); //se encontrar o corredor
                    printf("ID Produto: %d\n",prod->IDProduto);
					printf("Corredor: %d\n", prod->corredor);
                    printf("Armario: %d\n\n", prod->armario);
                }
            prod = prod->proximo; //aponta para o proximo nó (produto) da lista

            if(prod == NULL)
                {
                    printf("\nProduto nao encontrado ou lista chegou ao fim!\n");
                    return;
                }
        }
}

void MostraProdutobyCoordenadas(pno prod, int corredor, int armario)
{
    printf("Corredor: %d\nArmario: %d\n", corredor, armario);
    while(prod != NULL) //enquanto a lista nao chegar ao fim
        {
            if(prod->corredor == corredor && prod->armario == armario)   //se encontrar o armario e corredor
                {
                    printf("\nProduto Encontrado:\n\n");
                    printf("ID Produto: %d\n",prod->IDProduto);
                    printf("Quantidade: %d\n", prod->quantidade);
                }
            prod = prod->proximo; //aponta para o proximo nó (produto) da lista

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
    while(prod != NULL) //enquanto a lista nao chegar ao fim
        {
            if(prod->corredor == corredor)
                {
                    printf("\nProduto Encontrado:\n\n"); //se encontrar o corredor
                    printf("ID Produto: %d\n",prod->IDProduto);
                    printf("Quantidade: %d\n\n", prod->quantidade);
                }
            prod = prod->proximo; //aponta para o proximo nó (produto) da lista

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
    while(prod != NULL) //enquanto a lista nao chegar ao fim
        {
            if(prod->armario == armario)   //se encontrar o armario
                {
                    printf("\nProduto Encontrado:\n\n");
                    printf("ID Produto: %d\n",prod->IDProduto);
                    printf("Quantidade: %d\n", prod->quantidade);
                    printf("Corredor: %d\n\n", prod->corredor);
                }
            prod = prod->proximo; //aponta para o proximo nó (produto) da lista

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

    DataActual = time(NULL); //obtem a data actual
    c_DataActual = ctime(&DataActual); //formata a data

    strcat(filename, ext); //concatena o nome do ficheiro com a extensao

    file = OpenFile(&file, filename, "a+"); //abre o ficheiro

    fprintf(file, "\tResultado da Pesquisa\n\n");

    while(prod != NULL) //enquanto a lista nao chegar ao fim
        {
            fprintf(file, "ID: %d\nQuantidade: %d\n", prod->IDProduto, prod->quantidade);
            fprintf(file, "Coordenadas: Corredor->%d    Armario->%d\n\n", prod->corredor, prod->armario);
            prod = prod->proximo; //aponta para o proximo nó (produto) da lista
        }


    fprintf(file, "\n\n%s", c_DataActual); //escreve a data

    fclose(file); //fecha o ficheiro

    printf("\nFicheiro %s criado com sucesso.\n\n", filename);
}

void GuardaPesquisabyQnt(pno prod, char *filename, int Quantidade)
{

    FILE *file;
    time_t DataActual;
    char* c_DataActual;
    char *ext=".txt";

    DataActual = time(NULL); //obtem a data actual
    c_DataActual = ctime(&DataActual); //formata a data

    strcat(filename, ext); //concatena o nome do ficheiro com a extensao

    file = OpenFile(&file, filename, "a+"); //abre o ficheiro

    fprintf(file, "\tResultado da Pesquisa\n\n");

    fprintf(file, "Quantidade: %d\n", Quantidade);
    while(prod != NULL) //enquanto a lista nao chegar ao fim
        {
            if(prod->quantidade == Quantidade) //se encontrar a quantidade do parametro na lista:
                {
                    fprintf(file, "ID Produto: %d\n",prod->IDProduto);
					fprintf(file, "Corredor: %d\n", prod->corredor);
                    fprintf(file, "Armario: %d\n\n", prod->armario);
                }
            prod = prod->proximo; //aponta para o proximo nó (produto) da lista

            if(prod == NULL)
                {
                    fprintf(file, "\nProduto nao encontrado ou lista chegou ao fim!\n");
                    return;
                }
        }

	fprintf(file, "\n%s", c_DataActual); //escreve a data

    fclose(file); //fecha o ficheiro

    printf("\nFicheiro %s criado com sucesso.\n\n", filename);
}

void GuardaPesquisabyCoordenadas(pno prod, char *filename, int corredor, int armario)
{
    FILE *file;
    time_t DataActual;
    char* c_DataActual;
    char *ext=".txt";

    DataActual = time(NULL); //obtem a data actual
    c_DataActual = ctime(&DataActual); //formata a data

    strcat(filename, ext); //concatena o nome do ficheiro com a extensao

    file = OpenFile(&file, filename, "a+"); //abre o ficheiro

    fprintf(file, "\tResultado da Pesquisa\n\nCorredor: %d\nArmario: %d\n\n", corredor, armario);

    while(prod != NULL) //enquanto a lista nao chegar ao fim
        {
            if(prod->corredor == corredor && prod->armario == armario)   //se encontrar o prdotudo
                {
                    fprintf(file, "ID Produto: %d\n",prod->IDProduto);
                    fprintf(file, "Quantidade: %d\n\n", prod->quantidade);
                }
            prod = prod->proximo;  //aponta para o proximo nó (produto) da lista

            if(prod == NULL)
                {
                    printf("\nProduto nao encontrado ou lista chegou ao fim!\n");
                }
        }

    fprintf(file, "\n\n%s", c_DataActual); //escreve a data no fim do ficheiro

    fclose(file); //fecha ficheiro

    printf("\nFicheiro %s criado com sucesso.\n\n", filename);

}

void GuardaPesquisabyCorredor(pno prod, char *filename, int corredor)
{
    FILE *file;
    time_t DataActual;
    char* c_DataActual;
    char *ext=".txt";

    DataActual = time(NULL); //obtem a data actual
    c_DataActual = ctime(&DataActual); //formata a data

    strcat(filename, ext); //concatena o nome do ficheiro com a extensao

    file = OpenFile(&file, filename, "a+"); //abre o ficheiro

    fprintf(file, "\tResultado da Pesquisa\n\nCorredor: %d\n\n", corredor);

    while(prod != NULL) //enquanto a lista nao chegar ao fim
        {
            if(prod->corredor == corredor)   //se encontrar o corredor
                {
                    fprintf(file, "ID Produto: %d\n",prod->IDProduto);
                    fprintf(file, "Quantidade: %d\n\n", prod->quantidade);
                }
            prod = prod->proximo; //aponta para proximo produto

            if(prod == NULL)
                {
                    printf("\nProduto nao encontrado ou lista chegou ao fim!\n");
                }
        }

    fprintf(file, "\n\n%s", c_DataActual); //escreve a data

    fclose(file); //fecha ficheiro

    printf("\nFicheiro %s criado com sucesso.\n\n", filename);
}

void GuardaPesquisabyArmario(pno prod, char *filename, int armario)
{
    FILE *file;
    time_t DataActual;
    char* c_DataActual;
    char *ext=".txt";

    DataActual = time(NULL); //obtem a data actual
    c_DataActual = ctime(&DataActual); //formata a data

    strcat(filename, ext); //concatena o nome do ficheiro com a extensao

    file = OpenFile(&file, filename, "a+"); //abre o ficheiro

    fprintf(file, "\tResultado da Pesquisa\n\nArmario: %d\n\n", armario);

    while(prod != NULL) //enquanto a lista nao chegar ao fim
        {
            if(prod->armario == armario)   //se encontrar o armario
                {
                    fprintf(file, "ID Produto: %d\n",prod->IDProduto);
                    fprintf(file, "Quantidade: %d\n\n", prod->quantidade);
                }
            prod = prod->proximo; //aponta para o proximo produto

            if(prod == NULL)
                {
                    printf("\nProduto nao encontrado ou lista chegou ao fim!\n");
                }
        }

    fprintf(file, "\n\n%s", c_DataActual); //escreve data

    fclose(file); //fecha ficheiro

    printf("\nFicheiro %s criado com sucesso.\n\n", filename);
}

/* Gestao de Encomendas */

pno EliminaProd(pno prod, pno lista_auxiliar, int ProdID)
{
    pno actual, anterior = NULL;
    actual = lista_auxiliar;

    while(actual != NULL && actual->IDProduto != ProdID) //percorre toda a lista ate encontrar o ProdID passado por parametro
        {
            anterior = actual;
            actual = actual->proximo;
        }
    if(actual==NULL)
		{
			return;
		}
    if(anterior==NULL)
		{
			prod = actual->proximo;
		}
	else
		{
			anterior->proximo = actual->proximo;
		}

	free(actual);
	return;
}

void ActualizaProdutos(pno prod, int id, int quantidade, pno lista_auxiliar)
{
	FILE *file;
	int temp_qnt, temp_id;
	while (prod != NULL) //enquanto a lista nao chegar ao fim (estiver nula)
        {
            if(prod->IDProduto == id) //compara os ids com o id passado por parametro
                {
                    if(prod->quantidade >= quantidade) //produto existe, verifica stock
						{
							temp_qnt = prod->quantidade;
							temp_id = prod->IDProduto;
							//stock suficiente, actualiza novo stock
							prod->quantidade -= quantidade;
							if(prod->quantidade <= 0)
								{
									EliminaProd(prod, lista_auxiliar, id);
									file = OpenFile(&file, "RelatorioVendas.txt", "a+"); //abre o ficheiro
									fprintf(file, "\t\tRelatorio de Vendas\n\n");
									fprintf(file, "Foram vendidas %d unidades do produto %d\n", temp_qnt, temp_id);
									fclose(file);
									return;
								}
							return;
						}
                }
            prod = prod -> proximo; //passa para o proximo produto da lista
        }
}

int VerificaProduto(pno prod, int id)
{
	pno lista_inicio = prod;

    while (prod != NULL) //enquanto a lista nao chegar ao fim (estiver nula)
        {
            if(prod->IDProduto == id) //compara os ids com o id passado por parametro
                {
					return 1;
                }
            prod = prod -> proximo; //passa para o proximo produto da lista
        }
    prod = lista_inicio->proximo; //aponta a lista para o primeiro produto
	printf("Produto %d inexistente!\n", id);
	return 0; //nao encontra produto
}

int VerificaQuantidade(pno prod,int id, int quantidade)
{
    while (prod != NULL) //enquanto a lista nao chegar ao fim (estiver nula)
        {
            if(prod->IDProduto == id) //compara os ids com o id passado por parametro
                {
					if(prod->quantidade >= quantidade) //verifica se existe quantidade suficiente em stock
						{
							return 1;
						}
                }
            prod = prod -> proximo; //passa para o proximo produto da lista
        }
	printf("Quantidade em stock do produto %d insuficiente!\n", id);
	printf("Tem %d e precisa %d\n\n", prod->quantidade, quantidade);
	return 0; //quantidade insuficiente
}

void ProcessaEncomenda(const char *filename, pno prod, pno lista_auxiliar)
{
	FILE *file;
	char *lixo={NULL};
	char *ext=".txt";
	char *nomeEncomenda={NULL};
	int id, quantidade, n_erros=0;
	pno lista_inicio = prod;

	CLEAR_SCREEN();

    strcat(filename, ext); //concatena o nome do ficheiro passado por parametro com a extensão

	file = OpenFile(&file, filename, "r");

	lixo = BufferSpaceAlloc(&file, lixo); //aloca o espaço necessario
	nomeEncomenda = BufferSpaceAlloc(&file, nomeEncomenda); //aloca espaço necessario

	fscanf(file, "%s %s", nomeEncomenda, lixo); //obtem nome da encomenda

	printf("\nA Processar %s %s\n\n", nomeEncomenda, lixo);
	_sleep(2000);
    while (!feof(file)) //enquanto nao for fim do ficheiro:
        {
            fscanf(file, "%d%s%d", &id, lixo, &quantidade);
			
			if(VerificaProduto(prod, id)==0) //verifica se o produto existe
				{
					n_erros++;
				}
			prod = lista_inicio; //coloca lista no primeiro nó
			if(VerificaQuantidade(prod, id, quantidade)==0) //verifica se tem quantidade suficiente
				{
					n_erros++;
				}
			prod = lista_inicio; //coloca lista no primeiro nó
        }

	if(n_erros > 0)
		{
			printf("\nNota de encomenda nao processada!\n\n");
			return;
		}
	fseek(file, 0, SEEK_SET); //coloca o ponteiro no inicio do ficheiro
	fscanf(file, "%s %s", nomeEncomenda, lixo);
	while (!feof(file)) //enquanto nao for fim do ficheiro:
        {
            fscanf(file, "%d%s%d", &id, lixo, &quantidade);
			ActualizaProdutos(prod, id, quantidade, lista_auxiliar);
			prod = lista_inicio;
        }
    fclose(file); //fecha ficheiro
	printf("\nEncomenda processada com sucesso!\n\n\n");
	return;
}

/* Gestão de Stocks */

void ActualizaStock(pno prod, int id, int quantidade)
{
    int valor, corredor, armario, insercoes;
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
    char *lixo= {NULL};
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
	printf("\nStocks actualizados com sucesso!\n\n");
}

/* Outras Operações */

void CleanMemoryErrors(pno prod, pno lista_auxiliar)
{
	while(prod != NULL)
	{
		if(prod->quantidade <= 0)
			{
				EliminaProd(prod, lista_auxiliar, prod->IDProduto);
				prod = lista_auxiliar;
			}
		prod = prod->proximo;
	}
	
}

int ObtemTotalCorredores(pno prod)
{
    int cont;
    while ( prod != NULL )
        {
            cont = prod->corredor;
            prod = prod->proximo;
        }
    return cont;
}

int ObtemTotalArmarios(pno prod)
{
    int cont;
    while ( prod != NULL )
        {
            cont = prod->armario;
            prod = prod->proximo;
        }
    return cont;
}

int ObtemNProdutos_p_ArmarioInicial(pno prod, int search_armario)
{
    int cont=0, end, iteracoes=0;

    while ( prod != NULL )
        {
            if(prod->armario == search_armario)
                {
                    cont++;
                }
            else
                {
                    end=concatena(iteracoes, cont);
                    return end;
                }
            prod = prod->proximo;
            iteracoes++;
        }
}

int ObtemNProdutos_p_Armario(pno prod, int search_armario, int iteracoes)
{
    int cont=0, end;

    while ( prod != NULL )
        {
            iteracoes++;
            if(prod->armario == search_armario)
                {
                    cont++;
                }
            else
                {
                    end=concatena(iteracoes, cont);
                    return end;
                }
            prod = prod->proximo;
        }
}

/* Actualizar Ficheiro */

void ActualizaBIN(pno prod)
{
    int NProdutos_p_Armario;   //vars do armazem
    int i, j, h, NCorredores, NArmarios, search_armario=1, x=0, iteracoes;																//vars dos for's
    FILE *RetailFile;
    pno inicio = prod;

    NCorredores = ObtemTotalCorredores(prod);
    NArmarios = ObtemTotalArmarios(prod);

    RetailFile = OpenFile(&RetailFile, RETAIL_FILE_NAME, "wb"); //abre ficheiro para leitura

    fwrite(&NArmarios, sizeof(int), 1, RetailFile);
    fwrite(&NCorredores, sizeof(int), 1, RetailFile);

    /* Algoritmo para leitura do ficheiro binário */
    for (i = 0; i < NCorredores; i++)   //percorre os corredores
        {
            for (h = 0; h < NArmarios; h++)   //percorre os armarios
                {
                    if(x==0)
                        {
                            //1ª iteração
                            NProdutos_p_Armario = ObtemNProdutos_p_ArmarioInicial(prod, search_armario);
                            iteracoes = NProdutos_p_Armario/10;
                            NProdutos_p_Armario= NProdutos_p_Armario%10;
                            x++;
                        }
                    else
                        {
                            //outras iterações
                            search_armario++;
                            if (search_armario >= 4)
                                {
                                    search_armario=0;
                                    search_armario++;
                                }
                            NProdutos_p_Armario = ObtemNProdutos_p_Armario(prod, search_armario, iteracoes);
                            iteracoes = NProdutos_p_Armario/10;
                            NProdutos_p_Armario= NProdutos_p_Armario%10;
                        }
                    fwrite(&NProdutos_p_Armario, sizeof(int), 1, RetailFile); // escreve nº de produtos por armario
                    for(j = 0; j < NProdutos_p_Armario; j++)   //percore o nº de produtos por armario
                        {
                            //Escreve no ficheiro
                            fwrite(&prod->quantidade, sizeof(int), 1, RetailFile);
                            fwrite(&prod->IDProduto, sizeof(int), 1, RetailFile);
                            prod = prod->proximo;
							if(prod == NULL)
							{
								fclose(RetailFile);
								printf("\nVendas actualizadas com sucesso no ficheiro %s.\n\n", RETAIL_FILE_NAME);
								return;
							}
                        }
						
                }
        }
    fclose(RetailFile); //fecha o ficheiro
    printf("\nVendas actualizadas com sucesso no ficheiro %s.\n\n", RETAIL_FILE_NAME);
	return;
}

void ReportSales(pno prod, pno lista_comparacao)
{
	FILE *file;
	int diferenca;
	time_t DataActual;
    char* c_DataActual;

    DataActual = time(NULL); //obtem a data actual
    c_DataActual = ctime(&DataActual); //formata a data

	file = OpenFile(&file, "RelatorioVendas.txt", "a+"); //abre o ficheiro

	while(lista_comparacao != NULL) //enquanto houver produtos
		{
			while(lista_comparacao->IDProduto != prod->IDProduto) //se os ids dos produtos diferirem
				{
					lista_comparacao = lista_comparacao->proximo; //avança para o proximo produto
				}
			if(lista_comparacao->quantidade != prod->quantidade) //se houve alteracao na quantidade
				{
					if(lista_comparacao->quantidade > prod->quantidade) //se foram vendidos produtos
						{
							//calcula diferença
							diferenca = lista_comparacao->quantidade - prod->quantidade ;
							fprintf(file, "Foram vendidas %d unidades do produto %d\n", diferenca, prod->IDProduto);
						}
				}
			lista_comparacao = lista_comparacao->proximo;
			prod = prod->proximo;
		}
	fprintf(file, "\n%s\n", c_DataActual);
	fclose(file);
	printf("Foi gerado um relatorio de vendas chamado 'RelatorioVendas.txt'.\n");
	return;
}