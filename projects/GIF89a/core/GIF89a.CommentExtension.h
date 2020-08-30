#ifndef GIF89a_CommentExtension_h
#define GIF89a_CommentExtension_h 1
/** Dependencies **********************************************************************************/
#include <stdio.h>
#include "GIF89a.Block.h"
/** Declarations **********************************************************************************/

// Comment Extension [Block]
typedef struct CommentExtensionGIF89a {
    BlockGIF89a CommentData;
} CommentExtensionGIF89a;

// Function - Free Comment Extension Structure
void FreeCommentExtensionGIF89a(CommentExtensionGIF89a* data);

// Function - Read Comment Extension Structure
void ReadCommentExtensionGIF89a(FILE* file, CommentExtensionGIF89a* data);

/**************************************************************************************************/
#endif//GIF89a_CommentExtension_h