#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{

    FILE *fp = fopen(argv[1], "r");
    if (!fp)
    {
        perror("fopen failed");
        return EXIT_FAILURE;
    }
    
    bool minuend[8];
    for (int i = 7; 0 <= i; i--)
        minuend[i] = fgetc(fp) - 48;
    fgetc(fp);

    bool subtrahend[8];
    for (int i = 7; 0 <= i; i--)
        subtrahend[i] = fgetc(fp) - 48 ? 0 : 1;
    fclose(fp);

    bool carry = true;
    for (int i = 0; i < 8; i++)
    {
        if (carry)
        {
            if (subtrahend[i])
            {
                subtrahend[i] = false;
                carry = true;
            }
            else
            {
                subtrahend[i] = true;
                carry = false;
            }
        }
    }

    carry = false;
    bool difference[8];
    for (int i = 0; i < 8; i++)
    {
        if (carry)
        {
            if (subtrahend[i] && minuend[i])
            {
                carry = true;
                difference[i] = true;
            }
            else if (subtrahend[i] || minuend[i])
            {
                carry = true;
                difference[i] = false;
            }
            else
            {
                difference[i] = true;
                carry = false;
            }
        }
        else
        {
            if (subtrahend[i] && minuend[i])
            {
                carry = true;
                difference[i] = false;
            }
            else if (subtrahend[i] || minuend[i])
            {
                carry = false;
                difference[i] = true;
            }
            else
            {
                difference[i] = false;
                carry = false;
            }
        }
    }

    for (int i = 7; 0 <= i; i--)
        printf("%d", difference[i]);
    printf("\n");

    return EXIT_SUCCESS;
}
