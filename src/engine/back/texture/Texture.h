#pragma once

#include <GL/glew.h>
#include <compare>

#include "TextureBuffer.h"

#define MV_TEXTURE_DEFAULT_ID 0
#define MV_TEXTURE_DEFAULT_SLOT 0

namespace mv::engine 
{
    class Texture 
    {
        public:
            Texture();
            Texture(const TextureBuffer &, GLuint = GL_TEXTURE_2D);
            Texture(TextureBuffer &&, GLuint = GL_TEXTURE_2D);
            Texture(const Texture &);
            Texture(Texture &&);
            Texture & operator=(const Texture &);
            Texture & operator=(Texture &&);
           ~Texture();

            enum Wraping 
            {
                REPEAT              = GL_REPEAT,
                MIRRORED_REPEAT     = GL_MIRRORED_REPEAT,
                CLAMP_TO_BORDER     = GL_CLAMP_TO_BORDER,
                CLAMP_TO_EDGE       = GL_CLAMP_TO_EDGE
            };

            enum Axis 
            {
                S = 1,
                T = 2,
                R = 4
            };

            enum Format 
            {
                RGB     = GL_RGB,
                RGBA    = GL_RGBA,
            };

            void bind() const;
            void bind(GLuint) const;

            GLint width() const;
            GLint height() const;
            GLint type() const;
            GLint format() const;

            GLuint slot() const;
            GLuint identifier() const;

            void setSlot(GLuint);
            void setWraping(Wraping, Axis = static_cast<Axis>(S | T));
            void setSmoothing(bool);

            void load(const TextureBuffer &, GLint);
            
            bool usable() const;

            static void Unbind(GLuint = GL_TEXTURE_2D);
            static GLint CountUnit();
            static void SetDisabelingByteAligment(bool);

        protected:
            void load(GLint, GLint, const GLubyte *, GLint, GLint);

        private:
            GLuint m_id;
            mutable GLuint m_slot;   
    };
}