#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>
void rbtree_to_print(node_t *t, node_t *nil);
int main(int argc, char *argv[])
{
    rbtree *t = new_rbtree();
    for (int i = 1; i <= 15; i ++) {
        rbtree_insert(t, i);
    }
    rbtree_to_print(t->root, t->nil);
    return 0;
}
void rbtree_to_print(node_t *t, node_t *nil)
{
    // TODO: implement to_print
    if (t == nil)
    {
        printf("노드 바닥이에용\n");
        return;
    }
    printf("t.print %d\n", t->key);
    rbtree_to_print(t->left, nil);
    rbtree_to_print(t->right, nil);
}