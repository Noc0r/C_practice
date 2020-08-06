#include "list.h"
#include <stdlib.h>

typedef struct list_library list_lib;
typedef struct list
{
    node *first;
    node *last;
    int size;
    bool is_cyclic;
} list;

static list *create_list(bool is_cyclic);
static unsigned int count(list *list);
static void *get_by_index(list *list, unsigned int index);
static void set_by_index(list *list, unsigned int index, void *new_data);
static void pop_back(list *list);
static void pop_front(list *list);
static void clear(list *list);
static void push_back(list *list, void *data);
static void push_front(list *list, void *data);
static void insert_element(list *list, unsigned int pos, void *data);
static bool remove_element(list *list, void *element, int (*compare)(void *, void *));
static node *find_value(list *list, void *data, int (*compare)(void *, void *));

static list *create_list(bool is_cyclic)
{
    list *new_list = (list *)(malloc(sizeof(list)));
    new_list->first = NULL;
    new_list->last = NULL;
    new_list->is_cyclic = is_cyclic;
    new_list->size = 0;
    return new_list;
}

node *create_node(void *data)
{
    node *new_node = (node *)malloc(sizeof(node));
    new_node->data = data;
    new_node->next = NULL;
#ifdef LINKED_LIST
    {
        new_node->prev = NULL;
    }
#endif
    return new_node;
}

static void insert(node *pos, node *elem)
{
    elem->next = pos->next;
    pos->next = elem;
#ifdef LINKED_LIST
    {
        elem->prev = pos;
        if (elem->next)
            elem->next->prev = elem;
    }
#endif
}

static void insert_element(list *this, unsigned int pos, void *element)
{
    if (pos == 0)
        push_front(this, element);
    else if (pos >= this->size)
        push_back(this, element);
    else
    {
        node *elem = create_node(element);
        node *iter = this->first;
        for (size_t i = 0; i < pos - 1; i++)
        {
            iter = iter->next;
        }
        insert(iter, elem);
        this->size++;
    }
}

static bool remove_element(list *this, void *element, int (*compare)(void *, void *))
{
    if (!compare(this->first->data, element))
    {
        pop_front(this);
        return true;
    }
    for (node *iter = this->first; iter->next; iter = iter->next)
    {
        if (!compare(iter->next->data, element))
        {
            node *remove = iter->next;
            iter->next = remove->next;
#ifdef LINKED_LIST
            {
                if (remove->next)
                    remove->next->prev = iter;
            }
#endif
            if (remove == this->last)
                this->last = iter;
            free(remove);
            this->size--;
            return true;
        }
    }
    return false;
}

static node *find_value(list *this, void *find_data, int (*compare)(void *, void *))
{
    for (node *iter = this->first;; iter = iter->next)
    {
        if (!compare(iter->data, find_data))
            return iter;
        if (iter->next == this->first || iter->next == NULL)
            break;
    }
    return NULL;
}

static void pop_back(list *this)
{
    if (this->size)
    {
        node *iter = this->first;
#ifdef LINKED_LIST
        {
            iter = this->last->prev;
        }
#else
        for (; iter->next != this->last; iter = iter->next)
        {
        }
#endif
        node *remove = this->last;
        iter->next = remove->next;
        this->last = iter;
#ifdef LINKED_LIST
        {
            this->first->prev = this->last;
            if (remove->next)
                remove->next->prev = iter;
        }
#endif
        free(remove);
        this->size--;
        if (this->size == 0)
        {
            this->first = NULL;
            this->last = NULL;
        }
    }
}

static void pop_front(list *this)
{
    if (this->size)
    {
        node *remove = this->first;
        this->first = remove->next;
        if (this->is_cyclic)
        {
            this->last->next = this->first;
#ifdef LINKED_LIST
            this->first->prev = remove->prev;
#endif
        }
        free(remove);
        this->size--;
        if (this->size == 0)
        {
            this->first = NULL;
            this->last = NULL;
        }
    }
}

static void clear(list *this)
{
    while (this->size)
        pop_front(this);
}

static void push_back(list *this, void *element)
{
    node *elem = create_node(element);
    if (this->size)
    {
        insert(this->last, elem);
        this->last = elem;
    }
    else
    {
        this->first = elem;
        this->last = elem;
        if (this->is_cyclic)
            this->last->next = this->first;
    }
#ifdef LINKED_LIST
    this->first->prev = this->last;
#endif
    this->size++;
}

static void push_front(list *this, void *element)
{
    node *elem = create_node(element);
    if (this->size)
    {
        elem->next = this->first;
        this->first = elem;
    }
    else
    {
        this->first = elem;
        this->last = elem;
    }
    if (this->is_cyclic)
    {
        this->last->next = this->first;
#ifdef LINKED_LIST
        this->first->prev = this->last;
#endif
    }
    this->size++;
}

static unsigned int count(list *list)
{
    return list->size;
}

static void *get_by_index(list *list, unsigned int index)
{
    if (index < list->size)
    {
        node *tmp = list->first;
        for (size_t i = 0; i < index; i++)
            tmp = tmp->next;
        return tmp->data;
    }
    return NULL;
}

static void set_by_index(list *list, unsigned int index, void *new_data)
{
    if (index < list->size)
    {
        node *tmp = list->first;
        for (size_t i = 0; i < index; i++)
            tmp = tmp->next;
        tmp->data = new_data;
    }
}

list_lib *create_list_library()
{
    list_lib *library = (list_lib *)malloc(sizeof(list_lib));
    library->clear = clear;
    library->count = count;
    library->create_list = create_list;
    library->find_value = find_value;
    library->get_by_index = get_by_index;
    library->insert_element = insert_element;
    library->pop_back = pop_back;
    library->pop_front = pop_front;
    library->push_back = push_back;
    library->push_front = push_front;
    library->remove_element = remove_element;
    library->set_by_index = set_by_index;
    return library;
}