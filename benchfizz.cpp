#include <benchmark/benchmark.h>
#include <cstdio>
#include <cstring>

const int n = 100;

static void naive()
{
    for (unsigned int i = 1; i <= n; i++) {
        if (i % 15 == 0)
            printf("FizzBuzz");
        else if (i % 3 == 0)
            printf("Fizz");
        else if (i % 5 == 0)
            printf("Buzz");
        else  // if ((i % 3) && (i % 5))
            printf("%u", i);
        printf("\n");
    }
}


static void naive_s(char *buf)
{
    for (unsigned int i = 1; i <= n; i++) {
        if (i % 15 == 0)
            buf += sprintf(buf, "FizzBuzz");
        else if (i % 3 == 0)
            buf += sprintf(buf, "Fizz");
        else if (i % 5 == 0)
            buf += sprintf(buf, "Buzz");
        else  // if ((i % 3) && (i % 5))
            buf += sprintf(buf, "%u", i);
        sprintf(buf, "\n");
        ++buf;
    }
}

static void BM_naive(benchmark::State &state)
{
    for (auto _ : state) {
        naive();
    }
}

static void BM_naive_s(benchmark::State &state)
{
    char buf[n * 8];
    for (auto _ : state) {
        naive_s(buf);
    }
}


#define MSG_LEN 8

static inline bool is_divisible(uint32_t n, uint64_t M)
{
    return n * M <= M - 1;
}
static uint64_t M3 = UINT64_C(0xFFFFFFFFFFFFFFFF) / 3 + 1;
static uint64_t M5 = UINT64_C(0xFFFFFFFFFFFFFFFF) / 5 + 1;
static void bitwise()
{
    for (size_t i = 1; i <= n; i++) {
        uint8_t div3 = is_divisible(i, M3);
        uint8_t div5 = is_divisible(i, M5);
        unsigned int length = (2 << div3) << div5;

        char fmt[MSG_LEN + 1];
        strncpy(fmt, &"FizzBuzz%u"[(MSG_LEN >> div5) >> (div3 << 2)], length);
        fmt[length] = '\0';

        printf(fmt, i);
        printf("\n");
    }
}

static void bitwise_s(char *buf)
{
    for (size_t i = 1; i <= n; i++) {
        uint8_t div3 = is_divisible(i, M3);
        uint8_t div5 = is_divisible(i, M5);
        unsigned int length = (2 << div3) << div5;

        char fmt[MSG_LEN + 1];
        strncpy(fmt, &"FizzBuzz%u"[(MSG_LEN >> div5) >> (div3 << 2)], length);
        fmt[length] = '\0';

        buf += sprintf(buf, fmt, i);
        buf += sprintf(buf, "\n");
    }
}

static void BM_bitwise(benchmark::State &state)
{
    for (auto _ : state) {
        bitwise();
    }
}

static void BM_bitwise_s(benchmark::State &state)
{
    char buf[n * 8];
    for (auto _ : state) {
        bitwise_s(buf);
    }
}

BENCHMARK(BM_naive);
BENCHMARK(BM_bitwise);
BENCHMARK(BM_naive_s);
BENCHMARK(BM_bitwise_s);

BENCHMARK_MAIN();