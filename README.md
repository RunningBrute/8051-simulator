# 8051 Simulator

[![Build Linux](https://github.com/RunningBrute/8051-simulator/actions/workflows/build-linux.yml/badge.svg)](https://github.com/RunningBrute/8051-simulator/actions/workflows/build-linux.yml)
[![Build Windows](https://github.com/RunningBrute/8051-simulator/actions/workflows/build-windows.yml/badge.svg)](https://github.com/RunningBrute/8051-simulator/actions/workflows/build-windows.yml)
[![Test Linux](https://github.com/RunningBrute/8051-simulator/actions/workflows/test-linux.yml/badge.svg)](https://github.com/RunningBrute/8051-simulator/actions/workflows/test-linux.yml)
[![Test Windows](https://github.com/RunningBrute/8051-simulator/actions/workflows/test-windows.yml/badge.svg)](https://github.com/RunningBrute/8051-simulator/actions/workflows/test-windows.yml)

A minimal Intel 8051 microcontroller simulator focusing on CPU state modeling and instruction-level execution.  
The project emulates the 8051 architecture at the register and instruction level, with an emphasis on deterministic behavior and clear separation of hardware responsibilities.

---

## 🚀 Features (in progress)

- 🧩 Modular design (C++23 modules)
- ⚙️ Emulated CPU core with registers
- 💻 Cross-platform: Windows & Linux
- 🧪 Unit tests powered by Catch2
- 🧱 Modern CMake + GitHub Actions CI

---

## 🛠️ Build Instructions

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
cmake --build build
```

### Run

```bash
./build/Debug/8051-simulator examples\\test.asm
```

### Run tests

```bash
./build/Debug/8051-simulator-tests
```

### Run Linux CI locally with act

You can reproduce GitHub Actions locally using act

Install on Windows (PowerShell, run as Administrator)
```bash
choco install act-cli -y
```

Download the compatible image
```bash
act pull catthehacker/ubuntu:act-22.04
```

Run Linux build or tests locally
```bash
act -j build-linux -P ubuntu-latest=ghcr.io/catthehacker/ubuntu:full-latest
act -j test-linux -P ubuntu-latest=ghcr.io/catthehacker/ubuntu:full-latest
```

Speed up re-runs with cache reuse
```bash
act -j build-linux --reuse
```

---

## ℹ️ About

This project is a learning-oriented Intel 8051 emulator written in modern C++23.  
It uses C++ modules to model individual hardware blocks such as the CPU core and memory, focusing on instruction decoding, state transitions and deterministic execution.

The scope is intentionally limited to the CPU core to keep the architecture explicit and easy to reason about, making the project suitable for exploring system-level design trade-offs in CPU emulation.

## 🧑‍💻 Author

RunningBrute
https://github.com/RunningBrute


## 📜 License

MIT License © 2025 RunningBrute