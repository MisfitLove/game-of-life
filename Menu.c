#include "lib.h"

void PrintMenu()
{
	printf("%c - Ustal ziarno manualnie\n", MSetManual);
	printf("%c - Ustal ziarno losowo\n", MSetRandom);
	//printf("%c - Ustal ziarno losowo (lista)\n", MRandomList);
	printf("%c - Wczytaj zapisany stan gry\n", MLoad);
	printf("%c - Wyjdz\n", MExit);
}

void Menu()
{
	char c = '0';
	int nRows=0, nColumns=0, percent=0;
	array gameField;
	MenuOption option = Mdef;
	PrintMenu();
	while (option != MExit)
	{
		system("cls");
		PrintMenu();
		option = getchar();
		switch (option)
		{
		case MSetManual:
			printf("\npodaj wymiary pola gry (liczba wierszy i liczba kolumn)\n");
			scanf("%i", &gameField.nRows);
			scanf("%i", &gameField.nColumns);
			CreateArray(&gameField);
			SeedManual(&gameField);
			GameOn(&gameField);
			break;
		case MSetRandom:
			printf("\npodaj wymiary pola gry (liczba wierszy i liczba kolumn)\n");
			scanf("%i", &gameField.nRows);
			scanf("%i", &gameField.nColumns);
			printf("\npodaj wymiary procent wypelnienia planszy\n");
			scanf("%i", &percent);
			CreateArray(&gameField);
			SeedRandom(&gameField, percent);
			GameOn(&gameField);
			break;
		//case MRandomList:
		//	printf("\npodaj wymiary pola gry (liczba wierszy i liczba kolumn)\n");
		//	scanf("%i", &gameField.nRows);
		//	scanf("%i", &gameField.nColumns);
		//	SeedRandomList(gameField.nRows, gameField.nColumns);
			break;
		case MLoad:
			LoadGame(&gameField);
			GameOn(&gameField);
			break;
		case MExit:
			return;
			break;
		}

	}
}

void GameOn(array* gameField)
{
	char c = 'a';
	fflush(stdin);
	while (c != 'e')
	{
		Draw(gameField);
		printf("\n\n\tnacisnij 'e' aby wyjsc do menu\n\tnacisnij 's' aby zapisac aktualny stan gry\n\tlub dowolny inny klawisz by kontynuowac...");
		c = getchar();
		if (c == 's')
			SaveGame(gameField);
		Evolve(gameField);
	}
	free(gameField->tab);
}

void Draw(array* gameField)
{
	int i, j;
	system("cls");
	for (i = 0; i < gameField->nRows; i++)
	{
		printf("\n");
		for (j = 0; j < gameField->nColumns; j++)
		{
			printf("%i", gameField->tab[i][j]);

			//if(gameField->tab[i][j] == 1)
			//	printf("X");
			//else
			//{
			//	if (gameField->tab[i][j] == 0)
			//		printf("*");
			//	else
			//		printf("?");
			//}
		}
	}
}