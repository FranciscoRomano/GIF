#include <math.h>
#include <memory.h>
#include "GIF89a.ImageDescriptor.h"

void FreeImageDescriptorGIF89a(ImageDescriptorGIF89a* data)
{
    FreeBlockGIF89a(&data->LocalColorTable);
};

void ReadImageDescriptorGIF89a(FILE* file, ImageDescriptorGIF89a* data)
{
    fread_s(data, 9, 9, 1, file);
    if (data->PackedFields.LocalColorTableFlag)
    {
        unsigned long SizeOfLocalColorTable = data->PackedFields.SizeOfLocalColorTable;
        unsigned long size = ((unsigned long)pow(2.0, SizeOfLocalColorTable + 1.0)) * 3;
        data->LocalColorTable.BlockSize = size;
        data->LocalColorTable.DataValues = malloc(size);
        fread_s(data->LocalColorTable.DataValues, size, size, 1, file);
    }
};