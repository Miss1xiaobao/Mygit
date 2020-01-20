#ifndef SLIST_H
#define SLIST_H

/**
 * 双链表的结构体、初始化、增、删、查、改等；
*/

struct list_head
{   
    struct list_head *next;
    struct list_head *prev;
};

//循环双链表
//初始化链表头
#define INIT_LIST_HEAD(ptr)  do {  \
    (ptr)->next = (ptr);   (ptr)->prev = (ptr);  \
} while (0)

/*
 * Insert a new entry between two known consecutive entries. 
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static void __list_add(struct list_head *new, 
                    struct list_head *prev, 
                    struct list_head *next);



/**
 * list_add - add a new entry
 * @new: new entry to be added
 * @head: list head to add it after
 *
 * Insert a new entry after the specified head.
 * This is good for implementing stacks.
 */
void list_add(struct list_head *new, struct list_head *head);


/*
 * Delete a list entry by making the prev/next entries
 * point to each other.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static void __list_del(struct list_head *prev, struct list_head *next);



/**
 * list_del - deletes entry from list.
 * @entry: the element to delete from the list.
 * Note: list_empty on entry does not return true after this, the entry is in an undefined state.
 */
void list_del(struct list_head *entry);




/**
 * list_empty - tests whether a list is empty
 * @head: the list to test.
 */
// int list_isempty(struct list_head *head)
// {
//     return head->next == head;
// }

/* 通过结构体成员的地址，结构体的类型，找到该结构体的首地址 */
// 双链表每个entry的指针
/**
 * list_entry - get the struct for this entry
 * @ptr:	the &struct list_head pointer.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_struct within the struct.
 */
#define list_entry(ptr, type, member)               \
   ((type *)((char *)(ptr) - (unsigned long)(&((type *)0)->member)))

//遍历双链表
/**
 * list_for_each_entry_safe - iterate over list of given type safe against removal of list entry
 * @pos:	the type * to use as a loop counter.
 * @n:		another type * to use as temporary storage
 * @head:	the head for your list.
 * @member:	the name of the list_struct within the struct.
 */
#define list_for_each_entry_safe(pos, n, head, member)            \
    for (pos = list_entry((head)->next, typeof(*pos), member),    \
        n = list_entry(pos->member.next, typeof(*pos), member);   \
        &pos->member != (head);                                   \
        pos = n, n = list_entry(n->member.next, typeof(*n), member) \
    )

#endif