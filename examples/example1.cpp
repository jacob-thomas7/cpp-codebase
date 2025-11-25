#include "core/application.hpp"
#include "core/events/topic.hpp"
#include "core/system.hpp"

using namespace core;

class Vector2 {};

struct OnClick {
    int x;
    int y;
};

class GameWorld : public System
{
public:
    // use a normal overload instead of an explicit member-template specialization
    void handle_event(OnClick& event){
        (void)event.x;
    }

    //template <typename>
    // void handle_event<OnClick>()
    // {

    // }
    GameWorld()
    {
        events::Topic<OnClick>::subscribe(this);
    }
};

int main()
{
    GameWorld world;


    // Application app;
    // auto utils = app.add_layer_stack();
    // utils.push<Metadata>("Application Name", { 1, 0, 0 });
    // utils.push<Filesystem>();
    // utils.push<Window>();

    // auto game_world = app.add_layer_stack();
    // game_world.push<GameWorld>();
    // game_world.push<GameUI>();
    // game_world.suspend();

    // auto menu = app.add_layer_stack();
    // menu.push<MenuScreen>();
}