#include <stdio.h>
#include <stdlib.h>



struct list_head
{   
    struct list_head *next;
    struct list_head *prev;
};

#define INIT_LIST_HEAD(ptr)  do {  \
    (ptr)->next = (ptr);   (ptr)->prev = (ptr);  \
} while (0)



struct xiaom{
    int a;
    int b;
};


struct list_head *s;

int main() {
#if 0
    struct xiaom *zhao = NULL;
    zhao = (struct xiaom *)calloc(1, sizeof(int));
    if(zhao == NULL){
        return 0;
    }
    zhao->a = 6;
    zhao->b = 5;
    printf("a = %d, b = %d\n", zhao->a, zhao->b);
    free(zhao);
#endif

    struct list_head *head;
    printf("s = %p\n", s);
    printf("head = %p\n", head);
    
    INIT_LIST_HEAD(head); 
    s = head;

    printf("s = %p\n", s);
    
    return 0;
}