# rpg-c17-sdl2
Yet Another Iteration of the RPG

# Building the project

This projects uses `cmake` to manage the build, and `conan` for the dependencies.
We are handling SDL2, gmock and gtest outside of conan for now, so they must be installed by hand.
Once that is done, my initial setup looks like:

```
$ conan install .
$ cmake . -GNinja  # I like ninja :)
$ ninja main
$ ./bin/main
```
