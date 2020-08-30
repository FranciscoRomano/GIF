#ifndef GIF89a_GraphicsControlExtension_h
#define GIF89a_GraphicsControlExtension_h 1
/** Dependencies **********************************************************************************/
#include <stdio.h>
/** Declarations **********************************************************************************/

// Graphic Control Extension [5 Bytes]
typedef struct GraphicControlExtensionGIF89a {
    unsigned char BlockSize;
    struct {
        unsigned char TransparentColorFlag : 1;
        unsigned char UserInputFlag : 1;
        unsigned char DisposalMethod : 3;
        unsigned char Reserved : 3;
    } PackedFields;
    unsigned short DelayTime;
    unsigned char TransparentColorIndex;
} GraphicControlExtensionGIF89a;

// Function - Read Graphic Control Extension Structure
void ReadGraphicControlExtensionGIF89a(FILE* file, GraphicControlExtensionGIF89a* data);

/**************************************************************************************************/
#endif//GIF89a_GraphicsControlExtension_h