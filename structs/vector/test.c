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

void print_vector(vector *test)
{
    vector_lib *library = create_vector_library();
    for (int i = 0; i < library->count(test); i++)
    {
        printf("pos - %d, value - %d\n", i, *(int *)library->get_by_index(test, i));
    }
    free(library);
}

int main()
{
    vector_lib *library = create_vector_library();
    vector *test = library->create_vector(20);
    for (int i = 0; i < 70; i++)
    {
        int *k = (int *)malloc(sizeof(int));
        *k = i;
        library->push_back(test, k);
    }
    print_vector(test);
    int rem_elem = 25;
    library->remove_element(test, &rem_elem, compare);
    library->remove_index(test, 40);
    print_vector(test);
    free(library);
    return 0;
}