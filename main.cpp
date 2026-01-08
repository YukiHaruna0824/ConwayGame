#include "raylib.h"
#include "simulation.h"

#include <iostream>
#include <algorithm>
#include <string>

int main(int argc, char* argv[])
{   
    SetTraceLogLevel(LOG_ERROR);
    Color Grey = {30, 30, 30, 255};

    const int DEFAULT_WINDOW_WIDTH = 1200;
    const int DEFAULT_WINDOW_HEIGHT = 800;
    const int DEFAULT_CELL_SIZE = 5;
    const int DEFAULT_FPS = 15;

    int WINDOW_WIDTH = DEFAULT_WINDOW_WIDTH;
    int WINDOW_HEIGHT = DEFAULT_WINDOW_HEIGHT;
    int CELL_SIZE = DEFAULT_CELL_SIZE;
    int FPS = DEFAULT_FPS;

    // Parse command-line: ./main [width height cell_size fps]
    if (argc >= 3) {
        try {
            WINDOW_WIDTH = std::max(400, std::stoi(argv[1]));
            WINDOW_HEIGHT = std::max(400, std::stoi(argv[2]));
        } catch (...) {
            std::cerr << "Invalid width/height arguments; using defaults.\n";
            WINDOW_WIDTH = DEFAULT_WINDOW_WIDTH;
            WINDOW_HEIGHT = DEFAULT_WINDOW_HEIGHT;
        }
    }
    if (argc >= 4) {
        try { 
            CELL_SIZE = std::max(1, std::stoi(argv[3])); 
            // make sure less 4 * 4 Grid
            CELL_SIZE = std::min(CELL_SIZE, std::min(WINDOW_WIDTH, WINDOW_HEIGHT) / 4);
        } catch (...) { 
            std::cerr << "Invalid cell size; using default.\n"; 
            CELL_SIZE = DEFAULT_CELL_SIZE; 
        }
    }
    const int minFPS = 5;
    const int maxFPS = 120;
    if (argc >= 5) {
        try { 
            int v = std::stoi(argv[4]); 
            FPS = std::max(minFPS, std::min(maxFPS, v)); 
        } catch (...) { 
            std::cerr << "Invalid FPS; using default.\n"; 
            FPS = DEFAULT_FPS; 
        }
    }

    std::cout << "Window: " << WINDOW_WIDTH << "x" << WINDOW_HEIGHT << "  CellSize: " << CELL_SIZE << "  FPS: " << FPS << std::endl;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Conway's Game");
    SetTargetFPS(FPS);

    Simulation sim(WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE);
    
    // for mouse event usage
    int lastRow = -1;
    int lastCol = -1;

    while (!WindowShouldClose())
    {
        // Event Handler
        // mouse event
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 mousePosition = GetMousePosition();
            int row = mousePosition.y / CELL_SIZE;
            int col = mousePosition.x / CELL_SIZE;
            if (row != lastRow || col != lastCol) {
                sim.toggleCell(row, col);
                lastRow = row;  lastCol = col;
            }
        } else {
            lastRow = -1; lastCol = -1;
        }

        // keyboard event
        if (IsKeyPressed(KEY_Z)) {
            sim.start();
            SetWindowTitle("Conway's Game Is Running ...");
        } else if (IsKeyPressed(KEY_X)) {
            sim.stop();
            SetWindowTitle("Conway's Game Has Stopped.");
        } else if (IsKeyPressed(KEY_C)) {
            sim.clear();
        } else if (IsKeyPressed(KEY_R)) {
            sim.reset();
        } else if (IsKeyPressed(KEY_A)) {
            FPS = std::min(FPS + 5, maxFPS);   SetTargetFPS(FPS);
            printf("Current FPS : %d\n", FPS);
        } else if (IsKeyPressed(KEY_S)) {
            FPS = std::max(FPS - 5, minFPS);   SetTargetFPS(FPS);
            printf("Current FPS : %d\n", FPS);
        }

        // Update State
        sim.update();
        
        // Drawing
        BeginDrawing();
            ClearBackground(Grey);
            sim.draw();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
