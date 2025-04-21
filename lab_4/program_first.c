    #include "lib.h"
    #include <stdio.h>

    int main()
    {
        int request = 0;
        printf("requests:\n");
        printf("\"1\" - calculate PI \n");
        printf("\"2\" - converting a number to binary \n");
        printf("\"3\" - complete program \n");
        printf("Enter request: ");

        

        while (scanf("%d", &request) != EOF)
        {
                
            if (request == 1)
            {
                int order_row;

                printf("Enter order_row: ");
                scanf("%d", &order_row);
                printf("number PI: %f\n", pi(order_row));
            }
            else if (request == 2)
            {

                int decimal_number;
                printf("Enter decimal_number: ");
                scanf("%d", &decimal_number);
                char *binary_number = translation(decimal_number);
                printf("binary representation: %s\n", binary_number);
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
