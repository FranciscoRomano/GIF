#ifndef GIF89a_LogicalScreenDescriptor_h
#define GIF89a_LogicalScreenDescriptor_h 1
/** Dependencies **********************************************************************************/
#include <stdio.h>
#include "GIF89a.Block.h"
/** Declarations **********************************************************************************/

// Logical Screen Descriptor [7 Bytes + Block]
typedef struct LogicalScreenDescriptorGIF89a {
    unsigned short LogicalScreenWidth;
    unsigned short LogicalScreenHeight;
    struct {
        unsigned char SizeOfGlobalColorTable : 3;
        unsigned char SortFlag : 1;
        unsigned char ColorResolution : 3;
        unsigned char GlobalColorTableFlag : 1;
    } PackedFields;
    unsigned char BackgroundColorIndex;
    unsigned char PixelAspectRatio;
    BlockGIF89a GlobalColorTable;
} LogicalScreenDescriptorGIF89a;

// Function - Free Logical Screen Descriptor Structure
void FreeLogicalScreenDescriptorGIF89a(LogicalScreenDescriptorGIF89a* data);

// Function - Read Logical Screen Descriptor Structure
void ReadLogicalScreenDescriptorGIF89a(FILE* file, LogicalScreenDescriptorGIF89a* data);

/**************************************************************************************************/
#endif//GIF89a_LogicalScreenDescriptor_h