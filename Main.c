#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include <direct.h>
#include "Displays.h"
#include "FileFunctions.h"
#include "StructFunctions.h"

#pragma region Declaração_De_Variáveis
	pno ListaProdutos = NULL;																	//struct da lista de produtos
	FILE *RetailFile;																			//ficheiro do armazem/retail.bin
	char *buffer={NULL};																		//buffer para leitura do ficheiro
	char filename[256];
	typedef enum {
		ver=1, 
		gerir=2, 
		stocks=3, 
		configuracoes=4, 
		sair_menu=5
	} RespostaMenu;			
	RespostaMenu answer_menu;

	typedef enum {
		total=1, 
		corredor=2, 
		armario=3, 
		coordenadas=4, 
		quantidade=5, 
		sair_ver=6} 
	RespostaVer;
	RespostaVer answer_ver;

	int qnt, search_corredor, search_armario, DisplayMode;
#pragma endregion

int main()
{
	DisplayMode=GetDisplayMode();
	printf("Display: %d\n", DisplayMode);
	//UpdateSession(CONFIG_FILE_NAME);
	/*Abre o ficheiro de retail*/
	RetailFile = OpenFile(&RetailFile, RETAIL_FILE_NAME, "rb");
	/* Aloca Espaço necessario no buffer*/
	buffer = BufferSpaceAlloc(&RetailFile, buffer);
	/* Preenche a lista dos produtos lendo o ficheiro de retail */
	ListaProdutos=InitializeRetailWarehouse(ListaProdutos, RetailFile);
	/* fecha o ficheiro */
	fclose(RetailFile);
	

	/*			Corredor 1
		3P 2unidades 4 4unidades 7 78unidades 1	
		2P 55unidades 2 45unidades 12 
		1P 9unidades 2

				Corredor 2
		2P 3unidades 3 12unidades 2
		3P 20unidades 1 21unidades 2 22unidades 1
		1P 30unidade 5

				Corredor 3
		2P 1unidades 34 6unidades 23
		3P 46unidades 4 42unidades 4 7unidades 7
		1P 74unidades 4

				Corredor 4
		0P
		1P 48unidades 5
		3P 17unidades 1 18unidades 1 19unidades 1

				Corredor 5
		3P 24unidades 3 34unidades 4 37unidades 5
		1P 50unidades 5
		2P 57unidades 3 58unidades 3

	*/
		
	DisplayMenu();
		do {
			printf("Introduza uma opcao valida:\n");
			scanf("%d", &answer_menu);
			switch(answer_menu)
			{
			case ver:
				system("CLS");
				DisplayMenuVisualizacoes();
				do{
					printf("Insere uma opcao valida:\n");
					scanf("%d", &answer_ver);
					switch(answer_ver)
					{
					case total:
						if(DisplayMode==1){
							MostraProdutos(ListaProdutos);
							DisplayMenuVisualizacoes();
						}else{
							printf("Introduza o nome do ficheiro sem extensao: ");
							scanf("%s", &filename);
							GuardaPesquisaTotal(ListaProdutos, filename);
							printf("\n");
							DisplayMenuVisualizacoes();
						}
						break;
					case corredor:
						break;
					case armario:
						break;
					case coordenadas:
						printf("Insere o numero do corredor: ");
						scanf("%d", &search_corredor);
						printf("\nInsere o numero do armario: ");
						scanf("%d", &search_armario);
						if(DisplayMode==1){
							MostraProdutobyCoordenadas(ListaProdutos, search_corredor, search_armario);
						} else {
							printf("Introduza o nome do ficheiro sem extensao: ");
							scanf("%s", &filename);
							GuardaPesquisabyCoordenadas(ListaProdutos, filename, search_corredor, search_armario);
							printf("\n");
							DisplayMenuVisualizacoes();
						}
						break;
					case quantidade:
						printf("\nIntroduz a quantidade do produto:");
						scanf("%d", &qnt);
						if(DisplayMode==1){
							MostraProdutobyQuantidade(ListaProdutos, qnt);
						} else {
							printf("Introduza o nome do ficheiro sem extensao: ");
							scanf("%s", &filename);
							GuardaPesquisabyID(ListaProdutos, filename, qnt);
							printf("\n");
							DisplayMenuVisualizacoes();
						}
						break;
					}
				}while(answer_ver != sair_ver);
				break;
			case gerir:
				system("CLS");
				DisplayMenuEncomendas();
				break;
			case stocks:
				DisplayMenuStocks();
				break;
			case configuracoes:
				DisplayMenuConfiguracoes();
				
			}
		} while (answer_menu != sair_menu);
		printf("Ate uma proxima!\n");
}