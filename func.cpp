#include "func.h"


void diff_const (node **node) {

    assert (*node != nullptr);

    (*node)->data = 0;

    return;
}


void diff_var (node **node) {

    assert (*node != nullptr);

    (*node)->data = 1;
    (*node)->type = NUMBER;

    return;
}


void diff_sum (node **node) {

    assert (*node != nullptr);

    diff (&(*node)->left);
    diff (&(*node)->right);

    return;
}


void copy_node (node **dest, node *src) {

    assert (src != nullptr);

    if (*dest == nullptr)
        ctor (dest);
    
    (*dest)->type = src->type;
    (*dest)->data = src->data;

    if (src->left != nullptr)
        copy_node (&(*dest)->left, src->left);
    if (src->right != nullptr)
        copy_node (&(*dest)->right, src->right);
    
    return;
}


void diff_mul (node **node) {

    assert (*node != nullptr);

    struct node *plus = nullptr;
    ctor (&plus);
    plus->type = OPERATION;
    plus->data = '+';

    struct node *left_mul = nullptr;
    ctor (&left_mul);
    left_mul->type = OPERATION;
    left_mul->data = '*';

    struct node *right_mul = nullptr;
    ctor (&right_mul);
    right_mul->type = OPERATION;
    right_mul->data = '*';

    plus->left = left_mul;
    plus->right = right_mul;


    copy_node (&(left_mul)->right, (*node)->left);
    copy_node (&(right_mul)->right, (*node)->right);

    diff (&(*node)->left);
    diff (&(*node)->right);
    
    copy_node (&(left_mul)->left, (*node)->right);
    copy_node (&(right_mul)->left, (*node)->left);

    dtor_tree (node);

    (*node) = plus;

    return;
}


void diff_pow (node **node) {

    assert (*node != nullptr);


    return;
}
void diff (node **node) {
    
    switch ((*node)->type) {

        case NUMBER: {
            diff_const (node);
            return;
        break;
        }

        case VARIABLE: {
            diff_var (node);
            return;
        break;
        }

        case OPERATION: {

            switch ((*node)->data) {
                
                case '+': {
                    diff_sum (node);
                    return;
                break;
                }

                case '*': {
                    diff_mul (node);
                    return;
                break;
                }
                case '^': {
                    diff_pow (node);
                    return;
                break;
                }
                default:
                break;
            }

        break;
        }

        default:
        break;
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
                ctor (node);
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

        if (node->type == NUMBER) {
            fprintf (out, "%d [shape=oval];\n", node);
            fprintf (out, "%d [style=filled,color=\"hotpink\"];\n", node);
            fprintf (out, "%d [label=\"%d\"]\n", node, node->data);
        }
        else if (node->type == OPERATION) {
            fprintf (out, "%d [shape=record];\n", node);
            fprintf (out, "%d [style=filled,color=\"green\"];\n", node);
            fprintf (out, "%d [label=\"%c\"]\n", node, node->data);
        }
        else {
            fprintf (out, "%d [shape=diamond];\n", node);
            fprintf (out, "%d [style=filled,color=\"cyan2\"];\n", node);
            fprintf (out, "%d [label=\"%d\"]\n", node, node->data);
        }

        if (node->left->type == NUMBER) {
            fprintf (out, "%d [shape=oval];\n", node->left);
            fprintf (out, "%d [style=filled,color=\"hotpink\"];\n", node->left);
            fprintf (out, "%d [label=\"%d\"]\n", node->left, node->left->data);
        }
        else if (node->left->type == OPERATION) {
            fprintf (out, "%d [shape=record];\n", node->left);
            fprintf (out, "%d [style=filled,color=\"green\"];\n", node->left);
            fprintf (out, "%d [label=\"%c\"]\n", node->left, node->left->data);
        }
        else {
            fprintf (out, "%d [shape=diamond];\n", node->left);
            fprintf (out, "%d [style=filled,color=\"cyan2\"];\n", node->left);
            fprintf (out, "%d [label=\"%d\"]\n", node->left, node->left->data);
        }
        in_order_graph (node->left, out);
    }

    if (node->right != nullptr) {
        fprintf (out, "\"%d\" -> \"%d\";\n", node, node->right);

        if (node->type == NUMBER) {
            fprintf (out, "%d [shape=oval];\n", node);
            fprintf (out, "%d [style=filled,color=\"hotpink\"];\n", node);
            fprintf (out, "%d [label=\"%d\"]\n", node->right, node->right->data);
        }
        else if (node->type == OPERATION) {
            fprintf (out, "%d [shape=record];\n", node);
            fprintf (out, "%d [style=filled,color=\"green\"];\n", node);
            fprintf (out, "%d [label=\"%c\"]\n", node, node->data);
        }
        else {
            fprintf (out, "%d [shape=diamond];\n", node);
            fprintf (out, "%d [style=filled,color=\"cyan2\"];\n", node);
            fprintf (out, "%d [label=\"%c\"]\n", node, node->data);
        }

        if (node->right->type == NUMBER) {
            fprintf (out, "%d [shape=oval];\n", node->right);
            fprintf (out, "%d [style=filled,color=\"hotpink\"];\n", node->right);
            fprintf (out, "%d [label=\"%d\"]\n", node->right, node->right->data);
        }
        else if (node->right->type == OPERATION) {
            fprintf (out, "%d [shape=record];\n", node->right);
            fprintf (out, "%d [style=filled,color=\"green\"];\n", node->right);
            fprintf (out, "%d [label=\"%c\"]\n", node->right, node->right->data);
        }
        else {
            fprintf (out, "%d [shape=diamond];\n", node->right);
            fprintf (out, "%d [style=filled,color=\"cyan2\"];\n", node->right);
            fprintf (out, "%d [label=\"%c\"]\n", node->right, node->right->data); 
        }

        in_order_graph (node->right, out);

    }
    
    if (node->left == nullptr && node->right == nullptr) {
        if (node->type == NUMBER) {
            fprintf (out, "%d [shape=oval];\n", node);
            fprintf (out, "%d [style=filled,color=\"hotpink\"];\n", node);
            fprintf (out, "%d [label=\"%d\"];\n", node, node->data);
        }
        else if (node->type == OPERATION) {
            fprintf (out, "%d [shape=record];\n", node);
            fprintf (out, "%d [style=filled,color=\"green\"];\n", node);
            fprintf (out, "%d [label=\"%c\"];\n", node, node->data);          
        }
        else {
            fprintf (out, "%d [shape=diamond];\n", node);
            fprintf (out, "%d [style=filled,color=\"cyan2\"];\n", node);
            fprintf (out, "%d [label=\"%c\"];\n", node, node->data);
        }
    }
    return;
}


static size_t FILESIZE_FUNC_FSTAT (FILE *in) {

    assert (in != nullptr);

    struct stat buff = {};
    fstat (fileno (in), &buff);

    return buff.st_size;
}