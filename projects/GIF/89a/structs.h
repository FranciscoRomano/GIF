#pragma once

#include "typedefs.h"

namespace fuze {
    namespace GIF89a {

        // Block [?]
        struct Block {
            Unsigned32 BlockSize;
            Byte*      DataValues;
        };

        // Header [6 Bytes]
        struct Header {
            Byte Signature[3];
            Byte Version[3];
        };

        // LogicalScreenDescriptor [7 Bytes]
        struct LogicalScreenDescriptor {
            Unsigned LogicalScreenWidth;
            Unsigned LogicalScreenHeight;
            struct PackedField {
                Byte SizeOfGlobalColorTable : 3;
                Byte SortFlag : 1;
                Byte ColorResolution : 3;
                Byte GlobalColorTableFlag : 1;
            } PackedFields;
            Byte BackgroundColorIndex;
            Byte PixelAspectRatio;
            Block GlobalColorTable;
        };

        // ImageDescriptor [9 Bytes]
        struct ImageDescriptor {
            Unsigned ImageLeftPosition;
            Unsigned ImageTopPosition;
            Unsigned ImageWidth;
            Unsigned ImageHeight;
            struct PackedField {
                Byte SizeOfLocalColorTable : 3;
                Byte Reserved : 2;
                Byte SortFlag : 1;
                Byte InterlaceFlag : 1;
                Byte LocalColorTableFlag : 1;
            } PackedFields;
            Block LocalColorTable;
        };

        // ImageData [?]
        struct ImageData {
            Byte LZWMinimumCodeSize;
            Block ImageData;
        };

        // GraphicControlExtension [5 Bytes]
        struct GraphicControlExtension {
            Byte BlockSize;
            struct PackedField {
                Byte TransparentColorFlag : 1;
                Byte UserInputFlag : 1;
                Byte DisposalMethod : 3;
                Byte Reserved : 3;
            } PackedFields;
            Unsigned DelayTime;
            Byte TransparentColorIndex;
        };

        // CommentExtension [?]
        struct CommentExtension {
            Block CommentData;
        };
        
        // PlainTextExtension [13 Bytes]
        struct PlainTextExtension {
            Byte BlockSize;
            Unsigned TextGridLeftPosition;
            Unsigned TextGridRightPosition;
            Unsigned TextGridWidth;
            Unsigned TextGridHeight;
            Byte CharacterCellWidth;
            Byte CharacterCellHeight;
            Byte TextForegroundColorIndex;
            Byte TextBackgroundColorIndex;
            Block PlainTextData;
        };

        // ApplicationExtension [12 Bytes]
        struct ApplicationExtension {
            Byte BlockSize;
            Byte ApplicationIdentifier[8];
            Byte ApplicationAuthenticationCode[3];
            Block ApplicationData;
        };

    }; // namespace GIF89a
}; // namespace fuze