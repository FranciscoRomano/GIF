#ifndef GIF89a_ImageDescriptor_h
#define GIF89a_ImageDescriptor_h 1
/** Dependencies **********************************************************************************/
#include <stdio.h>
#include "GIF89a.Block.h"
/** Declarations **********************************************************************************/

// Image Descriptor [9 Bytes + Block]
typedef struct ImageDescriptorGIF89a {
    unsigned short ImageLeftPosition;
    unsigned short ImageTopPosition;
    unsigned short ImageWidth;
    unsigned short ImageHeight;
    struct {
        unsigned char SizeOfLocalColorTable : 3;
        unsigned char Reserved : 2;
        unsigned char SortFlag : 1;
        unsigned char InterlaceFlag : 1;
        unsigned char LocalColorTableFlag : 1;
    } PackedFields;
    BlockGIF89a LocalColorTable;
} ImageDescriptorGIF89a;

// Function - Free Image Descriptor Structure
void FreeImageDescriptorGIF89a(ImageDescriptorGIF89a* data);

// Function - Read Image Descriptor Structure
void ReadImageDescriptorGIF89a(FILE* file, ImageDescriptorGIF89a* data);

/**************************************************************************************************/
#endif//GIF89a_ImageDescriptor_h