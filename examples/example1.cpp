#include <iostream>
#include <stdexcept>

#include "core/application.hpp"
#include "core/systems/metadata.hpp"
#include "core/systems/window.hpp"

#include "core/event.hpp"

int run_application();

int main()
{
    try {
        run_application();
    } catch (std::runtime_error error) {
        std::cerr << "Unable to begin application: " << error.what() << std::endl;
        return 1;
    }
    
}

int run_application()
{
    core::Application app;
    core::systems::Metadata metadata("Test");
    //core::systems::Window window;
    
    core::Test test_evt;
    core::Event& e = test_evt;
    auto thing = *static_cast<core::Test*>(&e);
    std::cout << thing.e;

    app.register_system(metadata);
    app.on_event(test_evt);
    return 0;
}