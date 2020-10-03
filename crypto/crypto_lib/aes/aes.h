#include "header.h"


/**
 * Encrypt AES function
 * @param text  text for encryption
 * @param key   key(can be 16,24,32 bytes)
 * @return      encrypted text
*/
void encrypt(data_t* text, const data_t* key);


/**
 * Decrypt AES function
 * @param text  text for decryption
 * @param key   key(can be 16,24,32 bytes)
 * @return      decrypted text
*/
void decrypt(data_t* text, const data_t* key);