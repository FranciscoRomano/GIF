#ifndef GIF89a_Token_h
#define GIF89a_Token_h 1
/** Dependencies **********************************************************************************/

// Enum - Tokens [4+ Bytes]
enum TokenGIF89a {
    // Token - Trailer
    TokenTrailerGIF89a = 0x3B,
    // Token - Extension
    TokenExtensionGIF89a = 0x21,
    // Token - Block Terminator
    TokenBlockTerminatorGIF89a = 0x00,
    // Token - Image Descriptor
    TokenImageDescriptorGIF89a = 0x2C,
    // Token - Comment Extension
    TokenCommentExtensionGIF89a = 0xFE,
    // Token - Plain Text Extension
    TokenPlainTextExtensionGIF89a = 0x01,
    // Token - Application Extension
    TokenApplicationExtensionGIF89a = 0xFF,
    // Token - Graphic Control Extension
    TokenGraphicControlExtensionGIF89a = 0xF9,
};

/** Declarations **********************************************************************************/
/**************************************************************************************************/
#endif//GIF89a_Token_h