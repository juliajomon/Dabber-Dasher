#include "raylib.h"

struct AnimateData
{
    Rectangle rec;
    Vector2 pos;
    int frame;                    
    float updateTime;
    float RunningTime;
};

AnimateData updateanimeData( AnimateData Data ,float dt , int n ){
    Data.RunningTime += dt ;
    if(Data.RunningTime >= Data.updateTime)
            {
                Data.RunningTime = 0.0; //timer restart
                Data.rec.x = Data.frame * Data.rec.width;
                Data.frame++;
                if(Data.frame > n){
                    Data.frame = 0;
                }
            }
    return Data;
}
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

 //character initilization    
    Texture2D scrappy = LoadTexture("dapper-dasher-master-textures/textures/scarfy.png");

     AnimateData scrappyData{  {0.0,0.0,scrappy.width/6,scrappy.height} , 
                            {width/2 - scrappyData.rec.width/2,length - scrappyData.rec.height} ,
                            0,1.0/12.0,0};
    

//fire initialization
    Texture2D fire = LoadTexture("dapper-dasher-master-textures/textures/12_nebula_spritesheet.png");


    //fire velocity pixel/sec
    int fire_vel{-200};
    int j = 0;

    //size od fire array
    int size = 30;

    AnimateData fires[size];

    for(int i=0 ; i <size ; i++){

        fires[i].rec.x = 0.0;
        fires[i].rec.y = 0.0;
        fires[i].rec.width =fire.width/8;
        fires[i].rec.height =fire.height/8;
        fires[i].pos.x = width +j;
        fires[i].pos.y = length - fire.height/8;
        fires[i].frame = 0;
        fires[i].updateTime = 1.0/12.0;
        fires[i].RunningTime = 0;
        j=j+300;
    }

    bool collision{};

    float finishLine{ fires[size - 1].pos.x};

    Texture2D background = LoadTexture("dapper-dasher-master-textures/textures/far-buildings.png");
    float bgX= 0;
    float bgS = 20;

    Texture2D foreGround = LoadTexture("dapper-dasher-master-textures/textures/foreground.png");
    float fgX = 0;
    float fgS = 80;

    Texture2D Midground = LoadTexture("dapper-dasher-master-textures/textures/back-buildings.png");
    float mgX =0;
    float mgS = 40;
    while(WindowShouldClose() == false){

        if(IsKeyDown(KEY_F11)){
            ToggleFullscreen();
        }


        const float dt = GetFrameTime(); //delta time

        BeginDrawing();
        ClearBackground(BLACK);

//backgound scroll
        bgX -= bgS * dt;
        if(bgX <= -background.width *2){
            bgX = 0.0;
        }
         Vector2 bg1_pos{bgX,0}; 
        DrawTextureEx(background,bg1_pos,0 ,2.0, WHITE);

        Vector2 bg2_pos{bgX + background.width * 2.0 , 0.0};
        DrawTextureEx(background,bg2_pos,0,2.0,WHITE);

//midground scroll
        mgX -= mgS * dt;
        if(mgX <= -Midground.width *2){
            mgX = 0.0;
        }
        Vector2 mg1_pos{mgX,0}; 
        DrawTextureEx(Midground,mg1_pos,0 ,2.0, WHITE);

        Vector2 mg2_pos{mgX + Midground.width * 2.0 , 0.0};
        DrawTextureEx(Midground,mg2_pos,0,2.0,WHITE);

// foreground scroll        
        fgX -= fgS * dt;
        if(fgX <= -foreGround.width *2){
            fgX = 0.0;
        }
        Vector2 fg1_pos{fgX,0}; 
        DrawTextureEx(foreGround,fg1_pos,0 ,2.0, WHITE);

        Vector2 fg2_pos{fgX + foreGround.width * 2.0 , 0.0};
        DrawTextureEx(foreGround,fg2_pos,0,2.0,WHITE);


         //ground check
        if(scrappyData.pos.y >= length - scrappyData.rec.height){
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

//ANIMATION

    //collision check
    
    for(AnimateData fire : fires)
    {
        float pad = 80; // to reduse collision size od fire
        Rectangle fireRec{fire.pos.x + pad,fire.pos.y + pad ,fire.rec.width - 2*pad ,fire.rec.height - 2* pad};
        Rectangle scrappyRec{scrappyData.pos.x,scrappyData.pos.y,scrappyData.rec.width,scrappyData.rec.height};

        if(CheckCollisionRecs(fireRec, scrappyRec)){
            collision=true;
        }
    }

    
//update fire animation

    if(collision==false && scrappyData.pos.x >= finishLine){
        DrawText("YOU WIN",width/4,length/2,40,WHITE);
    }
    else if(collision == false){
            for(int i=0; i <size ; i++){   
            fires[i].pos.x += fire_vel *dt;

            fires[i]= updateanimeData(fires[i],dt, 7); 
                DrawTextureRec(fire,fires[i].rec,fires[i].pos,WHITE);//drwaing fire
            }   
        

        //update finish line
            finishLine += fire_vel * dt; 

        //update character animation

            scrappyData.pos.y += velocity * dt; //update scrappy position

            if(isInair == false){
                scrappyData = updateanimeData(scrappyData,dt,5);
            }

         
            
            DrawTextureRec(scrappy,scrappyData.rec,scrappyData.pos, WHITE); //drawing character
    }
    else{
        DrawText("GAME OVER",width/4,length/2,40,WHITE);
    }
        
        EndDrawing();

    }
    UnloadTexture(scrappy);
    UnloadTexture(fire);
    UnloadTexture(background);
    UnloadTexture(foreGround);
    UnloadTexture(Midground);
    CloseWindow();
}