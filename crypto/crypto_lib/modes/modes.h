#include "../header.h"

typedef void (*function)(data_t *, const data_t *);

/**
 * 1	Electronic Codebook (ECB)
 * 2	Cipher Block Chaining (CBC)
 * 3	Propagating Cipher Block Chaining (РСВС)
 * 4	Cipher Feedback (CFB)
 * 5	Output Feedback (OFB)
 * 6	Counter mode (CTR)
 * 7	Random Delta (RD)
 * 8	Galois/Counter Mode (GCM) и AEAD
 * The first block is IV, if it needed
 * @param blocks        input text divided to blocks_size equal parts
 * @param blocks_size   size of single block
 * @param function      encrypt/decrypt function for modify blocks
 * @return 
*/

void ECB_encr(data_t* blocks, uint32_t blocks_size, const data_t * key, function encrypt);
void ECB_decr(data_t* blocks, uint32_t blocks_size, const data_t * key, function decrypt);

void CBC_encr(data_t* blocks, uint32_t blocks_size, const data_t * key, function encrypt);
void CBC_decr(data_t* blocks, uint32_t blocks_size, const data_t * key, function decrypt);

void PCBC_encr(data_t* blocks, uint32_t blocks_size, const data_t * key, function encrypt);
void PCBC_decr(data_t* blocks, uint32_t blocks_size, const data_t * key, function decrypt);

void CFB_encr(data_t* blocks, uint32_t blocks_size, const data_t * key, function encrypt);
void CFB_decr(data_t* blocks, uint32_t blocks_size, const data_t * key, function decrypt);

void OFB_encr(data_t* blocks, uint32_t blocks_size, const data_t * key, function encrypt);
void OFB_decr(data_t* blocks, uint32_t blocks_size, const data_t * key, function decrypt);

void CTR_encr(data_t* blocks, uint32_t blocks_size, const data_t * key, function encrypt);
void CTR_decr(data_t* blocks, uint32_t blocks_size, const data_t * key, function decrypt);