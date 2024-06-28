#include "raylib.h"

int main(){
    //dimensions
    int width = 500;
    int length = 400;


    //velocity
    int velocity = 0;
    

    //gravity  (pixels/sec)/sec
    const int gravity = 1000;

    //to prevent double jump
    bool isInair = false;

    //pixel/sec
    int jump = -500;
    

    InitWindow(width,length,"DAPPER-DASHER");
    SetTargetFPS(60);

    //sprite sheet
    Texture2D scrappy = LoadTexture("dapper-dasher-master-textures/textures/scarfy.png");
    //character dimension
    Rectangle scrappy_size ;
    scrappy_size.width = scrappy.width/6;
    scrappy_size.height = scrappy.height;
    scrappy_size.x=0;
    scrappy_size.y=0;
    //character position
    Vector2 scrappy_pos ;
    scrappy_pos.x = width/2 - scrappy_size.width/2;
    scrappy_pos.y = length - scrappy_size.height;


    

    while(WindowShouldClose() == false){

        if(IsKeyDown(KEY_F11)){
            ToggleFullscreen();
        }

        const float dt = GetFrameTime(); //delta time

        BeginDrawing();
        ClearBackground(WHITE);

         //ground check
        if(scrappy_pos.y >= length - scrappy_size.height){
            velocity = 0;              //on ground
            isInair = false;
        }
        else{
            velocity += gravity * dt;    //apply gravity
            isInair = true;
        }
        
        //jump
        if(IsKeyPressed(KEY_SPACE) && isInair == false){
            velocity += jump;
        }
        
       
        scrappy_pos.y += velocity * dt;

        DrawTextureRec(scrappy,scrappy_size,scrappy_pos, WHITE);
        
        EndDrawing();

    }
    UnloadTexture(scrappy);
    CloseWindow();
}