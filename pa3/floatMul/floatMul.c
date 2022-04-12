#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define EXP_SZ 8
#define FRAC_SZ 23

bool *addOne(bool *binArr)
{
    bool carry = true;
    for (int i = 7; i >= 0; i--)
    {
        if (carry)
        {
            if (binArr[i])
            {
                binArr[i] = false;
                carry = true;
            }
            else
            {
                binArr[i] = true;
                carry = false;
            }
        }
    }
    return binArr;
}

bool *addBin(bool *binArr1, bool *binArr2)
{
    bool carry = false;
    bool *res = calloc(8, sizeof(bool));
    for (int i = 7; i >= 0; i--)
    {
        if (carry)
        {
            if (binArr1[i] && binArr2[i])
            {
                res[i] = true;
                carry = true;
            }
            else if (binArr1[i] || binArr2[i])
            {
                res[i] = false;
                carry = true;
            }
            else
            {
                res[i] = true;
                carry = false;
            }
        }
        else
        {
            if (binArr1[i] && binArr2[i])
            {
                res[i] = false;
                carry = true;
            }
            else if (binArr1[i] || binArr2[i])
            {
                res[i] = true;
                carry = false;
            }
            else
            {
                res[i] = false;
                carry = false;
            }
        }
    }
    return res;
}

int main(int argc, char *argv[])
{
    FILE *fp = fopen(argv[1], "r");
    if (!fp)
    {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    // read the binary number representation of multiplier
    bool multiplier_binary[32];
    for (int i = 0; i < 32; i++)
        multiplier_binary[i] = fgetc(fp) - 48;

    fgetc(fp);

    // read the binary number representation of multiplcand
    bool multiplicand_binary[32];
    for (int i = 0; i < 32; i++)
        multiplicand_binary[i] = fgetc(fp) - 48;

    // SIGN
    bool sign;
    if (multiplier_binary[0] != multiplicand_binary[0])
        sign = true;
    else
        sign = false;

    // EXP
    // get the exp field of the multiplier and multiplicand
    bool multiplier_exp_bin[8];
    bool multpilicand_exp_bin[8];
    for (int i = 0; i < 8; i++)
    {
        multiplier_exp_bin[i] = multiplier_binary[i + 1];
        multpilicand_exp_bin[i] = multiplicand_binary[i + 1];
    }

    // add the two exp together
    bool *exp_binary = addBin(multiplier_exp_bin, multpilicand_exp_bin);

    // subtract bias
    bool *bias = calloc(8, sizeof(bool));
    bias[0] = true;
    bias = addOne(bias);

    // add the sum of two exp and bias for two's complement subtraction
    bool *difference = addBin(exp_binary, bias);
    free(exp_binary);
    free (bias);

    // multiply the mantissas
    long int multiplier_mant = 0;
    long int multiplicand_mant = 0;
    int expCount = 0;
    for (int i = 31; i > 8; i--)
    {
        if (multiplicand_binary[i])
            multiplicand_mant += ldexp(1, expCount);
        if (multiplier_binary[i])
            multiplier_mant += ldexp(1, expCount);
        expCount++;
    }
    multiplicand_mant += ldexp(1, expCount);
    multiplier_mant += ldexp(1, expCount);
    long int product_mant = multiplicand_mant * multiplier_mant;

    // overflow and normalize
    bool product_mant_bin[64];
    for (int i = 63; i >= 0; i--)
    {
        product_mant_bin[i] = product_mant & 1;
        product_mant = product_mant >> 1;
    }

    bool mant[24];
    bool carry;
    int msbIndex = -1;
    int count = 0;
    while (!product_mant_bin[count])
        count++;
    msbIndex = count;
    if (msbIndex < 17)
        difference = addOne(difference);

    count = 0;
    for (int i = msbIndex; i < msbIndex + 24; i++)
    {
        mant[count] = product_mant_bin[i];
        count++;
    }

    // rounding
    if (product_mant_bin[msbIndex + 24])
    {
        carry = true;
        for (int i = 23; i >= 0; i--)
        {
            if (carry)
            {
                if (mant[i])
                {
                    mant[i] = false;
                    carry = true;
                }
                else
                {
                    mant[i] = true;
                    carry = false;
                }
            }
        }
    }

    printf("%d_", sign);
    for (int i = 0; i < 8; i++)
        printf("%d", difference[i]);
    printf("_");
    for (int i = 1; i < 24; i++)
        printf("%d", mant[i]);
    
    free(difference);
    return (EXIT_SUCCESS);
}
