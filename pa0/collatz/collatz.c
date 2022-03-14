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

    char buf[256];
    char *string = fgets(buf, 256, fp);
    int number = atoi(string);
    while (number > 1)
    {
        printf("%d\n", number);
        number = number % 2 ? 3 * number + 1 : number / 2;
    }
    printf("%d\n", number);
    return EXIT_SUCCESS;
}
