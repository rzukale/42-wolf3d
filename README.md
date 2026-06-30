# 42-wolf3d
Introduction to Ray-casting using SDL2 library

Prerequisites & Installation

This project compiles using standard `make` and relies on system-wide development libraries. Before compiling, you must install the C compiler toolchain, the SDL2 library, and utility mapping packages.

Open your terminal and run the following commands to install all required dependencies:

```bash
# 1. Update your system package index
sudo apt update

# 2. Install the foundational compilation tools (gcc, make)
sudo apt install build-essential

# 3. Install the SDL2 development package and pkg-config utility
sudo apt install libsdl2-dev pkg-config
```

### Compiling the Project

Once the dependencies are installed, you can clean, build, and launch the project using the provided Makefile:

```bash
# Clean previous build artifacts and compile the binary
make re

# Launch the executable
./wolf3d
```


Tested on Linux (Ubuntu)
