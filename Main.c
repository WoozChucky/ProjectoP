#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "Displays.h"
#include "FileFunctions.h"
#include "StructFunctions.h"

#pragma region Declaração_De_Variáveis
	pno ListaProdutos = NULL;													//struct da lista de produtos
	FILE *RetailFile;															//ficheiro do armazem/retail.bin
	char *buffer={NULL};														//buffer para leitura do ficheiro
	int NCorredores, NArmarios, NProdutos_p_Armario, cArmario=1, cCorredor=1;   //vars do armazem
	int i, j, h;																//vars dos for's
	typedef enum {sair_menu=4, ver=1, gerir=2, stocks=3} RespostaMenu;			//vars dos menus
	RespostaMenu answer_menu;
	typedef enum {total=1, corredor=2, armario=3, coordenadas=4, quantidade=5, sair_ver=6} RespostaVer;
	RespostaVer answer_ver;
	int qnt;
#pragma endregion

int main()
{
	/*Abre o ficheiro de retail*/
	RetailFile = OpenStorageFile(&RetailFile, RETAIL_FILE_NAME);
	/* Aloca Espaço necessario no buffer*/
	buffer = BufferSpaceAlloc(&RetailFile, buffer);
	
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
						MostraProdutos(ListaProdutos);
						break;
					case corredor:
						break;
					case armario:
						break;
					case coordenadas:
						break;
					case quantidade:
						printf("\nIntroduz a quantidade do produto:");
						scanf("%d", &qnt);
						MostraProdutobyQuantidade(ListaProdutos, qnt);
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
			}
		} while (answer_menu != sair_menu);
		printf("Opcao Invalida! SET_ENUM_TYPE 1");
}