#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/image/stb_image.h>

#include <iostream>

namespace mv
{
    Image::Image()
    : m_width(0), m_height(0), m_channels(3) {}

    Image::Image(const Image & src)
    : m_width(src.m_width), m_height(src.m_height), m_channels(src.m_channels), m_data(src.m_data) {}

    Image::Image(Image && src)
    : m_width(src.m_width), m_height(src.m_height), m_channels(src.m_channels), m_data(std::move(src.m_data)) {}

    Image & Image::operator=(const Image & src) 
    {
        m_width    = src.m_width;
        m_height   = src.m_height;
        m_channels = src.m_channels;
        m_data     = src.m_data;
        return *this;
    }

    Image & Image::operator=(Image && src) 
    {
        m_width    = src.m_width;
        m_height   = src.m_height;
        m_channels = src.m_channels;
        m_data     = std::move(src.m_data);
        return *this;
    }

    uint32 Image::width() const 
    {
        return m_width;
    }

    uint32 Image::height() const
    {
        return m_height;
    }

    uint32 Image::channels() const
    {
        return m_channels;
    }

    const Image::Pixels & Image::data() const
    {
        return m_data;
    }

    void Image::flipVerticaly() 
    {
        stbi__vertical_flip(m_data.data(), m_width, m_height, m_channels);
    }  

    void Image::load(const Path & path) 
    {
        if(std::filesystem::is_directory(path) || !std::filesystem::exists(path)) 
            throw std::runtime_error("Cannot load file : \"" + path.string() + "\"");

        int32 width = 0, height = 0, nrChannels = 0;
        Byte * data = stbi_load(path.string().c_str(), &width, &height, &nrChannels, 0);

        if(data == NULL) 
            throw std::runtime_error("File \"" + path.string() + "\" is NULL!");

        load(width, height, nrChannels, data);
        stbi_image_free(data);
    }

    void Image::load(uint32 w, uint32 h, uint32 c, const Byte * data)
    {
        m_width = w;
        m_height = h;
        m_channels = c;
        m_data = std::vector<Byte>(data, data + (w * h * c));
    }

    void Image::release() 
    {
        m_width    = 0;
        m_height   = 0;
        m_channels = 3;
        m_data.clear();
    }

    Byte Image::operator[](size_t index) const
    {
        return m_data[index];
    }
}