#include "grid.h"

Grid::Grid(int width, int height, int cellSize)
{
    this->rows = height / cellSize;
    this->columns = width / cellSize;
    this->cellSize = cellSize;
    this->cells = std::vector<std::vector<int>>(this->rows, std::vector<int>(this->columns, 0));

    this->cellColor = {0, 255, 0, 255};
    this->backgroundColor = {55, 55, 55, 255};
}

void Grid::draw()
{
    for (int r = 0; r < this->rows; ++r){
        for (int c = 0; c < this->columns; ++c){
            Color color = (this->cells[r][c] == 1) ? this->cellColor : this->backgroundColor;
            DrawRectangle(c * this->cellSize, r * this->cellSize, this->cellSize - 1, this->cellSize - 1, color);
        }
    }
}

void Grid::randomFill()
{
    for (int r = 0; r < this->rows; ++r){
        for (int c = 0; c < this->columns; ++c){
            int randomVal = GetRandomValue(0, 4);
            this->cells[r][c] = (randomVal == 4) ? 1 : 0;
        }
    }
}

void Grid::clear()
{
    for (int r = 0; r < this->rows; ++r){
        for (int c = 0; c < this->columns; ++c){
            this->cells[r][c] = 0;
        }
    }
}

void Grid::toggleCell(int r, int c)
{
    if (r >= 0 && r < this->rows && c >= 0 && c < this->columns) {
        this->cells[r][c] ^= 1;
    }
}

void Grid::setCellValue(int r, int c, int val)
{
    if (r >= 0 && r < this->rows && c >= 0 && c < this->columns) {
        this->cells[r][c] = val;
    }
}

int Grid::getCellValue(int r, int c)
{
    if (r >= 0 && r < this->rows && c >= 0 && c < this->columns) {
        return this->cells[r][c];
    }
    return 0;
}

void Grid::setCells(const std::vector<std::vector<int>> &cells)
{
    for (int r = 0; r < this->rows; ++r){
        for (int c = 0; c < this->columns; ++c){
            this->cells[r][c] = cells[r][c];
        }
    }
}