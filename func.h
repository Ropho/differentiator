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

    NUMBER   = 1,
    VARIABLE = 2,
    OPERATION = 3,

};


void ctor                  (node *head);
void graph                 (node* head);
static void in_order_graph (node *node, FILE *out);
static size_t FILESIZE_FUNC_FSTAT (FILE *in);
void get_buff_from_file (node **node, FILE *in);
void get_tree_from_buff (node **node, char **buff);