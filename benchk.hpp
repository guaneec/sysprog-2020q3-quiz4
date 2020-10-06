#pragma once
#include <vector>

struct KPCase {
    KPCase(int n,
           std::vector<int> parents,
           std::vector<std::pair<int, int>> queries)
        : n(n), parents(parents), queries(queries){};

    int n;
    std::vector<int> parents;
    std::vector<std::pair<int, int>> queries;
};
