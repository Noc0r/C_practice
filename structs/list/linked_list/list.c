#include "list.h"
#include <stdlib.h>

list *create_list(void *data)
{
    list *new_elem = (list *)malloc(sizeof(list));
    new_elem->data = data;
    new_elem->next = NULL;
    return new_elem;
}

void insert_element(list *position, void *element)
{
    list *elem = create_list(element);
    elem->next = position->next;
    position->next = elem->next;
}

list *remove_element(list *head, void *element, int (*compare)(void *, void *))
{
    if(!compare(head->data,element))
    {
        list* new_head = head->next;
        free(head);
        return new_head;
    }
    for (list *iter = head; iter->next; iter = iter->next)
    {
        if (!compare(iter->next->data, element))
        {
            list* remove = iter->next;
            iter->next = remove->next;
            free(remove);
            return head;
        }
    }
    return head;
}

list *find_value(list *head, void *find_data, int (*compare)(void *, void *))
{
    for (list *iter = head; iter; iter = iter->next)
        if (!compare(iter->data, find_data))
            return iter;
    return NULL;
}
