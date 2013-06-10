/*
main.h

Vale das Flores Retail
DEIS @ ISEC 2013

Fábio Fonseca - 21210424
Nuno Silva - 21220170

Fcheiro header com definição dos 'enums' dos menus e variadas opções
*/
#ifdef _WIN32 //se o compilador for windows
#    define CLEAR_SCREEN() system("cls") //define para windoes para limpar ecrã
#else //senao
#    define CLEAR_SCREEN() system("clear") //define para linux para limpar ecrã
#endif
#define LINE_BREAK() printf("\n"); //define para facilitar a quebra de linha

typedef enum
{
    ver=1,
    gerir=2,
    stocks=3,
    configuracoes=4,
    sair_menu=5
} RespostaMenu;
RespostaMenu answer_menu;

typedef enum
{
    total=1,
    corredor=2,
    armario=3,
    coordenadas=4,
    quantidade=5,
    sair_ver=6
} RespostaVer;
RespostaVer answer_ver;

typedef enum
{
    processar=1,
    sair_encomendas=2
} RespostaEncomendas;
RespostaEncomendas answer_encomendas;

typedef enum
{
    repor=1,
    sair_stocks=2
} RespostaStocks;
RespostaStocks answer_stocks;

typedef enum
{
    alterar_display=1,
    sair_configs =2
} RespostaConfigs;
RespostaConfigs answer_configs;

unsigned concatena(unsigned x, unsigned y)   //função para concatenar 2 inteiros
{
    unsigned pow = 10;
    while(y >= pow)
        pow *= 10;
    return x * pow + y; //devolve os valores concatenados
}

/*					Ficheiro Reatil.bin de Origem
						(Apenas para Testes)

						Corredor 1
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