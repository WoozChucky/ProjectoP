/*
Vale das Flores Retail
DEIS @ ISEC 2013

Fábio Fonseca - 21210424
Nuno Silva - 21220170

Fcheiro .c principal onde contem a gestão do "armazém"
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include "displays.h"
#include "filefunctions.h"
#include "structfunctions.h"
#include "main.h"

pno ListaProdutos = NULL;
char filename[256];
int qnt, search_corredor, search_armario, DisplayMode, ans;

int main()
{

    /* Obtem o modo de display das pesquisas (1 - consola / 0 - ficheiro) */
    DisplayMode=GetDisplayMode();
    /* Preenche a lista dos produtos lendo o ficheiro de retail */
    ListaProdutos=InitializeWarehouse(ListaProdutos);
    //printf("FALA: %d",qnt=ObtemNProdutos_p_Armario(ListaProdutos));
    DisplayMenu();
    do
        {
            DisplayMode=GetDisplayMode();
            printf("\nInsere uma opcao valida:\n");
            scanf("%d", &answer_menu);
            switch(answer_menu)
                {
                case ver:
                    CLEAR_SCREEN();
                    DisplayMenuVisualizacoes();
                    do
                        {
                            printf("\nInsere uma opcao valida:\n");
                            scanf("%d", &answer_ver);
                            switch(answer_ver)
                                {
                                case total:
                                    CLEAR_SCREEN();
                                    if(DisplayMode==1)
                                        {
                                            MostraProdutos(ListaProdutos);
                                            LINE_BREAK();
                                            DisplayMenuVisualizacoes();
                                        }
                                    else
                                        {
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
                                    if(DisplayMode==1)
                                        {
                                            MostraProdutobyCorredor(ListaProdutos, search_corredor);
                                            LINE_BREAK();
                                            DisplayMenuVisualizacoes();
                                        }
                                    else
                                        {
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
                                    if(DisplayMode==1)
                                        {
                                            MostraProdutobyArmario(ListaProdutos, search_armario);
                                            LINE_BREAK();
                                            DisplayMenuVisualizacoes();
                                        }
                                    else
                                        {
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
                                    if(DisplayMode==1)
                                        {
                                            LINE_BREAK();
                                            MostraProdutobyCoordenadas(ListaProdutos, search_corredor, search_armario);
                                            LINE_BREAK();
                                            DisplayMenuVisualizacoes();
                                        }
                                    else
                                        {
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
                                    if(DisplayMode==1)
                                        {
                                            MostraProdutobyQuantidade(ListaProdutos, qnt);
                                        }
                                    else
                                        {
                                            printf("Introduza o nome do ficheiro sem extensao: ");
                                            scanf("%s", &filename);
                                            GuardaPesquisabyQnt(ListaProdutos, filename, qnt);
                                            LINE_BREAK();
                                            DisplayMenuVisualizacoes();
                                        }
                                    break;
                                }
                        }
                    while(answer_ver != sair_ver);
                    DisplayMenu();
                    break;
                case gerir:            //FONSECA
                    CLEAR_SCREEN();
                    DisplayMenuEncomendas();
                    break;
                case stocks:
                    CLEAR_SCREEN();
                    DisplayMenuStocks();
                    do
                        {
                            printf("\nInsere uma opcao valida:\n");
                            scanf("%d", &answer_stocks);
                            switch(answer_stocks)
                                {
                                case repor:
                                    printf("Introduza o nome do ficheiro sem extensao: ");
                                    scanf("%s", &filename);
                                    ObtemStock(filename, ListaProdutos);
                                    CLEAR_SCREEN();
                                    DisplayMenuStocks();
                                    break;
                                }
                        }
                    while (answer_stocks != sair_stocks);
                    DisplayMenu();
                    break;
                case configuracoes:
                    CLEAR_SCREEN();
                    DisplayMenuConfiguracoes();
                    do
                        {
                            printf("\nInsere uma opcao valida:\n");
                            scanf("%d", &answer_configs);
                            switch(answer_configs)
                                {
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
                        }
                    while (answer_configs != sair_configs);
                    DisplayMenu();
                }
        }
    while (answer_menu != sair_menu);
    GuardaStruct(ListaProdutos);
    printf("Ate uma proxima!\n");
    _sleep(3500);
    return 1;
}