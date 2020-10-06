#include <cstdlib>

namespace kp_short
{
typedef struct {
    unsigned short **parent;
    int max_level;
    int n;
} TreeAncestor;

static unsigned short NEG1 = -1;

TreeAncestor *treeAncestorCreate(int n, int *parent, int parentSize)
{
    TreeAncestor *obj = (TreeAncestor *) malloc(sizeof(TreeAncestor));
    obj->parent = (unsigned short **) malloc(n * sizeof(unsigned short *));
    obj->n = n;

    int max_level = 32 - __builtin_clz(n) + 1;
    for (int i = 0; i < n; i++) {
        obj->parent[i] =
            (unsigned short *) malloc(max_level * sizeof(unsigned short));
        for (int j = 0; j < max_level; j++)
            obj->parent[i][j] = NEG1;
    }
    for (int i = 0; i < parentSize; i++)
        obj->parent[i][0] = parent[i];

    for (int j = 1;; j++) {
        int quit = 1;
        for (int i = 0; i < parentSize; i++) {
            obj->parent[i][j] = obj->parent[i][j - 1] == NEG1
                                    ? NEG1
                                    : obj->parent[obj->parent[i][j - 1]][j - 1];
            if (obj->parent[i][j] != NEG1)
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
    int max_level = obj->max_level;
    for (int i = 0; i < max_level && node != NEG1; ++i)
        if (k & (1 << i))
            node = obj->parent[node][i];
    return node == NEG1 ? -1 : node;
}

void treeAncestorFree(TreeAncestor *obj)
{
    for (int i = 0; i < obj->n; i++)
        free(obj->parent[i]);
    free(obj->parent);
    free(obj);
}
}  // namespace kp_short