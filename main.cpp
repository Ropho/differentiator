#include "func.h"
                                                                //TO DO
                                                                //REFACTORING
                                                                //1)INSERT RIGHT
                                                                //2)INSERT LEFT
                                                                //3)DELETE RIGHT/LEFT
                                                                //
                                                                //READ -1 from file
                                                                //add cos(x), ln(x)...


int main (void) {

    setlocale (LC_ALL, "Russian");

    FILE   *in  = fopen ("tree_in.txt", "r");
    assert (in != nullptr);

    node *head = nullptr;
    get_buff_from_file (&head, in);
    

    diff (&head);

    // graph (head);
    
    post_order (&head, simplify);

    graph (head);
    
    dtor (&head);
    
    return 0;
}