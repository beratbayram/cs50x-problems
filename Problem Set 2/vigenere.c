#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int normalize(char str[100]);

int main(int argc, char const *argv[])
{

    char key[100] = "";
    char str[100] = "";

    if (argc != 2) //get exactly 1 argument
    {
        printf("Usage: ./vigenere keyword\n");
        exit(1);
    }

    strcpy(key, argv[1]);

    if (normalize(key) == 1) // ensure that arg is valid
    {
        printf("Usage: ./vigenere keyword\n");
        exit(1);
    }

    while (1) //handling empty inputs
    {
        printf("plaintext:  ");
        fgets(str, 100, stdin);
        if (str[0] != '\n')
            break;
    }

    for (int keyShift = 0, i = 0; i < strlen(str); i++)
    {
        int keyNumber = key[(i + keyShift) % strlen(key)] - 'a';

        if (islower(str[i]))
            str[i] = (str[i] - 'a' + keyNumber) % 26 + 'a';
        else if (isupper(str[i]))
            str[i] = (str[i] - 'A' + keyNumber) % 26 + 'A';
        else
            keyShift--;
    }

    printf("ciphertext: %s\n", str);

    return 0;
}

int normalize(char str[100])
{
    for (size_t i = 0; i < strlen(str); i++)
    {
        if (!isalpha(str[i]))
            return 1;
        str[i] =  tolower(str[i]);
    }
    return 0;
}
