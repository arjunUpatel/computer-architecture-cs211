#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define EXP_SZ 8
#define FRAC_SZ 23

int main(int argc, char *argv[])
{

    FILE *fp = fopen(argv[1], "r");
    if (!fp)
    {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    unsigned int sign = 0, e = 0;
    double m = 0;

    sign = fgetc(fp) - 48;
    for (int i = 0; i < EXP_SZ; i++)
        e += fgetc(fp) - 48 ? pow(2, EXP_SZ - i - 1) : 0;

    for (int i = 0; i < FRAC_SZ; i++)
        m += fgetc(fp) - 48 ? pow(.5, i + 1) : 0;

    fclose(fp);

    if (e == 0 && m == 0)
    {
        printf("%e\n", (double)0);
        return EXIT_SUCCESS;
    }
    if (0 < e && e < 255)
        e -= 127;
    m += 1.0;

    double number = ldexp(m, e);
    number = sign ? -number : number;
    printf("%e\n", number);
    return EXIT_SUCCESS;
}
