#include <vector>
#include <iostream>
#include "GIF89a.h"

void fuze::GIF89a::Decode(std::ifstream& file, fuze::GIF89a::File& ref)
{
    unsigned char label = 0;                   
    GraphicControlExtension* current_gce = nullptr;

    // decode file head
    Decode(file, ref.header);
    Decode(file, ref.logicalScreenDescriptor);

    // decode file body
    while(file.get((char&)label)) switch(label)
    {
        case Trailer:
            return;
        case ImageDescriptorLabel:
            ref.imageList.push_back({});
            ref.imageList.back().gce = current_gce;
            Decode(file, ref.imageList.back().descriptor);
            Decode(file, ref.imageList.back().data);
            current_gce = nullptr;
            break;
        case CommentExtensionLabel:
            ref.commentExtensionList.push_back({});
            Decode(file, ref.commentExtensionList.back());
            break;
        case PlainTextExtensionLabel:
            ref.textList.push_back({});
            ref.textList.back().gce = current_gce;
            Decode(file, ref.textList.back().extension);
            current_gce = nullptr;
            break;
        case ApplicationExtensionLabel:
            ref.applicationExtensionList.push_back({});
            Decode(file, ref.applicationExtensionList.back());
            break;
        case GraphicControlExtensionLabel:
            ref.graphicControlExtensionList.push_back({});
            Decode(file, ref.graphicControlExtensionList.back());
            current_gce = &ref.graphicControlExtensionList.back();
            break;
    }
};

void fuze::GIF89a::Decode(std::ifstream& file, fuze::GIF89a::Block& ref)
{
    size_t offset;
    unsigned char label;
    std::vector<Byte> buffer;

    while (file.get((char&)label)) switch (label)
    {
        case BlockTerminator:
            ref.BlockSize = (Unsigned)buffer.size();
            ref.DataValues = new Byte[buffer.size()];
            std::copy(buffer.begin(), buffer.end(), ref.DataValues);
            return;
        default:
            offset = buffer.size();
            ref.BlockSize += label;
            buffer.resize(buffer.size() + label);
            file.read((char*)&buffer[offset], label);
            break;
    }
};

void fuze::GIF89a::Decode(std::ifstream& file, fuze::GIF89a::Header& ref)
{
    file.read((char*)&ref, 6);
};

void fuze::GIF89a::Decode(std::ifstream& file, fuze::GIF89a::ImageData& ref)
{
    file.get((char&)ref.LZWMinimumCodeSize);
    return Decode(file, ref.ImageData);
};

void fuze::GIF89a::Decode(std::ifstream& file, fuze::GIF89a::ImageDescriptor& ref)
{
    file.read((char*)&ref, 9);
    if (ref.PackedFields.LocalColorTableFlag)
    {
        ref.LocalColorTable.BlockSize = (int)pow(2.0f, ref.PackedFields.SizeOfLocalColorTable + 1.0f) * 3;
        ref.LocalColorTable.DataValues = new Byte[ref.LocalColorTable.BlockSize];
        file.read((char*)ref.LocalColorTable.DataValues, ref.LocalColorTable.BlockSize);
    }
};

void fuze::GIF89a::Decode(std::ifstream& file, fuze::GIF89a::CommentExtension& ref)
{
    return Decode(file, ref.CommentData);
};

void fuze::GIF89a::Decode(std::ifstream& file, fuze::GIF89a::PlainTextExtension& ref)
{
    file.read((char*)&ref, 13);
    return Decode(file, ref.PlainTextData);
};

void fuze::GIF89a::Decode(std::ifstream& file, fuze::GIF89a::ApplicationExtension& ref)
{
    file.read((char*)&ref, 12);
    return Decode(file, ref.ApplicationData);
};

void fuze::GIF89a::Decode(std::ifstream& file, fuze::GIF89a::LogicalScreenDescriptor& ref)
{
    file.read((char*)&ref, 7);
    if (ref.PackedFields.GlobalColorTableFlag)
    {
        ref.GlobalColorTable.BlockSize = (int)pow(2.0f, ref.PackedFields.SizeOfGlobalColorTable + 1.0f) * 3;
        ref.GlobalColorTable.DataValues = new Byte[ref.GlobalColorTable.BlockSize];
        file.read((char*)ref.GlobalColorTable.DataValues, ref.GlobalColorTable.BlockSize);
    }
};

void fuze::GIF89a::Decode(std::ifstream& file, fuze::GIF89a::GraphicControlExtension& ref)
{
    file.read((char*)&ref, 5);
    file.ignore();
};