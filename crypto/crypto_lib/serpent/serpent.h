#include "header.h"


/**
 * Encrypt Serpent function
 * @param text  text for encryption
 * @param key   key(can be 16,24,32 bytes)
 * @return      encrypted text
*/
void serpent_encrypt(data_t* text, const data_t* key);


/**
 * Decrypt Serpent function
 * @param text  text for decryption
 * @param key   key(can be 16,24,32 bytes)
 * @return      decrypted text
*/
void serpent_decrypt(data_t* text, const data_t* key);