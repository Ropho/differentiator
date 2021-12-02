#include "func.h"


node *diff (node *node) {
    
    switch (node->type) {

        case NUMBER:
            // return new_node (NUMBER, 0, nullptr, nullptr);
        case VARIABLE:
            return;
        default:
            return;
    }

    return;
}


void get_buff_from_file (node **head,  FILE *in) {
    
    size_t file_size = FILESIZE_FUNC_FSTAT (in);
    char buff[file_size + 1] = {};
    
    fread (buff, sizeof (char), file_size, in);

    (buff)[file_size] = '\0';
    puts (buff);

    char *ptr = &buff[0];
    get_tree_from_buff (head, &ptr);

    return;
}


void get_tree_from_buff (node **node, char **buff) {

    assert (node  != nullptr);
    assert (*buff != nullptr);

    while (1) {

        if (**buff == '(') {
            if (*node == nullptr) {
                *node = (struct node*)calloc(1, sizeof (struct node));
                ctor (*node);
                ++(*buff);
            }
            else {
                get_tree_from_buff (&(*node)->left, buff);
                
                (*node)->type = OPERATION;
                (*node)->data = **buff;
                printf ("%c", **buff);
                ++(*buff);
                
                get_tree_from_buff (&(*node)->right, buff);
            }
        }

        else if (**buff == ')') {
            ++(*buff);
            return;
        }

        else if (**buff != '\0') {

            if (isdigit (**buff)) {
                
                (*node)->type = NUMBER;
                (*node)->data = 10 * (*node)->data + **buff - '0';
                printf ("%c", **buff);
                ++(*buff);
            }
            else if (isalpha (**buff)) {
                
                (*node)->type = VARIABLE;
                (*node)->data = **buff;
                printf ("%c",**buff);
                ++(*buff);
            }
            else {
                assert (0);
            }
                
        }
        else
            break;
    }

    return;
}


void graph (node* head) {

    assert (head != nullptr);

    FILE *out = fopen ("demo.txt", "w");
    assert (out != nullptr);

    fputs ("digraph structs {\n", out);
    //fputs ("node [shape=record];\n", out);
    fputs ("node [style=filled,color=\"hotpink\"];\n", out);
    in_order_graph (head, out);
    fputs ("}", out);

    fclose (out);

    system (".\\graphviz\\bin\\dot -Tpng demo.txt -o graph.png");

    system ("graph.png");


    return;
}


static void in_order_graph (node *node, FILE *out) {
    
    assert (node != nullptr);
    assert (out  != nullptr);

    if (node->left != nullptr) {
        fprintf (out, "\"%d\" -> \"%d\";\n", node, node->left);

        if (node->type == NUMBER)
            fprintf (out, "%d [label=\"%d\"]\n", node, node->data);
        else
            fprintf (out, "%d [label=\"%c\"]\n", node, node->data);

        if (node->left->type == NUMBER)
            fprintf (out, "%d [label=\"%d\"]\n", node->left, node->left->data);
        else
            fprintf (out, "%d [label=\"%c\"]\n", node->left, node->left->data);

        in_order_graph (node->left, out);
    }

    if (node->right != nullptr) {
        fprintf (out, "\"%d\" -> \"%d\";\n", node, node->right);

         if (node->type == NUMBER)
            fprintf (out, "%d [label=\"%d\"]\n", node, node->data);
        else
            fprintf (out, "%d [label=\"%c\"]\n", node, node->data);

        if (node->right->type == NUMBER)
            fprintf (out, "%d [label=\"%d\"]\n", node->right, node->right->data);
        else
            fprintf (out, "%d [label=\"%c\"]\n", node->right, node->right->data);

        in_order_graph (node->right, out);

    }
    
    if (node->left == nullptr && node->right == nullptr) {
        if (node->type == NUMBER)
            fprintf (out, "%d [label=\"%d\"];\n", node, node->data);
        else
            fprintf (out, "%d [label=\"%c\"];\n", node, node->data);

    }
    return;
}


static size_t FILESIZE_FUNC_FSTAT (FILE *in) {

    assert (in != nullptr);

    struct stat buff = {};
    fstat (fileno (in), &buff);

    return buff.st_size;
}