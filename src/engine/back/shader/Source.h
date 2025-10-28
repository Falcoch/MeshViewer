#pragma once

#include <GL/glew.h>
#include <filesystem>

namespace mv::engine 
{
    class Source 
    {
        public:
            enum class Type : GLenum 
            {
                NONE            = 0,
                VERTEX          = GL_VERTEX_SHADER,
                FRAGMENT        = GL_FRAGMENT_SHADER,
                GEOMETRY        = GL_GEOMETRY_SHADER,
                TESS_CONTROL    = GL_TESS_CONTROL_SHADER,
                TESS_EVALUATION = GL_TESS_EVALUATION_SHADER,
                COMPUTE         = GL_COMPUTE_SHADER,
            };

            Source();
            Source(const std::filesystem::path &, Type);
            Source(const Source &);
            Source operator=(const Source &);
           ~Source();

            const std::filesystem::path & path() const;
            bool usable() const;
            GLuint id() const;
            Type type() const;

            void open(const std::filesystem::path &, Type);
            void release();

        private:
            GLuint m_id;
            Type m_type;
            std::filesystem::path m_path;
    };
}