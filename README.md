# Snowflakes

This project builds snowflakes so that Santa Clause and his elfs can focus on sending gifts to kids instead of making snowflakes.

## Requirements

The requirements are:

- CMake 3.11 or better; 3.14+ highly recommended
- A C++17 compatible compiler
- The Boost libararies
- Git
- OpenCV
- Doxygen (optional, highly recommended)

## Instructions

To configure:

```bash
cmake -S . -B build
```

Add `-GNinja` if you have Ninja.

To build:

```bash
cmake --build build
```

To test (`--target` can be written as `-t` in CMake 3.15+):

```bash
cmake --build build --target test
```

To run exe
```
./build/apps/app
```

To build and run exe
```
cmake --build build && ./build/apps/app
```

To build and test
```
cmake --build build && cmake --build build --target test
```

To build docs (requires Doxygen, output in `build/docs/html`):

```bash
cmake --build build --target docs
```

## Reference

* https://www.its.caltech.edu/~atomic/snowcrystals/class/class-old.htm
