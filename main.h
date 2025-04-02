#ifndef MAIN_H
#define MAIN_H

int addTwoNums(int a, int b);
int getUserInput();
int multiplyTwoNums(int x, int y);
struct DivisionResults {
    int quotient;
    int remainder;
    int decimalValue[5] = {0, 0, 0, 0, 0};
};
DivisionResults divideTwoNums(int dividend, int divisor);
void printDivResult(DivisionResults results, int dividend, int divisor);
std::string addTwoBinary(std::string bin1 ,std::string bin2);
int DecValTest(DivisionResults results);
void exitMessage();
enum operationType {
    EXIT = 0,
    ADDITION,
    MULTIPLICATION,
    DIVISION,
    ALL,
    BINARY
  };

#endif