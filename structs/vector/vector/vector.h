#ifndef VECTOR
#define VECTOR

#include <stdbool.h>

/**
 * Resizable dynamic array
 * @author Senatrev Ruslan
 * @param array              pointer to the data array
 * @param size               amount of elements  
*/

typedef struct vector vector;

typedef struct vector_library
{

    /**
    * Get size of current @param vect
    * @param vect           pointer to the vector
    * @return               amount of elements
    */
    unsigned int (*count)(vector *vect);

    /**
    * Get element of the array at chosen position
    * @param vect           pointer to the vector
    * @param index          element index in the array
    * @return               NULL, if index out of range, else pointer to the element
    */
    void *(*get_by_index)(vector *vect, unsigned int index);

    /**
    * Set element of the array at chosen position
    * @param vect           pointer to the vector
    * @param index          element index in the array
    * @param new_data       new data value for chosen element
    * @return               
    */
    void (*set_by_index)(vector *vect, unsigned int index, void *new_data);

    /**
    * Change maximum size of array
    * @param new_size       new max_size for array
    * @return              
    */
    void (*resize)(vector *vect, unsigned int new_size);

    /**
    * Remove last element from the vector
    * @param vect       pointer to the vector
    * @return              
    */
    void (*pop_back)(vector *vect);

    /**
    * Remove all elements from the vector
    * @param vect       pointer to the vector
    * @return              
    */
    void (*clear)(vector *vect);

    /**
    * Insert new element to the end of the vector
    * @param vect          pointer to the vector
    * @param data          data of new element       
    * @return              
    */
    void (*push_back)(vector *vect, void *data);

    /**
    * Insert new element after position
    * @param vect       pointer to the vector
    * @param pos        position in the vector
    * @param data       data of new element       
    * @return              
    */
    void (*insert_element)(vector *vect, unsigned int pos, void *data);

    /**
    * Remove element from the vector
    * @param vect          pointer to the vector
    * @param data          element to remove
    * @param compare       pointer to the compare function      
    * @return              true, if element exist in the vector
    */
    bool (*remove_element)(vector *vect, void *element, int (*compare)(void *, void *));

    /**
    * Remove element from the vector
    * @param vect          pointer to the vector
    * @param pos           position in the vector
    * @return              true, if element exist in the vector
    */
    bool (*remove_index)(vector *vect, unsigned int pos);

    /**
    * Remove element from the vector
    * @param vect          pointer to the vector
    * @param first         position of first element in the vector
    * @param second        position of second element in the vector
    * @return              true, if element exist in the vector
    */
    void (*swap)(vector *vect, unsigned int first, unsigned int second);
    /**
* Create new vector, if current vector is empty
* @param element_size   size of each element
* @param max_size       maximum size of array
* @return               pointer to the first element of vector
*/
    vector *(*create_vector)(unsigned int max_size);
} vector_lib;

vector_lib *create_vector_library();
#endif /* VECTOR */
