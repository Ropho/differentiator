#include "func.h"
                                        //TODO 6.12
                                        //add lib!!!

                                        //1) дифференциатор
                                        //2) LATEX
                                        //3) упрощение

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