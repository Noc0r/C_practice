#ifndef LIST
#define LIST
#include <stdbool.h>

/**
 * Linear one-directional list
 * @author Senatrev Ruslan
 * @param data          pointer to the data of element
 * @param next          pointer to next node in the list
*/
typedef struct list
{
    void *data;
    struct list *next;

    /**
    * Insert new element after position
    * @param position      position in the list
    * @param data          data of new element       
    * @return              
    */
    void (*insert_element)(struct list *position, void *element);

    /**
    * Remove element from the list
    * @param head          first element of list
    * @param element       element to remove      
    * @return              pointer to the new list
    */
    struct list *(*remove_element)(struct list *head, void *element, int (*compare)(void *, void *));

    /**
    * Find element in the list
    * @param head          first element of list
    * @param find_data     required data
    * @return              first element in the list @param head with data @param find_value, or NULL 
    */
    struct list *(*find_value)(struct list *head, void *find_data, int (*compare)(void *, void *));

} list;

/**
* Create new list
* @param data          pointer to the data
* @return              pointer to the first element of list
*/
list *create_list(void *data);
#endif /* LIST */