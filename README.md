# Handmade Game in C and X11

## About
This project is my personal follow-along of [**Handmade Hero**](https://youtube.com/playlist?list=PLnuhp3Xd9PYTt6svyQPyRO_AAuMWGxPzU&si=JGpl7qMlpWR0ufVa), but adapted for **Linux + X11**.  
The goal is to master:
- **C programming** (low-level memory, structs, pointers, compilation)
- **X11 programming** (creating windows, handling input, drawing pixels)
- **Game development fundamentals** (software rendering, input loop, timing, etc.)

This is not a clone of Handmade Hero, but a learning journey where I build the engine and game **from scratch**.

---

## Features (as I build them)
- Open a window with X11
- Event loop for keyboard + mouse input
- Software rendering with `XPutImage`
- Fixed timestep game loop
- (Later) sound, assets, and gameplay

---

## Requirements
- Linux
- C compiler (`gcc` or `clang`)
- X11 development headers
  - Ubuntu/Debian: `sudo apt-get install libx11-dev`
  - Arch: `sudo pacman -S libx11`
---

## Build
```bash
git clone https://github.com/rivado-e/heroquest.git
cd heroquest
make
./game

