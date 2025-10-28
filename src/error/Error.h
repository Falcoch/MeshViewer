#pragma once

#include <exception>
#include <source_location>
#include <string>

namespace mv::error
{
    class Error : public std::exception
    {
        public:
            Error(const std::source_location & = std::source_location::current());
            Error(const std::string &, const std::source_location & = std::source_location::current());
            Error(const Error &);
            Error(const Error &&);

            Error & operator=(const Error &);
            Error & operator=(const Error &&);
   
   virtual ~Error() = default;

            virtual const char * what() const noexcept;
            virtual const std::source_location & where() const;

        private:
            std::string m_what;
            std::source_location m_where;
    };
}