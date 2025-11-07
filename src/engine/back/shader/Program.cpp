#include "Program.h"

#include <iostream>
#include <list>
#include <exception>

#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>

namespace mv::engine::shader 
{
    Program::Program() 
    : m_id(MV_PROGRAM_DEFAULT_ID)
    {
        this->m_id = glCreateProgram();
    }

    Program::Program(Program && program)
    : m_id(std::move(program.m_id)), m_locations(std::move(program.m_locations))
    {
        program.m_id = MV_PROGRAM_DEFAULT_ID;
    }

    Program & Program::operator=(Program && program)
    {   
        m_id = std::move(program.m_id);
        m_locations = std::move(program.m_locations);

        program.m_id = MV_PROGRAM_DEFAULT_ID;

        return *this;
    }

    Program::~Program() 
    {
        if(m_id != MV_PROGRAM_DEFAULT_ID)
            glDeleteProgram(m_id);
    }

    GLuint Program::identifier() const
    {
        return m_id;
    }

    bool Program::linkable() const
    {
        GLint count;
        glGetProgramiv(m_id, GL_ATTACHED_SHADERS, &count);

        GLuint * sources = new GLuint[count];
        glGetAttachedShaders(m_id, count, NULL, sources);
        
        bool vertex = false, fragment = false, compute = false;

        for(GLint i = 0; i < count; ++i) 
        {
            GLint type = 0;
            glGetShaderiv(sources[i], GL_SHADER_TYPE, &type);

            switch(type)
            {
                case static_cast<GLint>(File::Type::Vertex):
                    vertex = true;
                    break;

                case static_cast<GLint>(File::Type::Fragment):
                    fragment = true;
                    break;

                case static_cast<GLint>(File::Type::Compute):
                    compute = true;
                    break;
            }
        }

        delete [] sources;

        return ((vertex && fragment) && !compute) || (compute && (!vertex && !fragment));
    }

    bool Program::usable() const
    {
        GLint status = GL_FALSE;
        glGetProgramiv(m_id, GL_LINK_STATUS, &status);
        return status;
    }

    bool Program::isCompute() const
    {
        GLint count;
        glGetProgramiv(m_id, GL_ATTACHED_SHADERS, &count);

        GLuint * sources = new GLuint[count];
        glGetAttachedShaders(m_id, count, NULL, sources);

        for(GLint i = 0; i < count; ++i) 
        {
            GLint type = 0;
            glGetShaderiv(sources[i], GL_SHADER_TYPE, &type);

            if(type == static_cast<GLint>(File::Type::Compute))
            {
                delete [] sources;
                return true;
            }
        }

        delete [] sources;
        return false;
    }

    void Program::attach(const Source & source) 
    {
        if(usable())
            throw std::logic_error("Cannot attach source to a linked program!"); 

        glAttachShader(m_id, source.identifier());
    }

    void Program::dettach(const Source & source)
    {
        if(usable())
            throw std::logic_error("Cannot dettach source from a linked program!"); 

        glDetachShader(m_id, source.identifier());
    }

    void Program::release() 
    {
        if(m_id != MV_PROGRAM_DEFAULT_ID)
            glDeleteProgram(m_id);

        this->m_id = glCreateProgram();
    }

    void Program::link() const
    {
        if(linkable()) 
        {
            glLinkProgram(m_id);

            int success;
            char infoLog[512];

            glGetProgramiv(m_id, GL_LINK_STATUS, &success);
            if(!success) 
            {
                glGetProgramInfoLog(m_id, 512, NULL, infoLog);
                throw std::runtime_error(String("Linking error: ").append(infoLog));
            }   

            GLint count;
            glGetProgramiv(m_id, GL_ACTIVE_UNIFORMS, &count);

            for(size_t i = 0; i < count; ++i) 
            {
                GLint length, size;
                GLenum type;
                GLchar name[64];
                glGetActiveUniform(m_id, static_cast<GLuint>(i), 64, &length, &size, &type, name);
                
                String var_name(name);
                m_locations[var_name.substr(0, var_name.find("["))] = glGetUniformLocation(m_id, name);
            }
        }
        else 
        {
            throw std::logic_error("Cannot link program!");   
        }
    }

    void Program::use() const 
    {
        if(usable())
            glUseProgram(m_id);
    }

    Program & Program::operator<<(const Source & source)
    {
        attach(source);
        return *this;
    }
  
    void Program::setUniform(const String & name, GLint value) const 
    {
        glUniform1i(m_locations.at(name), value);
    }

    void Program::setUniform(const String & name, GLuint value) const
    {
        glUniform1ui(m_locations.at(name), value);
    }

    void Program::setUniform(const String & name, GLfloat value) const 
    {
        glUniform1f(m_locations.at(name), value);
    }

    void Program::setUniform(const String & name, GLdouble value) const 
    {
        glUniform1d(m_locations.at(name), value);
    }

    void Program::setUniform(const String & name, GLchar value) const 
    {
        this->setUniform(name, static_cast<GLint>(value));
    }

    void Program::setUniform(const String & name, const glm::mat4 & value) const 
    {
        glUniformMatrix4fv(m_locations.at(name), 1, GL_FALSE, &value[0][0]);
    }
}