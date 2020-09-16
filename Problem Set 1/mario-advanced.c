#include <stdio.h>
#include <stdlib.h>

int main()
{
    int number = 0;

    while (1)
    {
        printf("Height: ");
        char str[100];
        gets(str);
        number = atoi(str);

        if (0 < number && number < 9)
            break;
    }
    for (int i = 1; i <= number; i++)
    {
        for (int j = 0; j < number - i; j++)
            printf(" ");
        for (int j = 0; j < i; j++)
            printf("#");

        printf("  ");

        for (int j = 0; j < i; j++)
            printf("#");
        for (int j = 0; j < number - i; j++)
            printf(" ");
        
        printf("\n");
    }
    return 0;
}
