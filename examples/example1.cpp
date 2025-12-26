#include <iostream>

#include "core/application.hpp"
#include "core/systems/metadata.hpp"
#include "core/systems/window.hpp"
#include "core/events/runtime.hpp"

using namespace core;

int main()
{
    Application app;
    app.register_system<systems::Metadata>("My App", systems::Version {0, 0, 1});
    app.register_system<systems::Window>();

    events::Update update;
    app.dispatch_event(update);
}