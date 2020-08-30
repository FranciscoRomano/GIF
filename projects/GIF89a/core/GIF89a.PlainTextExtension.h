#ifndef GIF89a_PlainTextExtension_h
#define GIF89a_PlainTextExtension_h 1
/** Dependencies **********************************************************************************/
#include <stdio.h>
#include "GIF89a.Block.h"
/** Declarations **********************************************************************************/

// Plain Text Extension [13 Bytes + Block]
typedef struct PlainTextExtensionGIF89a {
    unsigned char BlockSize;
    unsigned short TextGridLeftPosition;
    unsigned short TextGridRightPosition;
    unsigned short TextGridWidth;
    unsigned short TextGridHeight;
    unsigned char CharacterCellWidth;
    unsigned char CharacterCellHeight;
    unsigned char TextForegroundColorIndex;
    unsigned char TextBackgroundColorIndex;
    BlockGIF89a PlainTextData;
} PlainTextExtensionGIF89a;

// Function - Free Plain Text Extension Structure
void FreePlainTextExtensionGIF89a(PlainTextExtensionGIF89a* data);

// Function - Read Plain Text Extension Structure
void ReadPlainTextExtensionGIF89a(FILE* file, PlainTextExtensionGIF89a* data);

/**************************************************************************************************/
#endif//GIF89a_PlainTextExtension_h