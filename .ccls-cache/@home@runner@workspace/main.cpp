#include <iostream>

int getUserInput() {
  int x;
  std::cin >> x;
  // https://cplusplus.com/forum/beginner/207701/
  if (std::cin.fail()) {
    std::cerr << "Invalid input! Exiting program.\n" << std::endl;
    std::cin.clear();
    exit(1);
  }
  return x;
}
/*
  dividend                           ___ quotient___
  -------- = quotient        divisor ) dividend
  divisor
                    0.5
  1/2 = 0.5      2 ) 10

                    
  13/5 = 2.6    5 ) 13   5 ) 3*10 = 6
                     
                     
  13/5 -> 5)13 -> quo 2 then dividend  = quotient * divisor  13 - 2*5 = 3 (the remainder) -> 5)3 -> quo 0 then remainder * base(10) -> 5)30 = 6
  https://www.youtube.com/watch?v=B6AFLl_Gqmw

*/
void intOverflow() {
  std::cout << "Int overflow.\n" << std::endl;
  exit(1);
}

enum operationType {
  ADDITION = 1, 
  MULTIPLICATION,
  DIVISION,
};

struct InputNums {
  int firstNum;
  int secondNum;
};

struct DivisionResults {
  int quotient;
  int remainder;
};

InputNums getUserInputs() {
  InputNums input;
  input.firstNum = getUserInput();
  input.secondNum = getUserInput();
  return input;
}
/*
  multiplyTwoNums(int x, int y)
  
   1073741824 x 2  =  Overflow
   1073741823 x 2  =  2147483646
  -1073741825 x 2  =  Underflow
  -1073741824 x 2  = -2147483648
  -1073741824 x -2 =  Overflow
  -1073741823 x -2 =  2147483646
  -1073741824 x 2  = -2147483648
  -1073741825 x 2  =  Underflow

   2 x 2 = 4
   0 x 2 = 4
   1 x N = N
   0 x 0 = 0
  -1 x -3 = 3
  -1 x 3 = -3
   0 x -1 = 0
  -N x -1 = N
  -N x 1 = -N
*/
int multiplyTwoNums(int x, int y) {
  if (x > 0 && y > 0 && (x > 2147483647 / y)) {
    intOverflow();
  }
  if (x > 0 && y < 0 && (x > -2147483647 / y)) {
    intOverflow();
  }
  if (x < 0 && y < 0 && (x < 2147483647 / y)) {
    intOverflow();
  }
  if (x < 0 && y > 0 && (y > -2147483647 / x)) {
    intOverflow();
  }
  
  return x * y;
}

/*
  addTwoNums(int a, int b)
  
  -1073741824 - 1073741825 =  2147483647 Underflow
  -1073741824 - 1073741824 = -2147483648
  +1073741824 + 1073741824 = -2147483648 Overflow
  +1073741824 + 1073741823 =  2147483647


*/
int addTwoNums(int a, int b) {
  if ((a > 0 && b > 0 && (a + b) < 0) || (a < 0 && b < 0 && (a + b) > 0)) {
    intOverflow();
  }
  return a + b;
}

/*
  divideTwoNums(int a, int b)
  
  4/2 = 2 r = 0 -> 2 and 0/2
  5/2 = 2 r = 1 -> 2 and 1/2
  7/2 = 3 r = 1 -> 3 and 1/2
  10/2 = 5 r = 0 -> 5 and 0/2
  
  0/0 = 0 r = 0 -> 0 and 0/0
  1/0 = 0 r = 1 -> 0 and 1/0
  0/2 = 0 r = 0 -> 0 and 0/2

  2/2 = 1 r = 0 -> 1 and 0/2

  2/4 = 0 r = 2 -> 0 and 2/4
  2/5 = 0 r = 2 -> 0 and 2/5
  2/7 = 0 r = 2 -> 0 and 2/7
  2/10 = 0 r = 2 -> 0 and 2/10
  
*/
DivisionResults divideTwoNums(int dividend, int divisor) {
  DivisionResults results;
  results.quotient = dividend / divisor;
  results.remainder = dividend % divisor;

  if (results.remainder != 0) {

    int remainder = results.remainder;
    for(int i = 1; i < 3; i++) {
        remainder *= 10;
        int decimalNum = remainder / divisor;
        remainder %= divisor;
        std::cout << remainder;
      
        if(remainder == 0) {
          break;
        }
    }
    results.remainder = remainder;
  }
  return results;
}

void printAddResult(int result) {
  std::cout << "The sum of the two numbers is " << result << ".\n";
}
// 13/5 = 2 r 3
void printMultResult(int result) {
  std::cout << "The product of the two numbers is " << result << ".\n";
}

void printDivResult(DivisionResults results) {
  std::cout << "The quotient of the two numbers is " << results.quotient;
}
  

int main() {
  std::cout << "Select the Operation Type. \n";
  std::cout << "1. Addition \n";
  std::cout << "2. Multiplication \n";
  std::cout << "3. Division \n";
  int operationchoice = getUserInput();

  if (operationchoice < 1 || operationchoice > 3) {
    std::cerr << "Invalid input! Exiting program.\n";
    exit(1);
  }

  operationType operation = static_cast<operationType>(operationchoice);
  
  if (operation == ADDITION) {
    std::cout << "Enter two numbers to add: \n";
    InputNums inputs = getUserInputs();
    int result = addTwoNums(inputs.firstNum, inputs.secondNum);
    printAddResult(result);
  }
  if (operation == MULTIPLICATION) {
    std::cout << "Enter two numbers to multiply: \n";
    InputNums inputs = getUserInputs();
    int result = multiplyTwoNums(inputs.firstNum, inputs.secondNum);
    printMultResult(result);
  }
  if (operation == DIVISION) {
    std::cout << "Enter two numbers to divide: \n";
    InputNums inputs = getUserInputs(); 
    if (inputs.secondNum == 0) {
        std::cerr << "Invalid Input! Cannot divide by Zero.\n";
        exit(1);
    }
    DivisionResults results = divideTwoNums(inputs.firstNum, inputs.secondNum);
    printDivResult(results);
  }
}
