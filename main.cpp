#include "func.h"
                                                                //TO DO
                                                                //1)INSERT RIGHT
                                                                //2)INSERT LEFT
                                                                //3)DELETE RIGHT/LEFT

int main (void) {

    setlocale (LC_ALL, "Russian");

    FILE   *in  = fopen ("tree_in.txt", "r");
    assert (in != nullptr);

    node *head = nullptr;
    get_buff_from_file (&head, in);
    
    // graph (head);

    diff (&head);

    graph (head);
    
    dtor (&head);
    
    return 0;
}