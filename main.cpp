#include "func.h"
                                                                //TO DO 7.12
                                                                //1)производные cos,sin,ln
                                                                //2)добавить отриц числа
                                                                //3)рефакторинг (add,
                                                                //delete) node


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