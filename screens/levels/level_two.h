#include "../../components/phase.h"

#include "raylib.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//----------------------------------------------------------------------------------
// Global Variables DefInition (local to this module)
//----------------------------------------------------------------------------------

// Gameplay screen global variables
static int framesCounter;
static int finishScreen;
static int isAlive;
Vector2 playerBlock;
static int cameraTarget;

static FILE *fileWriteLevelTwo;
static FILE *fileReadLevelTwoCurrentUser;
static FILE *fileReadLevelTwo;

static char usernameLevelTwo[300];
static char nickLevelTwo[100];
static char currentUserLevelTwo[100];
static char spaceLevelTwo[100];

//----------------------------------------------------------------------------------
// Gameplay Screen Functions DefInition
//----------------------------------------------------------------------------------

// Gameplay Screen Initialization logic
void InitLevelTwoScreen(void)
{
    // TODO: Initialize GAMEPLAY screen variables here!
    framesCounter = 0;
    finishScreen = 0;
    isAlive = 1;

    cameraTarget = 200;

    StartVariables();
    LoadAllTextures();
    CreateEnemiesMap(2);
    CreateMap(2);
    CreateWall(7,106);
    
    fileWriteLevelTwo = fopen("save/save.txt", "a");
    fileReadLevelTwo = fopen("save/save.txt", "r");
    fileReadLevelTwoCurrentUser = fopen("save/current_player.txt", "r");

}

void UpdateLevelTwoScreen(void)
{

    framesCounter++;
    // TODO: Update GAMEPLAY screen variables here!
    camera.target = (Vector2){cameraTarget, hero.physic->position.y > 100 ? 200 : hero.physic->position.y + 100};
    cameraTarget += 2.5;

    if ( hero.body.x + hero.body.width < cameraTarget - (screenWidth / 2) ) KillPlayer(&hero);
    //_________________________________________________________
    UpdateGame(&hero);
    UpdateEnemy();
    //get the physical part of map
    ActivatePhysics();

    if(hero.isAlive == false && isAlive != 0){
        isAlive = 0; 
        framesCounter = 0;
    }

    if(framesCounter>120 && isAlive == 0){
        finishScreen = 1;
    }

    //_________________________________________________
    //get the player coordinate in blocks
    playerBlock = GetPlayerBlock();

    fgets(currentUserLevelTwo, 300, fileReadLevelTwoCurrentUser);
    fclose(fileReadLevelTwoCurrentUser);

    if(fileWriteLevelTwo == NULL){

    }else{
        while(fgets(usernameLevelTwo, 300, fileReadLevelTwo)!= NULL){

        }
        fclose(fileReadLevelTwo);

        strcpy(spaceLevelTwo, " ");
        strcat(spaceLevelTwo, currentUserLevelTwo);
        strcpy(nickLevelTwo, spaceLevelTwo);
        strcat(nickLevelTwo, " 2");

        if (strstr(usernameLevelTwo, nickLevelTwo) != NULL){
                
        }else{
            fprintf(fileWriteLevelTwo, " %s %i ", currentUserLevelTwo, 2);
            fclose(fileWriteLevelTwo);
        }
    }

    // Press enter or tap to change to ENDING screen
    if (playerBlock.x == 105)
    {
        finishScreen = 1;
    }
    // Condition to end the level if the player gets out of the screen
    // else if (playerBlock.x == cameraTarget)
    // {
    //     FinishScreen = 2;
    // }
}

// Gameplay Screen Draw logic
void DrawLevelTwoScreen(void)
{
    DrawTexture(background, 0, 0, WHITE);
    BeginMode2D(camera);
        DrawTextureMap();
        DrawEnemy();
        DrawEntities(&hero);

    EndMode2D();    
    DrawLifeBar(&hero);
    //DrawText(TextFormat("bloco: [%i,%i]\ncoordenada: [%f,%f]", (int)(playerBlock.x), (int)(playerBlock.y),(hero.physic->position.x),(hero.physic->position.y)), 315, 250, 20, DARKGRAY);
    //DrawFPS(screenWidth - 90, screenHeight - 30);
}

// Gameplay Screen Unload logic
void UnloadLevelTwoScreen(void)
{
    DestroyWalls();
    DestroyAllPhysics();
    UnloadAllTextures();
}

// Gameplay Screen should Finish?
int FinishLevelTwoScreen(void)
{
    return finishScreen;
}

int IsAliveLevelTwo(void)
{
    return isAlive;
}