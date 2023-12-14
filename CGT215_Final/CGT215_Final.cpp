#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

const int rows = 20;
const int cols = 40;
const int generations = 100;

void randomizeGrid(bool grid[rows][cols]) {
    std::srand(std::time(0));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            grid[i][j] = std::rand() % 2 == 0;
        }
    }
}

void displayGrid(bool grid[rows][cols]) {
    system("cls");  // for Windows, use "clear" for Linux/macOS

    // Calculate horizontal padding to center the grid
    int horizontalPadding = (80 - cols) / 2;

    for (int i = 0; i < rows; ++i) {
        // Add leading spaces for horizontal centering
        for (int k = 0; k < horizontalPadding; ++k) {
            std::cout << " ";
        }

        // Display the row
        for (int j = 0; j < cols; ++j) {
            std::cout << (grid[i][j] ? "█" : " ");
        }
        std::cout << std::endl;
    }
}

int countNeighbors(bool grid[rows][cols], int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;

            int ni = (x + i + rows) % rows;
            int nj = (y + j + cols) % cols;

            count += grid[ni][nj] ? 1 : 0;
        }
    }
    return count;
}

void updateGrid(bool grid[rows][cols]) {
    bool newGrid[rows][cols];

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int neighbors = countNeighbors(grid, i, j);

            newGrid[i][j] = (grid[i][j] && (neighbors == 2 || neighbors == 3)) ||
                (!grid[i][j] && neighbors == 3);
        }
    }

    // Copy the new grid back to the original grid
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            grid[i][j] = newGrid[i][j];
        }
    }
}

int main() {
    bool grid[rows][cols];
    randomizeGrid(grid);

    for (int generation = 0; generation < generations; ++generation) {
        system("cls");  // for Windows, use "clear" for Linux/macOS
        std::cout << "Generation: " << generation + 1 << std::endl;
        displayGrid(grid);
        std::this_thread::sleep_for(std::chrono::seconds(1));  // Increase the duration to slow down
        updateGrid(grid);
    }

    return 0;
}