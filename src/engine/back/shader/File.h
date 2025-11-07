#pragma once

#include <GL/glew.h>
#include <utils/Type.h>

namespace mv::engine::shader
{
    class File
    {
        public:
            enum class Type : GLenum 
            {
                None            = 0,
                Vertex          = GL_VERTEX_SHADER,
                Fragment        = GL_FRAGMENT_SHADER,
                Geometry        = GL_GEOMETRY_SHADER,
                Tess_Control    = GL_TESS_CONTROL_SHADER,
                Tess_Eveluation = GL_TESS_EVALUATION_SHADER,
                Compute         = GL_COMPUTE_SHADER,
            };

            File();
            File(Type, const Path &);
            File(const File &);
            File(File &&);
            File & operator=(const File &);
            File & operator=(File &&);

            bool usable() const;

            Type type() const;
            const Path & path() const;

            void setType(Type);
            void setPath(const Path &);

        private:
            Type m_type;
            Path m_path;
    };
}
