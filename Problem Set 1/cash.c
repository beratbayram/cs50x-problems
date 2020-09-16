// IN CASE OF LINKER PROBLEM, USE 
// "cc cash.c -lm"  TO COMPILE

#include <stdio.h>
#include <math.h>

int removeCents(int *money, int value);

int main()
{
    int money = 0;

    {
        char str[100];
        double changeOwed = 0.0;

        while (1)
        {
            printf("Change owed: ");
            fgets(str, 100, stdin);
            if (str[0] != '\n')
                break;
        }

        sscanf(str,"%lf",&changeOwed);
        money = (int)round(changeOwed * 100);
    } //casting float to int in local scope

    printf("%d\n", removeCents(&money, 25) +
                       removeCents(&money, 10) +
                       removeCents(&money, 5) +
                       removeCents(&money, 1));
    return 0;
}

int removeCents(int *money, int value)
{
    int counter = 0;

    while (*money >= value)
    {
        *money -= value;
        counter++;
    }

    return counter;
}
