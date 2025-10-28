#pragma once

#include "GenericBuffer.h"

#include <compare>

#include "VertexArray.h"
#include "Layout.h"
#include "EditMode.h"

namespace mv::engine 
{
    class VerticeBuffer : public GenericBuffer<float, GL_ARRAY_BUFFER> 
    {
        public:
            VerticeBuffer() = delete;
            VerticeBuffer(const VertexArray & vao, const Layout::Array &, uint64, EditMode = EditMode::STATIC);
            VerticeBuffer(const VertexArray & vao, const Layout::Array &, const Buffer<float> &, EditMode = EditMode::STATIC);
            VerticeBuffer(const VerticeBuffer &) = delete;
   virtual ~VerticeBuffer();

            const Layout::Array & layout() const {return this->m_layout;}

            uint64 weight() const;
            uint64 count() const;

            virtual GLuint id() const {return this->m_vbo;}
            virtual void bind() const;
            virtual void unbind() const;
            virtual void generate(const Buffer<float> &);

            bool compare(const Layout::Array &) const;

            bool operator==(const VerticeBuffer &) const;
            bool operator!=(const VerticeBuffer &) const;
            bool operator<=(const VerticeBuffer &) const;
            bool operator>=(const VerticeBuffer &) const;
            bool operator<(const VerticeBuffer &) const;
            bool operator>(const VerticeBuffer &) const;

            friend VerticeBuffer & operator<<(VerticeBuffer &, const Buffer<float> &);

        private:
            const VertexArray & m_vao;
            GLuint m_vbo;
            EditMode m_mode;
            Layout::Array m_layout;
    };
}