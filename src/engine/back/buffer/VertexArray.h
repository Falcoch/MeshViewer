#pragma once

#include <compare>
#include <GL/glew.h>

namespace mv::engine 
{
    class VertexArray 
    {
        public:
            VertexArray(bool = false);
            VertexArray(const VertexArray &) = delete;
           ~VertexArray();

            GLuint id() const noexcept {return this->m_vao;}

            virtual void bind() const;
            virtual void unbind() const;

            bool operator==(const VertexArray &) const;
            bool operator!=(const VertexArray &) const;
            bool operator<=(const VertexArray &) const;
            bool operator>=(const VertexArray &) const;
            bool operator()(const VertexArray &) const;

            bool operator<(const VertexArray &) const;
            bool operator>(const VertexArray &) const;

        private:
            GLuint m_vao;
    };
}