#include <memory.h>
#include "GIF89a.Header.h"

void ReadHeaderGIF89a(FILE* file, HeaderGIF89a* data)
{
    fread_s(data, 6, 6, 1, file);
};