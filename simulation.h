#pragma once

#include "grid.h"
#include "raylib.h"
#include <iostream>

class Simulation
{
public:
    Simulation(int width, int height, int cellSize) : grid(width, height, cellSize), isRun(false)
    {
        this->grid.randomFill();
    };
    void draw();
    void update();

    void start() { this->isRun = true; };
    void stop() { this->isRun = false; };
    void reset() { this->grid.randomFill(); };
    void clear() { this->grid.clear(); };
    void toggleCell(int r, int c) { if (!this->isRun) this->grid.toggleCell(r, c); };

    void setGridValue(int r, int c, int value);
    int getNeighborLiveCount(int r, int c);

private:
    Grid grid;
    bool isRun;
};