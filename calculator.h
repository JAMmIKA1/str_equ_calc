#ifndef CALCULATOR_H
#define CALCULATOR_H
#include "stack.h"

int Pow(int base, int power);
int digitsToNumber(char** str);
void stringParse(char** ptr, Stack* numbers, Stack* operators);
double process(Stack* numbers, Stack* operators);
double calc_tail(char** ptrr);
double calculate(char* ptr);

#endif // !CALCULATOR_H
