JaqubSuite Communcation App 
---------------------------

## Overview

JaqubSuite is a communcations application written in C++. It will be used 
for various methods of communcation in Tridentu-RK (and possibly other KDE distros).

## Features

- Modular Plugin System (for communcations protocols of all shapes and sizes)
- Various ways of handling certain Comm(unications) Plugins (i.e. Email UI vs. Chat UI)
- Simple (but effective) connection system
- Notifications-capable (can display notifications when messages are received and/or sent).

## Basic Dependencies

You need Qt5 and CMake 3.16 or higher

## Extra Dependencies

You will also need:

- [SimpleMail](https://github.com/cutelyst/simple-mail)

-- Build instructions --

cd /your/project/build
cmake -DCMAKE_INSTALL_PREFIX=/usr ../
make

./jaqubsuite



