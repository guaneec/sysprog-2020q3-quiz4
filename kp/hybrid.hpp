#include <cstdlib>

namespace kp_hybrid
{
const int threshold = 100;
typedef struct {
    int *parent_lo;
    int **parent;
    int max_level;
    int n;
} TreeAncestor;

TreeAncestor *treeAncestorCreate(int n, int *parent, int parentSize)
{
    TreeAncestor *obj = (TreeAncestor *) malloc(sizeof(TreeAncestor));
    obj->n = n;
    if (n <= threshold) {
        obj->parent_lo = parent;
        return obj;
    }
    obj->parent = (int **) malloc(n * sizeof(int *));

    int max_level = 32 - __builtin_clz(n) + 1;
    for (int i = 0; i < n; i++) {
        obj->parent[i] = (int *) malloc(max_level * sizeof(int));
        for (int j = 0; j < max_level; j++)
            obj->parent[i][j] = -1;
    }
    for (int i = 0; i < parentSize; i++)
        obj->parent[i][0] = parent[i];

    for (int j = 1;; j++) {
        int quit = 1;
        for (int i = 0; i < parentSize; i++) {
            obj->parent[i][j] = obj->parent[i][j - 1] == -1
                                    ? -1
                                    : obj->parent[obj->parent[i][j - 1]][j - 1];
            if (obj->parent[i][j] != -1)
                quit = 0;
        }
        if (quit)
            break;
    }
    obj->max_level = max_level - 1;
    return obj;
}

int treeAncestorGetKthAncestor(TreeAncestor *obj, int node, int k)
{
    if (obj->n <= threshold) {
        while (true) {
            if (!k)
                return node;
            if (!node)
                return -1;
            --k;
            node = obj->parent_lo[node];
        }
    }
    int max_level = obj->max_level;
    for (int i = 0; i < max_level && node != -1; ++i)
        if (k & (1 << i))
            node = obj->parent[node][i];
    return node;
}

void treeAncestorFree(TreeAncestor *obj)
{
    if (obj->n > threshold) {
        for (int i = 0; i < obj->n; i++)
            free(obj->parent[i]);
        free(obj->parent);
    }
    free(obj);
}
}  // namespace kp_hybrid