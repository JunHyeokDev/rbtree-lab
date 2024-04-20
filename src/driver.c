#include "rbtree.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// void rbtree_to_print(node_t *t, node_t * nil) {
//   // TODO: implement to_print
//   // printf("t.print 진입\n");
//   if( t == nil ){
//     return;
//   }
//   if (t != nil){
//     char tmp;
//     if (t->color == RBTREE_RED) {
//         tmp = 'R';
//     } else {
//         tmp = 'B';
//     }
//     printf("My Vale is : %d  ",t->key);
    
//     printf("My color is : %c \n",tmp);
//   }
//   if(t->left != nil){
//     rbtree_to_print(t->left, nil);
//   }
//   if(t->right != nil){
//     rbtree_to_print(t->right, nil);
//   }
//   // return 0;
// }

void rbtree_to_print(node_t *t, node_t *nil)
{
    // TODO: implement to_print
    if (t == nil)
    {
        printf("노드 바닥이에용\n");
        return;
    }
    printf("key = %d, color = %d \n", t->key, t->color);
    rbtree_to_print(t->left, nil);
    rbtree_to_print(t->right, nil);
}

int main(int argc, char *argv[]) {
    rbtree *t = new_rbtree();
    // node_t *p = rbtree_insert(t, 26);
    // key_t entries[] = {10, 5, 8, 34, 67};
    key_t entries[] = {10, 5, 8, 34, 67, 23, 156, 24, 2, 12, 24, 36, 990, 25};
    const size_t n = sizeof(entries) / sizeof(entries[0]);
    for (int i = 0; i < n; i++)
    {
        rbtree_insert(t, entries[i]);
        /* code */
    }
    printf("최초 트리 리스트 출력");
    rbtree_to_print(t->root,t->nil);
    for (int i = 0; i < n; i++)
    {
        node_t *p = rbtree_find(t, entries[i]);
        // printf("arr[%d] = %d\n", i, arr[i]);
        // assert(p != NULL);
        // assert(p->key == arr[i]);
        rbtree_erase(t, p);
        // printf("%d 키-", entries[i]);
        // printf("%d 번째 출력\n", i+1);
        rbtree_to_print(t->root,t->nil);
    }
    // rbtree_insert(t, 17);
    // rbtree_insert(t, 41);
    // rbtree_insert(t, 47);
    // rbtree_insert(t, 21);
    printf("\n");
}