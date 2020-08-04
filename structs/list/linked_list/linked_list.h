#ifndef LINKED_LIST
#define LINKED_LIST
#include <stdbool.h>

/**
 * Linear bi-directional list
 * @author Senatrev Ruslan
 * @param data          pointer to the data of element
 * @param next          pointer to next node in the linked_list
 * @param prev          pointer to previous node in the linked_list
*/
typedef struct linked_list
{
    void *data;
    struct linked_list *next;
    struct linked_list *prev;

    /**
    * Insert new element after position
    * @param position      position in the linked_list
    * @param data          data of new element       
    * @return              
    */
    void (*insert_element)(struct linked_list *position, void *element);

    /**
    * Remove element from the linked_list
    * @param head          first element of linked_list
    * @param element       element to remove      
    * @return              true, if element in the linked_list
    */
    struct linked_list *(*remove_element)(struct linked_list *head, void *element, int (*compare)(void *, void *));

    /**
    * Find element in the linked_list
    * @param head          first element of linked_list
    * @param find_data     required data
    * @return              first element in the linked_list @param head with data @param find_value, or NULL 
    */
    struct linked_list *(*find_value)(struct linked_list *head, void *find_data, int (*compare)(void *, void *));
} linked_list;

/**
* Create new linked_list
* @param data          pointer to the data
* @return              pointer to the first element of linked_list
*/
linked_list *create_linked_list(void *data);

#endif /* LINKED_LIST */