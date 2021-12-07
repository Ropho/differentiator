#ifndef LIBR_TREE_DIFF_H
#define LIBR_TREE_DIFF_H

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <locale.h>
#include <assert.h>
#include <sys\stat.h>
#include <ctype.h>



typedef struct node {

    int data    = 0;

    char type  = 0;

    node *left = nullptr;

    node *right = nullptr;

}node;


enum TYPE {

    NUMBER    = 1,
    VARIABLE  = 2,
    OPERATION = 3,
    FUNCTION  = 4,
    FUNCTION_NAME = 5,
};


enum FUNCTIONS {

    LN  = 'l' + 'n',
    COS = 'c' + 'o' + 's',
    SIN = 's' + 'i' + 'n',

};

void ctor (node **node);
void dtor (node **node);
void func (node *node);
void pre_order (node **node, void (*func) (struct node **));
void in_order (node **node, void (*func) (struct node **));
void post_order (node **node, void (*func) (struct node **));
void dtor_tree (node **node);

#endif