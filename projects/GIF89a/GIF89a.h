#ifndef GIF89a_h
#define GIF89a_h 1
/** Dependencies **********************************************************************************/
/** Declarations **********************************************************************************/

typedef struct FrameGIF89a {
    float seconds;
    unsigned short top;
    unsigned short left;
    unsigned short width;
    unsigned short height;
    unsigned short length;
    unsigned char* pixels;
} FrameGIF89a;

typedef struct ImageGIF89a {
    FrameGIF89a* frames;
    unsigned short width;
    unsigned short height;
    unsigned short length;
} ImageGIF89a;

void OpenImageGIF89a(const char* path, ImageGIF89a* image);

/**************************************************************************************************/
#endif//GIF89a_h