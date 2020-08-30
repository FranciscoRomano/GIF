#ifndef GIF89a_Block_h
#define GIF89a_Block_h 1
/** Dependencies **********************************************************************************/
#include <stdio.h>
/** Declarations **********************************************************************************/

// Block [4+ Bytes]
typedef struct BlockGIF89a {
    unsigned long BlockSize;
    unsigned char* DataValues;
} BlockGIF89a;

// Function - Free Block Structure
void FreeBlockGIF89a(BlockGIF89a* data);

// Function - Read Block Structure
void ReadBlockGIF89a(FILE* file, BlockGIF89a* data);

/**************************************************************************************************/
#endif//GIF89a_Block_h