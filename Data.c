#include "lib.h"

int modf(int a, int b)
{
	if (b < 0)
		return modf(-a, -b);
	int ret = a % b;
	if (ret < 0)
		ret += b;
	return ret;
}

void CreateArray (array* gameField)
{
	int i;
	gameField->tab = (int**)malloc(gameField->nRows*sizeof(int*));
	for (i = 0; i < gameField->nRows; i++)
	{
		gameField->tab[i] = (int*)malloc(gameField->nColumns*sizeof(int));
	}

}

void SeedRandom(array* gameField, int p)
{
	int i, j,c;
	srand(time(NULL));
	for (i = 0; i < gameField->nRows; i++)
	for (j = 0; j < gameField->nColumns; j++)
	{
		if (rand() / ((float)RAND_MAX + 1) <= (float)p / 100.0)
			c = 1;
		else
			c = 0;
		gameField->tab[i][j] = c;
	}
}

void SeedManual(array* gameField)
{
	char c = 'a';
	int i = 0, j = 0;

	for (i = 0; i < gameField->nRows; i++)
		for (j = 0; j < gameField->nColumns; j++)
			gameField->tab[i][j] = 0;
	while(c!='e')
	{
			system("cls");
			printf("\npodaj numer rzedu i i numer kolumny ktore chcesz zasiac\n");
			scanf("%i", &i);
			scanf("%i", &j);
			gameField->tab[modf((i - 1), gameField->nRows)][modf((j - 1), gameField->nColumns)] = 1;
			c = getchar();
	}
}

void LoadGame(array *gameField)
{
	FILE* fp;
	int i, j;
	if ((fp = fopen("pole gry.txt", "r")) == NULL)
	{
		printf("blad odczytu pliku...");
		getchar();
		getchar();
		return;
	}
	fscanf(fp, "%i", &gameField->nRows);
	//printf("wartosc nRows odczytana z pliku %i\n", gameField->nRows);
	fscanf(fp, "%i", &gameField->nColumns);
	//printf("wartosc nColumns odczytana z pliku %i\n", gameField->nColumns);
	CreateArray(gameField);
	for (i = 0; i < gameField->nRows; i++)
	for (j = 0; j < gameField->nColumns; j++){
	fscanf(fp, "%i", &gameField->tab[i][j]);
	//printf("rzad - %i, kolumna - %i, wartosc -%i\n", i, j, gameField->tab[i][j]);
}
	fclose(fp);
}

void SaveGame(array* gameField)
{
	FILE* fp;
	int i, j;
	if ((fp = fopen("pole gry.txt", "w")) == NULL)
	{
		printf("blad zapisu do pliku...");
		getchar();
		getchar();
		return;
	}
	fprintf(fp, "%i\n", gameField->nRows);
	fprintf(fp, "%i\n", gameField->nColumns);

	for (i = 0; i < gameField->nRows; i++)
	{
		fprintf(fp, "\n");
		for (j = 0; j < gameField->nColumns; j++)
			fprintf(fp, "%i ", gameField->tab[i][j]);
	}
	fclose(fp);
	printf("\n\t\tzapis sie powiodl");
	getchar();
	getchar();
}

void Evolve(array* gameField)
{
	int i, j, **tabn;

	tabn = (int**)malloc(gameField->nRows*sizeof(int*));
	for (i = 0; i < gameField->nRows; i++)
		tabn[i] = (int*)malloc(gameField->nColumns*sizeof(int));


	for (i = 0; i < gameField->nRows; i++)
	for (j = 0; j < gameField->nColumns; j++)
			tabn[i][j] = gameField->tab[i][j];


	for (i = 0; i < gameField->nRows; i++)
	for (j = 0; j < gameField->nColumns; j++)
		{
		if (gameField->tab[i][j] == 1)
			tabn[i][j] = ifAlive(i, j, gameField);
		else
			tabn[i][j] = ifDead(i, j, gameField);
		}


	for (i = 0; i < gameField->nRows; i++)
	for (j = 0; j < gameField->nColumns; j++)
			gameField->tab[i][j] = tabn[i][j];

	free(tabn);
}

int ifAlive(int i, int j, array* gameField)
{	
	int counter=0;
	if (gameField->tab[i][(j + 1) % gameField->nColumns] == 1)
		counter++;
	if (gameField->tab[(i + 1) % gameField->nRows][(j + 1) % gameField->nColumns] == 1)
		counter++;
	if (gameField->tab[(i + 1) % gameField->nRows][j] == 1)
		counter++;
	if (gameField->tab[(i + 1) % gameField->nRows][modf((j - 1), gameField->nColumns)] == 1)
		counter++;
	if (gameField->tab[i][modf((j - 1), gameField->nColumns)] == 1)
		counter++;
	if (gameField->tab[modf((i - 1), gameField->nRows)][modf((j - 1), gameField->nColumns)] == 1)
		counter++;
	if (gameField->tab[modf((i - 1), gameField->nRows)][j] == 1)
		counter++;
	if (gameField->tab[modf((i - 1), gameField->nRows)][(j + 1) % gameField->nColumns] == 1)
		counter++;

	if (counter == 2 || counter == 3)
		return 1;
	else
		return 0;
}

int ifDead(int i, int j, array* gameField)
{
	int counter=0;
	if (gameField->tab[i][(j + 1) % gameField->nColumns] == 1)
		counter++;
	if (gameField->tab[(i + 1) % gameField->nRows][(j + 1) % gameField->nColumns] == 1)
		counter++;
	if (gameField->tab[(i + 1) % gameField->nRows][j] == 1)
		counter++;
	if (gameField->tab[(i + 1) % gameField->nRows][modf((j - 1), gameField->nColumns)] == 1)
		counter++;
	if (gameField->tab[i][modf((j - 1), gameField->nColumns)] == 1)
		counter++;
	if (gameField->tab[modf((i - 1), gameField->nRows)][modf((j - 1), gameField->nColumns)] == 1)
		counter++;
	if (gameField->tab[modf((i - 1), gameField->nRows)][j] == 1)
		counter++;
	if (gameField->tab[modf((i - 1), gameField->nRows)][(j + 1) % gameField->nColumns] == 1)
		counter++;

	if (counter == 3)
		return 1;
	else
		return 0;
}

//void SeedRandomList(int Rows, int Columns)
//{
//	list* root,*currentNode;
//	int counter,c=1;
//	root = malloc(sizeof(list));
//	currentNode = root;
//	for (counter = 0; counter < Rows*Columns; counter++)
//	{
//		currentNode->next = malloc(sizeof(list));
///*		if (((rand() / (float)RAND_MAX)*10.0) < 5.0)
//			currentNode->data = 0;
//		else
//			currentNode->data = 1*/;
//	currentNode->data = c;
//		currentNode = currentNode->next;
//		c++;
//	}
//	currentNode = root;
//	counter = 0;
//	while (currentNode->data != NULL)
//	{
//		if (counter%Rows == 0)
//			printf("\n");
//		printf("%i", currentNode->data);
//		currentNode = currentNode->next;
//		counter++;
//	}
//}