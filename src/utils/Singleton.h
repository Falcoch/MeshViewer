#pragma once

#include <memory>

namespace mv
{
    template <class T>
    class Singleton
    {
        public:
            Singleton() = default;
           ~Singleton() = default;
            
            static const std::type_info & Type()
            {
                return typeid(T);
            }

            static bool Exist()
            {
                return Singleton<T>::m_instance != nullptr;
            }

            static T & Instance()
            {
                if(Singleton<T>::m_instance == nullptr)
                    Singleton<T>::m_instance = std::make_unique<T>();

                return *Singleton<T>::m_instance;
            } 

        private:
            inline static std::unique_ptr<T> m_instance = nullptr;
    };
}