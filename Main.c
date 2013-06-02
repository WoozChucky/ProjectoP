#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include "Displays.h"
#include "FileFunctions.h"
#include "StructFunctions.h"

#ifdef _WIN32
#    define CLEAR_SCREEN() system("cls")
#else
#    define CLEAR_SCREEN() system("clear")
#endif
#define LINE_BREAK() printf("\n");

#pragma region Declaração_De_Variáveis

	pno ListaProdutos = NULL;
	FILE *RetailFile;
	char *buffer={NULL};
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
		sair_ver=6
	} RespostaVer;
	RespostaVer answer_ver;

	typedef enum {
		alterar_display=1,
		sair_configs =2
	} RespostaConfigs;
	RespostaConfigs answer_configs;

	int qnt, search_corredor, search_armario, DisplayMode, ans;

#pragma endregion

int main()
{
	DisplayMode=GetDisplayMode();

	/*Abre o ficheiro de retail*/
	RetailFile = OpenFile(&RetailFile, RETAIL_FILE_NAME, "rb");
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
			printf("\nInsere uma opcao valida:\n");
			scanf("%d", &answer_menu);
			switch(answer_menu)
			{
			case ver:
				CLEAR_SCREEN();
				DisplayMenuVisualizacoes();
				do{
					printf("\nInsere uma opcao valida:\n");
					scanf("%d", &answer_ver);
					switch(answer_ver)
					{
					case total:
						CLEAR_SCREEN();
						if(DisplayMode==1){
							MostraProdutos(ListaProdutos);
							LINE_BREAK();
							DisplayMenuVisualizacoes();
						}else{
							printf("Introduza o nome do ficheiro sem extensao: ");
							scanf("%s", &filename);
							GuardaPesquisaTotal(ListaProdutos, filename);
							LINE_BREAK();
							DisplayMenuVisualizacoes();
						}
						break;
					case corredor:
						CLEAR_SCREEN();
						printf("\nInsere o numero do corredor: ");
						scanf("%d", &search_corredor);
						if(DisplayMode==1){
							MostraProdutobyCorredor(ListaProdutos, search_corredor);
							LINE_BREAK();
							DisplayMenuVisualizacoes();
						} else {
							LINE_BREAK();
							printf("Introduza o nome do ficheiro sem extensao: ");
							scanf("%s", &filename);
							GuardaPesquisabyCorredor(ListaProdutos, filename, corredor);
							LINE_BREAK();
							DisplayMenuVisualizacoes();
						}
						break;
					case armario:
						CLEAR_SCREEN();
						printf("\nInsere o numero do armario: ");
						scanf("%d", &search_armario);
						if(DisplayMode==1){
							MostraProdutobyArmario(ListaProdutos, search_armario);
							LINE_BREAK();
							DisplayMenuVisualizacoes();
						} else {
							LINE_BREAK();
							printf("Introduza o nome do ficheiro sem extensao: ");
							scanf("%s", &filename);
							GuardaPesquisabyArmario(ListaProdutos, filename, search_armario);
							LINE_BREAK();
							DisplayMenuVisualizacoes();
						}
						break;
					case coordenadas:
						CLEAR_SCREEN();
						printf("Insere o numero do corredor: ");
						scanf("%d", &search_corredor);
						printf("\nInsere o numero do armario: ");
						scanf("%d", &search_armario);
						if(DisplayMode==1){
							MostraProdutobyCoordenadas(ListaProdutos, search_corredor, search_armario);
							LINE_BREAK();
							DisplayMenuVisualizacoes();
						} else {
							LINE_BREAK();
							printf("Introduza o nome do ficheiro sem extensao: ");
							scanf("%s", &filename);
							GuardaPesquisabyCoordenadas(ListaProdutos, filename, search_corredor, search_armario);
							LINE_BREAK();
							DisplayMenuVisualizacoes();
						}
						break;
					case quantidade:
						CLEAR_SCREEN();
						printf("\nIntroduz a quantidade do produto:");
						scanf("%d", &qnt);
						if(DisplayMode==1){
							MostraProdutobyQuantidade(ListaProdutos, qnt);
						} else {
							printf("Introduza o nome do ficheiro sem extensao: ");
							scanf("%s", &filename);
							GuardaPesquisabyID(ListaProdutos, filename, qnt);
							LINE_BREAK();
							DisplayMenuVisualizacoes();
						}
						break;
					}
				}while(answer_ver != sair_ver);
				DisplayMenu();
				break;
			case gerir:						//ACABAR
				CLEAR_SCREEN();
				DisplayMenuEncomendas();
				break;
			case stocks:					//ACABAR
				CLEAR_SCREEN();
				DisplayMenuStocks();
				break;
			case configuracoes:
				CLEAR_SCREEN();
				DisplayMenuConfiguracoes();
				do{
					printf("\nInsere uma opcao valida:\n");
					scanf("%d", &answer_configs);
					switch(answer_configs){
					case alterar_display:
						printf("\t\tModos de Display\n\n");
						ShowDisplayMode(DisplayMode);
						printf("Pretende alterar o modo de display ? (1 - sim \\ 2 - nao): ");
						scanf("%d", &ans);
						if(ans == 1)
							UpdateDisplayMode(DisplayMode);
						else
							printf("Modo de display nao alterado.\n");
						LINE_BREAK();
						DisplayMenuConfiguracoes();
						break;
					}
				} while (answer_configs != sair_configs);
				DisplayMenu();
			}
		} while (answer_menu != sair_menu);
		printf("Ate uma proxima!\n");
}