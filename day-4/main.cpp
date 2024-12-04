#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int part1(std::string& s, std::size_t v, std::size_t h) {
    int count {};
    bool boundsCondition { false };

    /**
     * in the grid there is a horizontal component h and vertical v.
     * horizontally, 1 means right and -1 left.
     * vertically, 1 means down and -1 up.
     *  so eg. if v = -1 and h = -1 that means we are looking for "XMAS" going up and left from initial index i for which s[i] == 'X'
     * 
     * every combination of v and h has different conditions of not going out of bounds
     */

    for (size_t i { 0 }; i < s.length(); i++) {
        if (v == 0 && h == 1)           boundsCondition = i % 140 < 137;  // right
        else if (v == 0 && h == -1)     boundsCondition = i % 140 > 2;   // left
        else if (v == 1 && h == 0)      boundsCondition = i < s.length() - 3 * 140; // down
        else if (v == -1 && h == 0)     boundsCondition = i > 3 * 140 - 1;  //up
        else if (v == 1 && h == 1)      boundsCondition = i % 140 < 137 && i < s.length() - 3 * 140; // down right
        else if (v == 1 && h == -1)     boundsCondition = i % 140 > 2 && i < s.length() - 3 * 140; //down left
        else if (v == -1 && h == 1)     boundsCondition = i % 140 < 137 && i > 3 * 140 - 1; // up right
        else if (v == -1 && h == -1)    boundsCondition = i > 3 * 140 - 1 && i % 140 > 2; // up left

        if (boundsCondition
            && s[i] == 'X' 
            && s[i + 1 * 140 * v + 1 * h] == 'M'
            && s[i + 2 * 140 * v + 2 * h] == 'A' 
            && s[i + 3 * 140 * v + 3 * h] == 'S')
                count++;

        boundsCondition = false;
    }

    //std::cout << count << '\n';
    return count;
}

void part2(std::string& s, std::size_t v, std::size_t h, std::vector<std::size_t>* indeces) {
    
    bool boundsCondition { false };

    /**
     * storing valid indeces i in the vector such that s[i] == 'A' and you can spell "MAS" diagonally using that square as the 'A'
     * later we are looking for duplicate indeces in the vector. that means there is a cross of two "MAS" using that 'A'.
     */

    for (size_t i { 0 }; i < s.length(); i++) {
        if (v == 1 && h == 1)               boundsCondition = i % 140 < 139 && i < s.length() - 140; // down right
        else if (v == 1 && h == -1)          boundsCondition = i % 140 > 0 && i < s.length() - 140; //down left
        else if (v == -1 && h == 1)          boundsCondition = i % 140 < 139 && i > 139; // up right
        else if (v == -1 && h == -1)         boundsCondition = i % 140 > 0 && i > 139; // up left

        if (boundsCondition
            && s[i] == 'A' 
            && s[i + 140 * v + h] == 'S'
            && s[i - 140 * v - h] == 'M') 
                indeces->push_back(i);

        boundsCondition = false;
    }
}

int main() {
    std::ifstream inf { "input.txt" };
    std::string inputStr { };
    std::string s { };

    for (size_t i { 0 }; i < static_cast<size_t>(140); i++) {
        std::getline(inf, inputStr);
        s.append(inputStr);
    }

    int sump1 { 0 };
    int sump2 { 0 };
    std::vector<std::size_t> indeces {}; // for part 2

    sump1 += part1(s, 0, 1);
    sump1 += part1(s, 0, -1);
    sump1 += part1(s, 1, 0);
    sump1 += part1(s, -1, 0);
    sump1 += part1(s, -1, 1);
    sump1 += part1(s, 1, -1);
    sump1 += part1(s, 1, 1);
    sump1 += part1(s, -1, -1);

    part2(s, 1, 1, &indeces);
    part2(s, 1, -1, &indeces);
    part2(s, -1, 1, &indeces);
    part2(s, -1, -1, &indeces);

    // looking for duplicates
    std::sort(indeces.begin(), indeces.end());
    for (std::size_t i { 0 }; i < indeces.size(); ++i) {
        if (indeces[i] == indeces[i+1])
            sump2++;
    }

    std::cout << "sum part 1: " << sump1 << '\n';
    std::cout << "sum part 2: " << sump2 << '\n';
}