#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

bool tryVec(std::vector<int> vec, bool skipUsed, int incOrDec) {
    bool cond { };

    for (int i { 0 }; i < vec.size()-1; i++) {
        if (incOrDec == 1) cond = (vec[i+1] - vec[i] < 1 || vec[i+1] - vec[i] > 3);
        else if (incOrDec == -1) cond = (vec[i+1] - vec[i] > -1 || vec[i+1] - vec[i] < -3);
        if (cond) {
            if (skipUsed) 
                return false;
            else {
                std::vector<int> vec1 = vec;
                vec.erase(vec.begin() + i);
                vec1.erase(vec1.begin() + i + 1);
                if (tryVec(vec, true, incOrDec) || tryVec(vec1, true, incOrDec))
                    return true;
                else
                    return false;
            }
        }
    }
    return true;
}

int main() {
    std::ifstream inf { "input.txt" };
    std::cout << std::boolalpha;

    std::string line {};

    int countSafeReports { 0 };
    bool incSafe {};
    bool decSafe {};

    for (int i { 0 }; i<1000; i++) {
        std::getline(inf, line);
        std::cout << '\n' << line << '\n';
        std::stringstream ss { line };
        int s { };
        std::vector<int> vec {};

        incSafe = false;
        decSafe = false;

        while (ss >> s) {
            vec.push_back(s);
        }
        
        decSafe = tryVec(vec, false, -1); // -1 means decreasing
        incSafe = tryVec(vec, false, 1); // 1 means increasing

        if (incSafe || decSafe) countSafeReports++;

        std::cout << "     incsafe: " << incSafe << '\n';
        std::cout << "     decsafe: " << decSafe << '\n';
        std::cout << "     count: " << countSafeReports << '\n';
    }
    
    std::cout << '\n' << countSafeReports << '\n';
}