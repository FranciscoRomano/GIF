#include <vector>
#include <fstream>
#include "89a/consts.h"
#include "89a/structs.h"
#include "89a/typedefs.h"

namespace fuze {
    namespace GIF89a {

        struct File
        {
            struct Image
            {
                ImageData data;
                ImageDescriptor descriptor;
                GraphicControlExtension* gce;
            };

            struct Text
            {
                PlainTextExtension extension;
                GraphicControlExtension* gce;
            };

            Header header;
            std::vector<Text> textList;
            std::vector<Image> imageList;
            LogicalScreenDescriptor logicalScreenDescriptor;
            std::vector<CommentExtension> commentExtensionList;
            std::vector<ApplicationExtension> applicationExtensionList;
            std::vector<GraphicControlExtension> graphicControlExtensionList;
        };

        void Free(File&ref);
        void Decode(std::ifstream& file, File& ref);
        void Decode(std::ifstream& file, Block& ref);
        void Decode(std::ifstream& file, Header& ref);
        void Decode(std::ifstream& file, ImageData& ref);
        void Decode(std::ifstream& file, ImageDescriptor& ref);
        void Decode(std::ifstream& file, CommentExtension& ref);
        void Decode(std::ifstream& file, PlainTextExtension& ref);
        void Decode(std::ifstream& file, ApplicationExtension& ref);
        void Decode(std::ifstream& file, LogicalScreenDescriptor& ref);
        void Decode(std::ifstream& file, GraphicControlExtension& ref);

    }; // namespace GIF89a  
}; // namespace fuze