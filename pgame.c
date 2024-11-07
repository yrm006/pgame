//% cc pgame.c libraylib.a -framework IOKit -framework Cocoa
#include "raylib.h"

int main(){
    InitWindow(800, 450, "Ore-sama no GAME");
    SetTargetFPS(60);
    // ToggleFullscreen();

    int x = 400;
    int xv = 0;
    int y = 450 - 30;
    int yv = 0;
    Color col = YELLOW;

    Texture2D kumo = LoadTexture("kumo.png");
    Texture2D hero = LoadTexture("hero.png");
    Texture2D teki = LoadTexture("teki.png");

    while(! WindowShouldClose() ){
        if(IsKeyPressed(KEY_SPACE)){
            if(y == (450-60)){
                yv = -20;
            }
        }
        if(IsKeyDown(KEY_RIGHT)){
            xv = xv + 3;
        }
        if(IsKeyDown(KEY_LEFT)){
            xv = xv - 3;
        }

        x = x + xv;
        if((800-30) <= x){
            x = 800 - 30;
            xv = -xv * 80 / 100;
        }
        if(x <= (0 + 30)){
            x = 0 + 30;
            xv = -xv * 80 / 100;
        }

        y = y + yv;
        if((450-60) <= y){
            y = 450 - 60;
            yv = -yv * 5 / 100;
            xv = xv * 50 / 100;
        }else{
            yv = yv + 1;
        }

        if( ColorToInt(col) == ColorToInt(YELLOW) ){
            col = RED;
        }else{
            col = YELLOW;
        }

        if(CheckCollisionCircles((Vector2){x+30, y+30}, 30, (Vector2){500+30, 450-60+30}, 30)){
           // tekini atatta toki
           yv = -20; 
        }

        BeginDrawing();
            ClearBackground( LIME );
            DrawTexture(kumo, 400, 80, WHITE);
            DrawTexture(kumo, 200, 85, WHITE);
            DrawTexture(kumo, 650, 95, WHITE);
            // DrawCircle(x, y, 30, col);
            DrawTexture(hero, x, y, WHITE);
            DrawTexture(teki, 500, 450-60, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}