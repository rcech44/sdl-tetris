#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

typedef struct 
{
  SDL_Color color;
  SDL_Rect *indivCubes;
} Cubes;

typedef struct 
{
  int score;
} Game;


typedef struct 
{
  int *rows;      // pokud rows dosahne 9 = full
  int *isFull;    // pro kazdou row ukazatel, zda je plna nebo ne
} Row_data;

int checkForCollisionsAbsolute(int numberOfCubesOnScreen, int indexOfActive, int isActive, Cubes *cubes);
// prima kontrola kolize - jestli nejsou dva RECT na stejne pozici

int checkForCollisionsY(int numberOfCubesOnScreen, int indexOfActive, int isActive, Cubes *cubes);
// kontrola kolize s jinymi tvary pri posunu tvaru dolu

int checkForCollisionsX(int numberOfCubesOnScreen, int indexOfActive, int isActive, Cubes *cubes, int mode);
// kontrola kolize s jinymi tvary pri posunu do stran

void backup(int indexOfActive, Cubes **cubes, Cubes **backupCube);
// uchovani puvodniho tvaru, pokud byla detekovana kolize

void restore(int indexOfActive, Cubes **cubes, Cubes **backupCube);
// obnoveni puvodniho tvaru

void generateCube(int generatedIndexType, int indexOfActive, Cubes **cubes, int isPregenerated, int *gameOver, int numberOfCubesOnScreen);
// generace novych tvaru

void pregeneratedCubeEdit(Cubes **pregeneratedCube, int pregeneratedIndexType);
// zmena lokace tvaru na pravou cast obrazovky

int rotateCube(int generatedIndexType, int indexOfActive, int rotation, Cubes **cubes, Cubes **backupCube, int numberOfCubesOnScreen, int isActive);
// rotace aktivniho tvaru + kontrola kolize pri otoceni

int fullRowCheck(Cubes **cubes, Row_data **row_data, int indexOfActive);
// kontrola a check, jestli je jedna z 15 rows plne zaplnena

void rowDeletion(Cubes **cubes, Row_data **row_data, int numberOfCubesOnScreen, Game **game);
// mazani radku a pote posun vsech radku dolu