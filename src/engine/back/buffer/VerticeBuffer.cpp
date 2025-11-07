#include "VerticeBuffer.h"

#include <list>

namespace mv::engine 
{
    VerticeBuffer::VerticeBuffer(const VertexArray & vao, const layout::Array & attributes, size_t size, EditMode mode)
    : GenericBuffer(size, 0), m_vao(vao), m_vbo(0), m_mode(mode), m_layout(attributes) 
    {
        this->generate({});
    } 

    VerticeBuffer::VerticeBuffer(const VertexArray & vao, const layout::Array & attributes, const std::vector<float> & vertices, EditMode mode)
    : GenericBuffer(vertices.size(), vertices.size()), m_vao(vao), m_vbo(0), m_mode(mode), m_layout(attributes) 
    {
        this->generate(vertices);
    }

    VerticeBuffer::~VerticeBuffer() 
    {
        this->unbind();
        glDeleteBuffers(1, &m_vbo);
    }

    uint64 VerticeBuffer::weight() const 
    {
        return layout::weight(m_layout);
    }

    uint64 VerticeBuffer::count() const {
        return this->size() / this->weight();
    }

    void VerticeBuffer::bind() const 
    {
        if(m_vbo != 0) 
        {
            m_vao.bind();
            glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        }
    }

    void VerticeBuffer::unbind() const 
    {
        GLint vbo = 0;
        glGetIntegerv(GL_ARRAY_BUFFER, &vbo);
        if(static_cast<GLuint>(vbo) == m_vbo) 
        {
            m_vao.unbind();
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
    }

    void VerticeBuffer::generate(const Buffer<float> & vertices) 
    {
        m_vao.bind();

        if(m_vbo != 0) 
        {
            glBindBuffer(GL_ARRAY_BUFFER,0);
            glDeleteBuffers(1, &m_vbo);
        }

        glGenBuffers(1,&m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, this->max_size()*sizeof(float), vertices.size() == 0 ? NULL : vertices.data(), m_mode);

        uint32 layer = 0; 
        uint64 accumulateWeight = 0; 
        uint64 totalWeight = static_cast<uint64>(this->weight());
        for(auto & attribute : m_layout) 
        {
            glVertexAttribPointer(layer, static_cast<GLint>(attribute.weight), GL_FLOAT, GL_FALSE, static_cast<GLsizei>(totalWeight) * sizeof(float), (void*)(accumulateWeight * sizeof(float)));
            glEnableVertexAttribArray(layer++);
            accumulateWeight += attribute.weight;
        }
    }

    bool VerticeBuffer::compare(const layout::Array & layout) const 
    {
        return m_layout == layout;
    }

    bool VerticeBuffer::operator==(const VerticeBuffer & vbo) const 
    {
        return m_vbo == vbo.m_vbo;
    }

    bool VerticeBuffer::operator!=(const VerticeBuffer & vbo) const 
    {
        return m_vbo != vbo.m_vbo;
    }

    bool VerticeBuffer::operator>(const VerticeBuffer & vbo) const 
    {
        return m_vbo > vbo.m_vbo;
    }

    bool VerticeBuffer::operator>=(const VerticeBuffer & vbo) const 
    {
        return m_vbo >= vbo.m_vbo;
    }

    bool VerticeBuffer::operator<(const VerticeBuffer & vbo) const 
    {
        return m_vbo < vbo.m_vbo;
    }

    bool VerticeBuffer::operator<=(const VerticeBuffer & vbo) const 
    {
        return m_vbo <= vbo.m_vbo;
    }

    VerticeBuffer & operator<<(VerticeBuffer & vbo,const Buffer<float> & data) 
    {
        vbo.push_back(data);
        return vbo;
    }
}