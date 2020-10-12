#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <numeric>
#include <random>
#include <vector>

#define MSG_LEN 8
const int n = 1500;

static void naive_si(char *buf, unsigned i)
{
    if (i % 15 == 0)
        buf += sprintf(buf, "FizzBuzz");
    else if (i % 3 == 0)
        buf += sprintf(buf, "Fizz");
    else if (i % 5 == 0)
        buf += sprintf(buf, "Buzz");
    else  // if ((i % 3) && (i % 5))
        buf += sprintf(buf, "%u", i);
    sprintf(buf, "\n");
}

int main()
{
    std::vector<unsigned> inputs(n);
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<unsigned> dist(1, n);
    for (auto &i : inputs)
        i = dist(gen);
    char buf[16];
    for (int j = 0; j < 10000; ++j) {
        for (auto i : inputs) {
            naive_si(buf, i);
            asm volatile("" ::"g"(buf) : "memory");
        }
    }
}