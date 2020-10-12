#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <numeric>
#include <vector>

#define MSG_LEN 8
const int n = 1500;

static void bitwise_si(char *buf, unsigned i)
{
    uint8_t div3 = !(i % 3);
    uint8_t div5 = !(i % 5);
    unsigned int length = (2 << div3) << div5;

    char fmt[MSG_LEN + 1];
    strncpy(fmt, &"FizzBuzz%u"[(MSG_LEN >> div5) >> (div3 << 2)], length);
    fmt[length] = '\0';

    buf += sprintf(buf, fmt, i);
    buf += sprintf(buf, "\n");
}

int main()
{
    std::vector<unsigned> inputs(n);
    std::iota(inputs.begin(), inputs.end(), 1);
    char buf[16];
    for (int j = 0; j < 10000; ++j) {
        for (auto i : inputs) {
            bitwise_si(buf, i);
            asm volatile("" ::"g"(buf) : "memory");
        }
    }
}