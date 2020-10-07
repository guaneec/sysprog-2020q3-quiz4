#include <cstdlib>

namespace kp_offset
{
typedef struct {
    int **parent;
    int max_level;
    int n;
} TreeAncestor;

TreeAncestor *treeAncestorCreate(int n, int *parent, int parentSize)
{
    TreeAncestor *obj = (TreeAncestor *) malloc(sizeof(TreeAncestor));
    obj->parent = (int **) malloc((n + 1) * sizeof(int *));
    obj->n = n;

    int max_level = 32 - __builtin_clz(n) + 1;
    for (int i = 0; i < n + 1; i++) {
        obj->parent[i] = (int *) malloc(max_level * sizeof(int));
        for (int j = 0; j < max_level; j++)
            obj->parent[i][j] = 0;
    }
    for (int i = 0; i < parentSize; i++)
        obj->parent[i + 1][0] = parent[i] + 1;



    for (int j = 1;; j++) {
        int quit = 1;
        for (int i = 0; i < parentSize; i++) {
            obj->parent[i + 1][j] =
                obj->parent[obj->parent[i + 1][j - 1]][j - 1];
            if (obj->parent[i + 1][j])
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
    node = node + 1;
    int max_level = obj->max_level;
    for (int i = 0; i < max_level && node; ++i)
        if (k & (1 << i))
            node = obj->parent[node][i];
    return node - 1;
}

void treeAncestorFree(TreeAncestor *obj)
{
    for (int i = 0; i < obj->n + 1; i++)
        free(obj->parent[i]);
    free(obj->parent);
    free(obj);
}
}  // namespace kp_shift
