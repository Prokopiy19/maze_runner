# maze_runner

Simple game inspired by certain classic game. You find yourself in a randomly generated maze. Don't run into monsters and collect as many apples as possible.

The game is fully written in C++ using SDL2. Maze is randomly generated upon each launch. Monsters' AI is very simple - they move in random directions. At the beginning there are only 5 monsters, and every 5 seconds additional monster spawns - game gets harder with time.

If you die, just close the window, it currently doesn't support in-game restarting.

# Compiling

The game was compiled using following command:

    clang++ src/*.cpp `sdl2-config --cflags --libs` `pkg-config sdl2_image --cflags --libs` `pkg-config sdl2_ttf --cflags --libs` -std=c++20

It was done in msys2 building environment. If you compile the game yourself, you will need .dll files which you can get from msys2.
