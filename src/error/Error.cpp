#include "Error.h"

namespace mv::error
{
    Error::Error(const std::source_location & where)
    : m_what(""), m_where(where) {}

    Error::Error(const std::string & what, const std::source_location & where)
    : m_what(what), m_where(where) {}

    Error::Error(const Error & error)
    : m_what(error.m_what), m_where(error.m_where) {}

    Error::Error(const Error && error)
    : m_what(std::move(error.m_what)), m_where(std::move(error.m_where)) {}

    Error & Error::operator=(const Error & error)
    {
        m_what = error.m_what;
        m_where = error.m_where;
        return *this;
    }

    Error & Error::operator=(const Error && error)
    {
        m_what = std::move(error.m_what);
        m_where = std::move(error.m_where);
        return *this;
    }

    const char * Error::what() const
    {
        return m_what.c_str();
    }

    const std::source_location & Error::where() const
    {
        return m_where;
    }
}