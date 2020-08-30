#pragma once

#include <vector>

namespace fuze {
    namespace GIF {

        struct Image
        {
            unsigned short x;
            unsigned short y;
            unsigned short width;
            unsigned short height;
            std::vector<unsigned char> pixels;
        };

        struct Canvas
        {
            unsigned short width;
            unsigned short height;
            std::vector<Image> images;
        };

        void Read(const char* filename, Canvas* canvas);
        
    }; // namespace GIF
}; // namespace fuze