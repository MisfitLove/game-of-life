#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


typedef enum
{
	MSetManual = 'm',
	MRandomList = 'u',
	MSetRandom = 'r',
	MLoad = 'l',
	MSave = 's',
	MExit = 'e',
	Mdef = '0'
}MenuOption;

typedef struct{
	int** tab;
	int nRows, nColumns;
}array;

typedef struct 
{
	int data;
	struct list *next;
}list;

void Menu();
void Printmenu();
void SeedRandom(array* gameField, int p);
void SeedManual(array* gameField);
void Evolve(array* gameField);
int ifAlive(int i, int j, array* gameField);
int ifDead(int i, int j, array* gameField);
void Draw(array* gameField);
void GameOn(array* gameField);
void CreateArray(array* gameField);
void SaveGame(array* gameField);
void LoadGame(array *gameField);
void SeedRandomList(int Rows, int Columns);
