# C++ Codebase
A framework for C++ applications.

## Design
Most of the program's functionality is to be placed in an [Application](./include/core/application.hpp).
The Application owns a set of objects derived from [System](./include/core/system.hpp) through several
stacks. For example:

|            |          |           |
|------------|----------|-----------|
|            | Renderer | GameUI    |
| Filesystem | Window   | GameWorld |
| Stack 1    | Stack 2  | Stack 3   |

## Events
There are two types of communication between Systems, inspired from [ROS2's event system](https://docs.ros.org/en/jazzy/index.html)

### Topics
[Topics](./include/core/events/topic.hpp) are templated objects which recieve [Messages](./include/core/events/message.hpp).

* Publishers are Systems which send Messages to Topics.
* Subscribers are Systems which listen for Messages from Topics.

A Topic can have any number of Subscribers and any number of Publishers (of course)