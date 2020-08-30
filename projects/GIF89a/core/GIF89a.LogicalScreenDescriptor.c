#include <math.h>
#include <memory.h>
#include "GIF89a.LogicalScreenDescriptor.h"

void FreeLogicalScreenDescriptorGIF89a(LogicalScreenDescriptorGIF89a* data)
{
    FreeBlockGIF89a(&data->GlobalColorTable);
};

void ReadLogicalScreenDescriptorGIF89a(FILE* file, LogicalScreenDescriptorGIF89a* data)
{
    fread_s(data, 7, 7, 1, file);
    if (data->PackedFields.GlobalColorTableFlag)
    {
        unsigned long SizeOfGlobalColorTable = data->PackedFields.SizeOfGlobalColorTable;
        unsigned long size = ((unsigned long)pow(2.0, SizeOfGlobalColorTable + 1.0)) * 3;
        data->GlobalColorTable.BlockSize = size;
        data->GlobalColorTable.DataValues = malloc(size);
        fread_s(data->GlobalColorTable.DataValues, size, size, 1, file);
    }
};
