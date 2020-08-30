#include <memory.h>
#include "GIF89a.PlainTextExtension.h"

void FreePlainTextExtensionGIF89a(PlainTextExtensionGIF89a* data)
{
    FreeBlockGIF89a(&data->PlainTextData);
};

void ReadPlainTextExtensionGIF89a(FILE* file, PlainTextExtensionGIF89a* data)
{
    fread_s(data, 13, 13, 1, file);
    ReadBlockGIF89a(file, &data->PlainTextData);
};