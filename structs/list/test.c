#include <stdio.h>
#include "list/list.h"

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
    list *first = create_list(true);
    push_front(first, &test_a1);
    push_front(first, &test_a1);
    insert_element(first, 3, &test_a2);
    insert_element(first, 3, &test_a3);
    remove_element(first, &test_a3, compare);
    node *find_test = find_value(first, &test_a3, compare);
    if (find_test)
    {
        printf("find_test - %d\n", *((int *)find_test->data));
    }
    else
    {
        printf("find_test - not found\n");
    }
    pop_front(first);
    insert_element(first, 1, &test_a2);
    pop_back(first);
    printf("%d\n", first->size);
    printf("LIST TEST END\n");
    return 0;
}