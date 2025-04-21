#include "lib.h"
#include <stdlib.h>

float pi(int row_order){    // Формула Валисса
    float PI = 2.0;
    for (size_t iteration_row = 1; iteration_row <= row_order; ++iteration_row)
    {
        PI *= (4.0 * iteration_row * iteration_row) / ((4.0 * iteration_row * iteration_row) - 1);
    }
    return PI;
}

char *translation(long x)
{
    int max_ternary_length = 8 * sizeof(long) + 1;

    char *ternary_number = (char *)malloc(max_ternary_length);

    int index = max_ternary_length - 1;

    ternary_number[index--] = '\0';

    if (x == 0)
    {
        ternary_number[index] = '0';
        return ternary_number;
    }

    while (x != 0)
    {
        int remainder = x % 3;
        ternary_number[index--] = remainder + '0';
        x /= 3;
    }

    return &ternary_number[index + 1];
}
