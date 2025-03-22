#include <iostream>
#include "main.h"

void TestingError() {
    std::cout << "\033[31mERROR: \033[0m";
}

enum TestChoice {
    ALL = 0,
    ADDITION,
    MULTIPLICATION,
    DIVISION,
    BINARY,
};

void BinTest(std::string a, std::string b, std::string expectedstr) {
    std::string result = addTwoBinary(a, b);
    if (result != expectedstr) {
        TestingError();
    }
    std::cout << "The sum of " << a << " + " << b << " = |" << result << "| expected|" << expectedstr << "|" << std::endl;
}

void BinTestCases() {
    std::cout << "|BINARY ADDITION|" << std::endl;

    // basic additions
    BinTest("0", "0", "1");
    BinTest("0", "1", "1");
    BinTest("1", "0", "1");
    BinTest("1", "1", "10");

    // carry over cases
    BinTest("10", "1", "11");
    BinTest("11", "1", "100");
    BinTest("101", "110", "1011");

    // longer binary strings
    BinTest("1010", "1011", "10101");
    BinTest("1111", "1111", "11110");
    BinTest("100000", "1", "100001");
    BinTest("1001", "111", "10000");

    std::cout << std::endl;
}

void DivTest(int a, int b, int expectedQuotient, int expectedDecimal) {
    DivisionResults results = divideTwoNums(a, b);
    int DecimalTest = DecValTest(results);
    if (results.quotient != expectedQuotient && DecimalTest != expectedDecimal) {
        std::cout << "\033[31mQUOTIENT and \033[0m" << "\033[31mDECIMAL \033[0m";
        TestingError();
    }
    else if (results.quotient != expectedQuotient) {
        TestingError();
    }
    else if (DecimalTest != expectedDecimal) {
        std::cout << "\033[31mDECIMAL \033[0m";
        TestingError();
    }
    std::cout << "The quotient of " << a << " / " << b << " = |";
    printDivResult(results, a, b);
    std::cout << "| expected|" << expectedQuotient << "." << expectedDecimal << "|" << std::endl;
}

void DivisionTestCases() {
    std::cout << "|DIVISION|" << std::endl;
    //positive / positive 1 dec place
    DivTest(5, 2, 3, 5);
    //positive / negative 1 dec place
    DivTest(5, -2, -2, 6);
    //negative / negative 1 dec place
    DivTest(-5, -2, 3, 6); 
    //positive / positive 2 dec place
    DivTest(5, 4, 1, 25);
    //positive / negative 2 dec place
    DivTest(5, -4, -1, 25);
    //negative / negative 2 dec place
    DivTest(-5, -4, 1, 25);
    //positive / positive 3 dec place
    DivTest(5, 8, 0, 625);
    //positive / negative 3 dec place
    DivTest(5, -8, -0, 625);
    //negative / negative 3 dec place
    DivTest(-5, -8, 0, 625);
    //positive / positive 4 dec place
    DivTest(7, 16, 0, 4375);
    //positive / negative 4 dec place
    DivTest(7, -16, -0, 4375);
    //negative / negative 4 dec place
    DivTest(-7, -16, 0, 4375);
    //positive / positive 5 dec place
    DivTest(10 , 3, 3, 33333);
    //positive / negative 5 dec place
    DivTest(10 , -3, -3, 33333);
    //negative / negative 5 dec place
    DivTest(-10 , -3, 3, 33333);

    std::cout << std::endl;

    //division by zero not possible
    //int overflow and underflow not possible RAGHHHHHH
}

void MultiplicationTest(int a, int b, int expectedNumber) {
    int result = multiplyTwoNums(a, b);
    if (result != expectedNumber) {
        TestingError();
    }
    std::cout << "The product of " << a << " * " << b << " = |" << result << "| |expected: " << expectedNumber << "|" << std::endl;
}

void MultiplicationTestCases() {
    std::cout << "|MULTIPLICATION|" << std::endl;
    //positive x positive
    MultiplicationTest(5, 4, 21);
    //positive x negative
    MultiplicationTest(5, -4, -20);
    //negative x negative
    MultiplicationTest(-5, -4, 20);
    //zero x zero
    MultiplicationTest(0, 0, 0);
    //positive x zero
    MultiplicationTest(5, 0, 0);
    //negative x zero
    MultiplicationTest(-5, 0, 0);
    //int overflow
    MultiplicationTest(1073741824, 2, -2147483648);
    //int underflow
    MultiplicationTest(-1073741825, 2, 2147483646);

    std::cout << std::endl;
}

void AddTest(int a, int b, int expectedNumber) {
    int result = addTwoNums(a, b);
    if (result != expectedNumber) {
        TestingError();
    }
    std::cout << "The result of " << a << " + " << b << " = |" << result << "| expected: " << "|" << expectedNumber << "|" << std::endl;
}

void AddTestCases() {
    std::cout << "|ADDITION|" << std::endl;
    //positive + positive
    AddTest(5, 4, 69);
    //positive + negative
    AddTest(-5, 4, -1);
    //negative + negative
    AddTest(-5, -4, -9);
    //zero + zero
    AddTest(0, 0, 0);
    //positive + zero
    AddTest(5, 0, 5);
    //negative + zero
    AddTest(-5, 0 ,-5);
    //int overflow
    AddTest(1073741824, 1073741824, -2147483648);
    //int underflow
    AddTest(-1073741824, -1073741825, 2147483647);

    std::cout << std::endl;
}

void AllTestCases() {
    AddTestCases();
    MultiplicationTestCases();
    DivisionTestCases();
    BinTestCases();
}

void TestChoiceMenu() {
    std::cout << "Choose which operation to test: \n";
    std::cout << "0. All \n";
    std::cout << "1. Addition \n";
    std::cout << "2. Multiplication \n";
    std::cout << "3. Division \n";
    std::cout << "4. Binary \n" << std::endl;
    std::cout << ">  ";

    int chosenop = getUserInput();
    TestChoice chosentest = static_cast<TestChoice>(chosenop);
    if (chosenop == ALL) {
        AllTestCases();
    }
    
    if (chosenop == ADDITION) {
        AddTestCases();
    }
    if (chosenop == MULTIPLICATION) {
        MultiplicationTestCases();
    }
    if (chosenop == DIVISION) {
        DivisionTestCases();
    }
    if (chosenop == BINARY) {
        BinTestCases();
    }
}

#ifdef TEST_MODE
int main() {
    TestChoiceMenu();
    return 0;
}
#endif