# 8051 Simulator

A basic **Intel 8051 microcontroller simulator**. This project aims to emulate
the 8051 CPU architecture at the register and instruction level — purely in software,
just for fun and educational purposes.

---

## Features (in progress)

- Modular design
- Emulated CPU core with registers
- Simple memory and I/O model
- Cross-platform (Windows & Linux)
- Unit tests via Catch2

---

## How to build

### Install Conan

```bash
pip install conan
```

### Install dependencies

```bash
conan install . --output-folder=build --build=missing
```

### Configure and build

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug
# The project uses C++23 standard (modules supported)
cmake --build build
```

### Run

```bash
./build/Debug/8051-simulator
```

### Run tests

```bash
./build/Debug/8051-simulator-tests
```

---

## About

This project is a learning-oriented 8051 emulator written in modern C++23,
leveraging modules to represent each hardware block (CPU, Memory, IO).
The ultimate goal is to create a real, byte-accurate simulation of the original Intel 8051.
