#include <cstdlib>

namespace kp_rstore
{
typedef struct {
    int **parent;
    int max_level;
    int n;
} TreeAncestor;

TreeAncestor *treeAncestorCreate(int n, int *parent, int parentSize)
{
    TreeAncestor *obj = (TreeAncestor *) malloc(sizeof(TreeAncestor));
    obj->parent = (int **) malloc(n * sizeof(int *));
    obj->n = n;

    int max_level = 32 - __builtin_clz(n) + 1;
    for (int i = 0; i < n; i++) {
        obj->parent[i] = (int *) malloc(max_level * sizeof(int));
        for (int j = 0; j < max_level; j++)
            obj->parent[i][max_level - j - 1] = -1;
    }
    for (int i = 0; i < parentSize; i++)
        obj->parent[i][max_level - 1] = parent[i];

    for (int j = 1;; j++) {
        int quit = 1;
        for (int i = 0; i < parentSize; i++) {
            obj->parent[i][max_level - j - 1] = obj->parent[i][max_level - j] == -1
                                    ? -1
                                    : obj->parent[obj->parent[i][max_level - j]][max_level - j];
            if (obj->parent[i][max_level - j - 1] != -1)
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
    for (int i = 0; i < max_level && node != -1; ++i)
        if (k & (1 << i))
            node = obj->parent[node][max_level - 1 - i];
    return node;
}

void treeAncestorFree(TreeAncestor *obj)
{
    for (int i = 0; i < obj->n; i++)
        free(obj->parent[i]);
    free(obj->parent);
    free(obj);
}
}  // namespace kp_base