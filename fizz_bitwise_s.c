#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define MSG_LEN 8

static inline bool is_divisible(uint32_t n, uint64_t M)
{
    return n * M <= M - 1;
}

static uint64_t M3 = UINT64_C(0xFFFFFFFFFFFFFFFF) / 3 + 1;
static uint64_t M5 = UINT64_C(0xFFFFFFFFFFFFFFFF) / 5 + 1;

int main(int argc, char *argv[])
{
    char outstr[800];
    char *buf = outstr;
    for (size_t i = 1; i <= 100; i++) {
        uint8_t div3 = is_divisible(i, M3);
        uint8_t div5 = is_divisible(i, M5);
        unsigned int length = (2 << div3) << div5;

        char fmt[MSG_LEN + 1];
        strncpy(fmt, &"FizzBuzz%u"[(MSG_LEN >> div5) >> (div3 << 2)], length);
        fmt[length] = '\0';

        buf += sprintf(buf, fmt, i);
        buf += sprintf(buf, "\n");
    }
    printf("%s", outstr);
    return 0;
}