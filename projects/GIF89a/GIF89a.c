// https://www.w3.org/Graphics/GIF/spec-gif89a.txt

#include <math.h>
#include <stdlib.h>
#include <memory.h>

#include "core/GIF89a.ApplicationExtension.h"
#include "core/GIF89a.Block.h"
#include "core/GIF89a.CommentExtension.h"
#include "core/GIF89a.GraphicsControlExtension.h"
#include "core/GIF89a.Header.h"
#include "core/GIF89a.ImageData.h"
#include "core/GIF89a.ImageDescriptor.h"
#include "core/GIF89a.LogicalScreenDescriptor.h"
#include "core/GIF89a.PlainTextExtension.h"
#include "core/GIF89a.Token.h"

#include "GIF89a.h"


unsigned char GetByte(FILE* file)
{
    static unsigned char value;
    fread(&value, sizeof(unsigned char), 1, file);
    return value;
};

void DecodeGIF89a(BlockGIF89a block, ImageDataGIF89a image, unsigned char* pixels)
{
    const ResetCodeTable = block.BlockSize;
    const EndOfStream = block.BlockSize + 1;

    
};

void OpenImageGIF89a(const char* path, ImageGIF89a* image)
{
    // defaults
    FILE* file;
    fopen_s(&file, path, "rb");
    GraphicControlExtensionGIF89a graphicControlExtension;
    memset(&graphicControlExtension, 0, sizeof(GraphicControlExtensionGIF89a));
    
    // read header
    HeaderGIF89a header;
    ReadHeaderGIF89a(file, &header);

    // read logical screen descriptor
    LogicalScreenDescriptorGIF89a logicalScreenDescriptor;
    ReadLogicalScreenDescriptorGIF89a(file, &logicalScreenDescriptor);
    memset(&image, 0, sizeof(ImageGIF89a));
    image->width = logicalScreenDescriptor.LogicalScreenWidth;
    image->height = logicalScreenDescriptor.LogicalScreenHeight;

    while(1) switch (GetByte(file))
    {
        case TokenImageDescriptorGIF89a:
            // read image descriptor
            ImageDescriptorGIF89a imageDescriptor;
            ReadImageDescriptorGIF89a(file, &imageDescriptor);
            // read image data
            ImageDataGIF89a imageData;
            ReadImageDataGIF89a(file, &imageData);
            // prepare frame
            realloc(image->frames, sizeof(FrameGIF89a) * (image->length + 1));
            image->frames[image->length].top = imageDescriptor.ImageTopPosition;
            image->frames[image->length].left = imageDescriptor.ImageLeftPosition;
            image->frames[image->length].width = imageDescriptor.ImageWidth;
            image->frames[image->length].height = imageDescriptor.ImageHeight;
            image->frames[image->length].length = imageDescriptor.ImageWidth * imageDescriptor.ImageHeight;
            image->frames[image->length].pixels = malloc(image->frames[image->length].length * 4);
            image->frames[image->length].seconds = ((float)graphicControlExtension.DelayTime) / 100.0f;
            if (imageDescriptor.PackedFields.LocalColorTableFlag)
            {
                DecodeGIF89a(imageDescriptor.LocalColorTable, imageData, image->frames[image->length++].pixels);
            }
            else
            {
                DecodeGIF89a(logicalScreenDescriptor.GlobalColorTable, imageData, image->frames[image->length++].pixels);
            }
            break;
        case TokenCommentExtensionGIF89a:
            // read comment extension
            CommentExtensionGIF89a comment_extension;
            ReadCommentExtensionGIF89a(file, &comment_extension);
            break;
        case TokenPlainTextExtensionGIF89a:
            // read plain text extension
            PlainTextExtensionGIF89a plain_text_extension;
            ReadPlainTextExtensionGIF89a(file, &plain_text_extension);
            break;
        case TokenApplicationExtensionGIF89a:
            // read application extension
            ApplicationExtensionGIF89a application_extension;
            ReadApplicationExtensionGIF89a(file, &application_extension);
            break;
        case TokenGraphicControlExtensionGIF89a:
            // read graphic control extension
            ReadGraphicControlExtensionGIF89a(file, &graphicControlExtension);
            break;
        default:
            return;
    }
};