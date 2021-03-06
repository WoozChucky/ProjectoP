/*
displays.h

Vale das Flores Retail
DEIS @ ISEC 2013

F�bio Fonseca - 21210424
Nuno Silva - 21220170

Fcheiro header com fun��es de display para mostrar os variados menus
*/
void DisplayMenu()
{
    printf("\t****************************************************\n");
    printf("\t*                                                  *\n");
    printf("\t*               Vale das Flores Retail             *\n");
    printf("\t*                                                  *\n");
    printf("\t*                     DEIS @ ISEC                  *\n");
    printf("\t*                        2013                      *\n");
    printf("\t*                                                  *\n");
    printf("\t*                                                  *\n");
    printf("\t*              Fabio Fonseca - 21210424            *\n");
    printf("\t*              Nuno Silva - 21220170               *\n");
    printf("\t*                                                  *\n");
    printf("\t****************************************************\n");
    printf("\n\n");
    printf("\t\t\t      **Menu**\n\n");
    printf("\t\t 1 - Visualizacao de Produtos\n");
    printf("\t\t 2 - Gestao de Encomendas\n");
    printf("\t\t 3 - Reposicao Stocks\n");
    printf("\t\t 4 - Configuracoes\n");
    printf("\t\t 5 - Sair\n");
}
void DisplayMenuVisualizacoes()
{
    printf("\t\t\t      **Menu de Visualizacoes**\n\n");
    printf("\t\t 1 - Visualizacao Total\n");
    printf("\t\t 2 - Visualizacao por Corredor\n");
    printf("\t\t 3 - Visualizacao por Armario\n");
    printf("\t\t 4 - Visualizacao por Coordenadas\n");
    printf("\t\t 5 - Visualizacao por Quantidade\n");
    printf("\t\t 6 - Sair\n");
}

void DisplayMenuStocks()
{
    printf("\t\t\t      **Menu de Stocks**\n\n");
    printf("\t\t 1 - Repor Stocks\n");
    printf("\t\t 2 - Sair\n");
}

void DisplayMenuEncomendas()
{
    printf("\t\t\t      **Menu de Encomendas**\n\n");
    printf("\t\t 1 - Processar Encomenda\n");
    printf("\t\t 2 - Sair\n");
}

void DisplayMenuConfiguracoes()
{
    printf("\t\t\t      **Menu de Configuracoes**\n\n");
    printf("\t\t 1 - Modo de Display\n");
    printf("\t\t 2 - Sair\n");
}

void ShowDisplayMode(int DisplayMode)
{
    if(DisplayMode == 1)
        printf("Consola - 1 (Activo)\nFicheiro de Texto - 0\n\n");
    else
        printf("Consola - 1\nFicheiro de Texto - 0 (Activo)\n\n");
}