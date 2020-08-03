#include "linked_list.h"
#include <stdlib.h>

linked_list *create_linked_list(void *data)
{
    linked_list *new_elem = (linked_list *)malloc(sizeof(linked_list));
    new_elem->data = data;
    new_elem->next = NULL;
    new_elem->prev = NULL;
    return new_elem;
}

void insert_element(linked_list *position, void *element)
{
    linked_list *elem = create_linked_list(element);
    elem->next = position->next;
    elem->prev = position;
    if(elem->next)
        elem->next->prev = elem;
    position->next = elem->next;
}

linked_list *remove_element(linked_list *head, void *element, int (*compare)(void *, void *))
{
    if(!compare(head->data,element))
    {
        linked_list* new_head = head->next;
        if(new_head)
            new_head->prev = head->prev;
        free(head);
        return new_head;
    }
    for (linked_list *iter = head; iter->next; iter = iter->next)
    {
        if (!compare(iter->next->data, element))
        {
            linked_list* remove = iter->next;
            iter->next = remove->next;
            if(iter->next)
                iter->next->prev = iter; 
            free(remove);
            return head;
        }
    }
    return head;
}

linked_list *find_value(linked_list *head, void *find_data, int (*compare)(void *, void *))
{
    for (linked_list *iter = head; iter; iter = iter->next)
        if (!compare(iter->data, find_data))
            return iter;
    return NULL;
}
