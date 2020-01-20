#include <stdio.h>

static int a = 0;

void fun()
{
    a = 2;
    a++;
}

void print()
{
    printf("a = %d\n", a);
}
int main(int argc, char *argv[]) {
    printf("a = %d\n", a);
    fun();
    print();
    printf("a = %d\n", a);
    return 0;
}