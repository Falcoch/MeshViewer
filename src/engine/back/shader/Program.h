#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <set>
#include <unordered_map>

#include "Source.h"

#define MV_PROGRAM_DEFAULT_ID 0

namespace mv::engine::shader 
{
    class Program 
    {
        public:
            Program();
            Program(const Program &) = delete;
            Program(Program &&);
            Program & operator=(const Program &) = delete;
            Program & operator=(Program &&);
   virtual ~Program();

            GLuint identifier() const;

            bool linkable() const;
            bool usable() const;

            bool isCompute() const;

            void attach(const Source &);
            void dettach(const Source &);
            void release();

            virtual void link() const;
            virtual void use() const;

            Program & operator<<(const Source & source);

            void setUniform(const String &, GLint) const;
            void setUniform(const String &, GLuint) const;
            void setUniform(const String &, GLfloat) const;
            void setUniform(const String &, GLdouble) const;
            void setUniform(const String &, GLchar) const;

            void setUniform(const String &, const glm::mat4 &) const;

        private:
            GLuint m_id;
            mutable std::unordered_map<String, GLuint> m_locations;
    };
}