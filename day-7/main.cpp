#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>

long total(std::string& str, bool part1) {
    long ans { std::stol(str.substr(0, str.find(':'))) };

    std::vector<long> vec { };
    std::stringstream ss { str.substr(str.find(':') + 2, str.length()-1) };
    std::string tempStr { };

    while (std::getline(ss, tempStr, ' ')) {
        vec.push_back(stol(tempStr));
    }

    long num { vec[0] };

    // part 1
    if (part1) {
        int j { 2 };
        int q { 1 };

        for (std::size_t i { 0 }; i < pow(2, vec.size()-1); ++i) {
            for (std::size_t t { 1 }; t < vec.size(); ++t, j*=2, q*=2) {
                if (i % j >= 0 && i % j < q) {
                    num += vec[t];
                }
                else {
                    num *= vec[t];
                }
            }

            j = 2;
            q = 1;
        
            if (num == ans) return ans;
            num = vec[0];
        }

        return 0;
    }

    // part 2
    int j { 3 };
    int q { 1 };

    std::string s_num { std::to_string(num) };

    for (std::size_t i { 0 }; i < pow(3, vec.size()-1); ++i) {
        for (std::size_t t { 1 }; t < vec.size(); ++t, j*=3, q*=3) {
            if (i % j >= 0 && i % j < q) {
                num += vec[t];
            }
            else if (i % j >= q && i % j < 2*q) {
                num *= vec[t];
            }
            else {
                s_num = std::to_string(num);
                s_num += std::to_string(vec[t]);
                num = stol(s_num);
            }
        }

        j = 3;
        q = 1;
    
        if (num == ans) {
            return ans;
        }
        num = vec[0];
        s_num = std::to_string(num);
        }

    return 0;
}

int main() {
    std::ifstream inf { "input.txt" };
    std::string str { };

    long sum { };

    while (inf.good()) {
        std::getline(inf, str);
        sum += total(str, false);
    }

    std::cout << sum << '\n';
}

/**
 * trying all possible combinations of operators
 * part 1 there are 2^(amount of operators) combinations
 * part 2 there are 3^(amount of operators) combinations
*/