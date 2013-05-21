#include<stdio.h>
#include<string.h>
#include<stdlib.h>

	int GetNextData(FILE *file)
	{
		int variavel;
		fread(&variavel, sizeof(int), 1, file);
		return variavel;
	}