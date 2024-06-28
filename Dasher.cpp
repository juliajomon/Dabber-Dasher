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
    Texture2D fire = LoadTexture("dapper-dasher-master-textures/textures/12_nebula_spritesheet.png");

    //fire dimension
    Rectangle fire_size{0.0,0.0, fire.width/8,fire.height/8};

    //fire postion
    Vector2 fire_pos{width,length-fire_size.height};
    
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

    //fire velocity pixel/sec
    int fire_vel{-500};

    //animation frame 
    int frame{};
    float UpdateTime = 1.0/12.0 ;
    float runningtime{};

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
        
       fire_pos.x += fire_vel *dt;
        scrappy_pos.y += velocity * dt; //update scrappy position

        //animation
        runningtime += dt ;
        if(isInair == false){
            if(runningtime >= UpdateTime)
            {
                runningtime = 0.0; //timer restart
                scrappy_size.x = frame * scrappy_size.width;
                frame++;
                if(frame > 5){
                    frame = 0;
                }
            }
        }
        DrawTextureRec(fire,fire_size,fire_pos,WHITE);//drwaing fire
        DrawTextureRec(scrappy,scrappy_size,scrappy_pos, WHITE); //drawing character
        
        EndDrawing();

    }
    UnloadTexture(scrappy);
    UnloadTexture(fire);
    CloseWindow();
}