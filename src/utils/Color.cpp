#include "Color.h"

#include <iostream>

#include "Std.h"

namespace mv
{
    Color::Color(uint8 value)
    : m_red(value), m_green(value), m_blue(value), m_alpha(255)
    {}

    Color::Color(uint8 r, uint8 g, uint8 b, uint8 a)
    : m_red(r), m_green(g), m_blue(b), m_alpha(a)
    {}

    Color::Color(const glm::vec4 & glm)
    : m_red(static_cast<uint8>(glm.r)), m_green(static_cast<uint8>(glm.b)), 
      m_blue(static_cast<uint8>(glm.b)), m_alpha(static_cast<uint8>(glm.a))
    {}

    Color::Color(const std::string & value)
    : m_red(0), m_green(0), m_blue(0), m_alpha(255)
    {
        setValue(value);
    }

    Color::Color(const Color & color)
    : m_red(color.m_red), m_green(color.m_green),
      m_blue(color.m_blue), m_alpha(color.m_alpha)
    {}

    Color::Color(const Color && color)
    : m_red(std::move(color.m_red)), m_green(std::move(color.m_green)),
      m_blue(std::move(color.m_blue)), m_alpha(std::move(color.m_alpha))
    {}

    Color & Color::operator=(const Color & color)
    {
        m_red   = color.m_red;
        m_green = color.m_green;
        m_blue  = color.m_blue;
        m_alpha = color.m_alpha;

        return *this;
    }

    Color & Color::operator=(const Color && color)
    {
        m_red   = std::move(color.m_red);
        m_green = std::move(color.m_green);
        m_blue  = std::move(color.m_blue);
        m_alpha = std::move(color.m_alpha);

        return *this;
    }

    Color & Color::operator=(const glm::vec4 & color)
    {
        m_red   = static_cast<uint8>(color.r);
        m_green = static_cast<uint8>(color.g);
        m_blue  = static_cast<uint8>(color.b);
        m_alpha = static_cast<uint8>(color.a);

        return *this;
    }

    Color & Color::operator=(const glm::vec4 && color)
    {
        m_red   = std::move(static_cast<uint8>(color.r * 255));
        m_green = std::move(static_cast<uint8>(color.g * 255));
        m_blue  = std::move(static_cast<uint8>(color.b * 255));
        m_alpha = std::move(static_cast<uint8>(color.a * 255));

        return *this;
    }

    uint8 Color::red() const 
    {
        return m_red;
    }

    uint8 Color::green() const
    {
        return m_green;
    }

    uint8 Color::blue() const
    {
        return m_blue;
    }

    uint8 Color::alpha() const
    {
        return m_alpha;
    }

    Vec4<uint8> Color::value() const
    {
        return {m_red, m_green, m_blue, m_alpha};
    }

    float Color::redf() const 
    {
        return m_red / 255.f;
    }

    float Color::greenf() const
    {
        return m_green / 255.f;
    }

    float Color::bluef() const
    {
        return m_blue / 255.f;
    }

    float Color::alphaf() const
    {
        return m_alpha / 255.f;
    }

    Vec4<float> Color::valuef() const
    {
        return {redf(), greenf(), bluef(), alphaf()};
    }

    glm::vec4 Color::glm() const
    {
        return {redf(), greenf(), bluef(), alphaf()};
    }

    void Color::setValue(uint8 r, uint8 g, uint8 b, uint8 a)
    {
        m_red   = r;
        m_green = g;
        m_blue  = b;
        m_alpha = a;
    }

    void Color::setValue(float r, float g, float b, float a)
    {
        m_red   = static_cast<uint8>(r * 255.f);
        m_green = static_cast<uint8>(g * 255.f);
        m_blue  = static_cast<uint8>(b * 255.f);
        m_alpha = static_cast<uint8>(a * 255.f);
    }

    void Color::setValue(const glm::vec4 & color)
    {
        setValue(color.r, color.g, color.b, color.a);
    }

    void Color::setValue(const std::string & value)
    {
        uint8 offset = 0;
        std::string hex = std::to_lower(value);

        while(hex.at(offset) == '#' && offset < hex.size())
            ++offset;

        while((hex.size() - offset) < 8)
            hex.append("f");

        std::cout << "Hex: " << hex << std::endl;
        std::cout << "Offset: " << static_cast<unsigned int>(offset) << std::endl;

        uint32_t integer = std::stoul(hex.substr(offset), nullptr, 16);
        m_red   = (integer >> 24) & 0xFF;
        m_green = (integer >> 16) & 0xFF;
        m_blue  = (integer >> 8)  & 0xFF;
        m_alpha =  integer        & 0xFF;
    }
}