#include "simulation.h"

void Simulation::draw()
{
    this->grid.draw();
}

void Simulation::setGridValue(int r, int c, int value)
{
    this->grid.setCellValue(r, c, value);
}

int Simulation::getNeighborLiveCount(int r, int c)
{
    int rows = this->grid.getRows(), cols = this->grid.getColumns();
    if (r < 0 || r >= rows || c < 0 || c >= cols) {
        std::cout << "invalid position" << std::endl;
        return 0;
    }

    int count = 0;
    int dir[8] = {0, 1, 2, 3, 5, 6, 7, 8};
    for (int d : dir) {
        int newRow = (r + d / 3 - 1 + rows) % rows;
        int newCol = (c + d % 3 - 1 + cols) % cols;
        count += (this->grid.getCellValue(newRow, newCol) == 1) ? 1 : 0;
    }
    return count;
}

void Simulation::update()
{
    if (!this->isRun)   return;

    int rows = this->grid.getRows(), cols = this->grid.getColumns();
    std::vector<std::vector<int>> next(rows, std::vector<int>(cols, 0));

    for (int r = 0; r < rows; ++r){
        for (int c = 0; c < cols; ++c){
            int neighborCount = this->getNeighborLiveCount(r, c);
            int cellValue = this->grid.getCellValue(r, c);
            if (cellValue == 1) {
                if (neighborCount == 2 || neighborCount == 3)   next[r][c] = 1;
            } else {
                if (neighborCount == 3) next[r][c] = 1;
            }
        }
    }
    this->grid.setCells(next);
}