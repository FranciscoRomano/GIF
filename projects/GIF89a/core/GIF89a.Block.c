#include <stdlib.h>
#include <memory.h>
#include "GIF89a.Block.h"

void FreeBlockGIF89a(BlockGIF89a* data)
{
    free(data->DataValues);
};

void ReadBlockGIF89a(FILE* file, BlockGIF89a* data)
{
    unsigned char size;
    unsigned long offset;

    memset(data, 0, sizeof(BlockGIF89a));
    fread(&size, sizeof(unsigned char), 1, file);

    while (size != 0)
    {
        offset = data->BlockSize;
        data->BlockSize += (unsigned long)size;
        data->DataValues = realloc(data->DataValues, data->BlockSize);

        for (unsigned long i = offset; i < data->BlockSize; i++)
        {
            fread_s(data->DataValues + offset, size, size, 1, file);
        }

        fread(&size, sizeof(unsigned char), 1, file);
    }
};

void* array_twin(void** dst, void* src)
{
    free(*dst);
    *dst = src;
    return *dst;
};

void* array_ldel(void* src, const size_t src_s, const size_t size, void* dst)
{
    size_t length = src_s - size;
    if (dst) memcpy(src, dst, size);
    memcpy(src, (char*)src + size, size);
    return realloc(src, length);
};

void* array_rdel(void* src, const size_t src_s, const size_t size, void* dst)
{
    size_t length = src_s - size;
    if (dst) memcpy((char*)src + length, dst, size);
    return realloc(src, length);
};

void* array_ladd(void* dst, const size_t dst_s, const void* rhs, const size_t rhs_s)
{
    return array_twin(&dst, array_join(rhs, rhs_s, dst, dst_s));
};

void* array_radd(void* dst, const size_t dst_s, const void* rhs, const size_t rhs_s)
{
    return array_twin(&dst, array_join(dst, dst_s, rhs, rhs_s));
};

void* array_join(const void* lhs, const size_t lhs_s, const void* rhs, const size_t rhs_s)
{
    char* t = malloc(lhs_s + rhs_s);
    memcpy(t + lhs_s, rhs, rhs_s);
    memcpy(t, lhs, lhs_s);
    return t;
};