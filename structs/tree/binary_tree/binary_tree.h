#ifndef BINARY_TREE
#define BINARY_TREE
#include <stdbool.h>
#include <stdlib.h>

/**
 * Binary tree, based on default pointer nodes
 * @author Senatrev Ruslan
 * @param data           pointer to the data of element
 * @param right          pointer to the right node(son) in the tree
*/

typedef struct node node;

typedef struct bin_tree bin_tree;

typedef struct bin_tree_library
{


    /**
    * Preorder traversal
    * @param bin_tree           pointer to the tree
    * @param func               pointer to the function, used for each element
    * @return                   amount of elements
    */
    void (*preorder)(bin_tree *bin_tree, void (*func)(void* data));
    /**
    * Inorder traversal
    * @param bin_tree           pointer to the tree
    * @param func               pointer to the function, used for each element
    * @return                   amount of elements
    */
    void (*inorder)(bin_tree *bin_tree, void (*func)(void* data));
    /**
    * Postorder traversal 
    * @param bin_tree           pointer to the tree
    * @param func               pointer to the function, used for each element
    * @return                   amount of elements
    */
    void (*postorder)(bin_tree *bin_tree, void (*func)(void* data));
    /**
    * Get size of current tree
    * @param bin_tree           pointer to the tree
    * @return                   amount of elements
    */
    unsigned int (*count)(bin_tree *bin_tree);

    /**
    * Remove all elements in the tree
    * @param bin_tree           pointer to the tree
    * @return               
    */
    void (*clear)(bin_tree *bin_tree);

    /**
    * Insert new element int the tree
    * @param bin_tree           pointer to the tree
    * @param data               data of new element       
    * @return              
    */
    void (*insert_element)(bin_tree *bin_tree, void *data);

    /**
    * Remove element from the tree
    * @param bin_tree           pointer to the tree
    * @param data               element to remove   
    * @return                   true, if element exist in the tree
    */
    bool (*remove_element)(bin_tree *bin_tree, void *data);

    /**
    * Find element in the tree
    * @param bin_tree           pointer to the tree
    * @param data               element to remove
    * @return                   true, if element contains in the tree, else false
    */
    bool (*find_value)(bin_tree *bin_tree, void *data);

    /**
    * Create new bin_tree
    * @param compare            pointer to the compare objects function
    * @return                   pointer to the new binary tree
    */
    bin_tree *(*create_bin_tree)(int (*compare)(void *, void *));
} bin_tree_lib;

/**
* Create new bin_tree library and connect function pointers to the implementation 
* @return              pointer to the library
*/
bin_tree_lib *create_bin_tree_library();
#endif /* BINARY_TREE */