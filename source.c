#include "source.h"
#include "sdl.h"
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

int checkForCollisionsAbsolute(int numberOfCubesOnScreen, int indexOfActive, int isActive, Cubes *cubes)
{
    isActive = 0;
    for (int activeBlock = 0; activeBlock < 4; activeBlock++)
    {
        for (int numberOfInactiveBlocks = 0; numberOfInactiveBlocks < (numberOfCubesOnScreen - 1); numberOfInactiveBlocks++)
        {
            for (int individualBlock = 0; individualBlock < 4; individualBlock++)
            {   
                //printf("%d\n\n\n", cubes[indexOfActive].indivCubes[activeBlock].y);
                if (cubes[indexOfActive].indivCubes[activeBlock].y == cubes[numberOfInactiveBlocks].indivCubes[individualBlock].y && cubes[indexOfActive].indivCubes[activeBlock].x == cubes[numberOfInactiveBlocks].indivCubes[individualBlock].x)
                {
                isActive = 1;
                //printf("COLLISION DEBUG= Active block: %d\tInactive block:%d (block ID: %d)\n", activeBlock, individualBlock, numberOfInactiveBlocks);
                }
            }
        }
    }

    if (isActive == 0)
    {
        for (int i = 0; i < 4; i++)
        {
            if (cubes[indexOfActive].indivCubes[i].x < 50 || cubes[indexOfActive].indivCubes[i].x >= 410 || cubes[indexOfActive].indivCubes[i].y >= 650 || cubes[indexOfActive].indivCubes[i].y < 50)
            {
                isActive = 1;
                //printf("DEBUG= Out of bounds.");
            }
        }
    }


    if (isActive == 0)
    {
        
        return 0;
    }
    else
    {
        return 1;
    }
    
    
}

int checkForCollisionsY(int numberOfCubesOnScreen, int indexOfActive, int isActive, Cubes *cubes)
{
    for (int activeBlock = 0; activeBlock < 4; activeBlock++)
    {
        for (int numberOfInactiveBlocks = 0; numberOfInactiveBlocks < (numberOfCubesOnScreen - 1); numberOfInactiveBlocks++)
        {
            for (int individualBlock = 0; individualBlock < 4; individualBlock++)
            {   
                if ((cubes[indexOfActive].indivCubes[activeBlock].y + 40) == cubes[numberOfInactiveBlocks].indivCubes[individualBlock].y && cubes[indexOfActive].indivCubes[activeBlock].x == cubes[numberOfInactiveBlocks].indivCubes[individualBlock].x)
                {
                isActive = 0;
                //printf("COLLISION DEBUG= Active block: %d\tInactive block:%d (block ID: %d)\n", activeBlock, individualBlock, numberOfInactiveBlocks);
                }
            }
        }
    }
    if (isActive == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int checkForCollisionsX(int numberOfCubesOnScreen, int indexOfActive, int isActive, Cubes *cubes, int mode)
{
    
    // mode 0 = vlevo, mode 1 = vpravo
    
    if (mode == 0)
    {
        for (int activeBlock = 0; activeBlock < 4; activeBlock++)
        {
            for (int numberOfInactiveBlocks = 0; numberOfInactiveBlocks < (numberOfCubesOnScreen - 1); numberOfInactiveBlocks++)
            {
                for (int individualBlock = 0; individualBlock < 4; individualBlock++)
                {   
                    if ((cubes[indexOfActive].indivCubes[activeBlock].x - 40) == cubes[numberOfInactiveBlocks].indivCubes[individualBlock].x && cubes[indexOfActive].indivCubes[activeBlock].y == cubes[numberOfInactiveBlocks].indivCubes[individualBlock].y)
                    {
                    isActive = 0;
                    //printf("COLLISION DEBUG= Active block: %d\tInactive block:%d (block ID: %d)\n", activeBlock, individualBlock, numberOfInactiveBlocks);
                    }
                }
            }
        }
        if (isActive == 0)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else    // mode == 1
    {
        for (int activeBlock = 0; activeBlock < 4; activeBlock++)
        {
            for (int numberOfInactiveBlocks = 0; numberOfInactiveBlocks < (numberOfCubesOnScreen - 1); numberOfInactiveBlocks++)
            {
                for (int individualBlock = 0; individualBlock < 4; individualBlock++)
                {   
                    if ((cubes[indexOfActive].indivCubes[activeBlock].x + 40) == cubes[numberOfInactiveBlocks].indivCubes[individualBlock].x && cubes[indexOfActive].indivCubes[activeBlock].y == cubes[numberOfInactiveBlocks].indivCubes[individualBlock].y)
                    {
                    isActive = 0;
                    //printf("COLLISION DEBUG= Active block: %d\tInactive block:%d (block ID: %d)\n", activeBlock, individualBlock, numberOfInactiveBlocks);
                    }
                }
            }
        }
        if (isActive == 0)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
}

void backup(int indexOfActive, Cubes **cubes, Cubes **backupCube)
{
    for (int i = 0; i < 4; i++)
    {
        (*backupCube)[0].indivCubes[i].x = (*cubes)[indexOfActive].indivCubes[i].x;
        (*backupCube)[0].indivCubes[i].y = (*cubes)[indexOfActive].indivCubes[i].y;
    }
}

void restore(int indexOfActive, Cubes **cubes, Cubes **backupCube)
{
    for (int i = 0; i < 4; i++)
    {
        (*cubes)[indexOfActive].indivCubes[i].x = (*backupCube)[0].indivCubes[i].x;
        (*cubes)[indexOfActive].indivCubes[i].y = (*backupCube)[0].indivCubes[i].y;
    }
}

void pregeneratedCubeEdit(Cubes **pregeneratedCube, int pregeneratedIndexType)
{
    for (int i = 0; i < 4; i++)
    {
        // if (pregeneratedIndexType == 3)
        // {
        //     (*pregeneratedCube)[0].indivCubes[i].x += 405;
        //     (*pregeneratedCube)[0].indivCubes[i].y += 150;
        // }
        // else if (pregeneratedIndexType == 0)
        // {
        //     (*pregeneratedCube)[0].indivCubes[i].x += 360;
        //     (*pregeneratedCube)[0].indivCubes[i].y += 155;
        // }
        // else
        // {
        //     (*pregeneratedCube)[0].indivCubes[i].x += 380;
        //     (*pregeneratedCube)[0].indivCubes[i].y += 150;
        // }
    }
}

void generateCube(int generatedIndexType, int indexOfActive, Cubes **cubes, int isPregenerated, int *gameOver, int numberOfCubesOnScreen)
{
    // *gameOver = 1;
    int offsetX = 550;
    int offsetY = 230;
    if (isPregenerated == 1 && generatedIndexType == 0)
    {
        offsetX = 530;
    }
    else if (isPregenerated == 1 && generatedIndexType == 3)
    {
        offsetX = 570;
    }

    if (isPregenerated == 0 && generatedIndexType == 0)
    {
        offsetX = 50 + ((rand() % (5 - 0 + 1) + 0) * 40);
        offsetY = 90;
    }
    else if (isPregenerated == 0 && generatedIndexType == 3)
    {
        offsetX = 50 + ((rand() % (7 - 0 + 1) + 0) * 40);
        offsetY = 90;
    }
    else if (isPregenerated == 0)
    {
        offsetX = 50 + ((rand() % (6 - 0 + 1) + 0) * 40);
        offsetY = 90;
    }
    //printf("offsetX= %d\n", offsetX);
    switch (generatedIndexType)
    {
        case 0:
            for (int i = 0; i < 4; i++)
            {
                (*cubes)[indexOfActive].indivCubes[i].h = (*cubes)[indexOfActive].indivCubes[i].w = 40;
            }
            (*cubes)[indexOfActive].indivCubes[0].x = offsetX;
            (*cubes)[indexOfActive].indivCubes[0].y = offsetY - 40;
            (*cubes)[indexOfActive].indivCubes[1].x = offsetX + 40;                 //   
            (*cubes)[indexOfActive].indivCubes[1].y = offsetY - 40;                  //  OOOO
            (*cubes)[indexOfActive].indivCubes[2].x = offsetX + 80;                 //
            (*cubes)[indexOfActive].indivCubes[2].y = offsetY - 40;
            (*cubes)[indexOfActive].indivCubes[3].x = offsetX + 120;
            (*cubes)[indexOfActive].indivCubes[3].y = offsetY - 40;
            (*cubes)[indexOfActive].color.r = 0;
            (*cubes)[indexOfActive].color.g = 255;
            (*cubes)[indexOfActive].color.b = 255;
            break;
        case 1:
            for (int i = 0; i < 4; i++)
            {
                (*cubes)[indexOfActive].indivCubes[i].h = (*cubes)[indexOfActive].indivCubes[i].w = 40;
            }
            (*cubes)[indexOfActive].indivCubes[0].x = offsetX;
            (*cubes)[indexOfActive].indivCubes[0].y = offsetY;
            (*cubes)[indexOfActive].indivCubes[1].x = offsetX + 40;         //  O 
            (*cubes)[indexOfActive].indivCubes[1].y = offsetY;                  //  OOO
            (*cubes)[indexOfActive].indivCubes[2].x = offsetX + 80;         //
            (*cubes)[indexOfActive].indivCubes[2].y = offsetY;
            (*cubes)[indexOfActive].indivCubes[3].x = offsetX;
            (*cubes)[indexOfActive].indivCubes[3].y = offsetY - 40;
            (*cubes)[indexOfActive].color.r = 0;
            (*cubes)[indexOfActive].color.g = 0;
            (*cubes)[indexOfActive].color.b = 255;
            break;
        case 2:
            for (int i = 0; i < 4; i++)
            {
                (*cubes)[indexOfActive].indivCubes[i].h = (*cubes)[indexOfActive].indivCubes[i].w = 40;
            }
            (*cubes)[indexOfActive].indivCubes[0].x = offsetX;
            (*cubes)[indexOfActive].indivCubes[0].y = offsetY;
            (*cubes)[indexOfActive].indivCubes[1].x = offsetX + 40;                 //    O
            (*cubes)[indexOfActive].indivCubes[1].y = offsetY;                  //  OOO
            (*cubes)[indexOfActive].indivCubes[2].x = offsetX + 80;                 //
            (*cubes)[indexOfActive].indivCubes[2].y = offsetY;
            (*cubes)[indexOfActive].indivCubes[3].x = offsetX + 80;
            (*cubes)[indexOfActive].indivCubes[3].y = offsetY - 40;
            (*cubes)[indexOfActive].color.r = 255;
            (*cubes)[indexOfActive].color.g = 127;
            (*cubes)[indexOfActive].color.b = 0;
            break;
        case 3:
            for (int i = 0; i < 4; i++)
            {
                (*cubes)[indexOfActive].indivCubes[i].h = (*cubes)[indexOfActive].indivCubes[i].w = 40;
            }
            (*cubes)[indexOfActive].indivCubes[0].x = offsetX;
            (*cubes)[indexOfActive].indivCubes[0].y = offsetY - 40;
            (*cubes)[indexOfActive].indivCubes[1].x = offsetX + 40;         //  OO 
            (*cubes)[indexOfActive].indivCubes[1].y = offsetY - 40;                  //  OO
            (*cubes)[indexOfActive].indivCubes[2].x = offsetX;         //
            (*cubes)[indexOfActive].indivCubes[2].y = offsetY;
            (*cubes)[indexOfActive].indivCubes[3].x = offsetX + 40;
            (*cubes)[indexOfActive].indivCubes[3].y = offsetY;
            (*cubes)[indexOfActive].color.r = 255;
            (*cubes)[indexOfActive].color.g = 255;
            (*cubes)[indexOfActive].color.b = 0;
            break;
        case 4:
            for (int i = 0; i < 4; i++)
            {
                (*cubes)[indexOfActive].indivCubes[i].h = (*cubes)[indexOfActive].indivCubes[i].w = 40;
            }
            (*cubes)[indexOfActive].indivCubes[0].x = offsetX;
            (*cubes)[indexOfActive].indivCubes[0].y = offsetY;
            (*cubes)[indexOfActive].indivCubes[1].x = offsetX + 40;                 //   OO
            (*cubes)[indexOfActive].indivCubes[1].y = offsetY;                  //  OO
            (*cubes)[indexOfActive].indivCubes[2].x = offsetX + 40;                 //
            (*cubes)[indexOfActive].indivCubes[2].y = offsetY - 40;
            (*cubes)[indexOfActive].indivCubes[3].x = offsetX + 80;
            (*cubes)[indexOfActive].indivCubes[3].y = offsetY - 40;
            (*cubes)[indexOfActive].color.r = 0;
            (*cubes)[indexOfActive].color.g = 255;
            (*cubes)[indexOfActive].color.b = 0;
            break;
        case 5:
            for (int i = 0; i < 4; i++)
            {
                (*cubes)[indexOfActive].indivCubes[i].h = (*cubes)[indexOfActive].indivCubes[i].w = 40;
            }
            (*cubes)[indexOfActive].indivCubes[0].x = offsetX;
            (*cubes)[indexOfActive].indivCubes[0].y = offsetY;
            (*cubes)[indexOfActive].indivCubes[1].x = offsetX + 40;                 //   O
            (*cubes)[indexOfActive].indivCubes[1].y = offsetY;                  //  OOO
            (*cubes)[indexOfActive].indivCubes[2].x = offsetX + 80;                 //
            (*cubes)[indexOfActive].indivCubes[2].y = offsetY;
            (*cubes)[indexOfActive].indivCubes[3].x = offsetX + 40;
            (*cubes)[indexOfActive].indivCubes[3].y = offsetY - 40;
            (*cubes)[indexOfActive].color.r = 128;
            (*cubes)[indexOfActive].color.g = 0;
            (*cubes)[indexOfActive].color.b = 128;
            break;
        case 6:
            for (int i = 0; i < 4; i++)
            {
                (*cubes)[indexOfActive].indivCubes[i].h = (*cubes)[indexOfActive].indivCubes[i].w = 40;
            }
            (*cubes)[indexOfActive].indivCubes[0].x = offsetX + 40;
            (*cubes)[indexOfActive].indivCubes[0].y = offsetY;
            (*cubes)[indexOfActive].indivCubes[1].x = offsetX + 80;                 //  OO 
            (*cubes)[indexOfActive].indivCubes[1].y = offsetY;                  //   OO
            (*cubes)[indexOfActive].indivCubes[2].x = offsetX;                 //
            (*cubes)[indexOfActive].indivCubes[2].y = offsetY - 40;
            (*cubes)[indexOfActive].indivCubes[3].x = offsetX + 40;
            (*cubes)[indexOfActive].indivCubes[3].y = offsetY - 40;
            (*cubes)[indexOfActive].color.r = 255;
            (*cubes)[indexOfActive].color.g = 0;
            (*cubes)[indexOfActive].color.b = 50;
            break;
    }
    if (isPregenerated == 0)
    {
        for (int activeBlock = 0; activeBlock < 4; activeBlock++)
        {
            for (int numberOfInactiveBlocks = 0; numberOfInactiveBlocks < (numberOfCubesOnScreen - 1); numberOfInactiveBlocks++)
            {
                for (int individualBlock = 0; individualBlock < 4; individualBlock++)
                {   
                    //printf("%d\n\n\n", cubes[indexOfActive].indivCubes[activeBlock].y);
                    if ((*cubes)[indexOfActive].indivCubes[activeBlock].y == (*cubes)[numberOfInactiveBlocks].indivCubes[individualBlock].y && (*cubes)[indexOfActive].indivCubes[activeBlock].x == (*cubes)[numberOfInactiveBlocks].indivCubes[individualBlock].x && (*cubes)[indexOfActive].indivCubes[activeBlock].y <= 130)
                    {
                    *gameOver = 1;
                    //printf("COLLISION DEBUG= Active block: %d\tInactive block:%d (block ID: %d)\n", activeBlock, individualBlock, numberOfInactiveBlocks);
                    }
                }
            }
        }
    }
    

}

int rotateCube(int generatedIndexType, int indexOfActive, int rotation, Cubes **cubes, Cubes **backupCube, int numberOfCubesOnScreen, int isActive)
{
    int collision = 0;
    switch (generatedIndexType)
    {
        case 0:
            switch (rotation)
            {
                case 0:
                    backup(indexOfActive, cubes, backupCube);
                    (*cubes)[indexOfActive].indivCubes[0].x += 80;
                    (*cubes)[indexOfActive].indivCubes[0].y -= 80;               
                    (*cubes)[indexOfActive].indivCubes[1].x += 40;               
                    (*cubes)[indexOfActive].indivCubes[1].y -= 40;
                    (*cubes)[indexOfActive].indivCubes[3].x -= 40;
                    (*cubes)[indexOfActive].indivCubes[3].y += 40;
                    collision = checkForCollisionsAbsolute(numberOfCubesOnScreen, indexOfActive, isActive, *cubes);
                    if (collision == 1)
                    {
                        restore(indexOfActive, cubes, backupCube);
                        //printf("DEBUG= CANNOT ROTATE\n");
                        return 0;
                    }
                    else
                    {
                        return 1;
                    }
                    break;
                case 1:
                    backup(indexOfActive, cubes, backupCube);
                    (*cubes)[indexOfActive].indivCubes[0].x += 40;
                    (*cubes)[indexOfActive].indivCubes[0].y += 80;                             
                    (*cubes)[indexOfActive].indivCubes[1].y += 40;
                    (*cubes)[indexOfActive].indivCubes[2].x -= 40;
                    (*cubes)[indexOfActive].indivCubes[3].x -= 80;
                    (*cubes)[indexOfActive].indivCubes[3].y -= 40;
                    collision = checkForCollisionsAbsolute(numberOfCubesOnScreen, indexOfActive, isActive, *cubes);
                    if (collision == 1)
                    {
                        restore(indexOfActive, cubes, backupCube);
                        //printf("DEBUG= CANNOT ROTATE\n");
                        return 0;
                    }
                    else
                    {
                        return 1;
                    }
                    break;
                case 2:
                    backup(indexOfActive, cubes, backupCube);
                    (*cubes)[indexOfActive].indivCubes[0].x -= 40;
                    (*cubes)[indexOfActive].indivCubes[0].y += 40;               
                    (*cubes)[indexOfActive].indivCubes[2].x += 40;               
                    (*cubes)[indexOfActive].indivCubes[2].y -= 40;
                    (*cubes)[indexOfActive].indivCubes[3].x += 80;
                    (*cubes)[indexOfActive].indivCubes[3].y -= 80;
                    collision = checkForCollisionsAbsolute(numberOfCubesOnScreen, indexOfActive, isActive, *cubes);
                    if (collision == 1)
                    {
                        restore(indexOfActive, cubes, backupCube);
                        //printf("DEBUG= CANNOT ROTATE\n");
                        return 0;
                    }
                    else
                    {
                        return 1;
                    }
                    break;
                case 3:
                    backup(indexOfActive, cubes, backupCube);
                    (*cubes)[indexOfActive].indivCubes[0].x -= 80;
                    (*cubes)[indexOfActive].indivCubes[0].y -= 40;                             
                    (*cubes)[indexOfActive].indivCubes[1].x -= 40;
                    (*cubes)[indexOfActive].indivCubes[2].y += 40;
                    (*cubes)[indexOfActive].indivCubes[3].x += 40;
                    (*cubes)[indexOfActive].indivCubes[3].y += 80;
                    collision = checkForCollisionsAbsolute(numberOfCubesOnScreen, indexOfActive, isActive, *cubes);
                    if (collision == 1)
                    {
                        restore(indexOfActive, cubes, backupCube);
                        //printf("DEBUG= CANNOT ROTATE\n");
                        return 0;
                    }
                    else
                    {
                        return 1;
                    }
                    break;
            }
            break;
        case 1:
            switch (rotation)
            {
                case 0:
                    backup(indexOfActive, cubes, backupCube);
                    (*cubes)[indexOfActive].indivCubes[0].x += 40;
                    (*cubes)[indexOfActive].indivCubes[0].y -= 40;               
                    (*cubes)[indexOfActive].indivCubes[2].x -= 40;               
                    (*cubes)[indexOfActive].indivCubes[2].y += 40;
                    (*cubes)[indexOfActive].indivCubes[3].x += 80;
                    collision = checkForCollisionsAbsolute(numberOfCubesOnScreen, indexOfActive, isActive, *cubes);
                    if (collision == 1)
                    {
                        restore(indexOfActive, cubes, backupCube);
                        //printf("DEBUG= CANNOT ROTATE\n");
                        return 0;
                    }
                    else
                    {
                        return 1;
                    }
                    break;
                case 1:
                    backup(indexOfActive, cubes, backupCube);
                    (*cubes)[indexOfActive].indivCubes[0].x += 40;
                    (*cubes)[indexOfActive].indivCubes[0].y += 40;               
                    (*cubes)[indexOfActive].indivCubes[2].x -= 40;               
                    (*cubes)[indexOfActive].indivCubes[2].y -= 40;
                    (*cubes)[indexOfActive].indivCubes[3].y += 80;
                    collision = checkForCollisionsAbsolute(numberOfCubesOnScreen, indexOfActive, isActive, *cubes);
                    if (collision == 1)
                    {
                        restore(indexOfActive, cubes, backupCube);
                        //printf("DEBUG= CANNOT ROTATE\n");
                        return 0;
                    }
                    else
                    {
                        return 1;
                    }
                    break;
                case 2:
                    backup(indexOfActive, cubes, backupCube);
                    (*cubes)[indexOfActive].indivCubes[0].x -= 40;
                    (*cubes)[indexOfActive].indivCubes[0].y += 40;               
                    (*cubes)[indexOfActive].indivCubes[2].x += 40;               
                    (*cubes)[indexOfActive].indivCubes[2].y -= 40;
                    (*cubes)[indexOfActive].indivCubes[3].x -= 80;
                    collision = checkForCollisionsAbsolute(numberOfCubesOnScreen, indexOfActive, isActive, *cubes);
                    if (collision == 1)
                    {
                        restore(indexOfActive, cubes, backupCube);
                        //printf("DEBUG= CANNOT ROTATE\n");
                        return 0;
                    }
                    else
                    {
                        return 1;
                    }
                    break;
                case 3:
                    backup(indexOfActive, cubes, backupCube);
                    (*cubes)[indexOfActive].indivCubes[0].x -= 40;
                    (*cubes)[indexOfActive].indivCubes[0].y -= 40;               
                    (*cubes)[indexOfActive].indivCubes[2].x += 40;               
                    (*cubes)[indexOfActive].indivCubes[2].y += 40;
                    (*cubes)[indexOfActive].indivCubes[3].y -= 80;
                    collision = checkForCollisionsAbsolute(numberOfCubesOnScreen, indexOfActive, isActive, *cubes);
                    if (collision == 1)
                    {
                        restore(indexOfActive, cubes, backupCube);
                        //printf("DEBUG= CANNOT ROTATE\n");
                        return 0;
                    }
                    else
                    {
                        return 1;
                    }
                    break;
            }
            break;
        case 2:
            switch (rotation)
            {
                case 0:
                    backup(indexOfActive, cubes, backupCube);
                    (*cubes)[indexOfActive].indivCubes[0].x += 40;
                    (*cubes)[indexOfActive].indivCubes[0].y -= 40;               
                    (*cubes)[indexOfActive].indivCubes[2].x -= 40;               
                    (*cubes)[indexOfActive].indivCubes[2].y += 40;
                    (*cubes)[indexOfActive].indivCubes[3].y += 80;
                    collision = checkForCollisionsAbsolute(numberOfCubesOnScreen, indexOfActive, isActive, *cubes);
                    if (collision == 1)
                    {
                        restore(indexOfActive, cubes, backupCube);
                        //printf("DEBUG= CANNOT ROTATE\n");
                        return 0;
                    }
                    else
                    {
                        return 1;
                    }
                    break;
                case 1:
                    backup(indexOfActive, cubes, backupCube);
                    (*cubes)[indexOfActive].indivCubes[0].x += 40;
                    (*cubes)[indexOfActive].indivCubes[0].y += 40;               
                    (*cubes)[indexOfActive].indivCubes[2].x -= 40;               
                    (*cubes)[indexOfActive].indivCubes[2].y -= 40;
                    (*cubes)[indexOfActive].indivCubes[3].x -= 80;
                    collision = checkForCollisionsAbsolute(numberOfCubesOnScreen, indexOfActive, isActive, *cubes);
                    if (collision == 1)
                    {
                        restore(indexOfActive, cubes, backupCube);
                        //printf("DEBUG= CANNOT ROTATE\n");
                        return 0;
                    }
                    else
                    {
                        return 1;
                    }
                    break;
                case 2:
                    backup(indexOfActive, cubes, backupCube);
                    (*cubes)[indexOfActive].indivCubes[0].x -= 40;
                    (*cubes)[indexOfActive].indivCubes[0].y += 40;               
                    (*cubes)[indexOfActive].indivCubes[2].x += 40;               
                    (*cubes)[indexOfActive].indivCubes[2].y -= 40;
                    (*cubes)[indexOfActive].indivCubes[3].y -= 80;
                    collision = checkForCollisionsAbsolute(numberOfCubesOnScreen, indexOfActive, isActive, *cubes);
                    if (collision == 1)
                    {
                        restore(indexOfActive, cubes, backupCube);
                        //printf("DEBUG= CANNOT ROTATE\n");
                        return 0;
                    }
                    else
                    {
                        return 1;
                    }
                    break;
                case 3:
                    backup(indexOfActive, cubes, backupCube);
                    (*cubes)[indexOfActive].indivCubes[0].x -= 40;
                    (*cubes)[indexOfActive].indivCubes[0].y -= 40;               
                    (*cubes)[indexOfActive].indivCubes[2].x += 40;               
                    (*cubes)[indexOfActive].indivCubes[2].y += 40;
                    (*cubes)[indexOfActive].indivCubes[3].x += 80;
                    collision = checkForCollisionsAbsolute(numberOfCubesOnScreen, indexOfActive, isActive, *cubes);
                    if (collision == 1)
                    {
                        restore(indexOfActive, cubes, backupCube);
                        //printf("DEBUG= CANNOT ROTATE\n");
                        return 0;
                    }
                    else
                    {
                        return 1;
                    }
                    break;
            }
            break;
        case 4:
            switch (rotation)
            {
                case 0:
                    backup(indexOfActive, cubes, backupCube);
                    (*cubes)[indexOfActive].indivCubes[0].x += 40;
                    (*cubes)[indexOfActive].indivCubes[0].y -= 80;               
                    (*cubes)[indexOfActive].indivCubes[1].y -= 40;               
                    (*cubes)[indexOfActive].indivCubes[2].x += 40;
                    (*cubes)[indexOfActive].indivCubes[3].y += 40;
                    collision = checkForCollisionsAbsolute(numberOfCubesOnScreen, indexOfActive, isActive, *cubes);
                    if (collision == 1)
                    {
                        restore(indexOfActive, cubes, backupCube);
                        //printf("DEBUG= CANNOT ROTATE\n");
                        return 0;
                    }
                    else
                    {
                        return 1;
                    }
                    break;
                case 1:
                    backup(indexOfActive, cubes, backupCube);
                    (*cubes)[indexOfActive].indivCubes[0].x += 40;
                    (*cubes)[indexOfActive].indivCubes[0].y += 40;               
                    (*cubes)[indexOfActive].indivCubes[2].x -= 40;               
                    (*cubes)[indexOfActive].indivCubes[2].y += 40;
                    (*cubes)[indexOfActive].indivCubes[3].x -= 80;
                    collision = checkForCollisionsAbsolute(numberOfCubesOnScreen, indexOfActive, isActive, *cubes);
                    if (collision == 1)
                    {
                        restore(indexOfActive, cubes, backupCube);
                        //printf("DEBUG= CANNOT ROTATE\n");
                        return 0;
                    }
                    else
                    {
                        return 1;
                    }
                    break;
                case 2:
                    backup(indexOfActive, cubes, backupCube);
                    (*cubes)[indexOfActive].indivCubes[0].y += 40;
                    (*cubes)[indexOfActive].indivCubes[1].x += 40;               
                    (*cubes)[indexOfActive].indivCubes[2].y -= 40;               
                    (*cubes)[indexOfActive].indivCubes[3].x += 40;
                    (*cubes)[indexOfActive].indivCubes[3].y -= 80;
                    collision = checkForCollisionsAbsolute(numberOfCubesOnScreen, indexOfActive, isActive, *cubes);
                    if (collision == 1)
                    {
                        restore(indexOfActive, cubes, backupCube);
                        //printf("DEBUG= CANNOT ROTATE\n");
                        return 0;
                    }
                    else
                    {
                        return 1;
                    }
                    break;
                case 3:
                    backup(indexOfActive, cubes, backupCube);
                    (*cubes)[indexOfActive].indivCubes[0].x -= 80;
                    (*cubes)[indexOfActive].indivCubes[1].x -= 40;  
                    (*cubes)[indexOfActive].indivCubes[1].y += 40;                            
                    (*cubes)[indexOfActive].indivCubes[3].x += 40;
                    (*cubes)[indexOfActive].indivCubes[3].y += 40;
                    collision = checkForCollisionsAbsolute(numberOfCubesOnScreen, indexOfActive, isActive, *cubes);
                    if (collision == 1)
                    {
                        restore(indexOfActive, cubes, backupCube);
                        //printf("DEBUG= CANNOT ROTATE\n");
                        return 0;
                    }
                    else
                    {
                        return 1;
                    }
                    break;
            }
            break;
        case 5:
            switch (rotation)
            {
                case 0:
                    backup(indexOfActive, cubes, backupCube);
                    (*cubes)[indexOfActive].indivCubes[0].y -= 80;
                    (*cubes)[indexOfActive].indivCubes[1].x -= 40;               
                    (*cubes)[indexOfActive].indivCubes[1].y -= 40;               
                    (*cubes)[indexOfActive].indivCubes[2].x -= 80;
                    collision = checkForCollisionsAbsolute(numberOfCubesOnScreen, indexOfActive, isActive, *cubes);
                    if (collision == 1)
                    {
                        restore(indexOfActive, cubes, backupCube);
                        //printf("DEBUG= CANNOT ROTATE\n");
                        return 0;
                    }
                    else
                    {
                        return 1;
                    }
                    break;
                case 1:
                    backup(indexOfActive, cubes, backupCube);
                    (*cubes)[indexOfActive].indivCubes[0].x += 80;
                    (*cubes)[indexOfActive].indivCubes[1].x += 40;               
                    (*cubes)[indexOfActive].indivCubes[1].y -= 40;               
                    (*cubes)[indexOfActive].indivCubes[2].y -= 80;
                    collision = checkForCollisionsAbsolute(numberOfCubesOnScreen, indexOfActive, isActive, *cubes);
                    if (collision == 1)
                    {
                        restore(indexOfActive, cubes, backupCube);
                        //printf("DEBUG= CANNOT ROTATE\n");
                        return 0;
                    }
                    else
                    {
                        return 1;
                    }
                    break;
                case 2:
                    backup(indexOfActive, cubes, backupCube);
                    (*cubes)[indexOfActive].indivCubes[0].y += 80;
                    (*cubes)[indexOfActive].indivCubes[1].x += 40;               
                    (*cubes)[indexOfActive].indivCubes[1].y += 40;               
                    (*cubes)[indexOfActive].indivCubes[2].x += 80;
                    collision = checkForCollisionsAbsolute(numberOfCubesOnScreen, indexOfActive, isActive, *cubes);
                    if (collision == 1)
                    {
                        restore(indexOfActive, cubes, backupCube);
                        //printf("DEBUG= CANNOT ROTATE\n");
                        return 0;
                    }
                    else
                    {
                        return 1;
                    }
                    break;
                case 3:
                    backup(indexOfActive, cubes, backupCube);
                    (*cubes)[indexOfActive].indivCubes[0].x -= 80;
                    (*cubes)[indexOfActive].indivCubes[1].x -= 40;               
                    (*cubes)[indexOfActive].indivCubes[1].y += 40;               
                    (*cubes)[indexOfActive].indivCubes[2].y += 80;
                    collision = checkForCollisionsAbsolute(numberOfCubesOnScreen, indexOfActive, isActive, *cubes);
                    if (collision == 1)
                    {
                        restore(indexOfActive, cubes, backupCube);
                        //printf("DEBUG= CANNOT ROTATE\n");
                        return 0;
                    }
                    else
                    {
                        return 1;
                    }
                    break;
            }
            break;
        case 6:
            switch (rotation)
            {
                case 0:
                    backup(indexOfActive, cubes, backupCube);
                    (*cubes)[indexOfActive].indivCubes[0].y -= 40;
                    (*cubes)[indexOfActive].indivCubes[1].x -= 40;               
                    (*cubes)[indexOfActive].indivCubes[3].x += 40;               
                    (*cubes)[indexOfActive].indivCubes[2].x += 80;
                    (*cubes)[indexOfActive].indivCubes[2].y -= 40;
                    collision = checkForCollisionsAbsolute(numberOfCubesOnScreen, indexOfActive, isActive, *cubes);
                    if (collision == 1)
                    {
                        restore(indexOfActive, cubes, backupCube);
                        //printf("DEBUG= CANNOT ROTATE\n");
                        return 0;
                    }
                    else
                    {
                        return 1;
                    }
                    break;
                case 1:
                    backup(indexOfActive, cubes, backupCube);
                    (*cubes)[indexOfActive].indivCubes[1].x -= 40;
                    (*cubes)[indexOfActive].indivCubes[1].y -= 40;               
                    (*cubes)[indexOfActive].indivCubes[2].y += 80;               
                    (*cubes)[indexOfActive].indivCubes[3].x -= 40;
                    (*cubes)[indexOfActive].indivCubes[3].y += 40;
                    collision = checkForCollisionsAbsolute(numberOfCubesOnScreen, indexOfActive, isActive, *cubes);
                    if (collision == 1)
                    {
                        restore(indexOfActive, cubes, backupCube);
                        //printf("DEBUG= CANNOT ROTATE\n");
                        return 0;
                    }
                    else
                    {
                        return 1;
                    }
                    break;
                case 2:
                    backup(indexOfActive, cubes, backupCube);
                    (*cubes)[indexOfActive].indivCubes[0].x += 40;
                    (*cubes)[indexOfActive].indivCubes[1].x += 80;               
                    (*cubes)[indexOfActive].indivCubes[1].y -= 40;               
                    (*cubes)[indexOfActive].indivCubes[2].x -= 40;
                    (*cubes)[indexOfActive].indivCubes[3].y -= 40;
                    collision = checkForCollisionsAbsolute(numberOfCubesOnScreen, indexOfActive, isActive, *cubes);
                    if (collision == 1)
                    {
                        restore(indexOfActive, cubes, backupCube);
                        //printf("DEBUG= CANNOT ROTATE\n");
                        return 0;
                    }
                    else
                    {
                        return 1;
                    }
                    break;
                case 3:
                    backup(indexOfActive, cubes, backupCube);
                    (*cubes)[indexOfActive].indivCubes[0].x -= 40;
                    (*cubes)[indexOfActive].indivCubes[0].y += 40;  
                    (*cubes)[indexOfActive].indivCubes[1].y += 80;                            
                    (*cubes)[indexOfActive].indivCubes[2].x -= 40;
                    (*cubes)[indexOfActive].indivCubes[2].y -= 40;
                    collision = checkForCollisionsAbsolute(numberOfCubesOnScreen, indexOfActive, isActive, *cubes);
                    if (collision == 1)
                    {
                        restore(indexOfActive, cubes, backupCube);
                        //printf("DEBUG= CANNOT ROTATE\n");
                        return 0;
                    }
                    else
                    {
                        return 1;
                    }
                    break;
            }
            break;
        case 7:
            // nothing to happen, skipping
            break;
    }
}

int fullRowCheck(Cubes **cubes, Row_data **row_data, int indexOfActive)
{
    int temp;
    int isAnyFull = 0;
    for (int i = 0; i < 4; i++)
    {
        temp = ((*cubes)[indexOfActive].indivCubes[i].y - 50) / 40;
        (*row_data)->rows[temp]++;
        if ((*row_data)->rows[temp] == 9)
        {
            (*row_data)->isFull[temp] = 1;
        }
    }    
    for (int i = 0; i < 15; i++)
    {
        if ((*row_data)->isFull[i] == 1)
        {
            isAnyFull = 1;
        }
    }
    if (isAnyFull == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    
}

void rowDeletion(Cubes **cubes, Row_data **row_data, int numberOfCubesOnScreen, Game **game)
{
    for (int i = 0; i < 15; i++)
    {
        if ((*row_data)->isFull[i] == 1)
        {
            (*game)->score++;
            (*row_data)->isFull[i] = 0;
            (*row_data)->rows[i] = 0;
            printf("Row %d full. Deleting...\n", i);
            for (int rowToMove = i; rowToMove >= 0; rowToMove--)
            {
                if (rowToMove != 0)
                {
                    (*row_data)->rows[rowToMove] = (*row_data)->rows[rowToMove - 1];
                    (*row_data)->isFull[rowToMove] = (*row_data)->isFull[rowToMove - 1];    
                }
                else
                {
                    (*row_data)->rows[rowToMove] = 0;
                    (*row_data)->isFull[rowToMove] = 0;
                }
                if (rowToMove == i)         // vymazani plneho radku
                {
                    for (int z = 0; z < numberOfCubesOnScreen; z++)
                    {
                        for (int z2 = 0; z2 < 4; z2++)
                        {
                            if ((*cubes)[z].indivCubes[z2].y == (50 + (rowToMove * 40)))
                            {
                                (*cubes)[z].indivCubes[z2].x = 0;
                                (*cubes)[z].indivCubes[z2].y = 0;
                            }
                        }
                    }
                }
                else                        // posun ostatnich radku dolu
                {
                    for (int z = 0; z < numberOfCubesOnScreen; z++)
                    {
                        for (int z2 = 0; z2 < 4; z2++)
                        {
                            if ((*cubes)[z].indivCubes[z2].y == (50 + (rowToMove * 40)))
                            {
                                (*cubes)[z].indivCubes[z2].y += 40;
                            }
                        }
                    }
                }
                
            }

        }
    }
}