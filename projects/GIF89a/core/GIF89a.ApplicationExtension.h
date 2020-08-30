#ifndef GIF89a_ApplicationExtension_h
#define GIF89a_ApplicationExtension_h 1
/** Dependencies **********************************************************************************/
#include <stdio.h>
#include "GIF89a.Block.h"
/** Declarations **********************************************************************************/

// Application Extension [12 Bytes + Block]
typedef struct ApplicationExtensionGIF89a {
    unsigned char BlockSize;
    unsigned char ApplicationIdentifier[8];
    unsigned char ApplicationAuthenticationCode[3];
    BlockGIF89a ApplicationData;
} ApplicationExtensionGIF89a;

// Function - Free Application Extension Structure
void FreeApplicationExtensionGIF89a(ApplicationExtensionGIF89a* data);

// Function - Read Application Extension Structure
void ReadApplicationExtensionGIF89a(FILE* file, ApplicationExtensionGIF89a* data);

/**************************************************************************************************/
#endif//GIF89a_ApplicationExtension_h