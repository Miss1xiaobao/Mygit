#include <stdio.h>

#define list_entry(ptr, type, member) \
   ((type *)((char *)(ptr) - (unsigned long)(&((type *)0)->member)))

typedef struct dev{
    int a;
    int b;
    char name[20];
    char flag;
}dev;

#if 0

int main() {
    struct dev x = {1, 2, "xiaohu", 9};
    struct dev *y;
    y = list_entry(&(x.flag), typeof(struct dev), flag);

    printf("%p\n", y);

    printf("x = %p\n", (void *)&x);
    unsigned int f =  (unsigned int)(&((struct dev *)0)->flag);
    printf("f = %x\n", f);
    printf("x = %p\n", (char *)&(x.flag));
    printf("x = %p\n", &(x.flag));
    printf("x = %p\n", ((char *)&(x.flag) - f));
}
#endif