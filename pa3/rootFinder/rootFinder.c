#include <stdlib.h>
#include <stdio.h>
#include <float.h>

double fabs(double value)
{
    return value < 0.0 ? -value : value;
}

double multiply(double val, size_t exponent)
{
    double res = 1;
    for (size_t i = 0; i < exponent; i++)
        res *= val;
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
    double x;
    fscanf(fp, "%lf", &x);

    size_t n;
    fscanf(fp, "%ld", &n);

    double precision;
    fscanf(fp, "%lf", &precision);

    double guess_r_max = x < 1.0 ? 1.0 : x;
    double guess_r_min = 0.0;
    while (precision < multiply(guess_r_max, n) - multiply(guess_r_min, n))
    {
        double guess_r_mid = (guess_r_min + guess_r_max) / 2;
        if (multiply(guess_r_mid, n) > x)
            guess_r_max = guess_r_mid;
        else
            guess_r_min = guess_r_mid;
    }

    double guess_r = (guess_r_min + guess_r_max) / 2;
    printf("%lf\n", guess_r);
    
    return EXIT_SUCCESS;
}
