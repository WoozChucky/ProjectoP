#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "Displays.h"
#include "FileFunctions.h"
#include "StructFunctions.h"

#define RETAIL_FILE_NAME "retail.bin"

int main()
{
	/*Declaração de Variáveis*/
	prod_pointer ListaProdutos = NULL;
	FILE *file;
	char *buffer;
	int FileLenght, NCorredores, NArmarios, resp_menu=0, resp_sub_menu=0, i, j, h, NProdutos_p_Armario, cArmario, cCorredor=1;

	/*Abre o ficheiro*/
	*file = OpenStorageFile(file, RETAIL_FILE_NAME);

	fseek(file, 0, SEEK_END);
	FileLenght=ftell(file);
	fseek(file, 0, SEEK_SET);

	buffer=(char *)malloc(FileLenght+1);

	if(!buffer)
	{
		return;
	}
	
	fread(&NArmarios, sizeof(int), 1, file);   //Obtem numero de armarios
	fread(&NCorredores, sizeof(int), 1, file); //Obtem numero de corredores

	cArmario = 1;
	cCorredor =1;
	
	for (i = 0; i < NCorredores; i++) { //corre 5 vezes

		for (h = 0; h < NArmarios; h++) {
			fread(&NProdutos_p_Armario, sizeof(int), 1, file); //nº produtos no armario X
			for(j = 0; j < NProdutos_p_Armario; j++) { //corre NProdutos_p_Armario vezes

				//Guarda dados na struct
				ListaProdutos=AdicionaProduto(ListaProdutos, GetNextData(file), GetNextData(file), cCorredor, cArmario);

			}

			cArmario++;
			if (cArmario >= 4)
			{
				cArmario = 1;
			}
			
		}
		cCorredor++;
	}

	fclose(file);

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
		scanf("%d", &resp_menu);

		switch(resp_menu)
		{
		case 1:
			{
				/*     -- Visualização / Pesquisa --
					O programa deve poder fazer listagens completas e parciais dos Produtos existentes em
					armazém. Exemplos de listagens parciais incluem: mostrar todos os Produtos de um
					determinado corredor/armário ou indicar a localização/quantidade em stock de um
					ListaProdutos específico. De acordo com a preferência do utilizador, a informação pode ser
					apresentada na consola ou enviada para um ficheiro de texto. 
				*/
				system("CLS");
				DisplayMenuVisualizacoes();
				scanf("%d", &resp_sub_menu);
				switch(resp_sub_menu)
				{
				case 1:
					{
						MostraProdutos(ListaProdutos);
						system("pause");
						break;
					}
				case 2:
					{
						EliminaProd(ListaProdutos);
						system("CLS");
						break;
					}
				case 3:
					{
						system("CLS");
						break;
					}
				case 4:
					{
						break;
					}
				default:
					{
						printf("Opcao Invalida!\n");
						break;
					}
				}			
				break;
			}
		case 2:
			{
				/*		 -- Gestao de Encomendas --
					Ao receber uma encomenda, o programa deve verificar se existem Produtos em stock
					para satisfazer a totalidade da encomenda. Caso falte algum ListaProdutos, a encomenda é
					cancelada e gerado um alerta sobre o ListaProdutos (ou Produtos) em falta.
				*/
				break;
			}
		case 3:
			{
				/*		-- Reposição de Stocks --
					Deve ser possível actualizar as quantidades de Produtos existentes em armazém e
					adicionar novos Produtos.
					Nesta funcionalidade, o programa deve aceder ao ficheiro de texto e actualizar as
					quantidades em stock. Se um ListaProdutos surgir no ficheiro, mas não existir em armazém,
					deve ser colocado num dos armários com menos diversidade de Produtos.
				*/
				break;
			}
		case 4:
			{
				break;
				return EXIT_SUCCESS;
			}
		default:
			{
				printf("Opcao Invalida! Programa vai Terminar!\n");
				return EXIT_FAILURE;
			}
		}
	//Programa nao deve chegar aqui #TESTE#
	printf("\n#TESTE#\n");
}