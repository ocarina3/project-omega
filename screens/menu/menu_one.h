#include "raylib.h"
#include <math.h> 
#include <stdlib.h> 

//----------------------------------------------------------------------------------
// Global Variables DefInition (local to this module)
//----------------------------------------------------------------------------------

// Gameplay screen global variables
static int framesCounter;
static int finishScreen;
static int hasEnterBeenPressed;

static Texture2D new;       
static Texture2D load;        
static Texture2D quit;       
static Texture2D currentTexture;
static int currentCounter;

static Music theme;
static Sound enter ;
static Sound selection;

static Vector2 scleraLeftPosition = { 800/2 - 65, 450/2 - 150};
static Vector2 scleraRightPosition = { 800/2 + 85, 450/2 - 150 };
static float scleraRadius;

static Vector2 irisLeftPosition = { 800/2 - 100, 450/2 };
static Vector2 irisRightPosition = { 800/2 + 100, 450/2};
static float irisRadius;

static float angle;
static float dx, dy, dxx, dyy;

//----------------------------------------------------------------------------------
// Gameplay Screen Functions DefInition
//----------------------------------------------------------------------------------

// Gameplay Screen Initialization logic
void InitMenuOneScreen(void)
{
    // TODO: Initialize GAMEPLAY screen variables here!
    framesCounter = 0;
    finishScreen = 0;
    hasEnterBeenPressed = 0;

    new = LoadTexture("resources/textures/main_menu_screen/menu_one.png");
    load = LoadTexture("resources/textures/main_menu_screen/menu_two.png");
    quit = LoadTexture("resources/textures/main_menu_screen/menu_three.png");
    currentTexture = new;
    currentCounter = 1;

    theme = LoadMusicStream("resources/audio/main_menu_screen/theme-song.mp3");
    enter = LoadSound("resources/audio/main_menu_screen/enter-song.mp3");
    selection = LoadSound("resources/audio/main_menu_screen/selection-song.mp3");
    SetMusicVolume(theme, 0.3f);
    SetSoundVolume(selection, 1.4f);
    PlayMusicStream(theme);


    scleraRadius = 30;

    irisRadius = 14;

    angle = 0.0f;
    dx = 0.0f; 
    dy = 0.0f; 
    dxx = 0.0f; 
    dyy = 0.0f;

}

// Gameplay Screen Update logic
void UpdateMenuOneScreen(void)
{
    // TODO: Update GAMEPLAY screen variables here!

    framesCounter++;

    UpdateMusicStream(theme);

    irisLeftPosition = GetMousePosition();
    irisRightPosition = GetMousePosition();

    if(framesCounter == 360){
        if(hasEnterBeenPressed == 1){
            finishScreen = 1; 
        }else{

        }
    }

        if (!CheckCollisionPointCircle(irisLeftPosition, scleraLeftPosition, scleraRadius - 20))
        {
            dx = irisLeftPosition.x - scleraLeftPosition.x;
            dy = irisLeftPosition.y - scleraLeftPosition.y;

            angle = atan2f(dy, dx);

            dxx = (scleraRadius - irisRadius)*cosf(angle);
            dyy = (scleraRadius - irisRadius)*sinf(angle);

            irisLeftPosition.x = scleraLeftPosition.x + dxx;
            irisLeftPosition.y = scleraLeftPosition.y + dyy;
        }

        if (!CheckCollisionPointCircle(irisRightPosition, scleraRightPosition, scleraRadius - 20))
        {
            dx = irisRightPosition.x - scleraRightPosition.x;
            dy = irisRightPosition.y - scleraRightPosition.y;

            angle = atan2f(dy, dx);

            dxx = (scleraRadius - irisRadius)*cosf(angle);
            dyy = (scleraRadius - irisRadius)*sinf(angle);

            irisRightPosition.x = scleraRightPosition.x + dxx;
            irisRightPosition.y = scleraRightPosition.y + dyy;
        }


    if (IsKeyPressed(KEY_W))
        {
            if(hasEnterBeenPressed == 0){
                PlaySound(selection);

                if(currentCounter == 1){
                    currentCounter = 3;
                    currentTexture = quit; 
                }else if (currentCounter == 2){
                    currentCounter = 1;
                    currentTexture = new;
                }else{
                    currentCounter = 2;
                    currentTexture = load; 
                }
            }else{

            }

        }

        if (IsKeyPressed(KEY_S))
        {
            if(hasEnterBeenPressed == 0){
                 PlaySound(selection);

                if(currentCounter == 1){
                    currentCounter = 2;
                    currentTexture = load; 
                }else if (currentCounter == 2){
                    currentCounter = 3;
                    currentTexture = quit;
                }else{
                    currentCounter = 1;
                    currentTexture = new; 
                }  
            }else{

            }
            
        }

    // Press enter or tap to change to ENDING screen
    if (IsKeyPressed(KEY_ENTER))
    {
        if(hasEnterBeenPressed == 0){
           framesCounter = 0;
            hasEnterBeenPressed = 1;

            StopMusicStream(theme);
            PlaySound(enter); 
        }
        
                 
    }
}

// Gameplay Screen Draw logic
void DrawMenuOneScreen(void)
{
    ClearBackground(RAYWHITE);
    // TODO: Draw GAMEPLAY screen here!
    DrawTexture(currentTexture, 0, 0, WHITE);

    DrawCircleV(irisRightPosition, irisRadius, DARKPURPLE);
    DrawCircleV(irisRightPosition, 7, BLACK);

    DrawCircleV(irisLeftPosition, irisRadius, DARKPURPLE);
    DrawCircleV(irisLeftPosition, 7, BLACK);
}

// Gameplay Screen Unload logic
void UnloadMenuOneScreen(void)
{
    // TODO: Unload GAMEPLAY screen variables here!
    UnloadTexture(currentTexture);
    UnloadTexture(new);
    UnloadTexture(load);
    UnloadTexture(quit);

    UnloadMusicStream(theme);
    UnloadSound(enter);
    UnloadSound(selection);
}

// Gameplay Screen should Finish?
int FinishMenuOneScreen(void)
{
    return finishScreen;
}

int loadOption(void)
{
    return currentCounter;
}