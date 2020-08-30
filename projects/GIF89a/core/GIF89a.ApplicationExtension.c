#include <memory.h>
#include "GIF89a.ApplicationExtension.h"

void FreeApplicationExtensionGIF89a(ApplicationExtensionGIF89a* data)
{
    FreeBlockGIF89a(&data->ApplicationData);
};

void ReadApplicationExtensionGIF89a(FILE* file, ApplicationExtensionGIF89a* data)
{
    fread_s(data, 12, 12, 1, file);
    ReadBlockGIF89a(file, &data->ApplicationData);
};