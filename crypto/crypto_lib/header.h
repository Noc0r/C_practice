#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#define min(X, Y) (((X) < (Y)) ? (X) : (Y))
#define max(X, Y) (((X) > (Y)) ? (X) : (Y))

typedef struct data
{
    uint8_t *data;
    uint32_t size;
} data_t;

data_t *split_data(const data_t *s_data, uint32_t block_size)
{
    uint32_t padding = (block_size - s_data->size % block_size);
    uint32_t res_size = s_data->size + padding;
    uint8_t *result = (uint8_t *)malloc(res_size * sizeof(uint8_t));
    memcpy(result, s_data->data, s_data->size);
    //need add/del padding function
    memset(result + s_data->size, 0, padding);
    uint32_t block_count = (res_size / block_size);
    data_t *blocks = (data_t *)malloc(block_count * sizeof(data));
    for (size_t i = 0; i < block_count; i++)
    {
        blocks[i].data = result + block_size * i;
        blocks[i].size = block_size;
    }
    return blocks;
}

data_t *xor_unmodify(const data_t *first, const data_t *second)
{
    uint32_t size = min(first->size, second->size);
    uint8_t *res_xor = (uint8_t *)malloc(size * sizeof(uint8_t));
    for (size_t i = 0; i < size; i++)
    {
        res_xor[i] = first->data[i] ^ second->data[i];
    }
    data_t *result = (data_t *)malloc(sizeof(data_t));
    result->data = res_xor;
    result->size = size;
    return result;
}

void xor_modify(data_t *first, const data_t *second)
{
    uint32_t size = min(first->size, second->size);
    for (size_t i = 0; i < size; i++)
    {
        first->data[i] ^= second->data[i];
    }
}