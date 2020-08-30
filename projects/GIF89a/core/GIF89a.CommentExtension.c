#include <memory.h>
#include "GIF89a.CommentExtension.h"

void FreeCommentExtensionGIF89a(CommentExtensionGIF89a* data)
{
    FreeBlockGIF89a(&data->CommentData);
};

void ReadCommentExtensionGIF89a(FILE* file, CommentExtensionGIF89a* data)
{
    ReadBlockGIF89a(file, &data->CommentData);
};