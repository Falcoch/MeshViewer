#pragma once

#include <vector>
#include <filesystem>

#include <GL/glew.h>
#include <utils/Type.h>

namespace mv
{
    class Image
    {
        public:
            using Pixels = std::vector<Byte>;

            Image();
            Image(const Image &);
            Image(Image &&);
            Image & operator=(const Image &);
            Image & operator=(Image &&);
           ~Image() = default;

            uint32 width() const;
            uint32 height() const;
            uint32 channels() const;

            const Pixels & data() const;

            void flipVerticaly();

            void load(const Path &);
            void load(uint32, uint32, uint32, const Byte *);
            void release();

            Byte operator[](size_t) const;

        private:
            uint32 m_width;
            uint32 m_height;
            uint32 m_channels;
            Pixels m_data;
    };
}