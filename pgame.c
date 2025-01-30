//% cc pgame.c libraylib.a -framework IOKit -framework Cocoa
//% x86_64-w64-mingw32-gcc pgame.c libraylib.a -lgdi32 -lwinmm
//% afconvert -f WAVE -d LEI24 xxx.m4a xxx.wav
#include "raylib.h"
#include <stdio.h>

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

int Teki_atattaka(struct Teki* this, Vector2 hero_xy, int hero_r){
    if( CheckCollisionCircles((Vector2){this->x+30, this->y+30}, 30, hero_xy, hero_r) ){
        int sa = (this->y+30) - hero_xy.y;
        if(sa < 30){
            return 2;
        }else{
            return 1;
        }
    }else{
        return 0;
    }
}

int Teki_yarareta(struct Teki* this, Texture2D yarare_tx){
    this->hp = this->hp - 1;
    if(this->hp == 0){
        this->tx = yarare_tx;
        this->ugoki = Teki_ugoki_yarareta;
        return 1;
    }
    return 0;
}



int main(){
    InitAudioDevice();
    InitWindow(800, 450, "Ore-sama no GAME");
    SetTargetFPS(60);
    // ToggleFullscreen();

    Texture2D kumo = LoadTexture("res/kumo.png");
    Texture2D hero = LoadTexture("res/hero.png");
    Texture2D teki = LoadTexture("res/teki.png");
    Texture2D teki180 = LoadTexture("res/teki180.png");

    Sound snd_jump = LoadSound("res/jump.mp3");
    Sound snd_punch = LoadSound("res/punch.mp3");
    Sound snd_teeen = LoadSound("res/teeen.mp3");
    Sound snd_clear = LoadSound("res/clear.mp3");

REPLAY:
    printf("game start\n");

    float x = 400;
    float xv = 0;
    float y = 450 - 30;
    float yv = 0;
    Color col = YELLOW;

    // int teki_hp = 3;
    struct Teki teki0;{
        teki0.x = 500;
        teki0.y = 450-60;
        teki0.hp = 3;
        teki0.tx = teki;
        teki0.ugoki = Teki_ugoki_normal;
    }
    struct Teki teki1;{
        teki1.x = 550;
        teki1.y = 450-60;
        teki1.hp = 3;
        teki1.tx = teki;
        teki1.ugoki = Teki_ugoki_normal;
    }
    struct Teki teki2;{
        teki2.x = 600;
        teki2.y = 450-60;
        teki2.hp = 5;
        teki2.tx = teki;
        teki2.ugoki = Teki_ugoki_normal;
    }

    int teki0_timer = 60*5;
    int teki1_timer = 60*8;
    int teki2_timer = 60*6;

    Color bg = LIME;
    int score = 0;

    while(! WindowShouldClose() ){
        if(IsKeyPressed(KEY_SPACE)){
            if( (450-60)-1 <= y ){
                PlaySound(snd_jump);
                yv = -20;
            }
        }
        if(IsKeyDown(KEY_RIGHT)){
            if( (450-60) <= y ){
                xv = xv + 3;
            }else{
                xv = xv + 0.4;
            }
        }
        if(IsKeyDown(KEY_LEFT)){
            if( (450-60) <= y ){
                xv = xv - 3;
            }else{
                xv = xv - 0.4;
            }
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

        if( !--teki0_timer ){
            teki0.x = 500;
            teki0.y = 450-60;
            teki0.hp = 3;
            teki0.tx = teki;
            teki0.ugoki = Teki_ugoki_normal;

            teki0_timer = 60*5;
        }
        if( !--teki1_timer ){
            teki1.x = 550;
            teki1.y = 450-60;
            teki1.hp = 3;
            teki1.tx = teki;
            teki1.ugoki = Teki_ugoki_normal;

            teki1_timer = 60*8;
        }
        if( !--teki2_timer ){
            teki2.x = 600;
            teki2.y = 450-60;
            teki2.hp = 5;
            teki2.tx = teki;
            teki2.ugoki = Teki_ugoki_normal;

            teki2_timer = 60*6;
        }

        teki0.ugoki(&teki0);
        teki1.ugoki(&teki1);
        teki2.ugoki(&teki2);

        if( ColorToInt(col) == ColorToInt(YELLOW) ){
            col = RED;
        }else{
            col = YELLOW;
        }

        int atattaka0 = Teki_atattaka(&teki0, (Vector2){x+30, y+30}, 30);
        if( atattaka0 == 1 ){
            PlaySound(snd_punch);
            y = y - 30;
            yv = -20;
            int yarare = Teki_yarareta(&teki0, teki180);
            if(yarare == 1){
                score = score + 1;
            }
        }else
        if( atattaka0 == 2 ){
            if(ColorToInt(bg) == ColorToInt(RED)){
                // none
            }else{
                PlaySound(snd_teeen);
                bg = RED;
                break;
            }
        }

        int atattaka1 = Teki_atattaka(&teki1, (Vector2){x+30, y+30}, 30);
        if( atattaka1 == 1 ){
            PlaySound(snd_punch);
            y = y - 30;
            yv = -20;
            int yarare = Teki_yarareta(&teki1, teki180);
            if(yarare == 1){
                score = score + 1;
            }
        }else
        if( atattaka1 == 2 ){
            if(ColorToInt(bg) == ColorToInt(RED)){
                // none
            }else{
                PlaySound(snd_teeen);
                bg = RED;
                break;
            }
        }

        int atattaka2 = Teki_atattaka(&teki2, (Vector2){x+30, y+30}, 30);
        if( atattaka2 == 1 ){
            PlaySound(snd_punch);
            y = y - 30;
            yv = -20;
            int yarare = Teki_yarareta(&teki2, teki180);
            if(yarare == 1){
                score = score + 1;
            }
        }else
        if( atattaka2 == 2 ){
            if(ColorToInt(bg) == ColorToInt(RED)){
                // none
            }else{
                PlaySound(snd_teeen);
                bg = RED;
                break;
            }
        }

        if(20 <= score){
            bg = GOLD;
            PlaySound(snd_clear);
            break;
        }

        BeginDrawing();
            ClearBackground( bg );
            DrawTexture(kumo, 400, 80, WHITE);
            DrawTexture(kumo, 200, 85, WHITE);
            DrawTexture(kumo, 650, 95, WHITE);
            // DrawCircle(x, y, 30, col);
            DrawTexture(hero, x, y, WHITE);
            DrawTextureEx(teki0.tx, (Vector2){teki0.x, teki0.y}, 0, 1, WHITE);
            DrawTextureEx(teki1.tx, (Vector2){teki1.x, teki1.y}, 0, 1, WHITE);
            DrawTextureEx(teki2.tx, (Vector2){teki2.x, teki2.y}, 0, 1, WHITE);
            DrawText(TextFormat("%d", score), 10, 10, 64, WHITE);
        EndDrawing();
    }

    if(20 <= score){
        // game clear
        while(! WindowShouldClose() ){
            if(IsKeyPressed(KEY_ENTER)){
                goto REPLAY;
            }

            BeginDrawing();
                ClearBackground(bg);

                DrawText("OMEDETO!", 300, 220, 32, WHITE);
                DrawTexture(hero, x, y, WHITE);
            EndDrawing();
        }
    }else{
        // game over
        while(! WindowShouldClose() ){
            if(IsKeyPressed(KEY_ENTER)){
                goto REPLAY;
            }

            BeginDrawing();
                ClearBackground(bg);

                DrawText("YOU LOSE!", 300, 220, 32, WHITE);
                DrawTexture(hero, x, y, WHITE);
            EndDrawing();
        }
    }

    CloseWindow();
    return 0;
}