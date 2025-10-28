#pragma once

#include "Buffer.h"

#include <vector>
#include <functional>
#include <stdint.h>

#include <GL/glew.h>

#include <utils/Type.h>

namespace mv::engine 
{
    template <typename T, uint32 Y>
    class GenericBuffer 
    {
        public:
            GenericBuffer() = delete;
            GenericBuffer(uint64, uint64);
           ~GenericBuffer() = default;

            uint64 size() const;
            uint64 max_size() const;
            
            bool isEmpty() const;
            bool isFull() const;
           
            void set(const Buffer<T> &);
            void insert(uint64, const Buffer<T> &);
            void erase(uint64, uint64);
            void resize(uint64);
            void clear();
            
            void push_back(const Buffer<T> &);
            void push_front(const Buffer<T> &);
            void pop_back(uint64 = 1);
            void pop_front(uint64 = 1);
            
            T back() const;
            T front() const;
            T at(uint64) const;
            
            Buffer<T> extract() const;
            Buffer<T> extract(uint64 from, uint64 to) const;
            
            virtual void generate(const Buffer<T> &) = 0;
            virtual void bind() const = 0;
            virtual void unbind() const = 0;
            virtual GLuint id() const = 0;
            
            T operator[](uint64 index) const;

        private:
            uint64 m_max_size, m_size;
    };
}

#include "GenericBuffer.tpp"