#include <stdio.h>
#include <locale.h>
int main (void) {

    setlocale (LC_ALL, "Russian");

    puts ("всем привет, я только проснулся");

    return 0;
}