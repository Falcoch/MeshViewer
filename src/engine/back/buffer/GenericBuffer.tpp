#include "GenericBuffer.h"

#include <GL/glew.h>

#include <exception>
#include <stdexcept>
#include <cstring>

#include <iostream>

namespace mv::engine 
{
    template <typename T, uint32 Y>
    GenericBuffer<T, Y>::GenericBuffer(uint64 max, uint64 current)
    : m_max_size(max), m_size(current) 
    {
        if(max == 0)
            throw std::runtime_error("Cannot allocate an empty GenericBuffer!");
    }

    template <typename T, uint32 Y>
    uint64 GenericBuffer<T, Y>::size() const 
    {
        return m_size;
    }

    template <typename T, uint32 Y>
    uint64 GenericBuffer<T, Y>::max_size() const 
    {
        return m_max_size;
    }

    template <typename T, uint32 Y>
    bool GenericBuffer<T, Y>::isEmpty() const 
    {
        return m_size == 0;
    }

    template <typename T, uint32 Y>
    bool GenericBuffer<T, Y>::isFull() const 
    {
        return m_size == m_max_size;
    }

    template <typename T, uint32 Y>
    void GenericBuffer<T, Y>::set(const Buffer<T> & vertices) 
    {
        m_max_size = vertices.size();
        m_size = vertices.size();
        generate(vertices);
    }

    template <typename T, uint32 Y>
    void GenericBuffer<T, Y>::insert(uint64 pos, const Buffer<T> & vertices) 
    {
        if(m_size + vertices.size() > m_max_size) 
        {
            Buffer<T> data = extract();
            data.insert(data.begin() + pos, vertices.begin(), vertices.end());
            set(data);
            return;
        }

        if(id() != 0) 
        {
            bind();
            uint8 * writer = static_cast<uint8 *>(glMapBuffer(Y, GL_READ_WRITE));
                
            if(pos < m_size)
                memmove(writer + ((pos + vertices.size()) * sizeof(T)), writer + (pos * sizeof(T)), (m_size - pos) * sizeof(T));

            memmove(writer + (pos * sizeof(T)), Buffer<T>(vertices).data(), vertices.size() * sizeof(T));
            glUnmapBuffer(Y);
                
            m_size += vertices.size();
        }
        else
        {
            generate(vertices);
        }
    }  

    template <typename T, uint32 Y>
    void GenericBuffer<T, Y>::erase(uint64 from, uint64 to) 
    {
        if(isEmpty())
            throw std::range_error("Buffer is empty.");

        if(m_size - to - from  < 0)
            throw std::underflow_error("Cannot erase datas out of buffer.");
        
        bind();
    
        uint8 * writer = static_cast<uint8 *>(glMapBuffer(Y, GL_READ_WRITE));
        memmove(writer + (from * sizeof(T)), writer + ((to + 1) * sizeof(T)), (m_size - to) * sizeof(T));
        glUnmapBuffer(Y);

        m_size -= (to + 1 - from);
    }

    template <typename T, uint32 Y>
    void GenericBuffer<T, Y>::resize(uint64 max_size) 
    {
        if(m_size > max_size)
            throw std::overflow_error("Cannot set a new max size that is greater than current size");

        Buffer<T> save = extract();
        m_max_size = max_size;
        generate(save);
    }

    template <typename T, uint32 Y>
    void GenericBuffer<T, Y>::push_back(const Buffer<T> & vertices) 
    {
        insert(m_size, vertices);
    }

    template <typename T, uint32 Y>
    void GenericBuffer<T, Y>::push_front(const Buffer<T> & vertices) 
    {
        insert(0, vertices);
    }

    template <typename T, uint32 Y>
    void GenericBuffer<T, Y>::pop_back(uint64 offset) 
    {
        if(offset > m_size)
            throw std::underflow_error("Cannot erase datas out of buffer.");

        if(offset > 0)
            erase(m_size - offset + 1, m_size);
    }

    template <typename T, uint32 Y>
    void GenericBuffer<T, Y>::pop_front(uint64 offset) 
    {
        if(offset > m_size)
            throw std::overflow_error("Cannot add datas out of buffer.");

        if(offset > 0)
            erase(0, offset - 1);
    }

    template <typename T, uint32 Y>
    void GenericBuffer<T, Y>::clear() 
    {
        generate({});
    }

    template <typename T, uint32 Y>
    T GenericBuffer<T, Y>::back() const 
    {
        if(isEmpty())
            throw std::underflow_error("Cannot get data from empty buffer.");
        
        return operator[](0);
    }

    template <typename T, uint32 Y>
    T GenericBuffer<T, Y>::front() const 
    {
        if(isEmpty())
            throw std::underflow_error("Cannot get data from empty buffer.");
        
        return operator[](m_size - 1);
    }

    template <typename T, uint32 Y>
    T GenericBuffer<T, Y>::at(uint64 index) const 
    {
        return operator[](index);
    }

    template <typename T, uint32 Y>
    Buffer<T> GenericBuffer<T, Y>::extract() const 
    {
        return extract(0, m_size);
    }

    template <typename T, uint32 Y>
    Buffer<T> GenericBuffer<T, Y>::extract(uint64 from, uint64 to) const 
    {
        if(to > m_size)
            throw std::overflow_error("Cannot extract datas out of buffer.");

        bind();
        void * writer = glMapBuffer(Y, GL_WRITE_ONLY);
        Buffer<T> data{static_cast<T *>(writer) + from, static_cast<T *>(writer) + from + (to - from)};
        glUnmapBuffer(Y);

        return data;
    }

    template <typename T, uint32 Y>
    T GenericBuffer<T, Y>::operator[](uint64 index) const 
    {
        return extract(index,index)[0];
    }
}