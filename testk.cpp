
#include <assert.h>
#include <cstdio>
#include "kpcases.hpp"

#include "kp/base.hpp"
#include "kp/ctzl.hpp"
#include "kp/fflip.hpp"
#include "kp/flatten.hpp"
#include "kp/fnoflip.hpp"
#include "kp/ftrans.hpp"
#include "kp/full.hpp"
#include "kp/hybrid.hpp"
#include "kp/level.hpp"
#include "kp/memcpy.hpp"
#include "kp/offset.hpp"
#include "kp/rscan.hpp"
#include "kp/rstore.hpp"
#include "kp/short.hpp"

#define TEST(version)                                                         \
    do {                                                                      \
        printf("testing " #version "...\n");                                  \
        for (auto &kp : kpcs) {                                               \
            auto ta1 = kp_base::treeAncestorCreate(kp.n, kp.parents.data(),   \
                                                   kp.parents.size());        \
            auto ta2 = kp_##version::treeAncestorCreate(                      \
                kp.n, kp.parents.data(), kp.parents.size());                  \
            for (const auto &pair : kp.queries) {                             \
                const auto ans1 = kp_base::treeAncestorGetKthAncestor(        \
                    ta1, pair.first, pair.second);                            \
                const auto ans2 = kp_##version::treeAncestorGetKthAncestor(   \
                    ta2, pair.first, pair.second);                            \
                if (ans1 != ans2) {                                           \
                    std::printf("\tTEST FAILED: expected %d, got %d\n", ans1, \
                                ans2);                                        \
                    return 1;                                                 \
                }                                                             \
            }                                                                 \
            kp_base::treeAncestorFree(ta1);                                   \
            kp_##version::treeAncestorFree(ta2);                              \
        }                                                                     \
        std::printf("\tTEST PASSED\n");                                       \
    } while (0)


int main()
{
    TEST(base);
    TEST(offset);
    TEST(ctzl);
    TEST(flatten);
    TEST(ftrans);
    TEST(hybrid);
    TEST(short);
    TEST(level);
    TEST(memcpy);
    TEST(rscan);
    TEST(rstore);
    TEST(fflip);
    TEST(fnoflip);
    TEST(full);
}