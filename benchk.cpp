#include "benchk.hpp"
#include <benchmark/benchmark.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "kp/base.hpp"
#include "kp/ctzl.hpp"
#include "kp/flatten.hpp"
#include "kp/ftrans.hpp"
#include "kp/full.hpp"
#include "kp/hybrid.hpp"
#include "kp/level.hpp"
#include "kp/memcpy.hpp"
#include "kp/offset.hpp"
#include "kp/short.hpp"
#include "kpcases.hpp"

#define BENCH_KP(version)                                           \
    static void BM_##version(benchmark::State &state)               \
    {                                                               \
        auto &kp = kpcs[state.range(0) - 1];                        \
        for (auto _ : state) {                                      \
            auto ta = kp_##version::treeAncestorCreate(             \
                kp.n, kp.parents.data(), kp.parents.size());        \
            for (const auto &pair : kp.queries) {                   \
                int ans = kp_##version::treeAncestorGetKthAncestor( \
                    ta, pair.first, pair.second);                   \
                asm volatile("" : : "g"(ans) : "memory");           \
            }                                                       \
            kp_##version::treeAncestorFree(ta);                     \
        }                                                           \
    }                                                               \
    BENCHMARK(BM_##version)->DenseRange(1, 10)

BENCH_KP(base);
BENCH_KP(offset);
BENCH_KP(ctzl);
BENCH_KP(flatten);
BENCH_KP(ftrans);
BENCH_KP(hybrid);
BENCH_KP(short);
BENCH_KP(level);
BENCH_KP(memcpy);
BENCH_KP(full);



BENCHMARK_MAIN();
