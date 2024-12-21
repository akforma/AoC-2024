#include <iostream>
#include <fstream>
#include <set>

const std::size_t ROWS { 50 };
const std::size_t COLS { 50 };

void antinode(char grid[ROWS][COLS], std::size_t r1, std::size_t c1,
                    std::set<std::pair<std::size_t, std::size_t>>& locs) {

    char antenna = grid[r1][c1];
    grid[r1][c1] = '.';

    for (std::size_t r2 = 0; r2 < ROWS; r2++) {
        for (std::size_t c2 = 0; c2 < COLS; c2++) {
            if (grid[r2][c2] == antenna) {
                //part 2 included
                int flag { 0 };
                int dist { 1 }; //multiplier
                while (true) {
                    if (r2+dist*(r2-r1) < ROWS && c2+dist*(c2-c1) < COLS) {
                        flag++;
                        std::cout << r2+dist*(r2-r1) << ", " << c2+dist*(c2-c1) << '\n';
                        locs.insert( {r2+dist*(r2-r1), c2+dist*(c2-c1)} );
                    }
                    //other direction, pretty WET code but idc
                    if (r2-dist*(r2-r1) < ROWS && c2-dist*(c2-c1) < COLS) {
                        flag++;
                        std::cout << r2-dist*(r2-r1) << ", " << c2-dist*(c2-c1) << '\n';
                        locs.insert( {r2-dist*(r2-r1), c2-dist*(c2-c1)} );
                    }
                    if (flag == 0) break; //can no longer go in either direction
                    else {
                        flag = 0;
                        dist++;
                    }
                }
            }
        }
    }
    grid[r1][c1] = antenna;
}

int main() {
    std::ifstream inf { "input.txt" };
    std::string str { };
    char grid[ROWS][COLS] { };
    int sum { };
    std::set<std::pair<std::size_t, std::size_t>> locs { };

    std::size_t row { 0 };
    std::size_t col { 0 };

    //stream into grid
    for (; row<ROWS; row++) {
        inf >> str;
        for (col = 0; col<COLS; col++) {
            grid[row][col] = str[col];
        }
    }

    for (row = 0; row<ROWS; row++) {
        for (col = 0; col<COLS; col++) {
            if (grid[row][col] != '.') {
                antinode(grid, row, col, locs);
            }
        }
    }

    std::cout << "sum: " << locs.size() << '\n';
}

/**
 * the antinode of the antennas [r1][c1] and [r2][c2]
 * is at [r2+multiplier*(r2-r1)][c2+multiplier*(c2-c1)] (multiplier is just 1 in part1)
 * we are checking if that antinode's coords are inside the grid
 * if yes then add those coords to the set
 */