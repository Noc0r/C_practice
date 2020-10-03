#include "modes.h"

void ECB_encr(data_t *blocks, uint32_t blocks_size, const data_t *key, function encrypt)
{
    for (size_t i = 0; i < blocks_size; i++)
    {
        encrypt(&blocks[i], key);
    }
}
void ECB_decr(data_t *blocks, uint32_t blocks_size, const data_t *key, function decrypt)
{
    for (size_t i = 0; i < blocks_size; i++)
    {
        decrypt(&blocks[i], key);
    }
}

void CBC_encr(data_t *blocks, uint32_t blocks_size, const data_t *key, function encrypt)
{
    for (size_t i = 1; i < blocks_size; i++)
    {
        xor_modify(&blocks[i], &blocks[i - 1]);
        encrypt(&blocks[i], key);
    }
}
void CBC_decr(data_t *blocks, uint32_t blocks_size, const data_t *key, function decrypt)
{
    for (size_t i = 1; i < blocks_size; i++)
    {
        decrypt(&blocks[i], key);
        xor_modify(&blocks[i], &blocks[i - 1]);
    }
}

void PCBC_encr(data_t *blocks, uint32_t blocks_size, const data_t *key, function encrypt)
{
}
void PCBC_decr(data_t *blocks, uint32_t blocks_size, const data_t *key, function decrypt)
{
}

void CFB_encr(data_t *blocks, uint32_t blocks_size, const data_t *key, function encrypt)
{
}
void CFB_decr(data_t *blocks, uint32_t blocks_size, const data_t *key, function decrypt)
{
}

void OFB_encr(data_t *blocks, uint32_t blocks_size, const data_t *key, function encrypt)
{
}
void OFB_decr(data_t *blocks, uint32_t blocks_size, const data_t *key, function decrypt)
{
}

void CTR_encr(data_t *blocks, uint32_t blocks_size, const data_t *key, function encrypt)
{
}
void CTR_decr(data_t *blocks, uint32_t blocks_size, const data_t *key, function decrypt)
{
}

void RD_encr(data_t *blocks, uint32_t blocks_size, const data_t *key, function encrypt)
{
}
void RD_decr(data_t *blocks, uint32_t blocks_size, const data_t *key, function decrypt)
{
}

void GCM_encr(data_t *blocks, uint32_t blocks_size, const data_t *key, function encrypt)
{
}
void GCM_decr(data_t *blocks, uint32_t blocks_size, const data_t *key, function decrypt)
{
}