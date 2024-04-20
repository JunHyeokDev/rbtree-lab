#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

void RB_Insert_Fixup(rbtree *t, node_t *z);
node_t *Find_successor(node_t *cur, node_t *nil);
void RB_TransPlant(rbtree *t, node_t *u, node_t *v);
void RB_Delete_fixup(rbtree *t, node_t *cur);
rbtree *new_rbtree(void);
node_t *rbtree_min(const rbtree *t);

rbtree *new_rbtree(void)
{
    // TODO: initialize struct if needed
    rbtree *p = (rbtree *)malloc(sizeof(rbtree));

    p->nil = (node_t *)malloc(sizeof(node_t));
    p->nil->color = RBTREE_BLACK;
    p->nil->parent = p->root;
    p->root = p->nil;

    return p;
}

void delete_rbtree_recursively(node_t *cur, node_t *nil)
{
    if (cur == nil)
    {
        return;
    }
    delete_rbtree_recursively(cur->left, nil);
    delete_rbtree_recursively(cur->right, nil);
    free(cur);
}

void delete_rbtree(rbtree *t)
{
    // TODO: reclaim the tree nodes's memory
    delete_rbtree_recursively(t->root, t->nil);
    free(t->nil);
    free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key)
{
    // TODO: implement insert
    node_t *y = t->nil;
    node_t *x = t->root;
    node_t *z = (node_t *)malloc(sizeof(node_t));

    z->key = key;

    while (x != t->nil)
    {
        y = x;
        if (z->key < x->key)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    z->parent = y;

    if (y == t->nil)
    {
        t->root = z;
    }
    else if (z->key < y->key)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }
    z->left = t->nil;
    z->right = t->nil;
    z->color = RBTREE_RED;
    RB_Insert_Fixup(t, z);
    return t->root;
}

void Left_Rotate(rbtree *t, node_t *cur)
{
    node_t *target = cur->right;
    cur->right = target->left;

    if (target->left != t->nil)
    {
        target->left->parent = cur;
    }
    target->parent = cur->parent;

    if (cur->parent == t->nil)
    {
        t->root = target;
    }
    else if (cur == cur->parent->left)
    {
        cur->parent->left = target;
    }
    else
    {
        cur->parent->right = target;
    }
    target->left = cur;
    cur->parent = target;
}

void Right_Rotate(rbtree *t, node_t *cur)
{
    printf("라이트 로테이트\n");
    // y = cur
    node_t *target = cur->left;
    cur->left = target->right;

    if (target->right != t->nil)
    {
        target->right->parent = cur;
    }

    target->parent = cur->parent;

    if (cur->parent == t->nil)
    {
        t->root = target;
    }

    else if (cur == cur->parent->right)
    {
        cur->parent->right = target;
    }
    else
    {
        cur->parent->left = target;
    }
    target->right = cur;
    cur->parent = target;
}

void RB_Insert_Fixup(rbtree *t, node_t *cur)
{
    printf("픽스업 진입\n");
    while (cur->parent->color == RBTREE_RED)
    {
        if (cur->parent == cur->parent->parent->left)
        {
            node_t *uncle = cur->parent->parent->right;

            if (uncle->color == RBTREE_RED)
            {
                cur->parent->color = RBTREE_BLACK;
                uncle->color = RBTREE_BLACK;
                cur->parent->parent->color = RBTREE_RED;
                cur = cur->parent->parent;
                continue;
            }
            else if (cur == cur->parent->right)
            {
                cur = cur->parent;
                Left_Rotate(t, cur);
            }
            cur->parent->color = RBTREE_BLACK;
            cur->parent->parent->color = RBTREE_RED;
            Right_Rotate(t, cur->parent->parent);
        }
        else
        {
            node_t *uncle = cur->parent->parent->left;

            if (uncle->color == RBTREE_RED)
            {
                cur->parent->color = RBTREE_BLACK;
                uncle->color = RBTREE_BLACK;
                cur->parent->parent->color = RBTREE_RED;
                cur = cur->parent->parent;
                continue;
            }
            else if (cur == cur->parent->left)
            {
                cur = cur->parent;
                Right_Rotate(t, cur);
            }
            cur->parent->color = RBTREE_BLACK;
            cur->parent->parent->color = RBTREE_RED;
            Left_Rotate(t, cur->parent->parent);
        }
    }
    t->root->color = RBTREE_BLACK;
}

node_t *rbtree_find(const rbtree *t, const key_t key)
{
    // TODO: implement find
    node_t *cur = t->root;

    while (cur != t->nil)
    {
        if (cur->key == key)
        {
            return cur;
        }
        else if (cur->key < key)
        {
            cur = cur->right;
        }
        else
        {
            cur = cur->left;
        }
    }
    return NULL;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  if (t->root == t->nil) {
    return NULL;
  }
  node_t * curr = t->root;

  while (curr->left != t->nil) {
    curr = curr->left;
  }
  return curr;
}

node_t *rbtree_max(const rbtree *t)
{
    // TODO: implement find
    return t->root;
}

void RB_TransPlant(rbtree *t, node_t *u, node_t *v)
{
    // printf("TransPlant 진입 u is : %d  !! \n", u->key );
    // printf("TransPlant 진입 v is : %d  !! \n", v->key );

    if (u->parent == t->nil)
    {
        t->root = v;
    }
    else if (u == u->parent->left)
    {
        u->parent->left = v;
    }
    else
    {
        u->parent->right = v;
    }
    // printf("TransPlant 탈출 u parent is : %d  !! \n", u->parent->key );
    // printf("TransPlant 탈출 v parent is : %d  !! \n", v->parent->key );

    v->parent = u->parent;
    // printf("TransPlant 탈출 u parent is : %d  !! \n", u->parent->key );
    // printf("TransPlant 탈출 v parent is : %d  !! \n", v->parent->key );

}

node_t *Find_successor(node_t *cur, node_t *nil)
{
    printf("Before Successor 값 : %d !! \n",cur->key );
    while (cur->left != nil)
    {
        cur = cur->left;
    }
    printf("After Successor 값 : %d !! \n",cur->key );
    return cur;
}

int rbtree_erase(rbtree *t, node_t *target)
{
    // TODO: implement erase
    node_t *replcae = target;
    color_t target_original_color = replcae->color;
    node_t *successor;
    node_t *x;
    // printf("Target 값 : %d !! \n",target->key );
    // printf("Target right 값 : %d !! \n",target->right->key );
    // printf("Target left  값 : %d !! \n",target->left->key );

    if (target->left == t->nil)
    {
        x = target->right;
        RB_TransPlant(t, target, target->right);
    }
    else if (target->right == t->nil)
    {
        x = target->left;
        RB_TransPlant(t, target, target->left);
    }
    else
    {
        // printf("Target Before go to Find_Successor값 : %d !! \n",target->key );
        
        successor = target->right;
        while(successor->left != t->nil){
            successor = successor->left;
        }

        target_original_color = successor->color;
        x = successor->right;
        
        if (successor->parent == target)
        {
            x->parent = successor;
        }
        else
        {
            RB_TransPlant(t, successor, successor->right);
            successor->right = target->right;
            successor->right->parent = successor;
        }
        RB_TransPlant(t, target, successor);
        successor->left = target->left;
        successor->left->parent = successor;
        successor->color = target->color;
    }
    // printf("target is deleted? or ? %d\n", target->key);
    if (target_original_color == RBTREE_BLACK)
    {
        RB_Delete_fixup(t, x);
    }
    // free zone
    free(target);

    return 0; // return what ?
}

void RB_Delete_fixup(rbtree *t, node_t *cur)
{
    node_t *bro;
    while (cur != t->root && cur->color == RBTREE_BLACK) {
        if (cur == cur->parent->left)
        {
            bro = cur->parent->right;
            if (bro->color == RBTREE_RED)
            {                                    // 형제의 컬러가 Red인 경우
                bro->color = RBTREE_BLACK;       // 형제는 Black으로
                cur->parent->color = RBTREE_RED; // 부모의 색상을 RED로 바꾼 뒤 부모를 기준으로 회전.
                Left_Rotate(t, cur->parent);
                bro = cur->parent->right;
            }
            if (bro->left->color == RBTREE_BLACK && bro->right->color == RBTREE_BLACK)
            {
                bro->color = RBTREE_RED; // 여기서 bro가 쭈왑 당해서 레드가 됨.
                cur = cur->parent;       // cur는 위로 올림. 따라서 cur 는 Doubly black이 되거나 Red_and_black이 되어
                // 다음 이터레이션에서 또 다른 케이스를 만나게 될 것임.
            }
            else
            {
                if (bro->right->color == RBTREE_BLACK)
                {
                    bro->left->color = RBTREE_BLACK;
                    bro->color = RBTREE_RED;
                    Right_Rotate(t, bro);
                    bro = cur->parent->right;
                }
                bro->color = cur->parent->color;
                cur->parent->color = RBTREE_BLACK;
                bro->right->color = RBTREE_BLACK;
                Left_Rotate(t, cur->parent);
                cur = t->root;
            }
        }
        else
        {
            bro = cur->parent->left;
            if (bro->color == RBTREE_RED)
            {                                    // 형제의 컬러가 Red인 경우
                bro->color = RBTREE_BLACK;       // 형제는 Black으로
                cur->parent->color = RBTREE_RED; // 부모의 색상을 RED로 바꾼 뒤 부모를 기준으로 회전.
                Right_Rotate(t, cur->parent);
                bro = cur->parent->left;
            }
            if (bro->right->color == RBTREE_BLACK && bro->left->color == RBTREE_BLACK)
            {
                bro->color = RBTREE_RED; // 여기서 bro가 쭈왑 당해서 레드가 됨.
                cur = cur->parent;       // cur는 위로 올림. 따라서 cur 는 Doubly black이 되거나 Red_and_black이 되어
                // 다음 이터레이션에서 또 다른 케이스를 만나게 될 것임.
            }
            else
            {
                if (bro->left->color == RBTREE_BLACK)
                {
                    bro->right->color = RBTREE_BLACK;
                    bro->color = RBTREE_RED;
                    Left_Rotate(t, bro);
                    bro = cur->parent->left;
                }
                bro->color = cur->parent->color;
                cur->parent->color = RBTREE_BLACK;
                bro->left->color = RBTREE_BLACK;
                Right_Rotate(t, cur->parent);
                cur = t->root;
            }
        }
    }
    cur->color = RBTREE_BLACK;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n)
{
    // TODO: implement to_array
    return 0;
}
