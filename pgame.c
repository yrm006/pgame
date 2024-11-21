//% cc pgame.c libraylib.a -framework IOKit -framework Cocoa
#include "raylib.h"

struct Teki{
    int x;
    int y;
    int hp;
    Texture2D tx;
    void (*ugoki)(struct Teki* this);
};

void Teki_ugoki_normal(struct Teki* this){
    this->x = this->x - 1;
}

void Teki_ugoki_yarareta(struct Teki* this){
    this->y = this->y + 1;
}

int main(){
    InitWindow(800, 450, "Ore-sama no GAME");
    SetTargetFPS(60);
    // ToggleFullscreen();

    Texture2D kumo = LoadTexture("kumo.png");
    Texture2D hero = LoadTexture("hero.png");
    Texture2D teki = LoadTexture("teki.png");
    Texture2D teki180 = LoadTexture("teki180.png");

    int x = 400;
    int xv = 0;
    int y = 450 - 30;
    int yv = 0;
    Color col = YELLOW;

    // int teki_hp = 3;
    struct Teki teki0;{
        teki0.x = 500;
        teki0.y = 450-60;
        teki0.hp = 3;
        teki0.tx = teki;
        teki0.ugoki = Teki_ugoki_normal;
    }

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

        teki0.ugoki(&teki0);

        if( ColorToInt(col) == ColorToInt(YELLOW) ){
            col = RED;
        }else{
            col = YELLOW;
        }

        if(CheckCollisionCircles((Vector2){x+30, y+30}, 30, (Vector2){teki0.x+30, teki0.y+30}, 30)){
            // tekini atatta toki
            yv = -20;
            teki0.hp = teki0.hp - 1;
            if(teki0.hp == 0){
                teki0.tx = teki180;
                teki0.ugoki = Teki_ugoki_yarareta;   
            }
        }

        BeginDrawing();
            ClearBackground( LIME );
            DrawTexture(kumo, 400, 80, WHITE);
            DrawTexture(kumo, 200, 85, WHITE);
            DrawTexture(kumo, 650, 95, WHITE);
            // DrawCircle(x, y, 30, col);
            DrawTexture(hero, x, y, WHITE);
            DrawTextureEx(teki0.tx, (Vector2){teki0.x, teki0.y}, 0, 1, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}