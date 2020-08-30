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

    memset(data, NULL, sizeof(BlockGIF89a));
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