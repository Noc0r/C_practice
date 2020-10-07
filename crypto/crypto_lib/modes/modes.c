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
    ECB_encr(blocks, blocks_size, key, decrypt);
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
    data_t tmp = blocks[0];
    data_t tmp1;
    memset(tmp.data, 0, tmp.size);
    for (size_t i = 1; i < blocks_size; i++)
    {
        tmp1 = blocks[i];
        xor_modify(&blocks[i], &blocks[i - 1]);
        xor_modify(&blocks[i], &tmp);
        encrypt(&blocks[i], key);
        tmp = tmp1;
    }
}

void PCBC_decr(data_t *blocks, uint32_t blocks_size, const data_t *key, function decrypt)
{
    data_t tmp = blocks[0];
    data_t tmp1;
    memset(tmp.data, 0, tmp.size);
    for (size_t i = 1; i < blocks_size; i++)
    {
        tmp1 = blocks[i];
        decrypt(&blocks[i], key);
        xor_modify(&blocks[i], &blocks[i - 1]);
        xor_modify(&blocks[i], &tmp);
        tmp = tmp1;
    }
}

void CFB_encr(data_t *blocks, uint32_t blocks_size, const data_t *key, function encrypt)
{
    //copy IV, because loop modify it
    data_t IV = blocks[0];
    for (size_t i = 1; i < blocks_size; i++)
    {
        encrypt(&blocks[i - 1], key);
        xor_modify(&blocks[i], &blocks[i - 1]);
    }
    memcpy(&blocks[0], &IV, sizeof(data_t));
}

void CFB_decr(data_t *blocks, uint32_t blocks_size, const data_t *key, function decrypt)
{
    data_t tmp = blocks[0];
    for (size_t i = 1; i < blocks_size; i++)
    {
        decrypt(&tmp, key);
        xor_modify(&blocks[i], &tmp);
    }
}

void OFB_encr(data_t *blocks, uint32_t blocks_size, const data_t *key, function encrypt)
{
    data_t tmp = blocks[0];
    for (size_t i = 1; i < blocks_size; i++)
    {
        encrypt(&tmp, key);
        xor_modify(&blocks[i], &tmp);
    }
}

void OFB_decr(data_t *blocks, uint32_t blocks_size, const data_t *key, function decrypt)
{
    OFB_encr(blocks, blocks_size, key, decrypt);
}

void CTR_encr(data_t *blocks, uint32_t blocks_size, const data_t *key, function encrypt)
{
    data_t counter;
    counter.data = (uint8_t *)malloc(blocks[0].size);
    counter.size = blocks[0].size;
    memset(counter.data, 0, counter.size);
    uint32_t *counter_ptr = (uint32_t *)(counter.data + counter.size - sizeof(uint32_t));
    for (size_t i = 0; i < blocks_size; i++)
    {
        *counter_ptr++;
        encrypt(&counter, key);
        xor_modify(&blocks[i], &counter);
    }
    free(counter.data);
}

void CTR_decr(data_t *blocks, uint32_t blocks_size, const data_t *key, function decrypt)
{
    CTR_encr(blocks, blocks_size, key, decrypt);
}