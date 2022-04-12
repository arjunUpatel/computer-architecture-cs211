#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define EXP_SZ 11
#define FRAC_SZ 52

int main(int argc, char *argv[])
{

    FILE *fp = fopen(argv[1], "r");
    if (!fp)
    {
        perror("fopen failed");
        return 0;
    }

    double value;
    fscanf(fp, "%lf", &value);

    if (1.0 / value == -INFINITY)
    {
        printf("%d_", 1);
        for (int i = 0; i < EXP_SZ; i++)
            printf("0");
        printf("_");
        for (int i = 0; i < FRAC_SZ; i++)
            printf("0");
        return EXIT_SUCCESS;
    }
    else if (1.0 / value == INFINITY)
    {
        printf("%d_", 0);
        for (int i = 0; i < EXP_SZ; i++)
            printf("0");
        printf("_");
        for (int i = 0; i < FRAC_SZ; i++)
            printf("0");
        return EXIT_SUCCESS;
    }

    bool sign = value < 0.0;
    printf("%d_", sign);

    double fraction = sign ? -value : value;
    signed short E = 0;
    unsigned int shift = 0;
    if (fraction < ldexp(1.0, -1023))
    {
        for (int i = 0; i < EXP_SZ; i++)
            printf("0");
        printf("_");

        while (!(fraction >= 1.0 && fraction < 2.0))
        {
            fraction *= 2.0;
            shift++;
        }
        shift -= 1022;
    }
    else
    {
        if (fraction < 1.0)
        {
            while (!(fraction >= 1.0 && fraction < 2.0))
            {
                fraction *= 2.0;
                E--;
            }
        }
        else
        {
            while (!(fraction >= 1.0 && fraction < 2.0))
            {
                fraction /= 2.0;
                E++;
            }
        }
        unsigned short bias = (1 << (EXP_SZ - 1)) - 1;
        signed short exp = E + bias;

        for (int exp_index = EXP_SZ - 1; 0 <= exp_index; exp_index--)
        {
            bool exp_bit = 1 & exp >> exp_index;
            printf("%d", exp_bit);
        }
        printf("_");
    }

    // THE FRAC FIELD
    fraction -= 1;
    double x = .5;

    bool frac_array[FRAC_SZ + 1]; // one extra LSB bit for rounding
    for (int frac_index = FRAC_SZ; 0 <= frac_index; frac_index--)
    {
        frac_array[frac_index] = false; // frac set to zero to enable partial credit
        if (fraction >= x)
        {
            fraction -= x;
            frac_array[frac_index] = true;
        }
        x /= 2;
    }

    if (frac_array[0])
    {
        bool carry = true;
        for (int i = 1; i < FRAC_SZ; i++)
        {
            if (carry)
            {
                if (frac_array[i])
                {
                    frac_array[i] = false;
                    carry = true;
                }
                else
                {
                    frac_array[i] = true;
                    carry = false;
                }
            }
        }
    }
    if (shift != 0)
    {
        for (int i = shift + 1; i < FRAC_SZ; i++)
        {
            frac_array[i - shift] = frac_array[i];
        }
        if (shift == 1)
            frac_array[FRAC_SZ] = true;
        else if (shift == 2)
        {
            frac_array[FRAC_SZ] = false;
            frac_array[FRAC_SZ - 1] = true;
        }
    }

    for (int frac_index = FRAC_SZ - 1; 0 <= frac_index; frac_index--)
    {
        bool frac_bit = frac_array[frac_index + 1]; // skipping the extra LSB bit for rounding
        printf("%d", frac_bit);
    }
}
