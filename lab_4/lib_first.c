#include "lib.h"
#include <stdlib.h>


float pi(int row_order){    //Ряд Лейбница
    float PI=0.0;
    int sign=1;
    for (size_t iteration_row = 0; iteration_row < row_order; ++iteration_row)
    {
        PI+=(4.0/(2*iteration_row+1)*sign);
        sign*=-1;
    }
    return PI;
}

char* translation(long x) {     //перевод в двоичную систему счисления
    int max_binary_length = 8 * sizeof(long) + 1;
    char* binary_number = (char*)malloc(max_binary_length);

    int index = max_binary_length - 1;
    
    binary_number[index--] = '\0';

    if (x == 0) {
        binary_number[index] = '0';
        return binary_number;
    }

    while (x != 0) {
        int remainder = x % 2;
        binary_number[index--] = remainder + '0';
        x /= 2;
    }
    return &binary_number[index + 1]; 
}
