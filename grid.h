#pragma once

#include <vector>
#include "raylib.h"

class Grid
{
public:
    Grid(int width, int height, int cellSize);

    void draw();

    void randomFill();
    void clear();
    void toggleCell(int r, int c);

    void setCellValue(int r, int c, int value);
    int getCellValue(int r, int c);

    void setCells(const std::vector<std::vector<int>> &cells);
    int getRows() { return this->rows; };
    int getColumns() { return this->columns; };

private:
    int rows;
    int columns;
    int cellSize;
    std::vector<std::vector<int>> cells;

    Color cellColor;
    Color backgroundColor;
};