#ifdef _WIN32
#    define CLEAR_SCREEN() system("cls")
#else
#    define CLEAR_SCREEN() system("clear")
#endif
#define LINE_BREAK() printf("\n");

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
		repor=1,
		sair_stocks=2
	} RespostaStocks;
	RespostaStocks answer_stocks;

	typedef enum {
		alterar_display=1,
		sair_configs =2
	} RespostaConfigs;
	RespostaConfigs answer_configs;

	unsigned concatena(unsigned x, unsigned y) {
		unsigned pow = 10;
		while(y >= pow)
			pow *= 10;
		return x * pow + y;        
	}
