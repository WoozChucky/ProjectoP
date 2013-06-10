/*
filefunctions.h

Vale das Flores Retail
DEIS @ ISEC 2013

Fábio Fonseca - 21210424
Nuno Silva - 21220170

Fcheiro header com funções de abertura / leitura / escrita de ficheiros
*/
#define RETAIL_FILE_NAME "retail.bin"
#define CONFIG_FILE_NAME "config.dat"


FILE * OpenFile(FILE **file, char *FileName, char *mode)
{
    *file = fopen(FileName, mode); //abre o ficheiro
    /* nome do ficheiro seguido do modo de abertura */
    
    if (!*file) //verifica se abriu correctamente
        {
            printf("Erro ao abrir %s\n", FileName);
			_sleep(3500); //para programa durante 3,5 segundos
            exit(EXIT_FAILURE);
        }
    return *file; //devolve ficheiro aberto
}

char * BufferSpaceAlloc(FILE **RetailFile, char *buffer)
{
    int FileLenght;

    fseek(*RetailFile, 0, SEEK_END); //coloca o ponteiro no fim do ficheiro
    FileLenght=ftell(*RetailFile); //obtem a comprimento do ficheiro
    fseek(*RetailFile, 0, SEEK_SET); //coloca o ponteiro no inicio do ficheiro

    buffer=(char *)malloc(FileLenght+1); //aloca o espaco

    if(!buffer) //verifica se alocou bem o espaço
        {
            printf("Erro ao alocar memoria!\n");
            _sleep(3500);
            exit(EXIT_FAILURE);
        }
    return buffer; //devolve variavel com espaço alocado
}

int GetData(FILE *file)
{
    int variavel;
    fread(&variavel, sizeof(int), 1, file); //lê valor e do ficheiro passao por argumento e guarda em variavel
    return variavel; //devolve a variavel
}

int GetDisplayMode()
{
    FILE *file;
    int DisplayMode=2;

    file=OpenFile(&file, CONFIG_FILE_NAME, "r"); //abre ficheiro de configuração para leitura

    fscanf(file, "%d", &DisplayMode); //obtem modo de display e guarda em variavel

    fclose(file); //fecha ficheiro

    return DisplayMode; //devolve modo de display
}

void UpdateDisplayMode(int CurrentDisplayMode)
{
    FILE *file;

    file=OpenFile(&file, CONFIG_FILE_NAME, "w"); //abre ficheiro em modo de escrita

    if(CurrentDisplayMode==1) //altera modo de display consoante o valor do argumento
        fprintf(file, "%d", 0); //escreve no ficheiro
    else
        fprintf(file, "%d", 1); //escreve no ficheiro

    fclose(file);//fecha ficheiro
}

