#include "File.h"

namespace mv::engine::shader
{
    File::File()
    : m_path(""), m_type(Type::None)
    {}

    File::File(Type type, const Path & path)
    : m_type(type), m_path(path)
    {}

    File::File(const File & file)
    : m_type(file.m_type), m_path(file.m_path)
    {}

    File::File(File && file)
    : m_type(file.m_type), m_path(std::move(file.m_path))
    {}

    File & File::operator=(const File & file)
    {
        m_type = file.m_type;
        m_path = file.m_path;
        return *this;
    }

    File & File::operator=(File && file)
    {
        m_type = file.m_type;
        m_path = std::move(file.m_path);
        return *this;
    }

    bool File::usable() const
    {
        return m_type != Type::None && (std::filesystem::exists(m_path) && !std::filesystem::is_directory(m_path));
    }

    File::Type File::type() const
    {
        return m_type;
    }

    const Path & File::path() const
    {
        return m_path;
    }

    void File::setType(Type type)
    {
        m_type = type;
    }

    void File::setPath(const Path & path)
    {
        m_path = path;
    }
}