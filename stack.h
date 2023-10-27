#ifndef STACK_H
#define STACK_H

typedef double stack_entry;
typedef struct {
    int top;
    int capacity;
    stack_entry *data;
} Stack;

Stack* newStack();
stack_entry pop(Stack *stack);
stack_entry top(Stack *stack);
stack_entry returnFirst(Stack *stack);
void push(Stack *stack, stack_entry data);
void stkcpy(Stack *stack1, Stack *stack2);
void expand(Stack *stack);
void destroy(Stack *target);
void reverse(Stack *stack);
int blncchk(char *target);
int isEmpty(Stack *stack);
int isFull(Stack *stack);
int size(Stack *stack);

#endif // !STACK_H
