#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

int part2(std::vector<int>& vec, std::vector<std::pair<int, int>> rules, int& middle) {    
    middle = vec[vec.size()/2];

    for (std::size_t l { 0 }; l < vec.size(); ++l) {
        for (auto rule : rules) {
            if (rule.second == vec[l]) {
                for (std::size_t j { l }; j<vec.size(); j++) {
                    if (vec[j] == rule.first) {
                        //std::cout << "failed rule " << vec[j] << '|' << vec[l] << '\n';
                        int temp = vec[j];
                        vec[j] = vec[l];
                        vec[l] = temp;
                        part2(vec, rules, middle);
                    }
                }
            }
        }
    }

    return middle;
}

int main() {
    std::ifstream pages { "pages.txt" };
    std::ifstream rules { "rules.txt" };
    std::string pageLine {};
    std::string ruleLine {};
    std::string el {};
    std::string s_num1 {};
    std::string s_num2 {};
    bool fail { false };
    int middleElement {};
    int sumP1 {};
    int sumP2 {};
    std::size_t vecSize {};

    std::vector<int> vecPart1 {};
    std::vector<int> vecPart2 {};

    std::vector<std::pair<int,int>> rulesVec { };

    for (std::size_t i { 0 }; i < 1176; ++i) {
        std::getline(rules, ruleLine);
        s_num1 = ruleLine[0];
        s_num1 += ruleLine[1];
        s_num2 = ruleLine[3];
        s_num2 += ruleLine[4];

        rulesVec.push_back( { stoi(s_num1), stoi(s_num2) } );
    }

    for (std::size_t i { 0 }; i < 202; ++i) {

        fail = false;
        //std::cout << std::boolalpha;
        //std::cout << fail << '\n';

        std::getline(pages, pageLine);
        std::stringstream ss { pageLine };

        vecPart2.clear();

        while (ss.good()) {
            std::getline(ss, el, ',');
            vecPart1.push_back(stoi(el));
            vecPart2.push_back(stoi(el));
        }

        vecSize = vecPart1.size();
        middleElement = vecPart1[vecPart1.size()/2];

        /*for (auto k : vecPart1) { std::cout << k << ' '; }
        std::cout << '\n';*/

        for (std::size_t l { 0 }; l < vecSize; ++l) {
            for (auto rule : rulesVec) {
                if (rule.second == vecPart1[0]) {
                    for (auto j : vecPart1) {
                        if (j == rule.first) {
                            fail = true;
                        }
                    }
                }
            }

            if (vecPart1.size() > 0) {
                vecPart1.erase(vecPart1.begin());
            }
        }

        if (!fail) {
            sumP1 += middleElement;
        }
        else {
            int middlep2 = -1;
            sumP2 += part2(vecPart2, rulesVec, middlep2);
        }
    }

    std::cout << "sum 1: " << sumP1 << '\n';
    std::cout << "sum 2: " << sumP2 << '\n';
}

/**
 * check if first element in a page is on right side of any rule,
 * if left side of that rule does not exist later in the same page (vector)
 * the page is ordered so far. we remove that first element from the vector and test again for the next element which is the new vecPart1[0]
 * if the page is ordered we add the middle element to sumP1
 * 
 * if left side of a rule exists somewhere in the same page
 * that means that the page is not ordered right, we put fail flag to true and later send that vector to part 2
 * 
 * part 2 recursively calls itself after swapping elements that fail a rule, when it is ordered it returns middle element, we add that to sumP2
 */