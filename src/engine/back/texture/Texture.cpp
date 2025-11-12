#include "Texture.h"

#include <exception>
#include <iostream>

namespace mv::engine 
{
    Texture::Texture() 
    : m_id(MV_TEXTURE_DEFAULT_ID), m_slot(MV_TEXTURE_DEFAULT_SLOT) 
    {
        glGenTextures(1, &m_id);
    }

    Texture::Texture(const TextureBuffer & buffer, GLuint type)
    : Texture() 
    {
        load(buffer, type);
    }

    Texture::Texture(TextureBuffer && buffer, GLuint type) 
    : Texture() 
    {
        load(buffer, type);
    }

    Texture::Texture(const Texture & texture)
    : m_id(texture.m_id), m_slot(texture.m_slot)
    {}

    Texture::Texture(Texture && texture)
    : m_id(std::move(texture.m_id)), m_slot(std::move(texture.m_slot))
    {
        texture.m_id   = MV_TEXTURE_DEFAULT_ID;
        texture.m_slot = MV_TEXTURE_DEFAULT_SLOT;
    }

    Texture & Texture::operator=(const Texture & texture)
    {
        m_id   = texture.m_id;
        m_slot = texture.m_slot;
        return *this;
    }

    Texture & Texture::operator=(Texture && texture)
    {
        m_id   = std::move(texture.m_id);
        m_slot = std::move(texture.m_slot);
        texture.m_id   = MV_TEXTURE_DEFAULT_ID;
        texture.m_slot = MV_TEXTURE_DEFAULT_SLOT;
        return *this;
    }

    Texture::~Texture() 
    {
        if(this->usable())
            glDeleteTextures(1, &m_id);
    }

    void Texture::bind() const 
    {
        glActiveTexture(GL_TEXTURE0 + m_slot);
        glBindTexture(type(), m_id);
    }

    void Texture::bind(GLuint slot) const
    {
        m_slot = slot;
        bind();
    }

    GLint Texture::width() const
    {
        GLint width = 0;
        glGetTexLevelParameteriv(type(), 0, GL_TEXTURE_WIDTH, &width);
        return width;
    }

    GLint Texture::height() const
    {
        GLint height = 0;
        glGetTexLevelParameteriv(type(), 0, GL_TEXTURE_HEIGHT, &height);
        return height;
    }

    GLint Texture::type() const
    {
        GLint target = GL_TEXTURE_2D;
        glGetTextureParameteriv(m_id, GL_TEXTURE_TARGET, &target);
        return target;
    }

    GLint Texture::format() const
    {
        GLint format = GL_RED;
        glGetTexLevelParameteriv(type(), 0, GL_TEXTURE_INTERNAL_FORMAT, &format);
        return format;
    }

    void Texture::setSlot(GLuint slot) 
    {
        m_slot = slot;
    }

    void Texture::setWraping(Wraping wraping, Axis flags) 
    {
        GLint texture_type = type();
        glBindTexture(texture_type, m_id);
        if(flags != 0) 
        {
            if((flags & S) != 0) 
            {
                glTexParameteri(texture_type, GL_TEXTURE_WRAP_S, wraping);
            }

            if((flags & T) != 0) 
            {
                glTexParameteri(texture_type, GL_TEXTURE_WRAP_T, wraping);
            }

            if((flags & R) != 0) 
            {
                glTexParameteri(texture_type, GL_TEXTURE_WRAP_R, wraping);
            }
        }
    }

    void Texture::setSmoothing(bool state) 
    {
        GLint texture_type = type();
        glBindTexture(texture_type, m_id);
        glTexParameteri(texture_type, GL_TEXTURE_MIN_FILTER, state ? GL_LINEAR : GL_NEAREST);
        glTexParameteri(texture_type, GL_TEXTURE_MAG_FILTER, state ? GL_LINEAR : GL_NEAREST);
    }

    void Texture::load(GLint width, GLint height, const GLubyte * data, GLint format, GLint type) 
    {
        if(usable()) 
        {
            glDeleteTextures(1, &m_id);
            glGenTextures(1, &m_id);
        }

        glBindTexture(type, m_id);
        glTexImage2D(type, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(type);

        setWraping(CLAMP_TO_BORDER, static_cast<Axis>(S | T));
        setSmoothing(false);
    }

    void Texture::load(const TextureBuffer & texture, GLint type)
    {
        if(texture.data().empty()) 
        {
            throw std::runtime_error("Cannot load texturebuffer.");
        }

        load(texture.width(), texture.height(), texture.data().data(), texture.format(), type);
    }

    bool Texture::usable() const 
    {
        return m_id != MV_TEXTURE_DEFAULT_ID;
    }

    void Texture::Unbind(GLuint type)
    {
        glBindTexture(type, MV_TEXTURE_DEFAULT_SLOT);
    }

    GLint Texture::CountUnit() 
    {
        GLint units = 0;
        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &units);
        return units;
    }

    void Texture::SetDisabelingByteAligment(bool state) 
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, state);
    }
}