#ifndef GIF89a_ImageData_h
#define GIF89a_ImageData_h 1
/** Dependencies **********************************************************************************/
#include <stdio.h>
#include "GIF89a.Block.h"
/** Declarations **********************************************************************************/

// Image Data [1 Byte + Block]
typedef struct ImageDataGIF89a {
    unsigned char LZWMinimumCodeSize;
    BlockGIF89a ImageData;
} ImageDataGIF89a;

// Function - Free Image Data Structure
void FreeImageDataGIF89a(ImageDataGIF89a* data);

// Function - Read Image Data Structure
void ReadImageDataGIF89a(FILE* file, ImageDataGIF89a* data);

/**************************************************************************************************/
#endif//GIF89a_ImageData_h