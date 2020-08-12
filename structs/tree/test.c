#include "binary_tree.h"
#include <stdio.h>
#include <time.h>

int compare(void *a, void *b)
{
    return *(int *)a - *(int *)b;
}

void print_tree(void *val)
{
    printf("%d\t", *(int *)val);
}

int main()
{
    srand(time(0));
    bin_tree_lib *library = create_bin_tree_library();
    bin_tree *tree = library->create_bin_tree(compare);
    for (int i = 0; i < 1000000; i++)
    {
        int *k = (int *)malloc(sizeof(int));
        *k = rand() % 100000;
        library->insert_element(tree, k);
    }
    int *find = (int *)malloc(sizeof(int));
    *find = 111;
    int *find_son = (int *)malloc(sizeof(int));
    *find_son = 110;
    library->insert_element(tree, find);
    library->insert_element(tree, find_son);
    if (library->find_value(tree, find))
    {
        printf("tree contains %d\n", *find);
        library->remove_element(tree, find);
    }
    printf("OBH1\n");
    library->preorder(tree, print_tree);
    printf("\n\n");

    printf("OBH2\n");
    library->inorder(tree, print_tree);
    printf("\n\n");

    printf("OBH3\n");
    library->postorder(tree, print_tree);
    printf("\n\n");
    library->clear(tree);
    free(library);
    return 0;
}