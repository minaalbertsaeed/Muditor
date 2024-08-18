#define POSIX_C_SOURCE 200809L
#include <stdbool.h>
#include <stdint.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "./libmuditor/libmuditor.h"

static const size_t Width = 800;
static const size_t Height = 600;

void *libmuditor = NULL;        
Muditor muditor = {0};

/* Functions Declaration*/
fp_muditor_init muditor_init = NULL;
fp_muditor_renderframe muditor_renderframe = NULL;

bool reload_muditor(const char* libmuditor_path){
    libmuditor = dlopen(libmuditor_path, RTLD_LAZY);

    if (libmuditor == NULL) {
        dprintf(STDERR_FILENO, "Cannot open the %s, %s\n", libmuditor_name, dlerror());
        return false;
    }

    for (size_t i = 0; i < SYMBOLS_NO; i++) {
        fp_table[i] = dlsym(libmuditor, symbols_table[i]);
        if (fp_table[i] == NULL) {
            dprintf(STDERR_FILENO, "Cannot open the %s, %s\n", symbols_table[i], dlerror());
            return EXIT_FAILURE;
        }
    }

    return true;
}


int 
main(int argc, char *argv[])
{
    if(!reload_muditor(libmuditor_name)) 
        return EXIT_FAILURE;

    if (argc != 2) {
        dprintf(STDERR_FILENO, "Invalid number of arguments passed");
    }

    char *music_path = argv[1];
    if (access(music_path, F_OK)){
        dprintf(STDERR_FILENO, "File does not exist");
        return EXIT_FAILURE;
    }

    InitWindow(Width, Height, "Muditor");
    SetTargetFPS(60);            

    // Audio
    InitAudioDevice();
    muditor.music = LoadMusicStream(music_path);
    ((fp_muditor_init)fp_table[MUDITOR_INIT])(&muditor);

    // Per frame rendering
    while (!WindowShouldClose()){
        /* r for Hot Reloading */
        if(IsKeyPressed(KEY_R)){
            dlclose(libmuditor);
            reload_muditor(libmuditor_name);
        }
        // muditor_renderframe(&muditor);
        ((fp_muditor_renderframe)fp_table[MUDITOR_RENDERFRAME])(&muditor);
    }

    // De-Initialization
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
