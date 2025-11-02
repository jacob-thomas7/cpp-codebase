#pragma once

#include <string>

namespace core
{
    class Event
    {
        public:
        std::string_view id() { return _id; }
        
        private:
        std::string_view _id;

        protected:
        Event(std::string_view id) : _id(id) {}
    };

    class Test : public Event
    {
        public:
        static constexpr const std::string_view id = "start";
        int e = 4;
        Test() : Event(id) {}
    };
}