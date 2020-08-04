#include "list.h"
#include <stdlib.h>


static void link(list *list);

list *create_list(void *data)
{
    list *new_elem = (list *)malloc(sizeof(list));
    new_elem->data = data;
    new_elem->next = NULL;
    link(new_elem);
    return new_elem;
}

static void insert_element(list *position, void *element)
{
    list *elem = create_list(element);
    elem->next = position->next;
    position->next = elem;
}

static list *remove_element(list *head, void *element, int (*compare)(void *, void *))
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

static list *find_value(list *head, void *find_data, int (*compare)(void *, void *))
{
    for (list *iter = head; iter; iter = iter->next)
        if (!compare(iter->data, find_data))
            return iter;
    return NULL;
}

static void link(list *list)
{
    list->insert_element = insert_element;
    list->remove_element = remove_element;
    list->find_value = find_value;
}