#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

void RB_Insert_Fixup(rbtree *t, node_t *z);

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
    printf("라이트 로테이트");
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
    printf("픽스업 진입");
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
    while (cur != t->nil) {
        if (cur->key < key) 
        {
            cur = cur->right;
        }
        else if (cur->key > key)
        {
            cur = cur->left;
        }
        else {
            return cur;
        }
    }
    return NULL;
}

node_t *rbtree_min(const rbtree *t)
{
    // TODO: implement find
    return t->root;
}

node_t *rbtree_max(const rbtree *t)
{
    // TODO: implement find
    return t->root;
}

int rbtree_erase(rbtree *t, node_t *p)
{
    // TODO: implement erase
    return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n)
{
    // TODO: implement to_array
    return 0;
}
