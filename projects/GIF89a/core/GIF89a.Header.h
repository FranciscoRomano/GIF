#ifndef GIF89a_Header_h
#define GIF89a_Header_h 1
/** Dependencies **********************************************************************************/
#include <stdio.h>
/** Declarations **********************************************************************************/

// Header [6 Bytes]
typedef struct HeaderGIF89a {
    unsigned char Signature[3];
    unsigned char Version[3];
} HeaderGIF89a;

// Function - Read Header Structure
void ReadHeaderGIF89a(FILE* file, HeaderGIF89a* data);

/**************************************************************************************************/
#endif//GIF89a_Header_h