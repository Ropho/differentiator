#include <stdio.h>
#include <locale.h>
int main (void) {

    setlocale (LC_ALL, "Russian");

    puts ("���� ������, � ������ ���������");

    return 0;
}