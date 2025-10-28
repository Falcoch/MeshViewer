#include "Source.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <exception>

#include <utils/Log.h>

namespace mv::engine {
    Source::Source() 
    : m_id(0), m_type(Type::NONE), m_path("") 
    {}

    Source::Source(const std::filesystem::path & path, Type type) 
    : Source() 
    {
        open(path, type);
    }

    Source::~Source() 
    {
        glDeleteShader(m_id);
    }

    const std::filesystem::path & Source::path() const 
    {
        return m_path;
    }

    void Source::open(const std::filesystem::path & path, Type type)
    {
        if(m_id != 0) 
            release();

        if(!std::filesystem::exists(path))
            throw std::runtime_error(std::string("Can't open : ").append(path.string()));

        m_path = path;
        std::ifstream is(path);
        if(is.fail())
            throw std::runtime_error("Stream fail.");

        std::stringstream buffer;
        buffer << is.rdbuf();

        const char * code =  buffer.str().c_str();

        m_id = glCreateShader(static_cast<GLenum>(type));
        m_type = type;

        glShaderSource(m_id, 1, &code, NULL);
        glCompileShader(m_id);
        buffer.clear();
        
        int success;
        char infoLog[512];
        glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);
        if(!success) 
        {
            glGetShaderInfoLog(m_id, 512, NULL, infoLog);
            debug::log_error("Shader Error: " + std::string(infoLog));
        }
    }

    void Source::release() 
    {
        glDeleteShader(m_id);
        m_id = 0;
        m_type = Type::NONE;
    }
}