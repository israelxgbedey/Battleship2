#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "consts.h"
#include <iostream>
#include <vector>

class BaseGame {
protected:
    Board* board;
    virtual int solve() = 0;

public:
    BaseGame();
    ~BaseGame();
    int run();
};

class ControlGame : public BaseGame {
protected:
    int solve() override {
        int hits = 0;
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if (this->board->guess(i, j) == ResponseType::HIT) {
                    hits += 1;
                }
            }
        }
        return hits;
    }
};

const int dx[] = { -1, 1, 0, 0 };
const int dy[] = { 0, 0, -1, 1 };

class AssignmentGame : public BaseGame {
private:
    std::vector<std::vector<bool>> visited;

protected:
    int solve() override {
        int shipsRemaining = SHIP_COUNT;
        visited.resize(HEIGHT, std::vector<bool>(WIDTH, false));

        for (int i = 0; i < HEIGHT; ++i) {
            for (int j = 0; j < WIDTH; ++j) {
                if (!visited[i][j]) {
                    ResponseType result = this->board->guess(i, j);
                    std::cout << "Initial Guess at (" << i << ", " << j << "): " << result << std::endl;

                    if (result == ResponseType::HIT) {
                        // If a hit is found and the cell is not visited, perform DFS to find the entire ship
                        int shipSize = dfs(i, j);
                        std::cout << "DFS at (" << i << ", " << j << ") returned ship size: " << shipSize << std::endl;

                        if (shipSize > 0) {
                            shipsRemaining--;
                            std::cout << "Ship found! Remaining ships: " << shipsRemaining << std::endl;
                        }
                    }
                }
            }
        }

        return SHIP_COUNT - shipsRemaining;
    }


    int dfs(int x, int y) {
        if (x < 0 || x >= HEIGHT || y < 0 || y >= WIDTH || visited[x][y] || this->board->guess(x, y) != ResponseType::HIT) {
            // Base case: out of bounds, already visited, or not a hit
            return 0;
        }

        // Mark the current cell as visited
        visited[x][y] = true;

        int shipSize = 1; // Count the current cell

        // Explore in all four directions (up, down, left, right)
        for (int dir = 0; dir < 4; ++dir) {
            int newX = x + dx[dir];
            int newY = y + dy[dir];

            shipSize += dfs(newX, newY);
        }

        std::cout << "DFS exploring (" << x << ", " << y << ") - Ship size: " << shipSize << std::endl;

        return shipSize;
    }


};


#endif /* GAME_H */
