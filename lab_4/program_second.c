#include "lib.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dlfcn.h>


int main()
{
    float (*pi_function)(int row_order) = NULL;
    char *(*translation_function)(long x) = NULL;
    void *library_descriptor_first = NULL;
    void *library_descriptor_second = NULL;

    printf("requests:\n");
    printf("\"0\" - swap library \n");
    printf("\"1\" - calculate pi \n");
    printf("\"2\" - converting a number to binary/ternary \n");
    printf("\"3\" - complete program \n");
    printf("Enter request: ");

    bool is_first_library = true;
    int request = 0;

    if ((library_descriptor_first = dlopen("libLib1.so", RTLD_LAZY)) == 0)
    {
        printf("OPEN LIBRARY ERROR\n");
        exit(-1);
    }
    if ((library_descriptor_second = dlopen("libLib2.so", RTLD_LAZY)) == 0)
    {
        printf("OPEN LIBRARY ERROR\n");
        exit(-1);
    }
    pi_function = dlsym(library_descriptor_first, "pi");
    translation_function = dlsym(library_descriptor_first, "translation");

    while (scanf("%d", &request) != EOF)
    {
        if (request == 0)
        {
            if (is_first_library)
            {
                pi_function = dlsym(library_descriptor_second, "pi");
                translation_function = dlsym(library_descriptor_second, "translation");
                is_first_library=false;
            }
            else
            {
                pi_function = dlsym(library_descriptor_first, "pi");
                translation_function = dlsym(library_descriptor_first, "translation");
                is_first_library=true;
            }
        }
        else if (request == 1)
        {
            int order_row;
            printf("Enter order_row: ");
            scanf("%d", &order_row);
            printf("number pi_function: %f\n", (*pi_function)(order_row));
        }
        else if (request == 2)
        {

            int decimal_number;
            printf("Enter decimal_number: ");
            scanf("%d", &decimal_number);
            char *number = (*translation_function)(decimal_number);
            printf("number representation: %s\n", number);
        }
        else if (request == 3)
        {

            printf("The program is completed.\n");
            break;
        }   
        else
        {
            printf("entered the wrong request.\n");
        }
        printf("Enter request: ");
    }

    return 0;
}
