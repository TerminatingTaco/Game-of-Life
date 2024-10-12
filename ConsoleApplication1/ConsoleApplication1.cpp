#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>

const int GRID_HEIGHT = 20;
const int GRID_WIDTH = 40;

bool isPaused = true;
int generation = 0;

void initializeGrid(std::vector<std::vector<bool>>& grid);
void displayGrid(const std::vector<std::vector<bool>>& grid);
void updateGrid(std::vector<std::vector<bool>>& grid);
int countLiveNeighbors(const std::vector<std::vector<bool>>& grid, int x, int y);
void clearGrid(std::vector<std::vector<bool>>& grid);
void displayStatus(int generation, int aliveCells);
void handleInput(bool& isRunning, std::vector<std::vector<bool>>& grid);

int main() {
    std::vector<std::vector<bool>> grid(GRID_HEIGHT, std::vector<bool>(GRID_WIDTH, false));
    bool isRunning = true;

    initializeGrid(grid);

    while (isRunning) {
        handleInput(isRunning, grid);

        if (!isPaused) {
            updateGrid(grid);
            generation++;
        }

        displayGrid(grid);

        int liveCells = 0;
        for (int i = 0; i < GRID_HEIGHT; i++)
            for (int j = 0; j < GRID_WIDTH; j++)
                if (grid[i][j]) liveCells++;
        displayStatus(generation, liveCells);

        Sleep(300);
    }

    return 0;
}

void initializeGrid(std::vector<std::vector<bool>>& grid) {
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            grid[i][j] = rand() % 2 == 0;
        }
    }
}

void displayGrid(const std::vector<std::vector<bool>>& grid) {
    system("CLS");
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            std::cout << (grid[i][j] ? "O" : " ");
        }
        std::cout << std::endl;
    }
}

void updateGrid(std::vector<std::vector<bool>>& grid) {
    std::vector<std::vector<bool>> newGrid = grid;
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            int liveNeighbors = countLiveNeighbors(grid, i, j);
            if (grid[i][j]) {
                if (liveNeighbors < 2 || liveNeighbors > 3) {
                    newGrid[i][j] = false;
                }
                else {
                    newGrid[i][j] = true;
                }
            }
            else {
                if (liveNeighbors == 3) {
                    newGrid[i][j] = true;
                }
            }
        }
    }
    grid = newGrid;
}

int countLiveNeighbors(const std::vector<std::vector<bool>>& grid, int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int ni = x + i;
            int nj = y + j;
            if (ni >= 0 && ni < GRID_HEIGHT && nj >= 0 && nj < GRID_WIDTH) {
                if (grid[ni][nj]) count++;
            }
        }
    }
    return count;
}

void clearGrid(std::vector<std::vector<bool>>& grid) {
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            grid[i][j] = false;
        }
    }
}

void displayStatus(int generation, int aliveCells) {
    std::cout << "Generation: " << generation << " | Live cells: " << aliveCells << std::endl;
}

void handleInput(bool& isRunning, std::vector<std::vector<bool>>& grid) {
    if (_kbhit()) {
        char ch = _getch();
        switch (ch) {
        case 's':
            isPaused = false;
            break;
        case 'p':
            isPaused = true;
            break;
        case 'n':
            if (isPaused) {
                updateGrid(grid);
                generation++;
            }
            break;
        case 'c':
            clearGrid(grid);
            generation = 0;
            break;
        case 'q':
            isRunning = false;
            break;
        default:
            break;
        }
    }
}