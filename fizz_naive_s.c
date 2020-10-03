#include <stdio.h>

#define n 100

int main()
{
    char out[n*8];
    char *ptr = out;

    for (unsigned int i = 1; i <= 100; i++) {
        if (i % 15 == 0)
            ptr += sprintf(ptr, "FizzBuzz");
        else if (i % 3 == 0)
            ptr += sprintf(ptr, "Fizz");
        else if (i % 5 == 0)
            ptr += sprintf(ptr, "Buzz");
        else  // if ((i % 3) && (i % 5))
            ptr += sprintf(ptr, "%u", i);
        sprintf(ptr, "\n");
        ++ptr;
    }
    printf("%s", out);
    return 0;
}