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

    muditor_init = dlsym(libmuditor, "muditor_init");
    if(muditor_init == NULL){
        dprintf(STDERR_FILENO, "Cannot open the %s, %s\n", "muditor_init", dlerror());
        return false;
    }

    muditor_renderframe = dlsym(libmuditor, "muditor_renderframe");
    if(muditor_renderframe == NULL){
        dprintf(STDERR_FILENO, "Cannot open the %s, %s\n", "muditor_renderframe", dlerror());
        return false;
    }

    return true;
}


int 
main(int argc, char *argv[])
{
    if(!reload_muditor(libmuditor_name)) return EXIT_FAILURE;

    InitWindow(Width, Height, "Muditor");
    SetTargetFPS(60);            

    // Audio
    InitAudioDevice();

    muditor_init(&muditor);

    // Per frame rendering
    while (!WindowShouldClose()){
        /* r for Hot Reloading */
        if(IsKeyPressed(KEY_R)){
            dlclose(libmuditor);
            reload_muditor(libmuditor_name);
        }
        muditor_renderframe(&muditor);
    }

    // De-Initialization
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
