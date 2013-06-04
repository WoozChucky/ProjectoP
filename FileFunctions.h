#define RETAIL_FILE_NAME "retail.bin"
#define CONFIG_FILE_NAME "config.dat"


	FILE * OpenFile(FILE **file, char *FileName, char *mode)	{
		*file = fopen(FileName, mode);
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

	void UpdateSession(char *filename)
	{
		FILE *file;
		time_t DataActual;
		char* c_DataActual;

		file = OpenFile(&file, filename, "a");

		DataActual = time(NULL);
		c_DataActual = ctime(&DataActual);
		fprintf(file, "Ultimo Acesso: %s", c_DataActual);
		fclose(file);
	}

	int GetDisplayMode()
	{
		FILE *file;
		int DisplayMode=2;
		
		file=OpenFile(&file, CONFIG_FILE_NAME, "r");

		fscanf(file, "%d", &DisplayMode);

		fclose(file);

		return DisplayMode;
	}

	void UpdateDisplayMode(int CurrentDisplayMode)
	{
		FILE *file;
		
		file=OpenFile(&file, CONFIG_FILE_NAME, "w");

		if(CurrentDisplayMode==1)
			fprintf(file, "%d", 0);
		else
			fprintf(file, "%d", 1);

		fclose(file);
	}

