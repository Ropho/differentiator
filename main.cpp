#include "func.h"
                                        //TODO
                                        //1) ������� ����� �� ������������
                                        //2) LATEX
                                        //3) ��������������
                                        //4) ���������
                                        //5) ....????
int main (void) {

    setlocale (LC_ALL, "Russian");

    FILE   *in  = fopen ("tree_in.txt", "r");
    assert (in != nullptr);

    node *head = nullptr;
    get_buff_from_file (&head, in);
    
    graph (head);

    return 0;
}