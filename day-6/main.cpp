#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

const int COLS { 130 };
const int ROWS { 130 };

enum class Direction {
    none,
    right,
    down,
    left,
    up,
};

Direction turn(Direction dir) {
    switch (dir) {
        case Direction::up:     return Direction::right;
        case Direction::right:  return Direction::down;
        case Direction::down:   return Direction::left;
        case Direction::left:   return Direction::up;
    }

    return Direction::none;
}

bool stuck(std::vector<std::pair<std::size_t, Direction>>& obstacleHit, std::size_t pos, Direction dir) {
    std::pair<std::size_t, Direction> hit { pos, dir };
        if (std::find(obstacleHit.begin(), obstacleHit.end(), hit) != obstacleHit.end()) {
            return true;
        }
    obstacleHit.push_back(hit);
    return false;
}

// returns true if stuck, always returns false in part 1.
bool walk(std::string& map, Direction dir, std::size_t pos, bool part2) {
    std::vector<std::pair<std::size_t, Direction>> obstacleHit { };

    while (true) {
        map[pos] = 'X';

        switch (dir) {
        case Direction::up:
            if (pos % ROWS == pos) {
                return false;
            }
            else if (map[pos - COLS] == '#') {
                if (part2) {
                    if (stuck(obstacleHit, pos, dir)) return true;
                }
                dir = turn(dir);
            }
            else {
                pos -= COLS;
            }
            break;
        
        case Direction::right:
            if (pos % COLS == COLS - 1) {
                return false;
            }
            else if (map[pos + 1] == '#') {
                if (part2) {
                    if (stuck(obstacleHit, pos, dir)) return true;
                }
                dir = turn(dir);
            }
            else {
                pos += 1;
            }
            break;

        case Direction::down:
            if (pos >= COLS * (ROWS - 1)) {
                return false;
            }
            else if (map[pos + ROWS] == '#') {
                if (part2) {
                    if (stuck(obstacleHit, pos, dir)) return true;
                }
                dir = turn(dir);
            }
            else {
                pos += COLS;
            }
            break;

        case Direction::left:
            if (pos % COLS == 0) {
                return false;
            }
            else if (map[pos - 1] == '#') {
                if (part2) {
                    if (stuck(obstacleHit, pos, dir)) return true;
                }
                dir = turn(dir);
            }
            else {
                pos -= 1;
            }
            break;
        }
    }
}


int main() {
    std::ifstream inf { "input.txt" }; 
    std::string map { };
    std::string s { };
    int stuck { };

    std::size_t pos { std::string::npos };

    while (inf.good()) {
        std::getline(inf, s);
        map.append(s);
    }

    // Happened to find the '^' in the map, too lazy to create code for other starting directions.
    Direction dir { Direction::up };
    pos = map.find('^');

    std::size_t intialPos = pos; // need a copy for part 2

    // part 1
    walk(map, dir, pos, false);
    auto count = std::ranges::count(map, 'X');
    std::cout << "part 1: " << count << '\n';

    //part 2
    for (std::size_t i { 0 }; i < COLS * ROWS; ++i) {
        if (!(map[i] == '#' || map[i] == '^')) {
            map[i] = '#';
            stuck += walk(map, Direction::up, intialPos, true);
            map[i] = '.';
        }
    }

    std::cout << "part 2: " << stuck << '\n';
}

/**
 * part 1
 * change '.' into 'X' on visited square, finally count number of 'X' in map.
 * 
 * part 2
 * idea: if the guard hits the same obstacle twice from the same direction, it has to be stuck.
 * implementation: one by one, place '#' in all positions in map that if it is not already a #.
 * hits are stored in a vector containing a pair of the index of the obstacle and the hit direction.
 * if a similar pair already exists in the vector, the guard is stuck.
 */