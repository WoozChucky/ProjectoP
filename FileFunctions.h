#include<stdio.h>
#include<string.h>
#include<stdlib.h>

	FILE OpenStorageFile(FILE *file, char *FileName)
	{
		file = fopen(FileName, "rb");
		if (!file)
		{
			printf("Erro ao abrir %s\n", FileName);
			return;
		}
		return *file;
	}


	int GetNextData(FILE *file)
	{
		int variavel;
		fread(&variavel, sizeof(int), 1, file);
		return variavel;
	}