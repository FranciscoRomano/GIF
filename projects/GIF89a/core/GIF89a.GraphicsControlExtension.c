#include <memory.h>
#include "GIF89a.GraphicsControlExtension.h"

void ReadGraphicControlExtensionGIF89a(FILE* file, GraphicControlExtensionGIF89a* data)
{
    fread_s(data, 5, 5, 1, file);
};