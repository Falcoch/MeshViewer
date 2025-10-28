#include "VertexArray.h"

namespace mv::engine {
    VertexArray::VertexArray(bool binded) 
    : m_vao(0) 
    {
        glGenVertexArrays(1, &m_vao);
        if(binded)
            bind();
    }

    VertexArray::~VertexArray() 
    {
        unbind();
        glDeleteVertexArrays(1,&m_vao);
    }

    void VertexArray::bind() const 
    {
        if(m_vao != 0)
            glBindVertexArray(m_vao);
    }

    void VertexArray::unbind() const 
    {
        GLint vao;
        glGetIntegerv(GL_ARRAY_BUFFER, &vao);
        if(static_cast<GLuint>(vao) == m_vao)
            glBindVertexArray(0);
    }

    bool VertexArray::operator==(const VertexArray & vao) const 
    {
        return m_vao == vao.m_vao;
    }

    bool VertexArray::operator!=(const VertexArray & vao) const 
    {
        return m_vao != vao.m_vao;
    }

    bool VertexArray::operator>(const VertexArray & vao) const 
    {
        return m_vao > vao.m_vao;
    }

    bool VertexArray::operator>=(const VertexArray & vao) const 
    {
        return m_vao >= vao.m_vao;
    }

    bool VertexArray::operator()(const VertexArray & vao) const 
    {
        return *this > vao;
    }

    bool VertexArray::operator<(const VertexArray & vao) const 
    {
        return m_vao < vao.m_vao;
    }

    bool VertexArray::operator<=(const VertexArray & vao) const 
    {
        return m_vao <= vao.m_vao;
    }
}