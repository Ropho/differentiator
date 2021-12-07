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


void diff_sub (node **node) {

    assert (*node != nullptr);

    diff (&(*node)->left);
    diff (&(*node)->right);

    return;
}


void copy_node (node **dest, node *src) {

    assert (src != nullptr);

    if (*dest == nullptr)
        ctor (dest, 0);
    
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
    ctor (&plus, '+');

    struct node *left_mul = nullptr;
    ctor (&left_mul, '*');

    struct node *right_mul = nullptr;
    ctor (&right_mul, '*');

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

    puts ("ÑËÈØÊÎÌ ÑËÎÆÍÎ");

    abort ();
}


void diff_pow_number (node **node) {

    assert (*node != nullptr);

    struct node *right1 = nullptr;
    copy_node (&right1, (*node)->left);
    diff (&right1);

    struct node *mul2 = nullptr;
    ctor (&mul2, '*');

    copy_node (&(mul2->left), (*node)->right);
    copy_node (&(mul2->right), (*node));

    struct node *sub = nullptr;
    ctor (&sub, '-');

    copy_node (&(sub->left), mul2->left);
    ctor (&(sub->right), 0);
    sub->right->data = 1;
    sub->right->type = NUMBER;

    dtor (&(mul2->right->right));
    mul2->right->right = sub;

    struct node *mul1 = nullptr;
    ctor (&mul1, '*');
    mul1->right = right1;
    mul1->left = mul2;


    dtor_tree (node);
    *node = mul1;

    return;
}


void simplify (node **node) {

    assert (*node != nullptr);

    if ((*node)->type == OPERATION) {
        switch ((*node)->data) {

            case '*': 

                if ((*node)->right->data == 1) {
                    struct node *tmp = nullptr;
                    copy_node (&tmp, (*node)->left);

                    dtor_tree (node);
                    copy_node (node, tmp);
                }
                else if ((*node)->left->data == 1) {
                    struct node *tmp = nullptr;
                    copy_node (&tmp, (*node)->right);

                    dtor_tree (node);
                    copy_node (node, tmp);
                }
                else if ((*node)->right->data == 0 || (*node)->left->data == 0) {
                    dtor_tree (node);
                    ctor (node, 0);
                    (*node)->type = NUMBER;
                    (*node)->data = 0;
                }
                else if ((*node)->right->type == NUMBER && (*node)->left->type == NUMBER) {
                    
                    struct node *tmp = nullptr;
                    ctor (&tmp, 0);
                    tmp->type = NUMBER;
                    tmp->data = (*node)->left->data * (*node)->right->data;

                    dtor_tree (node);
                    copy_node (node, tmp);
                }
            break;

            case '+':

                if ((*node)->right->data == 0) {
                    struct node *tmp = nullptr;
                    copy_node (&tmp, (*node)->left);

                    dtor_tree (node);
                    copy_node (node, tmp);
                }
                else if ((*node)->left->data == 0) {
                    struct node *tmp = nullptr;
                    copy_node (&tmp, (*node)->right);

                    dtor_tree (node);
                    copy_node (node, tmp);
                }
                else if ((*node)->right->type == NUMBER && (*node)->left->type == NUMBER) {
                    
                    struct node *tmp = nullptr;
                    ctor (&tmp, 0);
                    tmp->type = NUMBER;
                    tmp->data = (*node)->left->data + (*node)->right->data;

                    dtor_tree (node);
                    copy_node (node, tmp);
                }
            break;

            case '-':

                if ((*node)->right->data == 0) {
                    struct node *tmp = nullptr;
                    copy_node (&tmp, (*node)->left);

                    dtor_tree (node);
                    copy_node (node, tmp);
                }
                else if ((*node)->left->data == 0) {
                    struct node *tmp = nullptr;
                    copy_node (&tmp, (*node)->right);

                    dtor_tree (node);
                    copy_node (node, tmp);
                }
                else if ((*node)->right->type == NUMBER && (*node)->left->type == NUMBER) {
                    
                    struct node *tmp = nullptr;
                    ctor (&tmp, 0);
                    tmp->type = NUMBER;
                    tmp->data = (*node)->left->data - (*node)->right->data;

                    dtor_tree (node);
                    copy_node (node, tmp);
                }
            break;

            case '^':

                if ((*node)->right->data == 1) {
                    
                    struct node *tmp = nullptr;
                    copy_node (&tmp, (*node)->left);

                    dtor_tree (node);
                    copy_node (node, tmp);
                }
                else if ((*node)->right->data == 0) {
                    struct node *tmp = nullptr;
                    ctor (&tmp, 0);
                    tmp->type = NUMBER;
                    tmp->data = 0;

                    dtor_tree (node);
                    copy_node (node, tmp);
                }
                
            break;
            default:
            break;
        }

    }
    return;
}


void diff_func (node **node) {

    assert (*node != nullptr);
    
    if ((*node)->left == nullptr)
        abort();

    switch ((*node)->left->data) {

        case LN: {
            (*node)->type = OPERATION;
            (*node)->data = '*';

            (*node)->left->type = OPERATION;
            (*node)->left->data = '^';
            copy_node (&(*node)->left->left, (*node)->right);
            ctor (&(*node)->left->right, 0);
            (*node)->left->right->type = NUMBER;
            (*node)->left->right->data = -1;

            diff (&(*node)->right);
        break;
        }
        case COS: {
            struct node *tmp = nullptr;
            ctor (&tmp, '*');
            
            struct node *sub = nullptr;
            ctor (&sub, 0);
            sub->type = NUMBER;
            sub->data = -1;

            (*node)->left->data = SIN;
            tmp->left = *node;
            tmp->right = sub;
            *node = tmp;

            tmp = nullptr;
            ctor (&tmp, '*');
            
            struct node *dif = nullptr;
            ctor (&dif, 0);
            copy_node (&dif, (*node)->left->right);
            diff (&dif);
            
            tmp->left = *node;
            tmp->right = dif;
            *node = tmp;
            break;
        }
        case SIN: {
           
            (*node)->left->data = COS;

            struct node *tmp = nullptr;
            ctor (&tmp, '*');
            
            struct node *dif = nullptr;
            ctor (&dif, 0);
            copy_node (&dif, (*node)->right);
            diff (&dif);
            
            tmp->left = *node;
            tmp->right = dif;
            *node = tmp;
            break;
        }
        default:
        break;
    }
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
                case '-': {
                    diff_sub (node);
                    return;
                break;
                }
                case '*': {
                    diff_mul (node);
                    return;
                break;
                }
                case '^': {
                    if ((*node)->right->type == NUMBER)
                        diff_pow_number (node);
                    else 
                        diff_pow (node);
                    return;
                break;
                }
                default:
                break;
            }

        break;
        }
        case FUNCTION :
            diff_func (node);
        break;

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
                ctor (node, 0);
                ++(*buff);
            }
            else {
                get_tree_from_buff (&(*node)->left, buff);
                
                if ((*node)->left->type != FUNCTION_NAME) {
                    (*node)->type = OPERATION;
                    (*node)->data = **buff;
                    printf ("%c", **buff);
                    ++(*buff);
                }
                else {
                    (*node)->type = FUNCTION;
                    (*node)->data = 'F';
                }
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
                if ((*node)->data >= 0) {
                    (*node)->data = 10 * (*node)->data + **buff - '0';
                }
                else if ((*node)->data != MINUS_ZERO)
                    (*node)->data = -1 * (10 * abs ((*node)->data) + **buff - '0');
                else 
                    (*node)->data = -1 * (**buff - '0');
                printf ("%c", **buff);
                ++(*buff);
            }
            else if (isalpha (**buff)) {

                if ((*node)->type == VARIABLE) {
                    (*node)->type = FUNCTION_NAME;
                    (*node)->data = (*node)->data + **buff;
                    printf ("%c", **buff);
                    ++(*buff);
                }
                else if ((*node)->type == FUNCTION_NAME) {
                    (*node)->data = (*node)->data + **buff;
                    printf ("%c", **buff);
                    ++(*buff);
                }
                else {
                    (*node)->type = VARIABLE;
                    (*node)->data = **buff;
                    printf ("%c", **buff);
                    ++(*buff);
                }
            }
            else if (**buff = '-') {
                (*node)->type = NUMBER;
                (*node)->data = MINUS_ZERO;
                printf ("%c", **buff);
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
        else if (node->type == VARIABLE) {
            fprintf (out, "%d [shape=diamond];\n", node);
            fprintf (out, "%d [style=filled,color=\"cyan2\"];\n", node);
            fprintf (out, "%d [label=\"%c\"]\n", node, node->data);
        }
        else if (node->type == FUNCTION_NAME) {
            fprintf (out, "%d [shape=star];\n", node);
            fprintf (out, "%d [style=filled,color=\"red\"];\n", node);
            fprintf (out, "%d [label=\"%d\"]\n", node, node->data);
        }
        else {
            fprintf (out, "%d [shape=oval];\n", node);
            fprintf (out, "%d [style=filled,color=\"hotpink\"];\n", node);
            fprintf (out, "%d [label=\"%c\"]\n", node, node->data); 
        }

    if (node->left != nullptr) {
        fprintf (out, "\"%d\" -> \"%d\";\n", node, node->left);

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
        else if (node->left->type == VARIABLE) {
            fprintf (out, "%d [shape=diamond];\n", node->left);
            fprintf (out, "%d [style=filled,color=\"cyan2\"];\n", node->left);
            fprintf (out, "%d [label=\"%c\"]\n", node->left, node->left->data);
        }
        else if (node->left->type == FUNCTION_NAME) {
            fprintf (out, "%d [shape=star];\n", node->left);
            fprintf (out, "%d [style=filled,color=\"red\"];\n", node->left);
            fprintf (out, "%d [label=\"%d\"]\n", node->left, node->left->data);
        }
        else {
            fprintf (out, "%d [shape=oval];\n", node->left);
            fprintf (out, "%d [style=filled,color=\"hotpink\"];\n", node->left);
            fprintf (out, "%d [label=\"%c\"]\n", node->left, node->left->data); 
        }
        fprintf (out, "\n");
        in_order_graph (node->left, out);
    }

    if (node->right != nullptr) {
        fprintf (out, "\"%d\" -> \"%d\";\n", node, node->right);

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
        else if (node->right->type == VARIABLE) {
            fprintf (out, "%d [shape=diamond];\n", node->right);
            fprintf (out, "%d [style=filled,color=\"cyan2\"];\n", node->right);
            fprintf (out, "%d [label=\"%c\"]\n", node->right, node->right->data);
        }
        else if (node->right->type == FUNCTION_NAME) {
            fprintf (out, "%d [shape=star];\n", node->right);
            fprintf (out, "%d [style=filled,color=\"red\"];\n", node->right);
            fprintf (out, "%d [label=\"%d\"]\n", node->right, node->right->data);
        }
        else {
            fprintf (out, "%d [shape=oval];\n", node->right);
            fprintf (out, "%d [style=filled,color=\"hotpink\"];\n", node->right);
            fprintf (out, "%d [label=\"%c\"]\n", node->right, node->right->data); 
        }        fprintf (out, "\n");
        in_order_graph (node->right, out);

    }
    
    return;
}


static size_t FILESIZE_FUNC_FSTAT (FILE *in) {

    assert (in != nullptr);

    struct stat buff = {};
    fstat (fileno (in), &buff);

    return buff.st_size;
}