#include <stdio.h>
#include <string.h>
#include "calculator.h"

int main(void) {
    char buffer[100];
    memset(buffer, 0, 100);
    scanf("%[^\n]%*c", buffer);
    double result = calculate(buffer);
    printf("%0.2lf", result);
}
