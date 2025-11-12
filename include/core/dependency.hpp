#pragma once

namespace core
{
    template <typename T>
    class Dependency {
    public:
        bool fulfilled();
    private:
        T* instance; 
    };

    class DependencyManager {
        
    };
}