#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char const *argv[])
{
    int key = 0;
    char str[100] = "";

    if (argc != 2) //get exactly 1 argument
    {
        printf("Usage: ./caesar key\n");
        exit(1);
    }

    key = atoi(argv[1]);

    while (1)
    {
        printf("plaintext:  ");
        fgets(str, 100, stdin);
        if (str[0] != '\n')
            break;
    }

    for (size_t i = 0; i < strlen(str); i++)
    {
        if (islower(str[i]))
            str[i] = (str[i] - 'a' + key) % 26 + 'a';
        else if (isupper(str[i]))
            str[i] = (str[i] - 'A' + key) % 26 + 'A';
    }

    printf("ciphertext: %s\n", str);

    return 0;
}
