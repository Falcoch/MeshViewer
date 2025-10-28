#include "Program.h"

#include <iostream>
#include <list>

#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>

namespace mv::engine 
{
    Program::Program() 
    : _id(0), _attached(NONE), _usable(false) 
    {
        this->_id = glCreateProgram();
    }

    Program::~Program() 
    {
        glDeleteProgram(this->_id);
    }

    const uint8_t Program::Categorie(const Source::Categorie categorie) 
    {
        switch (categorie) {
            case Source::Categorie::VERTEX:
                return 1;

            case Source::Categorie::FRAGMENT:
                return 2;

            case Source::Categorie::GEOMETRY:
                return 4;
            
            case Source::Categorie::TESS_CONTROL:
                return 8;

            case Source::Categorie::TESS_EVALUATION:
                return 16;

            case Source::Categorie::COMPUTE:
                return 32;
        
            default:
                return 0;
        }
    }

    void Program::attach(const Source & source) 
    {
        if(source.usable()) 
        {
            glAttachShader(this->_id, source.id());
            this->_attached |= Program::Categorie(source.categorie());
        }
    }

    void Program::dettach(const Source & source)
    {
        glDetachShader(this->_id, source.id());
        this->_attached = this->_attached & ~Program::Categorie(source.categorie());
        this->_usable = ((this->_attached & Bit_Categorie::VERTEX) != 0 && (this->_attached & Bit_Categorie::FRAGMENT) != 0);
    }

    void Program::link() 
    {
        this->_usable = ((this->_attached & Bit_Categorie::VERTEX) != 0 && (this->_attached & Bit_Categorie::FRAGMENT) != 0);
        if((this->_attached & Bit_Categorie::COMPUTE) != 0) 
        {
            if(this->_attached != Bit_Categorie::COMPUTE)
                //TODO: Throw errors
            
            this->_usable = true;
        }
       
        if(this->_usable) 
        {
            glLinkProgram(this->_id);

            int success;
            char infoLog[512];

            glGetProgramiv(this->_id, GL_LINK_STATUS, &success);
            if(!success) 
            {
                this->_usable = false;
                glGetProgramInfoLog(this->_id, 512, NULL, infoLog);
                throw error::shader_error(infoLog);
            }   

            GLint count;
            glGetProgramiv(this->_id, GL_ACTIVE_UNIFORMS, &count);

            for(size_t i = 0; i < count; ++i) {
                GLint length, size;
                GLenum type;
                GLchar name[64];
                glGetActiveUniform(this->_id, static_cast<GLuint>(i), 64, &length, &size, &type, name);
                
                std::string var_name(name);
                this->_locations[var_name.substr(0, var_name.find("["))] = glGetUniformLocation(this->_id, name);
            }
        }
        else 
        {
            if((this->_attached & Bit_Categorie::VERTEX) == 0)
                //TODO: Throw errors
            
            if((this->_attached & Bit_Categorie::FRAGMENT) == 0)
               //TODO: Throw errors
            
        }
    }

    void Program::use() const 
    {
        if(this->_usable)
            glUseProgram(this->_id);
    }

    void Program::kill() 
    {
        this->_usable = false;
        this->_attached = Bit_Categorie::NONE;
        this->_id = glCreateProgram();
    }

    bool Program::usable() const 
    {
        if(!this->_usable)
        {
            bool usable = ((this->_attached & Bit_Categorie::VERTEX) != 0 && (this->_attached & Bit_Categorie::FRAGMENT) != 0);
            if(usable && (this->_attached & Bit_Categorie::COMPUTE) != 0)
                return false;
        }
            
        return this->_usable; 
    }

    void Program::setUniform(const std::string & name, GLint value) const 
    {
        glUniform1i(this->_locations.at(name), value);
    }

    void Program::setUniform(const std::string & name, GLuint value) const
    {
        glUniform1ui(this->_locations.at(name), value);
    }

    void Program::setUniform(const std::string & name, GLfloat value) const 
    {
        glUniform1f(this->_locations.at(name), value);
    }

    void Program::setUniform(const std::string & name, GLdouble value) const 
    {
        glUniform1d(this->_locations.at(name), value);
    }

    void Program::setUniform(const std::string & name, GLchar value) const 
    {
        this->setUniform(name, static_cast<GLint>(value));
    }

    void Program::setUniform(const std::string & name, const glm::mat4 & value) const 
    {
        glUniformMatrix4fv(this->_locations.at(name), 1, GL_FALSE, &value[0][0]);
    }
}