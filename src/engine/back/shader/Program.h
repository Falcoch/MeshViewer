#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <set>
#include <unordered_map>

#include "Source.h"

namespace mv::engine 
{
    class Program {
        protected:
            enum Type 
            {
                NONE            = 0,
                VERTEX          = 1,
                FRAGMENT        = 2,
                GEOMETRY        = 4,
                TESS_CONTROL    = 8,
                TESS_EVALUATION = 16,
                COMPUTE         = 32,
            }; 

            static const uint8_t Categorie(const Source::Type);

        public:
            Program();
            Program(const Program &) = delete;
            Program(const Program &&) = delete;
            Program operator=(const Program &) = delete;
   virtual ~Program();

            void attach(const Source &);
            void dettach(const Source &);
            void release();

            void link();

            virtual void use() const;

            inline GLuint id() const {return this->_id;}
            bool isUsable() const;
            bool isCompute() const;

            inline void operator<<(const Source & source) {this->attach(source);}
            inline void operator()() const {if(isUsable()) use();}

            void setUniform(const std::string &, GLint) const;
            void setUniform(const std::string &, GLuint) const;
            void setUniform(const std::string &, GLfloat) const;
            void setUniform(const std::string &, GLdouble) const;
            void setUniform(const std::string &, GLchar) const;

            void setUniform(const std::string &, const glm::mat4 &) const;

        private:
            GLuint _id;
            uint8_t _attached;
            mutable std::unordered_map<std::string, GLuint> _locations;
    };
}