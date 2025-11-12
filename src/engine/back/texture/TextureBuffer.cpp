#include "TextureBuffer.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/image/stb_image.h>

#include <iostream>

namespace mv::engine 
{
    TextureBuffer::TextureBuffer()
    : m_width(0), m_height(0), m_format(GL_RGB) {}

    TextureBuffer::TextureBuffer(const TextureBuffer & src)
    : m_width(src.m_width), m_height(src.m_height), m_format(src.m_format), m_data(src.m_data) {}

    TextureBuffer::TextureBuffer(TextureBuffer && src)
    : m_width(src.m_width), m_height(src.m_height), m_format(src.m_format), m_data(std::move(src.m_data)) {}

    TextureBuffer & TextureBuffer::operator=(const TextureBuffer & src) 
    {
        m_width  = src.m_width;
        m_height = src.m_height;
        m_format = src.m_format;
        m_data   = src.m_data;
        return *this;
    }

    TextureBuffer & TextureBuffer::operator=(TextureBuffer && src) 
    {
        m_width  = src.m_width;
        m_height = src.m_height;
        m_format = src.m_format;
        m_data   = std::move(src.m_data);
        return *this;
    }

    uint32 TextureBuffer::width() const 
    {
        return m_width;
    }

    uint32 TextureBuffer::height() const
    {
        return m_height;
    }

    GLenum TextureBuffer::format() const
    {
        return m_format;
    }

    const TextureBuffer::Pixels & TextureBuffer::data() const
    {
        return m_data;
    }

    void TextureBuffer::flipVerticaly() 
    {
        stbi__vertical_flip(m_data.data(), m_width, m_height, TextureBuffer::FormatToChannel(m_format));
    }  

    void TextureBuffer::load(const Path & path) 
    {
        if(std::filesystem::is_directory(path) || !std::filesystem::exists(path)) 
            throw std::runtime_error("Cannot load file : \"" + path.string() + "\"");

        int32 width = 0, height = 0, nrChannels = 0;
        GLubyte * data = stbi_load(path.string().c_str(), &width, &height, &nrChannels, 0);

        if(data == NULL) 
            throw std::runtime_error("File is NULL : \"" + path.string() + "\"");

        m_width  = width;
        m_height = height;
        m_format = TextureBuffer::ChannelToFormat(nrChannels);

        load(data, width * height * nrChannels);

        stbi_image_free(data);
    }

    void TextureBuffer::load(const GLubyte * data, size_t size)
    {
        m_data = std::vector<GLubyte>(data, data + size);
    }

    void TextureBuffer::release() 
    {
        m_width  = 0;
        m_height = 0;
        m_format = GL_RGB;
        m_data.clear();
    }

    GLenum TextureBuffer::ChannelToFormat(GLuint count) 
    {
        switch (count)
        {
            case 3:
                return GL_RGB;
        
            case 4:
                return GL_RGBA;
        }

        throw std::runtime_error("Unsupported channels count");
    }

    GLuint TextureBuffer::FormatToChannel(GLenum format)
    {
        switch (format)
        {
            case GL_RGB:
                return 3;
        
            case GL_RGBA:
                return 4;
        }

        throw std::runtime_error("Unsupported GLenum color format");
    }

    GLubyte TextureBuffer::operator[](size_t index) const
    {
        return m_data[index];
    }
}