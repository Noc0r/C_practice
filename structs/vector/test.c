#include <stdio.h>
#include <stdlib.h>
#include "vector/vector.h"

int compare(void *a, void *b)
{
    if (*(int *)a > *(int *)b)
        return 1;
    if ((*(int *)a == *(int *)b))
        return 0;
    return -1;
}

void print_vector(vector* test)
{
    for (int i = 0; i < count(test); i++)
    {
        printf("pos - %d, value - %d\n", i, *(int *)get_by_index(test, i));
    }
}

int main()
{
    vector *test = create_vector(20);
    for (int i = 0; i < 70; i++)
    {
        int *k = (int *)malloc(sizeof(int));
        *k = i;
        push_back(test, k);
    }
    print_vector(test);
    int rem_elem = 25;
    remove_element(test, &rem_elem, compare);
    remove_index(test, 40);
    print_vector(test);
    return 0;
}