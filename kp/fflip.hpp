#include <cstdint>
#include <cstdlib>

namespace kp_fflip
{
typedef struct {
    uint16_t *parent;
    int max_level;
    int n;
} TreeAncestor;

static uint16_t NEG1 = -1;

TreeAncestor *treeAncestorCreate(int n, int *parent, int parentSize)
{
    TreeAncestor *obj = (TreeAncestor *) malloc(sizeof(TreeAncestor));
    obj->n = n;

    int max_level = obj->max_level = 32 - __builtin_clz(n);
    obj->parent = (uint16_t *) malloc(n * max_level * sizeof(uint16_t));

    for (int i = 0; i < parentSize; i++)
        obj->parent[i] = parent[i];
    for (int i = n; i < n * max_level; ++i)
        obj->parent[i] = NEG1;

    for (int j = 1; j < max_level; j++) {
        int quit = 1;
        for (int i = 0; i < parentSize; i++) {
            obj->parent[i + n * j] =
                obj->parent[i + n * (j - 1)] == NEG1
                    ? NEG1
                    : obj->parent[obj->parent[i + n * (j - 1)] + n * (j - 1)];
            if (obj->parent[i + n * j] != NEG1)
                quit = 0;
        }
        if (quit)
            break;
    }
    return obj;
}

int treeAncestorGetKthAncestor(TreeAncestor *obj, int node, int k)
{
    int max_level = obj->max_level;
    for (int i = max_level; i >= 0 && node != NEG1; --i)
        if (k & (1 << i))
            node = obj->parent[node + obj->n * i];
    return node == NEG1 ? -1 : node;
}

void treeAncestorFree(TreeAncestor *obj)
{
    free(obj->parent);
    free(obj);
}
}  // namespace kp_fflip