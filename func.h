#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <locale.h>
#include <assert.h>
#include <sys\stat.h>
#include <ctype.h>
#include "libr_tree_diff.h"



void ctor                  (node *head);
void dtor                  (node **node);
void graph                 (node* head);
static void in_order_graph (node *node, FILE *out);
static size_t FILESIZE_FUNC_FSTAT (FILE *in);
void get_buff_from_file (node **node, FILE *in);
void get_tree_from_buff (node **node, char **buff);