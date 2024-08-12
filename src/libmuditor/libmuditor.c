#include <stdio.h>
#include "libmuditor.h"


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

void muditor_init (Muditor* muditor){
    muditor->music = LoadMusicStream("/home/mina/repos/Muditor/music/Spektrem - Shine ｜ Progressive House ｜ NCS - Copyright Free Music [n4tK7LYFxI0].ogg");
    SetMusicVolume(muditor->music, 0.3f);
    PlayMusicStream(muditor->music);
    AttachAudioStreamProcessor(muditor->music.stream , audioCallBack);

}


void muditor_renderframe(Muditor* muditor){
        UpdateMusicStream(muditor->music);

        /*----------------------------------------------------------------------------------*/
        /* Pausing Using SPACE*/
        if(IsKeyPressed(KEY_SPACE)){
            if(IsMusicStreamPlaying(muditor->music)){
                PauseMusicStream(muditor->music);
            }else {
                PlayMusicStream(muditor->music);
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
                    DrawRectangle(i*cell_width, h/1 - (float)h/4.0*t, 4, (float)h/2.0*t, RED);
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


