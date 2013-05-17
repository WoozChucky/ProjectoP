#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "Displays.h"

#define RETAIL_FILE_NAME "retail.bin"
#define _CRT_SECURE_NO_WARNINGS 1
#define BSIZE 256

typedef struct produto produto, *prod_pointer;
	struct produto
	{
		int IDProduto;
		int quantidade;
		int coordenadas[1][1]; //Corredor + Armario
		prod_pointer proximo;
	};


void dump_buffer(void *buffer, int buffer_size)
{
  int i;
  for(i = 0;i < buffer_size;++i)
     printf("%c\n", ((char *)buffer)[i]);
}

int main()
{

	FILE *file;
	char *buffer;
	int FileLenght, n_corredores, n_armarios, resp_menu=0, resp_sub_menu=0;
	int i, j, k;

	//Abre o ficheiro
	file = fopen(RETAIL_FILE_NAME, "rb");
	if (!file)
	{
		printf("Erro ao abrir %s\n", RETAIL_FILE_NAME);
		return;
	}

	fseek(file, 0, SEEK_END);
	FileLenght=ftell(file);
	fseek(file, 0, SEEK_SET);

	buffer=(char *)malloc(FileLenght+1);

	if(!buffer)
	{
		return;
	}


	i = fread(buffer, FileLenght, 1, file);
	printf("Elementos Lidos: %d\n", i);
	//Lê o conteúdo do ficheiro
	//while(!feof(file)){
		//fgets(buffer, FileLenght, file);
		//printf("Data[]: %s\n", buffer);   
	//}

	dump_buffer(buffer, FileLenght);

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

	//DisplayMenu();
	scanf("%d", &resp_menu);

	switch(resp_menu)
	{
	case 1:
		{
			/*     -- Visualização / Pesquisa --
				O programa deve poder fazer listagens completas e parciais dos produtos existentes em
				armazém. Exemplos de listagens parciais incluem: mostrar todos os produtos de um
				determinado corredor/armário ou indicar a localização/quantidade em stock de um
				produto específico. De acordo com a preferência do utilizador, a informação pode ser
				apresentada na consola ou enviada para um ficheiro de texto. 
			*/
			system("CLS");
			DisplayMenuVisualizacoes();
			scanf("%d", &resp_sub_menu);
			switch(resp_sub_menu)
			{
			case 1:
				{
					printf("Vale das Flores Retail\n\n");
					printf("\t\tCorredor 1\n");
					printf("\t\tArmario 1\n");
					printf("\t2 Unidades do produto 4\n");
					printf("\t4 Unidades do produto 7\n");
					printf("\t78 Unidades do produto 1\n");
					system("pause");
				}
			case 2:
				{
					system("CLS");
				}
			case 3:
				{
					system("CLS");
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
				Ao receber uma encomenda, o programa deve verificar se existem produtos em stock
				para satisfazer a totalidade da encomenda. Caso falte algum produto, a encomenda é
				cancelada e gerado um alerta sobre o produto (ou produtos) em falta.
			*/
			break;
		}
	case 3:
		{
			/*		-- Reposição de Stocks --
				Deve ser possível actualizar as quantidades de produtos existentes em armazém e
				adicionar novos produtos.
				Nesta funcionalidade, o programa deve aceder ao ficheiro de texto e actualizar as
				quantidades em stock. Se um produto surgir no ficheiro, mas não existir em armazém,
				deve ser colocado num dos armários com menos diversidade de produtos.
			*/
			break;
		}
	case 4:
		{
			//Programa termina normalmente
			return EXIT_SUCCESS;
		}
	default:
		{
			//Nenhuma opção valida, programa termina
			return EXIT_FAILURE;
		}
	}

	/* Programa nao deve chegar aqui #TESTE# */
	printf("\n#TESTE#\n");
}

/* #define _CRT_SECURE_NO_WARNINGS 1

	

void preenche(pno p)
{
	printf("Nome: ");
	gets(p->nome);
	printf("Urgencia (1-3): ");
	scanf("%d", p->urgencia);
	p->prox = NULL;
}

int verifica_lista(pno p)
{
	if (p == NULL)
		return 1;
	else
		return 0;
}

pno adiciona_final(pno p)
{
	pno novo, aux;

	novo = malloc(sizeof(no));

	if(novo == NULL)
	{
		printf("Erro na alocacao de memoria!\n");
		return p;
	}

	preenche(novo);

	if(verifica_lista(p))
	{
		p = novo;
	}
	else
	{
		if(novo->urgencia >= 3)
		{
			//Restantes Pacientes
			aux = p;
			while(aux->prox != NULL)
				aux = aux->prox;
			aux->prox = novo;
		} else if(novo->urgencia == 2)
		{
			//Idosos e Criancas

		} else if(novo->urgencia <= 1)
		{
			//Gravidas
			novo->prox = p;
			p = novo;
		}
	}
	
	return p;
}

void mostra_lista(pno p)
{
	while(p != NULL)
	{
		printf("%s\n",p->nome);
		p = p->prox;
	}
}

pno atendimento(pno p)
{
	pno actual;
	actual = p;
	p = actual->prox;
	free(actual);
	return p;
}

pno desistencia(pno p)
{

}

int main()
{
	int resp=0;
	pno lista = NULL;
	
	printf("1. Novo Paciente\n");
	printf("2. Atendimento\n");
	printf("3. Visualizar Fila de Espera\n");
	printf("4. Desistencia\n");
	printf("5. Terminar\n");
	printf("Escolha uma opcao (1-5): ");
	scanf("%d", &resp);
	
	switch(resp)
	{
	case 1:
		{
			printf("\nAdicionar Novo Paciente\n\n");
			lista=adiciona_final(lista);
		}
	case 2:
		{
			lista=atendimento(lista);
		}
	case 3:
		{
			mostra_lista(lista);
		}
	case 4:
		{
			lista=desistencia(lista);
		}
	case 5:
		{
			printf("Terminado.\n");
			return 1;
		}
	default:
		{
			printf("Nenhuma Opcao Selecionada.\n");
			return 1;
		}
	}
}
*/