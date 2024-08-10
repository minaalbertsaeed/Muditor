#define POSIX_C_SOURCE 200809L
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <complex.h>
#include <sys/types.h>
#include "../raylib-5.0_linux_amd64/include/raylib.h"

#define ARRAY_LEN(x) sizeof(x)/sizeof(x[0])
#define MYCOLOR CLITERAL(Color){22 ,22 ,22 ,1}
#define WAVES_COLOR CLITERAL(Color) {10, 217, 89,1}

#define SAMPLES_NO (256)
static const size_t Width = 800;
static const size_t Height = 600;
float max_amp;

typedef struct {
    float left;
    float right;

}Frame ;

typedef float complex cplx;
// Frame  global_frames[4800] = {0} ;
// size_t global_frames_count = 0;

float in[SAMPLES_NO] = {0};
cplx out[SAMPLES_NO] = {0};

float ampl(cplx n){
    return sqrtf(crealf(n) * crealf(n)+ cimagf(n) * cimagf(n));
}

void fft(float in[], cplx out[], size_t step, size_t N){
    if(N == 1){
        out[0] = in[0];
        return;
    }

    fft(in       , out    , step*2, N/2);   /* Even */ 
    fft(in + step, out + N/2, step*2, N/2); /* Odd */ 

    for (size_t k = 0; k < N/2; k++) {
        float t = (float)k/N;
        cplx temp1 = cexp(-2*I*PI*t) * out[k + N/2];
        cplx temp2 = out[k];
        out[k]     = temp2 + temp1;
        out[k + N/2] = temp2 - temp1;
    }
}

/* Functions Declaration*/
void 
audioCallBack(void *bufferData, unsigned int frames){
    /* Resetting No. of frames*/
    if (frames < SAMPLES_NO) return ;
    Frame *ptrframes = bufferData;

    for (size_t i = 0; i < SAMPLES_NO; i++) {
        in[i] = ptrframes[i].left;
    }

    fft(in, out, 1, SAMPLES_NO);
    float max_amp = 0.0f;

    for (size_t i = 0; i < SAMPLES_NO; i++) {
        float a = ampl(out[i]);
        if(max_amp < a ) max_amp = a;
    }
}
int 
main(int argc, char *argv[])
{
    InitWindow(Width, Height, "Muditor");
    SetTargetFPS(60);            
    // Audio
    InitAudioDevice();
    Music music = LoadMusicStream("/home/mina/repos/Muditor/src/Spektrem - Shine ｜ Progressive House ｜ NCS - Copyright Free Music [n4tK7LYFxI0].ogg");
    
    PlayMusicStream(music);
    // SetMusicVolume(music, 0.2f);
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

        if(IsKeyPressed(KEY_F)){
            ToggleFullscreen(); 

        }
       

        /*----------------------------------------------------------------------------------*/
        int w = GetRenderWidth();
        int h = GetRenderHeight();
        BeginDrawing();
            ClearBackground(MYCOLOR);

            // if(IsMusicStreamPlaying(music)){
            //     DrawText("Press Space to pause", w/3, 3*h/4, 20, RAYWHITE);
            // }else {
            //     DrawText("Press Space to continue", w/3, 3*h/4, 20, RAYWHITE);
            // }

            float cell_width = (float)w/ SAMPLES_NO;
            for (size_t i = 0; i < SAMPLES_NO; i++) {
                    float t = ampl(out[i]) ;
                    DrawRectangle(i*cell_width, h/1 - (float)h/4.0*t, 4, (float)h/2.0*t, BLUE);
            }
            /* printing samples of one channel*/
            // for(size_t i = 0; i < global_frames_count; ++i ){
            //     float t = global_frames[i].left;
            //     if (t > 0) {
            //     }
            //     else {
            //         DrawRectangle(i*cell_width, h/2, 1, h/2*t, RAYWHITE);
            //     }
            //
            // }

        EndDrawing();
        /*----------------------------------------------------------------------------------*/
    }
    // De-Initialization
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
