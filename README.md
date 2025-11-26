# Entropy
A game and game framework written in C++. Currently a work in progress, end goal is to have a functional game called Entropy.

Can also be used a template for your own games!

## Build

### Linux

To build this project on Linux-based system, the following dependencies are required:
```
git cmake make
```

In addition, you will need a C/C++ compiler. The suggested one is `clang`/`clang++`.

You will also need the dependencies for SDL as defined [here](https://github.com/libsdl-org/SDL/blob/main/docs/README-linux.md#build-dependencies).

Clone the repository:
```bash
git clone --recurse-submodules https://github.com/Xtendera/Entropy && cd Entropy
```

Configure CMake:
```bash
mkdir build && cd build
CC=clang CXX=clang++ cmake..
```

Finally, build the project with make:
```bash
make -j$(nproc)
```

Run the game:
```bash
./entropy
```

## Credits

This project uses the SDL3 library (including subcomponents such as SDL3_image, and SDL3_ttf) and CMake.
