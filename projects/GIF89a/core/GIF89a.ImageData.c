#include <memory.h>
#include "GIF89a.ImageData.h"

void FreeImageDataGIF89a(ImageDataGIF89a* data)
{
    FreeBlockGIF89a(&data->ImageData);
};

void ReadImageDataGIF89a(FILE* file, ImageDataGIF89a* data)
{
    fread_s(data, 1, 1, 1, file);
    ReadBlockGIF89a(file, &data->ImageData);
};