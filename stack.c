#include <stdlib.h>
#include "stack.h"

Stack* newStack() {
    Stack* new_stack = (Stack*) malloc(sizeof(Stack));
    new_stack->top = -1;
    new_stack->capacity = 10;
    new_stack->data = (stack_entry*) malloc(sizeof(stack_entry) * new_stack->capacity);
    return new_stack;
}
stack_entry pop(Stack *stack) {
    if(isEmpty(stack)) {
        return -1;
    }
    stack->top--;
    return *(stack->data + stack->top + 1);
}
stack_entry top(Stack *stack) {
    if(isEmpty(stack)) {
        return -1;
    }
    return *(stack->data + stack->top);
}
void push(Stack *stack, stack_entry value) {
    if(isFull(stack)) {
        expand(stack);
    }
    stack->top++;
    *(stack->data + stack->top) = value;
}
void stkcpy(Stack *stack1, Stack *stack2) {
    destroy(stack1);
    stack1 = (Stack*) malloc(sizeof(Stack));
    stack1->top = stack2->top;
    stack1->capacity = stack2->capacity;
    stack1->data = (stack_entry*) malloc(sizeof(stack_entry) * stack1->capacity);
    for(int i = 0; i <= stack2->top; i++) {
        *(stack1->data + i) = *(stack2->data + i);
    }
}
void expand(Stack *stack) {
    stack_entry *old_data = stack->data;
    stack->capacity *= 2;
    stack->data = (stack_entry*) malloc(sizeof(stack_entry) * stack->capacity);
    for(int i = 0; i <= stack->top; i++) {
        *(stack->data + i) = *(old_data + i);
    }
    free(old_data);
}
int blncchk(char *target) {
    Stack* stack = newStack();
    char opened[] = {'(', '{', '[', '<'};
    char closed[] = {')', '}', ']', '>'};
    for(int i = 0; *(target + i) != '\0'; i++) {
        char current = *(target + i);
        for(int j = 0; j < 4; j++) {
            if(current == opened[j]) {
                push(stack, opened[j]);
                break;
            }
        }
        for(int j = 0; j < 4; j++) {
            if(current == closed[j]) {
                if(opened[j] == top(stack)) {
                    pop(stack);
                    break;
                }
                else {
                    return 0;
                }
            }
        }
    }
    if(isEmpty(stack)) {
        return 1;
    }
    else {
        return 0;
    }
}
void reverse(Stack* stack) {
    if(isEmpty(stack)) {
        return;
    }
    for(int i = 0; i <= stack->top/2; i++) {
        stack_entry tmp = *(stack->data + i);
        *(stack->data + i) = *(stack->data + stack->top - i);
        *(stack->data + stack->top - i) = tmp;
    }
}
stack_entry returnFirst(Stack *stack) {
    if(isEmpty(stack)) {
        return -1;
    }
    return stack->data[0];
}
void destroy(Stack *target) {
    free(target->data);
    free(target);
}
int isEmpty(Stack *stack) {
    return (stack->top < 0);
}
int isFull(Stack *stack) {
    return (stack->top >= stack->capacity - 1);
}
int size(Stack *stack) {
    return (stack->top + 1);
}
