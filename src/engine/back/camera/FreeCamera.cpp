#include "FreeCamera.h"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

namespace mv::engine
{
    constexpr const float CAMRA_DEFAULT_PITCH =  0.f;
    constexpr const float CAMRA_DEFAULT_YAW   = -90.f;
    constexpr const float CAMRA_DEFAULT_ROLL  =  0.f;

    constexpr const float CAMERA_DEFAULT_RANGE_MIN =  0.f;
    constexpr const float CAMERA_DEFAULT_RANGE_MAX =  100.f;
    constexpr const float CAMERA_DEFAULT_FOV       =  70.f;
    constexpr const float CAMERA_DEFAULT_RATIO     =  1.7777f;

    constexpr const glm::vec3 CAMERA_DEFAULT_UP_VECTOR = glm::vec3(0.f, 1.f, 0.f); 

    FreeCamera::FreeCamera(const glm::vec3 & position)
    : m_position(position), 
      m_rotation(CAMRA_DEFAULT_PITCH, CAMRA_DEFAULT_YAW, CAMRA_DEFAULT_ROLL),
      m_scale(0.f, 0.f, 0.f),
      m_range(CAMERA_DEFAULT_RANGE_MIN, CAMERA_DEFAULT_RANGE_MAX),
      m_fov(CAMERA_DEFAULT_FOV),
      m_ratio(CAMERA_DEFAULT_RATIO),   
      m_up(0.f, 1.f, 0.f),
      m_projection(1.f),
      m_view(1.f),
      m_flags(Modified::None)
    {
        update(Modified::View | Modified::Projection);
    }

    const glm::vec3 & FreeCamera::position() const
    {
        return m_position;
    }

    const glm::vec3 & FreeCamera::rotation() const
    {
        return m_rotation;
    }

    const glm::vec3 & FreeCamera::scale() const
    {
        return m_scale;
    }

    const glm::vec2 & FreeCamera::range() const
    {
        return m_range;
    }

    float FreeCamera::fov() const
    {
        return m_fov;
    }

    float FreeCamera::ratio() const
    {
        return m_ratio;
    }

    const glm::mat4x4 & FreeCamera::projection() const
    {
        update();
        return m_projection;
    }

    const glm::mat4x4 & FreeCamera::view() const
    {
        update();
        return m_view;
    }

    float FreeCamera::x() const
    {
        return m_position.x;
    }

    float FreeCamera::y() const
    {
        return m_position.y;
    }

    float FreeCamera::z() const
    {
        return m_position.z;
    }

    void FreeCamera::setPosition(const glm::vec3 & positon)
    {
        m_position = positon;
    }

    void FreeCamera::setRotation(const glm::vec3 & rotation)
    {
        m_rotation = rotation;
    }

    void FreeCamera::setScale(const glm::vec3 & scale)
    {
        m_scale = scale;
    }

    void FreeCamera::setRange(const glm::vec2 & range)
    {
        m_range = range;
    }

    void FreeCamera::setFov(float fov)
    {
        m_fov = fov;
    }

    void FreeCamera::setRatio(float ratio)
    {
        m_ratio = ratio;
    }

    void FreeCamera::setRatio(float a, float b)
    {
        m_ratio = a / b;
    }

    void FreeCamera::setPosition(float x, float y, float z)
    {
        m_position = glm::vec3(x, y ,z);
    }

    glm::mat4x4 FreeCamera::view_projection() const
    {
        update();
        return m_projection * m_view;
    }

    void FreeCamera::update(uint8 force) const
    {
        m_flags |= force;
        if((force & Modified::View) != 0)
        {
            glm::vec3 front;
            front.x = std::cos(glm::radians(m_rotation.y)) * std::cos(glm::radians(m_rotation.x));
            front.y = std::sin(glm::radians(m_rotation.x));
            front.z = std::sin(glm::radians(m_rotation.y)) * std::cos(glm::radians(m_rotation.x));
            front = glm::normalize(front);

            glm::vec3 right = glm::normalize(glm::cross(front, m_up));
            glm::mat4x4 rolling = glm::rotate(glm::mat4(1.f), glm::radians(m_rotation.z), front);

            m_up = glm::normalize(glm::cross(right, front));
            m_up = glm::mat3(rolling) * m_up;

            m_view = glm::lookAt(m_position, m_position + front, m_up);
        }

        if((force & Modified::Projection) != 0)
        {
            m_projection = glm::perspective(glm::radians(m_fov), m_ratio, m_range.x, m_range.y);
        }

        m_flags = Modified::None;
    }
}