#include <iostream>
#include "main.h"

void exitMessage() {
  std::cout << "Exitting program";
}

void generalErrorMessage() {
  std::cerr << "Invalid input! Exiting program.\n";
  exit(1);
}

int getUserInput() {
  int x;
  std::cin >> x;
  // https://cplusplus.com/forum/beginner/207701/
  if (std::cin.fail()) {
    generalErrorMessage();
    std::cin.clear();
    exit(1);
  }
  return x;
}

std::string getUserInputStr() {
  std::string userinput;
  std::cin >> userinput;
  for (unsigned i = 0; i < userinput.size(); i++) {
    char bit = userinput[i];

    if (bit != '0' && bit != '1') {
      std::cout << "Invalid input. Only 0 and 1 are allowed." << std::endl;
      exit(1);
    }
  }
  return userinput;
}
/*
  dividend                           ___ quotient___
  -------- = quotient        divisor ) dividend
  divisor
                    0.5
  1/2 = 0.5      2 ) 10


  13/5 = 2.6    5 ) 13   5 ) 3*10 = 6


  13/5 -> 5)13 -> quo 2 then dividend  = quotient * divisor  13 - 2*5 = 3 (the
  remainder) -> 5)3 -> quo 0 then remainder * base(10) -> 5)30 = 6
  https://www.youtube.com/watch?v=B6AFLl_Gqmw

*/

void intOverflow() {
  std::cout << "Int overflow.\n" << std::endl;
  exit(1);
}

enum baseType {
  EXITPROGRAM,
  BASETEN,
  BASETWO,
};

struct InputNums {
  int firstNum;
  int secondNum;
  std::string firstStr;
  std::string secondStr;
};

InputNums getUserInputsBaseTen() {
  InputNums input;
  input.firstNum = getUserInput();
  input.secondNum = getUserInput();
  return input;
}

InputNums getUserInputsBaseTwo() {
  InputNums input;
  input.firstStr = getUserInputStr();
  input.secondStr = getUserInputStr();
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
  #ifndef TEST_MODE
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
  #endif 

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
  #ifndef TEST_MODE
  if ((a > 0 && b > 0 && (a + b) < 0) || (a < 0 && b < 0 && (a + b) > 0)) {
    intOverflow();
  }
  #endif
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
  bool negativeResult = (dividend < 0) ^ (divisor < 0);

  int absDividend = abs(dividend);
  int absDivisor = abs(divisor);

  results.quotient = absDividend / absDivisor;
  results.remainder = absDividend % absDivisor;
  
  if (negativeResult) {
    results.quotient = -results.quotient;
  }

  int remainder = results.remainder;

  for (int i = 0; i < 5; i++) {
    remainder *= 10;
    int decimalNum = remainder / absDivisor;
    results.decimalValue[i] = decimalNum;
    remainder %= absDivisor;
    if (remainder == 0) {
      break;
    }
  }
  return results;
}
 
std::string addTwoBinary(std::string bin1 ,std::string bin2) {
  std::string result = "";
  int carry = 0;
  int bit1 = bin1.size() - 1;
  int bit2 = bin2.size() - 1;

  while (bit1 >= 0 || bit2 >= 0|| carry > 0 ) {
    int sum = carry;
    if (bit1 >= 0) {
      sum += bin1[bit1--] - '0';
    }
    if (bit2 >= 0) {
      sum += bin2[bit2--] - '0';
    }
    result = std::string(1, (sum % 2) + '0') + result;

    carry = sum / 2;
  }
  return result;
}

void printBinResult(std::string result) {
  std::cout << "The sum of the two binary numbers is " << result << ".\n";
}

void printAddResult(int result) {
  std::cout << "The sum of the two numbers is " << result << ".\n";
}

// 13/5 = 2 r 3
void printMultResult(int result) {
  std::cout << "The product of the two numbers is " << result << ".\n";
}

void printDivResult(DivisionResults results, int dividend, int divisor) {
  #ifndef TEST_MODE
  if (results.quotient == 0 && (dividend < 0) ^ (divisor < 0)) {
   std::cout << "The quotient of the two numbers is -0";
  } else {
    std::cout << "The quotient of the two numbers is " << results.quotient;
  }
  #endif
  #ifdef TEST_MODE
  if (results.quotient == 0 && (dividend < 0) ^ (divisor < 0)) {
    std::cout << "-0";
   } else {
     std::cout << results.quotient;
   }
   #endif
  if (results.remainder > 0) {
  std::cout << ".";
  for (int i = 0; i < 5; i++) {
    if (results.decimalValue[i] == 0) {
    break;
    }
    std::cout << results.decimalValue[i];
    }
  }
}

#ifdef TEST_MODE
int DecValTest(DivisionResults results) {
  int decNum = 0;
  for (int i = 0; i < 5; i++) {
    if (results.decimalValue[i] == 0) {
    break;
    }
    decNum = decNum * 10 + results.decimalValue[i];
  }
  return decNum;
}
#endif

void whileDivResult(DivisionResults results, int dividend, int divisor) {
  std::cout << "The quotient of the two numbers is " << results.quotient;

  if (results.remainder > 0) {
    std::cout << ".";
    int count = 0;
    int remainder = results.remainder;

    while (remainder > 0 && count < 5) {
      remainder *= 10;
      int decimalNum = remainder / divisor;
      remainder %= divisor;
      std::cout << decimalNum;
      count++;
      if (remainder == 0) {
        break;
      }
    }
  }
}


void BaseTenMath() {
  std::cout << "Select the Operation Type:\n";
  std::cout << "0. Exit \n";
  std::cout << "1. Addition \n";
  std::cout << "2. Multiplication \n";
  std::cout << "3. Division \n" << std::endl;
  std::cout << "> ";

  int operationchoice = getUserInput();
  if (operationchoice < 0 || operationchoice > 3) {
    generalErrorMessage();
  }

  operationType operation = static_cast<operationType>(operationchoice);

  if (operation == EXIT) {
    exitMessage();
    exit(0);
  }
  if (operation == ADDITION) {
    std::cout << "Enter two numbers to add: \n";
    InputNums inputs = getUserInputsBaseTen();
    int result = addTwoNums(inputs.firstNum, inputs.secondNum);
    printAddResult(result);
  }
  if (operation == MULTIPLICATION) {
    std::cout << "Enter two numbers to multiply: \n";
    InputNums inputs = getUserInputsBaseTen();
    int result = multiplyTwoNums(inputs.firstNum, inputs.secondNum);
    printMultResult(result);
  }
  if (operation == DIVISION) {
    std::cout << "Enter two numbers to divide: \n";
    InputNums inputs = getUserInputsBaseTen();
    if (inputs.secondNum == 0) {
     generalErrorMessage();
    }
    DivisionResults results = divideTwoNums(inputs.firstNum, inputs.secondNum);
    printDivResult(results, inputs.firstNum, inputs.secondNum);
  }
}

void BaseTwoMath() {
  std::cout << "Enter two numbers in Binary: \n";
  InputNums inputs = getUserInputsBaseTwo();
  std::string result = addTwoBinary(inputs.firstStr, inputs.secondStr);
  printBinResult(result);
}

void BaseMenuChoice() {
  std::cout << "Select Base Type:\n";
  std::cout << "0. Exit\n";
  std::cout << "1. Base Ten\n";
  std::cout << "2. Base Two\n" << std::endl;
  std::cout << ">  ";

  int choosebase = getUserInput();
  if (choosebase < 0 || choosebase > 2) {
    generalErrorMessage();
  }

  baseType baseChoice = static_cast<baseType>(choosebase);

  if (choosebase == EXITPROGRAM) {
    exitMessage();
    exit(0);
  }
  if (choosebase == BASETEN) {
    BaseTenMath();
  }
  if (baseChoice == BASETWO) {
    BaseTwoMath();
  } 
}


#ifndef TEST_MODE
int main() {
 BaseMenuChoice();
}
#endif

