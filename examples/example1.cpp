#include <iostream>

#include "core/application.hpp"

#include "core/systems/metadata.hpp"
#include "core/polymorphic/polymanager.hpp"

using namespace core;

int main()
{
    Application app;

    app.register_system<systems::Metadata>("C++ Codebase Example 1");

    // if (auto option = app.get_system<systems::Metadata>(); option.has_value()) {
    //     auto metadata = option.value().get();
    //     std::cout << metadata.name << ", " << metadata.version << ", " << metadata.license << std::endl;
    // }

    // std::cout << opt.has_value();
    // if (opt.has_value()) {
    //     //std::cout << std::endl << opt.value().get().a;
    //     //opt.value().get().a = 6;
    // }

    // auto m = app.systems.begin();
    // std::cout << m->first << ", " << static_cast<Metadata*>((app.systems.begin()->second.get()))->a;
    
    /*
    app.dipatch_event<Start>(1, 4){
        for event_handler
            if 
    }
    */
}