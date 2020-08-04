#include <stdio.h>
#include "list/list.h"
#include "linked_list/linked_list.h"

int compare(void *a, void *b)
{
    if (*(int *)a > *(int *)b)
        return 1;
    if ((*(int *)a == *(int *)b))
        return 0;
    return -1;
}

int main()
{
    int test_a1 = 24, test_a2 = 23, test_a3 = 22;
    printf("LIST TESTS START\n");
    list *first = create_list(&test_a1);
    first->insert_element(first, &test_a2);
    first->insert_element(first, &test_a3);
    first = first->remove_element(first, &test_a3, compare);
    list *find_test = first->find_value(first, &test_a3, compare);
    if (find_test)
    {
        printf("find_test - %d\n", *((int *)find_test->data));
    }
    else
    {
        printf("find_test - not found\n");
    }

    for (list *tmp = first; tmp; tmp = tmp->next)
    {
        printf("%d\n", *((int *)tmp->data));
    }
    printf("LIST TEST END\n");

    printf("LINKED_LIST TEST START\n");
    linked_list *first_l = create_linked_list(&test_a1);
    first_l->insert_element(first_l, &test_a2);
    first_l->insert_element(first_l, &test_a3);
    first_l = first_l->remove_element(first_l, &test_a3, compare);
    linked_list *find_test_l = first_l->find_value(first_l, &test_a3, compare);
    if (find_test_l)
    {
        printf("find_test - %d\n", *((int *)find_test_l->data));
    }
    else
    {
        printf("find_test - not found\n");
    }

    for (linked_list *tmp = first_l; tmp; tmp = tmp->next)
    {
        printf("%d\n", *((int *)tmp->data));
        if (!tmp->next)
            first_l = tmp;
    }
    for (linked_list *tmp = first_l; tmp; tmp = tmp->prev)
    {
        printf("%d\n", *((int *)tmp->data));
    }
    printf("LINKED_LIST TEST END\n");
    return 0;
}