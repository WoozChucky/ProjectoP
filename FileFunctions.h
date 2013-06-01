#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define RETAIL_FILE_NAME "retail.bin"

	FILE * OpenStorageFile(FILE **file, char *FileName)	{
		*file = fopen(FileName, "rb");
		if (!*file)
		{
			printf("Erro ao abrir %s\n", FileName);
			return;
		}
		return *file;
	}

	char * BufferSpaceAlloc(FILE **RetailFile, char *buffer)
	{
		int FileLenght;

		fseek(*RetailFile, 0, SEEK_END);
		FileLenght=ftell(*RetailFile);
		fseek(*RetailFile, 0, SEEK_SET);

		buffer=(char *)malloc(FileLenght+1);

		if(!buffer)
		{
			printf("Erro ao alocar memoria!\n");
			return;
		}
		return buffer;
	}

	int GetData(FILE *file)
	{
		int variavel;
		fread(&variavel, sizeof(int), 1, file);
		return variavel;
	}