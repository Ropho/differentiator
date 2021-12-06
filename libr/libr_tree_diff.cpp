#include "libr_tree_diff.h"


void ctor (node **node) {

    *node = (struct node*)calloc(1, sizeof (struct node));

    (*node)->right = nullptr;
    (*node)->left  = nullptr;

    (*node)->data  = 0;
    (*node)->type  = 0;

    return;
}


void func (node *node) {
    
    assert (node != nullptr);

    printf ("%d", node->data);

    return;
}


void pre_order (node *node, void (*func) (struct node *)) {

    assert (node != nullptr);

    func (node);

    if (node->left != nullptr)
        pre_order (node->left, func);
    if (node->right != nullptr)
        pre_order (node->right, func);

    return;
}


void in_order (node *node, void (*func) (struct node *)) {

    assert (node != nullptr);

    if (node->left != nullptr)
        in_order (node->left, func);
    
    func (node);

    if (node->right != nullptr)
        in_order (node->right, func);
    
    return;
}


void post_order (node *node, void (*func) (struct node *)) {

    assert (node != nullptr);

    if (node->left != nullptr)
        in_order (node->left, func);
    
    if (node->right != nullptr)
        in_order (node->right, func);

    func (node);

    return; 
}


void dtor (node **node) {

    if (*node == nullptr)
        return;

    (*node)->right = nullptr;
    (*node)->left  = nullptr;

    (*node)->data  = 0;
    (*node)->type  = 0;
    
    free (*node);

    *node = nullptr;

    return;
}


void dtor_tree (node **node) {

    assert (*node != nullptr);

    if ((*node)->left != nullptr)
        dtor_tree (&((*node)->left));
    if ((*node)->right != nullptr)
        dtor_tree (&((*node)->right));

    dtor (node);

    return;
}

