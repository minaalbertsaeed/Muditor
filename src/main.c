#include <stdio.h>
#include "../raylib-5.0_linux_amd64/include/raylib.h"
int main(int argc, char *argv[])
{
    InitWindow(600, 800, "MainApp");
    SetTargetFPS(60);
    while (!WindowShouldClose())        
    {
    }
    CloseWindow();
    return 0;
}
