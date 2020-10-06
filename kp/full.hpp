#include <cstdint>
#include <cstdlib>

namespace kp_full
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

    int max_level = 32 - __builtin_clz(n) + 1;
    obj->parent = (uint16_t *) malloc(n * max_level * sizeof(uint16_t));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < max_level; j++)
            obj->parent[i * max_level + j] = NEG1;
    }
    for (int i = 0; i < parentSize; i++)
        obj->parent[i * max_level] = parent[i];

    for (int j = 1;; j++) {
        int quit = 1;
        for (int i = 0; i < parentSize; i++) {
            obj->parent[i * max_level + j] =
                obj->parent[i * max_level + j - 1] == NEG1
                    ? NEG1
                    : obj->parent[(obj->parent[i * max_level + j - 1]) *
                                      max_level +
                                  j - 1];
            if (obj->parent[i * max_level + j] != NEG1)
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
    int max_level = obj->max_level + 1;
    while (k && node != NEG1) {
        int i = __builtin_ctzl(k);
        k ^= k & -k;
        node = obj->parent[node * max_level + i];
    }
    return node == NEG1 ? -1 : node;
}

void treeAncestorFree(TreeAncestor *obj)
{
    free(obj->parent);
    free(obj);
}
}  // namespace kp_full