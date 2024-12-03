#include <iostream>
#include <fstream>
#include <utility>

void multiply(std::pair<std::string, std::string>& pair, int& sum) {
    std::cout<< "mul(" << pair.first << "," << pair.second << ")" " = " << stoi(pair.first) * stoi(pair.second) << '\n';
    sum += (stoi(pair.first) * stoi(pair.second));
    pair.first = "";
    pair.second = "";
}

int main() {
    std::ifstream inf { "input.txt" };
    std::string inputStr { };

    int mulProgress { 0 };
    int enableProgress { 0 };
    bool enableMult { true };

    std::pair<std::string, std::string> pair { };
    int sum { };

    while (inf >> inputStr) {
        for (char c : inputStr) {
            switch (c) {
                case 'm':
                    mulProgress = 1;
                    break;
                case 'u':
                    mulProgress = mulProgress == 1 ? 2 : 0;
                    break;
                case 'l':
                    mulProgress = mulProgress == 2 ? 3 : 0;
                    break;
                case '(':
                    pair.first = ""; // have to be reset for weird edge case
                    pair.second = "";
                    mulProgress = mulProgress == 3 ? 4 : 0;
                    
                    if (enableProgress == 5) enableProgress = 6; // don't(
                    else if (enableProgress == 2) enableProgress = 30; // do(
                    else enableProgress = 0;
                    break;
                case ',':
                    mulProgress = mulProgress == 5 ? 6 : 0;
                    break;
                case ')':
                    if (mulProgress == 7 && enableMult) {
                        multiply(pair, sum);
                        mulProgress = 0;
                    }
                    else if (enableProgress == 6) {
                        enableMult = false;
                    }
                    else if (enableProgress == 30) {
                        enableMult = true;
                    }
                    break;
                case 'd':
                    mulProgress = 0; // have to reset mulProgress, otherwise something like mdul(2,2) would be allowed
                    enableProgress = 1;
                    break;
                case 'o':
                    mulProgress = 0;
                    enableProgress = enableProgress == 1 ? 2 : 0;
                    break;
                case 'n':
                    mulProgress = 0;
                    enableProgress = enableProgress == 2 ? 3 : 0;
                    break;
                case '\'':
                    mulProgress = 0;
                    enableProgress = enableProgress == 3 ? 4 : 0;
                    break;
                case 't':
                    mulProgress = 0;
                    enableProgress = enableProgress == 4 ? 5 : 0;
                    break;
    
                default:
                    if (iswdigit(c) && (mulProgress == 4 || mulProgress == 5)) {
                        pair.first = pair.first + c;
                        mulProgress = 5;
                    }
                    else if (iswdigit(c) && (mulProgress == 6 || mulProgress == 7)) {
                        pair.second = pair.second + c;
                        mulProgress = 7;
                    }
                    else {
                        mulProgress = 0;
                        pair.first = "";
                        pair.second = "";
                    } 
            }
        }
    }
    std::cout << "sum :" << sum << '\n';
}