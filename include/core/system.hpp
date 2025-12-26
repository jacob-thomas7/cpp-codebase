#pragma once

#include <stdexcept>
#include <string>

#include "core/application.hpp"

namespace core
{
    class MissingDependencyException : public std::runtime_error
    {
    public:
        MissingDependencyException(std::string current, std::string missing) :
            std::runtime_error(std::string("\"") + current + "\" is missing dependency \"" + missing + "\"") {}
    };

    class System
    {
    protected:
        System(Application& application) : application(application) {}
        template <typename T>
        T& require(){
            auto system = application.get_system<T>();
            if (!system.has_value()) {
                throw MissingDependencyException(typeid(this).name(), typeid(T).name());
            }
            return system.value();
        }
    private:
        Application& application;
    };
}