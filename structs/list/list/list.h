#ifndef LIST
#define LIST
#include <stdbool.h>

/**
 * Linear one-directional list or bi-directional(define LINKED_LIST)
 * @author Senatrev Ruslan
 * @param data          pointer to the data of element
 * @param next          pointer to next node in the list
*/

typedef struct node
{
    void *data;
    struct node *next;
#ifdef LINKED_LIST
    {
        struct node *prev;
    }
#endif
} node;

typedef struct list list;

typedef struct list_library
{
    /**
    * Get size of current list
    * @param list           pointer to the list
    * @return               amount of elements
    */
    unsigned int (*count)(list *list);

    /**
    * Get element of the array at chosen position
    * @param list           pointer to the list
    * @param index          element index in the array
    * @return               NULL, if index out of range, else pointer to the element
    */
    void *(*get_by_index)(list *list, unsigned int index);

    /**
    * Set element of the array at chosen position
    * @param list           pointer to the list
    * @param index          element index in the array
    * @return               
    */
    void (*set_by_index)(list *list, unsigned int index, void *new_data);

    /**
    * Remove last element from the list
    * @param list       pointer to the list
    * @return              
    */
    void (*pop_back)(list *list);

    /**
    * Remove first element from the list
    * @param list       pointer to the list
    * @return              
    */
    void (*pop_front)(list *list);

    /**
    * Remove all elements from the list
    * @param list       pointer to the list
    * @return              
    */
    void (*clear)(list *list);

    /**
    * Insert new element to the end of the list and make it last
    * @param list       pointer to the list
    * @param data          data of new element       
    * @return              
    */
    void (*push_back)(list *list, void *data);

    /**
    * Insert new element to the start of the list and make it first
    * @param list       pointer to the list
    * @param data          data of new element       
    * @return              
    */
    void (*push_front)(list *list, void *data);

    /**
    * Insert new element after position
    * @param list       pointer to the list
    * @param pos        position in the list
    * @param data       data of new element       
    * @return              
    */
    void (*insert_element)(list *list, unsigned int pos, void *data);

    /**
    * Remove element from the list
    * @param list          pointer to the list
    * @param data          element to remove
    * @param compare       pointer to the compare function      
    * @return              true, if element exist in the list
    */
    bool (*remove_element)(list *list, void *data, int (*compare)(void *, void *));

    /**
    * Find element in the list
    * @param list          pointer to the list
    * @param data          element to remove
    * @param compare       pointer to the compare function      
    * @return              first element in the list @param head with data @param find_value, or NULL 
    */
    node *(*find_value)(list *list, void *data, int (*compare)(void *, void *));

    /**
* Create new list, if current list is empty
* @param is_cyclic     
* @return              pointer to the first element of list
*/
    list *(*create_list)(bool is_cyclic);
} list_lib;

  /**
* Create new list library and connect function pointers to the implementation 
* @return              pointer to the library
*/
list_lib* create_list_library();
#endif /* LIST */
