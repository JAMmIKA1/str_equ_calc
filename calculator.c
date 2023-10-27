#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calculator.h"

int Pow(int base, int power) {
    int result = 1;
    for(int i = 0; i < power; i++) {
        result *= base;
    }
    return result;
}
int digitsToNumber(char** str) {
    Stack *digits = newStack();
    while(**str >= '0' && **str <='9') {
        push(digits, **str);
        (*str)++;
    }
    int stack_size = size(digits);
    int number = 0;
    for(int i = 0; i < stack_size; i++) {
        number += (pop(digits) - '0') * Pow(10, i);
    }
    return number;
}
void stringParse(char** ptr, Stack* numbers, Stack* operators) {
    int symbol_next = 0;
    while(**ptr != 0 && **ptr != ')') {
        if(**ptr >= '0' && **ptr <= '9') {
            if(symbol_next) {
                printf("Syntax ERROR!");
                exit(1);
            }
            symbol_next = 1;
            push(numbers, digitsToNumber(ptr));
            continue;
        }
        else if( **ptr == '/' || **ptr == '*' ||
            **ptr == '+' || **ptr == '-' ) {
            if(!symbol_next) {
                printf("Syntax ERROR!");
                exit(1);
            }
            symbol_next = 0;
            push(operators, **ptr);
        }
        else if( **ptr == '(' ) {
            (*ptr)++;
            if(symbol_next) {
                printf("Syntax ERROR!");
                exit(1);
            }
            symbol_next = 1;
            push(numbers, calc_tail(ptr));
            continue;
        }
        else if( **ptr != ' ' ) {
            printf("Invalid character '%c'", **ptr);
            exit(1);
        }
        (*ptr)++;
    }
    if(!symbol_next) {
        printf("Syntax ERROR!");
        exit(1);
    }
    (*ptr)++;
    reverse(numbers);
    reverse(operators);
}
double process(Stack* numbers, Stack* operators) {
    Stack *tmp = newStack();
    char tmp_op, crnt_op;
    push(tmp, pop(numbers));
    while(!isEmpty(numbers)) {
        tmp_op = pop(operators);
        if(tmp_op == '-' || tmp_op == '+') {
            while(top(operators) == '*' || top(operators) == '/') { 
                crnt_op = pop(operators);
                stack_entry frst = pop(numbers);
                stack_entry scnd = pop(numbers);
                if(crnt_op == '*') push(numbers, frst * scnd);
                if(crnt_op == '/') push(numbers, frst / scnd);
            }
        }
        stack_entry frst = pop(numbers);
        stack_entry scnd = pop(tmp);
        if(tmp_op == '-') push(tmp, scnd - frst);
        else if(tmp_op == '+') push(tmp, scnd + frst);
        else if(tmp_op == '*') push(tmp, scnd * frst);
        else if(tmp_op == '/') push(tmp, scnd / frst);
    }
    stack_entry result = pop(tmp);
    destroy(tmp);
    return result;
}
double calc_tail(char** ptrr) {
    Stack *numbers = newStack();
    Stack *operators = newStack();
    stringParse(ptrr, numbers, operators);
    double result = process(numbers, operators);
    destroy(numbers);
    destroy(operators);
    return result;
}
double calculate(char* ptr) {
    if(!blncchk(ptr)) {
        printf("Unbalanced equation.\n");
        exit(1);
    }
    return calc_tail(&ptr);
}
