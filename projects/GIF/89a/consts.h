#pragma once

#include "typedefs.h"

namespace fuze {
    namespace GIF89a {

        const Byte ApplicationExtensionLabel = 0xFF;
        const Byte BlockTerminator = 0x00;
        const Byte CommentExtensionLabel = 0xFE;
        const Byte ExtensionLabel = 0x21;
        const Byte GraphicControlExtensionLabel = 0xF9;
        const Byte ImageDescriptorLabel = 0x2C;
        const Byte PlainTextExtensionLabel = 0x01;
        const Byte Trailer = 0x3B;

    }; // namespace GIF89a
}; // namespace fuze