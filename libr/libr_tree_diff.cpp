#include "libr_tree_diff.h"


void ctor (node **node, char param) {

    *node = (struct node*)calloc(1, sizeof (struct node));

    switch (param) {
    
    case '*':
        (*node)->right = nullptr;
        (*node)->left  = nullptr;
        ctor (&(*node)->left, 0);
        ctor (&(*node)->right, 0);

        (*node)->type  = OPERATION;
        (*node)->data  = '*';
    break;
    
    case '+':
        (*node)->right = nullptr;
        (*node)->left  = nullptr;
        ctor (&(*node)->left, 0);
        ctor (&(*node)->right, 0);

        (*node)->type  = OPERATION;
        (*node)->data  = '+';
    break;

    case '-':
        (*node)->right = nullptr;
        (*node)->left  = nullptr;
        ctor (&(*node)->left, 0);
        ctor (&(*node)->right, 0);

        (*node)->type  = OPERATION;
        (*node)->data  = '-';
    break;

    default:
        (*node)->right = nullptr;
        (*node)->left  = nullptr;
    
        (*node)->data  = 0;
        (*node)->type  = 0;
    break;
    }
    return;
}


void pre_order (node **node, void (*func) (struct node **)) {

    assert (*node != nullptr);

    func (node);

    if ((*node)->left != nullptr)
        pre_order (&(*node)->left, func);
    
    if ((*node)->right != nullptr)
        pre_order (&(*node)->right, func);
    
    return;
}


void in_order (node **node, void (*func) (struct node **)) {

    assert (*node != nullptr);

    if ((*node)->left != nullptr)
        in_order (&(*node)->left, func);
    
    func (node);

    if ((*node)->right != nullptr)
        in_order (&(*node)->right, func);
    
    return;
}




void post_order (node **node, void (*func) (struct node **)) {

    assert (*node != nullptr);

    if ((*node)->left != nullptr)
        post_order (&(*node)->left, func);
    

    if ((*node)->right != nullptr)
        post_order (&(*node)->right, func);

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


