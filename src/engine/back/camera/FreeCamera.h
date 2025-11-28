#pragma once

#include <utils/Type.h>

#include "Camera.h"

namespace mv::engine
{
    class FreeCamera : public Camera
    {
        public:
            FreeCamera(const glm::vec3 & = glm::vec3(0.f, 0.f, 3.f));
   virtual ~FreeCamera() = default;

            const glm::vec3 & position() const;
            const glm::vec3 & rotation() const;
            const glm::vec3 & scale() const;
            const glm::vec2 & range() const;

            float fov() const;
            float ratio() const;

            const glm::mat4x4 & projection() const;
            const glm::mat4x4 & view() const;

            float x() const;
            float y() const;
            float z() const;

            void setPosition(const glm::vec3 &);
            void setRotation(const glm::vec3 &);
            void setScale(const glm::vec3 &);
            void setRange(const glm::vec2 &);

            void setFov(float);
            void setRatio(float);
            void setRatio(float, float);

            void setPosition(float, float, float = 0.f);

            glm::mat4x4 view_projection() const override;

        protected:
            enum Modified
            {
                None        = 0,
                Projection  = 1,
                View        = 2,
            };

            void update(uint8 = Modified::None) const;

        private:
            glm::vec3 m_position;
            glm::vec3 m_rotation;   // pitch / yaw / roll
            glm::vec3 m_scale;
            glm::vec2 m_range;
             
            float m_fov;
            float m_ratio;
            
            mutable glm::vec3 m_up;

            mutable glm::mat4x4 m_projection;
            mutable glm::mat4x4 m_view;
            mutable uint8 m_flags;
    };
}