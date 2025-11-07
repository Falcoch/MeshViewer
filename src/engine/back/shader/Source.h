#pragma once

#include <GL/glew.h>
#include <filesystem>

#include "File.h"

#define MV_SOURCE_DEFAULT_ID 0

namespace mv::engine::shader 
{
    class Source 
    {
        public:
            Source();
            Source(const Source &);
            Source(Source &&);
            Source & operator=(const Source &);
            Source & operator=(Source &&);
           ~Source();

            bool usable() const;
            
            GLuint identifier() const;
            const File & file() const;


            void load(const File &);
            void release();

            Source & operator<<(const File &);

        private:
            GLuint m_id;
            File m_file;
    };
}