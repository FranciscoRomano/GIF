#include "GIF.h"
#include "GIF89a.h"

typedef unsigned long u32;

#include <Windows.h>

#include <set>
#include <queue>
#include <string>
#include <fstream>
#include <iostream>

using namespace fuze;


class GifCodeTable
{
    std::vector<std::vector<u32>> table;
public:
    GifCodeTable(GIF89a::Block& color_table)
    {
        reset(color_table);
        // u32 size = color_table.BlockSize / 3;
        // // store table indexes
        // for (u32 i = 0; i < size; i++)
        //     table.push_back(std::vector<u32>{{ i }});
        // table.push_back({}); // clear code
        // table.push_back({}); // end of information code
    }

    u32 size() { return table.size(); }

    void push(std::vector<u32>&& data) { table.push_back(data); }

    void push(const std::vector<u32>& data) { table.push_back(data); }

    void reset(const GIF89a::Block& colors)
    {
        u32 size = colors.BlockSize / 3;
        // store table indexes
        table.clear();
        for (u32 i = 0; i < size; i++)
            table.push_back(std::vector<u32>{{ i }});
        table.push_back({}); // clear code
        table.push_back({}); // end of information code
    }

    bool contains(const std::vector<u32>& data)
    {
        for (u32 i = 0; i < table.size(); i++)
            if (table[i] == data) return true;
        return false;
    }

    std::vector<u32>& operator[](const u32& i) { return table[i]; }
};

class GifCodeStream
{
    u32              bitsize;
    u32              maxsize;
    u32              minsize;
    std::queue<bool> bitstream;
public:

    GifCodeStream(const GIF89a::ImageData& image_data)
    {
        // initialize variables
        minsize = image_data.LZWMinimumCodeSize;
        bitsize = image_data.LZWMinimumCodeSize + 1;
        maxsize = 1 << image_data.LZWMinimumCodeSize;

        // split image data block values
        for (u32 i = 0; i < image_data.ImageData.BlockSize; i++)
        {
            bitstream.push(0b00000001 & image_data.ImageData.DataValues[i]);
            bitstream.push(0b00000010 & image_data.ImageData.DataValues[i]);
            bitstream.push(0b00000100 & image_data.ImageData.DataValues[i]);
            bitstream.push(0b00001000 & image_data.ImageData.DataValues[i]);
            bitstream.push(0b00010000 & image_data.ImageData.DataValues[i]);
            bitstream.push(0b00100000 & image_data.ImageData.DataValues[i]);
            bitstream.push(0b01000000 & image_data.ImageData.DataValues[i]);
            bitstream.push(0b10000000 & image_data.ImageData.DataValues[i]);
        }
    }

    u32 get()
    {
        u32 code = 0;
        for (u32 i = 0; i < bitsize; i++)
        {
            code |= (bitstream.front() ? 1 : 0) << i;
            bitstream.pop();
        }
        return code;
    }

    u32 size()
    {
        return maxsize;
    }

    void reset()
    {
        bitsize = minsize + 1;
        maxsize = 1 << bitsize;
    }
    void increment()
    {
        if (bitsize < 12) bitsize++;
        maxsize = maxsize << 1;
    }
};

class GifDecompressor
{
public:
    std::vector<u32> indexstream;

    GifDecompressor(const GIF89a::ImageData& image_data, fuze::GIF89a::Block& color_table)
    {
        // prepare code wrappers
        bool init = true;
        u32 code = 0;
        u32 prev = color_table.BlockSize / 3;
        u32 ClearCode = color_table.BlockSize / 3;
        u32 EndOfInformationCode = ClearCode + 1;
        GifCodeTable codetable{ color_table };
        GifCodeStream codestream{ image_data };
        std::vector<u32> tempstream {};

        std::cout << "  cc: " << ClearCode << std::endl;
        std::cout << "  eoic: " << EndOfInformationCode << std::endl;
        std::cout << "  codetable: " << codetable.size() << std::endl;
        std::cout << "  codestream: " << codestream.size() << std::endl;
        while (true)
        {
            // get next code
            code = codestream.get();
            // std::cout << "code: " << code << std::endl;

            // check if clear code code
            if (code == ClearCode)
            {
                prev = code;
                codetable.reset(color_table);
                codestream.reset();
                std::cout << "  clear code\n";
                // std::cout << "  codetable: " << codetable.size() << std::endl;
                // std::cout << "  codestream: " << codestream.size() << std::endl;
                continue;
            }

            // check if end of information code
            if (code == EndOfInformationCode)
            {
                std::cout << "  end of information code\n";
                break;
            }

            // check code table is big enough for code
            if (code < codetable.size())
            {
                tempstream = codetable[prev];
                for (auto i : codetable[code])
                {
                    tempstream.push_back(i);
                    if (!codetable.contains(tempstream))
                    {
                        // std::cout << "  [1] new entry " << (codetable.size() - 1) << ": [ ";
                        // for (u32 i = 0; i < tempstream.size(); i++)
                        //     std::cout << tempstream[i] << " ";
                        // std::cout << " ]" << std::endl;
                        codetable.push(tempstream);
                        break;
                    }
                }
            }
            else if (tempstream.size())
            {
                tempstream.push_back(tempstream[0]);
                codetable.push(tempstream);
                // std::cout << "  [0] new entry " << (codetable.size() - 1) << ": [ ";
                // for (u32 i = 0; i < tempstream.size(); i++)
                //     std::cout << tempstream[i];
                // std::cout << " ]" << std::endl;
            }

            // increase code size when required
            if (!(codetable.size() < codestream.size()))
            {
                codestream.increment();
            }

            prev = code;
            tempstream = codetable[code];

            // add value from code table to index stream
            for (auto i : codetable[code]) indexstream.push_back(i);
            // std::cout << "  indexstream: [ ";
            // for (u32 i = 0; i < indexstream.size(); i++)
            //     std::cout << indexstream[i];
            // std::cout << " ]" << std::endl;
            Sleep(0);

        }
        //std::cout << "-------------------------\n";
    }
};

void Decompress(fuze::GIF89a::File::Image& in_image, fuze::GIF89a::Block& in_colors, fuze::GIF::Image& out_image)
{
    // get data references
    fuze::GIF89a::ImageDescriptor& idcpt = in_image.descriptor;
    fuze::GIF89a::ImageData& idata = in_image.data;
    unsigned colors_size = in_colors.BlockSize / 3;

    // decompress image data
    GifDecompressor decompressor{ idata, in_colors };

    out_image.x = idcpt.ImageLeftPosition;
    out_image.y = idcpt.ImageTopPosition;
    out_image.width = idcpt.ImageWidth;
    out_image.height = idcpt.ImageHeight;
    
    u32 index;
    u32 count = 0;
    out_image.pixels.resize(decompressor.indexstream.size() * 3);
    for (auto i : decompressor.indexstream)
    {
        index = i * 3;
        out_image.pixels[count++] = (int)in_colors.DataValues[index];
        out_image.pixels[count++] = (int)in_colors.DataValues[index + 1];
        out_image.pixels[count++] = (int)in_colors.DataValues[index + 2];
    }
    _sleep(0);
}

void fuze::GIF::Read(const char* filename, fuze::GIF::Canvas* canvas)
{
    std::ifstream file{ filename, std::ios::binary };
    if (file.is_open())
    {
        // decode gif file
        GIF89a::File gif;
        GIF89a::Decode(file, gif);
        GIF89a::LogicalScreenDescriptor& screen = gif.logicalScreenDescriptor;

        // set gif dimensions
        canvas->width = gif.logicalScreenDescriptor.LogicalScreenWidth;
        canvas->height = gif.logicalScreenDescriptor.LogicalScreenHeight;

        // iterate through gif images
        for (size_t i = 0; i < gif.imageList.size(); i++)
        {
            // get image
            GIF89a::File::Image& image = gif.imageList[i];
            
            // get image references
            GIF89a::ImageData& imgData = image.data;
            GIF89a::ImageDescriptor& imgDescriptor = image.descriptor;
            GIF89a::ImageDescriptor::PackedField& imgFields = imgDescriptor.PackedFields;

            // get image color table
            GIF89a::Block& colortable = imgFields.LocalColorTableFlag ? imgDescriptor.LocalColorTable : screen.GlobalColorTable;

            canvas->images.push_back({});
            Decompress(image, colortable, canvas->images.back());

        }

        file.close();
    }
};