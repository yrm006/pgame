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

int Teki_atattaka(struct Teki* this, Vector2 hero_xy, int hero_r){
    if( CheckCollisionCircles((Vector2){this->x+30, this->y+30}, 30, hero_xy, hero_r) ){
        return 1;
    }else{
        return 0;
    }
}

void Teki_yarareta(struct Teki* this, Texture2D yarare_tx){
    this->hp = this->hp - 1;
    if(this->hp == 0){
        this->tx = yarare_tx;
        this->ugoki = Teki_ugoki_yarareta;
    }
}



int main(){
    InitWindow(800, 450, "Ore-sama no GAME");
    SetTargetFPS(60);
    // ToggleFullscreen();

    Texture2D kumo = LoadTexture("kumo.png");
    Texture2D hero = LoadTexture("hero.png");
    Texture2D teki = LoadTexture("teki.png");
    Texture2D teki180 = LoadTexture("teki180.png");

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

    while(! WindowShouldClose() ){
        if(IsKeyPressed(KEY_SPACE)){
            if( (450-60)-1 <= y ){
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

        teki0.ugoki(&teki0);
        teki1.ugoki(&teki1);
        teki2.ugoki(&teki2);

        if( ColorToInt(col) == ColorToInt(YELLOW) ){
            col = RED;
        }else{
            col = YELLOW;
        }

        if( Teki_atattaka(&teki0, (Vector2){x+30, y+30}, 30) ){
            y = y - 30;
            yv = -20;
            Teki_yarareta(&teki0, teki180);
        }
        if( Teki_atattaka(&teki1, (Vector2){x+30, y+30}, 30) ){
            y = y - 30;
            yv = -20;
            Teki_yarareta(&teki1, teki180);
        }
        if( Teki_atattaka(&teki2, (Vector2){x+30, y+30}, 30) ){
            y = y - 30;
            yv = -20;
            Teki_yarareta(&teki2, teki180);
        }

        BeginDrawing();
            ClearBackground( LIME );
            DrawTexture(kumo, 400, 80, WHITE);
            DrawTexture(kumo, 200, 85, WHITE);
            DrawTexture(kumo, 650, 95, WHITE);
            // DrawCircle(x, y, 30, col);
            DrawTexture(hero, x, y, WHITE);
            DrawTextureEx(teki0.tx, (Vector2){teki0.x, teki0.y}, 0, 1, WHITE);
            DrawTextureEx(teki1.tx, (Vector2){teki1.x, teki1.y}, 0, 1, WHITE);
            DrawTextureEx(teki2.tx, (Vector2){teki2.x, teki2.y}, 0, 1, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}