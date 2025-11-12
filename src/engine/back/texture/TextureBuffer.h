#pragma once

#include <vector>
#include <filesystem>

#include <GL/glew.h>
#include <utils/Type.h>

namespace mv::engine 
{
    class TextureBuffer
    {
        public:
            using Pixels = std::vector<GLubyte>;

            TextureBuffer();
            TextureBuffer(const TextureBuffer &);
            TextureBuffer(TextureBuffer &&);
            TextureBuffer & operator=(const TextureBuffer &);
            TextureBuffer & operator=(TextureBuffer &&);
           ~TextureBuffer() = default;

            uint32 width() const;
            uint32 height() const;
            GLenum format() const;

            const Pixels & data() const;

            void flipVerticaly();

            void load(const Path &);
            void load(const GLubyte *, size_t);
            void release();

            GLubyte operator[](size_t) const;

        protected:
            static GLenum ChannelToFormat(GLuint);
            static GLuint FormatToChannel(GLenum); 

        private:
            uint32 m_width;
            uint32 m_height;
            GLenum m_format;
            Pixels m_data;
    };
}