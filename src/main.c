#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include "../raylib-5.0_linux_amd64/include/raylib.h"

#define ARRAY_LEN(x) sizeof(x)/sizeof(x[0])
#define MYCOLOR CLITERAL(Color){22 ,22 ,22 ,1}

static const size_t Width = 800;
static const size_t Height = 600;

typedef uint32_t SAMPLE_SIZE ;

SAMPLE_SIZE GLOBAL_FRAMES[1024] = {0} ;
size_t GLOBAL_FRAMES_COUNT = 0;

/* Functions Declaration*/

void 
audioCallBack(void *bufferData, unsigned int frames){
    /* Resetting No. of frames*/
    frames > ARRAY_LEN(GLOBAL_FRAMES) ?  frames = ARRAY_LEN(GLOBAL_FRAMES): frames; 

    memcpy(GLOBAL_FRAMES, bufferData, sizeof(SAMPLE_SIZE)*frames);
    GLOBAL_FRAMES_COUNT = frames;
}

int 
main(int argc, char *argv[])
{
    InitWindow(Width, Height, "Muditor");
    SetTargetFPS(30);            
    // Audio
    InitAudioDevice();
    Music music = LoadMusicStream("Spektrem - Shine ｜ Progressive House ｜ NCS - Copyright Free Music [n4tK7LYFxI0].ogg");
    
    PlayMusicStream(music);
    SetMusicVolume(music, 0.2f);
    AttachAudioStreamProcessor(music.stream, audioCallBack);

    // Per frame loop
    while (!WindowShouldClose()){
        UpdateMusicStream(music);

        /*----------------------------------------------------------------------------------*/
        /* Pausing Using SPACE*/
        if(IsKeyPressed(KEY_SPACE)){
            if(IsMusicStreamPlaying(music)){
                PauseMusicStream(music);
            }else {
                PlayMusicStream(music);
            }

        }

        /*----------------------------------------------------------------------------------*/
        BeginDrawing();
            ClearBackground(MYCOLOR);
            /* printing samples of one channel*/
            for(size_t i = 0; i < GLOBAL_FRAMES_COUNT; i++ ){
                int16_t sample = *(int16_t*)&GLOBAL_FRAMES[i];
                printf("%d\n", sample);
            }

        EndDrawing();
        /*----------------------------------------------------------------------------------*/
    }

    // De-Initialization
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
