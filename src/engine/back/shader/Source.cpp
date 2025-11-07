#include "Source.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <exception>

#include <utils/Log.h>

namespace mv::engine::shader 
{
    Source::Source() 
    : m_id(MV_SOURCE_DEFAULT_ID), m_file() 
    {}

    Source::Source(const Source & source)
    : m_id(MV_SOURCE_DEFAULT_ID), m_file()
    {
        if(source.m_file.usable())
            load(source.m_file);
    }

    Source::Source(Source && source)
    : m_id(std::move(source.m_id)), m_file(std::move(source.m_file))
    {
        source.m_id = MV_SOURCE_DEFAULT_ID;
    }

    Source & Source::operator=(const Source & source)
    {
        m_id = MV_SOURCE_DEFAULT_ID;
        m_file = {};

        if(source.m_file.usable())
            load(source.m_file);

        return *this;
    }

    Source & Source::operator=(Source && source)
    {
        m_id = source.m_id;
        m_file = std::move(source.m_file);

        source.m_id = MV_SOURCE_DEFAULT_ID;
        return *this;
    }

    Source::~Source() 
    {
        glDeleteShader(m_id);
    }

    bool Source::usable() const
    {
        return m_file.usable();
    }

    GLuint Source::identifier() const
    {
        return m_id;
    }

    const File & Source::file() const
    {
        return m_file;
    }

    void Source::load(const File & file)
    {
        if(m_id != MV_SOURCE_DEFAULT_ID) 
            release();

        if(!file.usable())
            throw std::runtime_error(String("Can't open : ").append(file.path().string()));
        
        std::ifstream is(file.path());
        if(is.fail())
            throw std::runtime_error("Stream fail.");

        std::stringstream buffer;
        buffer << is.rdbuf();

        String code = buffer.str(); // Needed since `buffer.str()` return a temporary  
        const char * ptr = code.c_str();

        m_id = glCreateShader(static_cast<GLenum>(file.type()));
        m_file = file;

        glShaderSource(m_id, 1, &ptr, NULL);
        glCompileShader(m_id);
        buffer.clear();
        
        int success;
        char infoLog[512];
        glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);
        if(!success) 
        {
            glGetShaderInfoLog(m_id, 512, NULL, infoLog);
            debug::log_error("Shader Error: " + String(infoLog));
        }
    }

    void Source::release() 
    {
        m_file = {};
        if(m_id == MV_SOURCE_DEFAULT_ID)
            return;

        glDeleteShader(m_id);
        m_id = MV_SOURCE_DEFAULT_ID;
    }

    Source & Source::operator<<(const File & file) 
    {
        load(file);
        return *this;
    }
}