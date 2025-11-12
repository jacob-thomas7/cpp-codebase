#include <iostream>

#include "core/application.hpp"

#include "core/systems/metadata.hpp"
#include "core/systems/window.hpp"
#include "core/system.hpp"
#include "core/polymorphic/polymanager.hpp"
#include "core/events/update.hpp"

using namespace core;

int main()
{
    Application app;
    auto metadata = app.register_system<systems::Metadata>("C++ Codebase Example 1");
    auto window = app.register_system<systems::Window>(app, metadata);
    
    app.dispatch_event<events::Update>();
}