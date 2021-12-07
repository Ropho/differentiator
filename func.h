#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <locale.h>
#include <assert.h>
#include <sys\stat.h>
#include <ctype.h>
#include "libr\libr_tree_diff.h"

#define MINUS_ZERO -666

void graph                 (node* head);
static void in_order_graph (node *node, FILE *out);
static size_t FILESIZE_FUNC_FSTAT (FILE *in);
void get_buff_from_file (node **node, FILE *in);
void get_tree_from_buff (node **node, char **buff);
void diff (node **node);
void copy_node (node **dest, node *src);
void diff_pow_number (node **node);
void simplify (node **node);

#endif