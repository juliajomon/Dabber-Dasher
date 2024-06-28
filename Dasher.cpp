#include "raylib.h"

int main(){
    //dimensions
    int width = 500;
    int length = 400;
    
    int rect_width = 40;
    int rect_heigth = 50;

    //velocity
    int velocity = 0;
    int y = length - rect_heigth;

    //gravity  (pixels/frame)/frame
    const int gravity = 1;

    //to prevent double jump
    bool isInair = false;

    int jump = -15;

    InitWindow(width,length,"DAPPER-DASHER");
    SetTargetFPS(60);

    while(WindowShouldClose() == false){

        if(IsKeyDown(KEY_F11)){
            ToggleFullscreen();
        }

        BeginDrawing();
        ClearBackground(WHITE);

         //ground check
        if(y >= length - rect_heigth){
            velocity = 0;              //on ground
            isInair = false;
        }
        else{
            velocity += gravity;    //apply gravity
            isInair = true;
        }
        
        //jump
        if(IsKeyPressed(KEY_SPACE) && isInair == false){
            velocity += jump;
        }
        
       
        y += velocity;

        DrawRectangle(width/2,y,rect_width,rect_heigth,RED);
        
        EndDrawing();

    }
}