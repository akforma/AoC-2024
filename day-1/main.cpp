#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>

void part1(std::vector<int>& left, std::vector<int>& right) {
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    int sum { 0 };
    for (int i { 0 }; i < left.size(); i++) {
        sum += (left[i] <= right[i] ? right[i] - left[i] : left[i] - right[i]);
    }

    std::cout << sum << '\n';
}

void part2(std::vector<int>& left, std::vector<int>& right) {
    int similarity { };

    for (int i : left) {
        similarity += (i * count(right.begin(), right.end(), i));
    }

    std::cout << similarity << '\n';
}

int main() {
    std::vector<int> left {};
    std::vector<int> right {};

    std::ifstream inf { "input.txt" };
    std::string strInput {};

    int i { 0 };
    while (inf >> strInput) {
        i++ % 2 == 0 ? (left.push_back(stoi(strInput))) : (right.push_back(stoi(strInput)));
    }

    part1(left, right);
    part2(left, right);

    return 0;
}