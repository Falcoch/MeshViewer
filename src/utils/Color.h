#pragma once

#include <glm/vec4.hpp>

#include "Type.h"

namespace mv
{
    class Color 
    {
        public:
            explicit Color(uint8 = 255);
            explicit Color(uint8, uint8, uint8, uint8 = 255);
            
            Color(const glm::vec4 &);
            Color(const std::string &);

            explicit Color(const Color &);
            explicit Color(const Color &&);

            Color & operator=(const Color &);
            Color & operator=(const Color &&);
            Color & operator=(const glm::vec4 &);
            Color & operator=(const glm::vec4 &&);

           ~Color() = default;

            uint8 red() const;
            uint8 green() const;
            uint8 blue() const;
            uint8 alpha() const;
            Vec4<uint8> value() const;

            float redf() const;
            float greenf() const;
            float bluef() const;
            float alphaf() const;
            Vec4<float> valuef() const;

            glm::vec4 glm() const;

            void setValue(uint8, uint8, uint8, uint8 = 255);
            void setValue(float, float, float, float = 1.f);
            void setValue(const glm::vec4 &);
            void setValue(const std::string &);

        private:    
            uint8 m_red, m_green, m_blue, m_alpha;
    };
}