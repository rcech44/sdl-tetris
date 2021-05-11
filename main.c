#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "sdl.h"
#include "source.h"
#include "audio.h"

int main() {
    srand(time(NULL));

    // deklarovani zakladnich promennych
    int width = 800;
    int height = 700;
    int isActive = 0, numberOfCubesOnScreen = 0, rotation = 0, successfulRotation = 0, startActive = 0, readyToDelete = 0, gameOver = 0, gameSpeed = 0;
    int indexOfActive = -1;
    int allowedMove = 1;
    int generatedIndexType = 7;       // special code for skipping first rotation
    int pregeneratedIndexType = rand() % (6 - 0 + 1) + 0;
    char blockText[128], scoreText1[128], scoreText2[128], difficultyText[128];
    char buffer[64];
    int difficultyTime = 1000;
    bool menu = true;
    bool quit = false;
    double remaining = 0;
    
    // deklarovani textu a struktur
    snprintf(blockText, 128, "%s", "Next block:");
    snprintf(scoreText1, 128, "%s", "Your score:");
    snprintf(difficultyText, 128, "%s", "Difficulty: Easy");
    
    Game *game = malloc(sizeof(Game));
    Cubes *cubes = malloc(sizeof(Cubes)*1000);
    Cubes *backupCube = malloc(sizeof(Cubes));
    Cubes *pregeneratedCube = malloc(sizeof(Cubes));
    SDL_Rect mouse_cube;
    SDL_Rect menuSetting1; menuSetting1.w = 400; menuSetting1.h = 80; menuSetting1.x = 200; menuSetting1.y = 450;
    SDL_Rect menuSetting0; menuSetting0.w = 400; menuSetting0.h = 80; menuSetting0.x = 200; menuSetting0.y = 300;
    SDL_Rect gameOverBox; gameOverBox.w = 300; gameOverBox.h = 80; gameOverBox.x = 80; gameOverBox.y = 310;
    Row_data *row_data = malloc(sizeof(Row_data));

    row_data[0].rows = malloc(sizeof(int)*15);
    row_data[0].isFull = malloc(sizeof(int)*15);
    backupCube[0].indivCubes = malloc(sizeof(SDL_Rect)*4);
    pregeneratedCube[0].indivCubes = malloc(sizeof(SDL_Rect)*4);

    game->score = 0;
    mouse_cube.w = mouse_cube.h = 6;

    for (int i = 0; i < 1000; i++)      // pro jistotu, at je dost pameti
    {
        cubes[i].indivCubes = malloc(sizeof(SDL_Rect)*4);
    }

    for (int i = 0; i < 15; i++)
    {
        row_data[0].rows[i] = 0;
        row_data[0].isFull[i] = 0;
    }

    // initialize SDL and create window (for details see sdl.h/sdl.c)
    SDL_Init(SDL_INIT_AUDIO);
    initAudio();
    playMusic("terraria-tetris.wav", SDL_MIX_MAXVOLUME);
    SDL_Context *ctx = sdl_context_new("Tetris", width, height);
    SDL_SetWindowSize(ctx->window, width, height);
    TTF_Font* Roboto_FPS = TTF_OpenFont("Roboto-Regular.ttf", 20);
    TTF_Font* Roboto_Game1 = TTF_OpenFont("Roboto-Regular.ttf", 30);
    TTF_Font* Roboto_Game2 = TTF_OpenFont("Roboto-Regular.ttf", 175);
    TTF_Font* Roboto_Game3 = TTF_OpenFont("Roboto-Regular.ttf", 45);
    TTF_Font* Roboto_Menu1 = TTF_OpenFont("Roboto-Regular.ttf", 35);
    SDL_Texture *image = IMG_LoadTexture(ctx->renderer, "tetris.png");
    if (image == NULL) {
        fprintf(stderr, "Failed to load image: %s\n", SDL_GetError());
    return 1;
    } 
    SDL_Color White = {255, 255, 255, 255};
    SDL_Point Mouse;
    if (image == NULL) {
        fprintf(stderr, "Failed to load image: %s\n", SDL_GetError());
        return 1;
    }
    Uint64 prevCounter = SDL_GetPerformanceCounter();
    while (menu)
    {
        Uint64 now = SDL_GetPerformanceCounter();
        double elapsed_ms = (now - prevCounter) * 1000 / (double) SDL_GetPerformanceFrequency();
        prevCounter = now;
        //printf("FPS: %d\n", (int)(1000.0 / elapsed_ms));
        SDL_Event e;

        while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                    break;
                }
                else if (e.type == SDL_KEYDOWN) {
                    // key is pressed DOWN
                    switch (e.key.keysym.sym) {
                    case SDLK_SPACE:
                        break;
                    case SDLK_ESCAPE:
                        menu = false;
                        quit = true;
                        break;
                    }
                } else if(e.type == SDL_MOUSEMOTION) {
                    // mouse move
                    //printf("mouse x=%d y=%d\n", e.motion.x, e.motion.y);
                    Mouse.x = e.motion.x;
                    Mouse.y = e.motion.y;
                    mouse_cube.x = Mouse.x - 3;
                    mouse_cube.y = Mouse.y - 3;
                } else if(e.type == SDL_MOUSEBUTTONUP) {
                    switch (e.button.button)
                    {
                        case SDL_BUTTON_LEFT:
                            // check for click on button 1
                            if (Mouse.x >= 200 && Mouse.x <= 600 && Mouse.y >= 300 && Mouse.y <= 380)
                            {
                                menu = false;
                            }
                            
                            // check for click on button 2
                            if (Mouse.x >= 200 && Mouse.x <= 600 && Mouse.y >= 450 && Mouse.y <= 530)
                            {
                                gameSpeed++;
                                switch (gameSpeed)
                                {
                                    case 0:
                                        snprintf(difficultyText, 128, "%s", "Difficulty: Easy");
                                        difficultyTime = 1000;
                                        break;
                                    case 1:
                                        snprintf(difficultyText, 128, "%s", "Difficulty: Medium");          // lowPeak's most favorite
                                        difficultyTime = 600;
                                        break;
                                    case 2:
                                        snprintf(difficultyText, 128, "%s", "Difficulty: Hard");
                                        difficultyTime = 350;
                                        break;
                                    case 3:
                                        snprintf(difficultyText, 128, "%s", "Difficulty: GLHF :)");
                                        difficultyTime = 150;
                                        printf("...well good luck with that lol\n");
                                        break;
                                }
                                if (gameSpeed == 4)
                                {
                                    gameSpeed = 0;
                                    difficultyTime = 1000;
                                    snprintf(difficultyText, 128, "%s", "Difficulty: Easy");
                                }
                            }
                            break;
                    }
                    // e.button.button: SDL_BUTTON_LEFT, SDL_BUTTON_MIDDLE, SDL_BUTTON_RIGHT
                    //printf("mouse x=%d y=%d button=%d\n", e.button.x, e.button.y, e.button.button);
                }
                }
                SDL_SetRenderDrawColor(ctx->renderer, 0, 0, 40, 255);
                SDL_RenderClear(ctx->renderer);
                
                // mouse hover on
                if (Mouse.x >= 200 && Mouse.x <= 600 && Mouse.y >= 300 && Mouse.y <= 380)
                {
                    SDL_SetRenderDrawColor(ctx->renderer, 20, 20, 130, 255);
                }
                else
                {
                    SDL_SetRenderDrawColor(ctx->renderer, 50, 50, 200, 255);
                }
                SDL_RenderFillRect(ctx->renderer, &menuSetting0);
                if (Mouse.x >= 200 && Mouse.x <= 600 && Mouse.y >= 450 && Mouse.y <= 530)
                {
                    SDL_SetRenderDrawColor(ctx->renderer, 20, 20, 130, 255);
                }
                else
                {
                    SDL_SetRenderDrawColor(ctx->renderer, 50, 50, 200, 255);
                }
                SDL_RenderFillRect(ctx->renderer, &menuSetting1);
                SDL_SetRenderDrawColor(ctx->renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(ctx->renderer, &mouse_cube);
                draw_text(ctx->renderer, Roboto_Menu1, difficultyText, 400, 470, White, true);
                draw_text(ctx->renderer, Roboto_Menu1, "Play", 400, 320, White, true);
                SDL_SetRenderDrawColor(ctx->renderer, 255, 255, 255, 0);
                SDL_Rect r;
                r.w = 391;
                r.h = 128;
                r.x = 210;
                r.y = 110;
                SDL_Rect r_image;
                r_image.w = r_image.h = 512;
                r_image.y = 0;
                r_image.x = 0;
                SDL_RenderFillRect(ctx->renderer, &r);
                SDL_RenderCopy(ctx->renderer, image, &r_image, &r);
                SDL_RenderPresent(ctx->renderer);

                if (remaining <= 0)
                {
                    //printf("DEBUG\n");
                    remaining = difficultyTime;
                }
                else
                {
                remaining -= elapsed_ms;
                }
                
            // menu = false;
        }

    while (!quit) {
        Uint64 now = SDL_GetPerformanceCounter();
        double elapsed_ms = (now - prevCounter) * 1000 / (double) SDL_GetPerformanceFrequency();
        prevCounter = now;
        //printf("FPS: %d\n", (int)(1000.0 / elapsed_ms));
        snprintf(buffer, sizeof(buffer), "%d", (int)(1000.0 / elapsed_ms));
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            quit = true;
            break;
        }
        else if (e.type == SDL_KEYDOWN) {
            // key is pressed DOWN
            switch (e.key.keysym.sym) {
            case SDLK_SPACE:
                if (generatedIndexType != 3)
                {
                    successfulRotation = rotateCube(generatedIndexType, indexOfActive, rotation, &cubes, &backupCube, numberOfCubesOnScreen, isActive);
                    if (successfulRotation == 1)
                    {
                        rotation++;
                        if (rotation == 4)
                        {
                            rotation = 0;
                        }      
                    }
                }
                break;
            case SDLK_ESCAPE:
            case SDLK_q:
                quit = true;
                break;
            case SDLK_DOWN:
                isActive = checkForCollisionsY(numberOfCubesOnScreen, indexOfActive, isActive, cubes);
                for (int i = 0; i < 4; i++)           // kontrola out of bounds
                    {
                        if (cubes[indexOfActive].indivCubes[i].y == 610)
                        {
                            isActive = 0;
                        }
                    }
                if (isActive == 1)
                {
                    for (int i = 0; i < 4; i++)
                    {
                        cubes[indexOfActive].indivCubes[i].y += 40;
                    }
                }
                
                break;
                case SDLK_RIGHT:
                //allowedMove = 1;
                allowedMove = checkForCollisionsX(numberOfCubesOnScreen, indexOfActive, isActive, cubes, 1);
                if (isActive == 1)
                {
                    for (int i = 0; i < 4; i++)
                    {
                        if (cubes[indexOfActive].indivCubes[i].x >= 370)
                        {
                            allowedMove = 0;
                        }
                    }
                    for (int i = 0; i < 4; i++)
                    {
                        if (allowedMove == 1)
                        {
                            cubes[indexOfActive].indivCubes[i].x += 40;
                        }
                    }
                }
                break;
                case SDLK_LEFT:
                //allowedMove = 1;
                allowedMove = checkForCollisionsX(numberOfCubesOnScreen, indexOfActive, isActive, cubes, 0);
                if (isActive == 1)
                {
                    for (int i = 0; i < 4; i++)
                    {
                        if (cubes[indexOfActive].indivCubes[i].x <= 50)
                        {
                            allowedMove = 0;
                        }
                    }

                    for (int i = 0; i < 4; i++)
                    {
                        if (allowedMove == 1)
                        {
                            cubes[indexOfActive].indivCubes[i].x -= 40;
                        }
                        
                    }
                }
                break;

            }
        }
        }
        SDL_SetRenderDrawColor(ctx->renderer, 0, 0, 40, 255);
        SDL_RenderClear(ctx->renderer);
        draw_text(ctx->renderer, Roboto_FPS, buffer, 0, 0, (SDL_Color){255, 255, 255, 255}, 0);

        if (remaining <= 0)
        {
            if (isActive == 0 && startActive == 1)
            {
                // kontrola zaplneneho radku jeste nez se vygeneruje novy tvar

                readyToDelete = fullRowCheck(&cubes, &row_data, indexOfActive);
                if (readyToDelete == 1)
                {
                    rowDeletion(&cubes, &row_data, numberOfCubesOnScreen, &game);
                }
            }
            if (isActive == 0)        // zde se generuje nova kostka, ve switchi jsou kostky definovane
            {
                startActive = 1;
                isActive = 1; 
                rotation = 0;
                indexOfActive++;
                numberOfCubesOnScreen++;
                generatedIndexType = pregeneratedIndexType;
                pregeneratedIndexType = rand() % (6 - 0 + 1) + 0;
                generateCube(pregeneratedIndexType, 0, &pregeneratedCube, 1, &gameOver, numberOfCubesOnScreen);
                pregeneratedCubeEdit(&pregeneratedCube, pregeneratedIndexType);
                //generatedIndexType = 0;         // testovani rotace
                generateCube(generatedIndexType, indexOfActive, &cubes, 0, &gameOver, numberOfCubesOnScreen);
            }
            else    // isActive = 1
            {
                isActive = checkForCollisionsY(numberOfCubesOnScreen, indexOfActive, isActive, cubes);
                if (isActive == 1)
                {
                    for (int i = 0; i < 4; i++)           // kontrola out of bounds
                    {
                        if (cubes[indexOfActive].indivCubes[i].y == 610)
                        {
                            isActive = 0;
                        }
                    }
                }
                if (isActive == 1)
                {
                    for (int i = 0; i < 4; i++)           // posun dolu
                    {
                        cubes[indexOfActive].indivCubes[i].y += 40;
                        // printf("%d      %d\n", cubes[0].indivCubes[0].y, cubes[indexOfActive].indivCubes[0].y);
                    }
                }
            }

            remaining = difficultyTime;
            //printf("%d\n", indexOfActive);
        }
        else
        {
            remaining -= elapsed_ms;
        }

        // rendering standard non-active and active cubes
        for (int i = 0; i < numberOfCubesOnScreen; i++)
        {
            SDL_SetRenderDrawColor(ctx->renderer, cubes[i].color.r, cubes[i].color.g, cubes[i].color.b, 255);
            for (int y = 0; y < 4; y++)
            {
                if (cubes[i].indivCubes[y].x == 0 && cubes[i].indivCubes[y].y == 0)
                {

                }
                else
                {
                    SDL_RenderFillRect(ctx->renderer, &cubes[i].indivCubes[y]);    
                }
            }
        }

        // rendering pre-generated cube
        SDL_SetRenderDrawColor(ctx->renderer, pregeneratedCube[0].color.r, pregeneratedCube[0].color.g, pregeneratedCube[0].color.b, 255);
        for (int y = 0; y < 4; y++)
        {
            SDL_RenderFillRect(ctx->renderer, &pregeneratedCube[0].indivCubes[y]);
        }

        // rendering next block text
        draw_text(ctx->renderer, Roboto_Game1, blockText, 535, 90, White, false);

        // rendering your score text
        draw_text(ctx->renderer, Roboto_Game1, scoreText1, 535, 400, White, false);

        // rendering current score text
        snprintf(scoreText2, 128, "%d", game->score);
        draw_text(ctx->renderer, Roboto_Game2, scoreText2, 610, 440, White, true);

        // rendering game field lines
        SDL_SetRenderDrawColor(ctx->renderer, 120, 120, 120, 255);
        int x_offset = 50;
        for (int i = 0; i < 10; i++)
        {
            SDL_RenderDrawLine(ctx->renderer, x_offset, 50, x_offset, 650);
            x_offset += 40;
        }
        int y_offset = 50;
        for (int i = 0; i < 16; i++)
        {
            SDL_RenderDrawLine(ctx->renderer, 50, y_offset, 411, y_offset);
            y_offset += 40;
        } 

        // final gameOver sequence
        if (gameOver == 1)
        {
            SDL_SetRenderDrawColor(ctx->renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(ctx->renderer, &gameOverBox);
            draw_text(ctx->renderer, Roboto_Game3, "Game over!", 116, 325, White, false);
            quit = true;
            SDL_RenderPresent(ctx->renderer);


            // kdyz uz je ta hra over, tak se uvidime u zaverecneho testu, zatim :)

            usleep(4000000);
        }

        SDL_RenderPresent(ctx->renderer);
    }

        free(game);
    for (int i = 0; i < 1000; i++)
    {
        free(cubes[i].indivCubes);
    }
    free(cubes);
    free(backupCube->indivCubes);
    free(backupCube);
    free(pregeneratedCube->indivCubes);
    free(pregeneratedCube);
    free(row_data->isFull);
    free(row_data->rows);
    free(row_data);
    // row_data[0].rows = malloc(sizeof(int)*15);
    // row_data[0].isFull = malloc(sizeof(int)*15);
    // backupCube[0].indivCubes = malloc(sizeof(SDL_Rect)*4);
    // pregeneratedCube[0].indivCubes = malloc(sizeof(SDL_Rect)*4);
    // cleanup all resources
    SDL_DestroyTexture(image);
    sdl_context_delete(ctx);
    return 0;
}