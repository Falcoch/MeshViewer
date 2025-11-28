#pragma once

#include <glm/glm.hpp>

namespace mv::engine
{
    class Camera
    {
        public:
            virtual glm::mat4x4 view_projection() const = 0;
    };
}