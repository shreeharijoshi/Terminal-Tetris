# Terminal-Tetris

## Overview
A console‑based Tetris clone implemented in C++ as part of the OOP coursework. The current version runs in a terminal using simple ASCII graphics.

## Rendering Refactor Roadmap

### 1️⃣ Current State
- **Model layer** (`gameBoard`, `Tetromino`) – fully functional.
- **Renderer interface** (`renderer.hpp`) – declared but not implemented.
- No external graphics library, assets, or rendering implementation.

### 2️⃣ What’s Needed
- Choose a graphics library (SDL2 or SFML) and add it to the build system.
- Implement `renderer.cpp` (window creation, drawing, double‑buffering).
- Add an `assets/` folder with sprite PNGs.
- Update CMake/VS project to link against the graphics library.
- Optional: introduce an abstract `IRenderer` for clean swapping.

### 3️⃣ Phase‑wise Plan
| Phase | Tasks | Deliverable |
|------|-------|-------------|
| A. Scope & Library Choice | Evaluate SDL2 vs SFML, decide asset format | Decision doc |
| B. Project Bootstrap | Add library to build, create placeholder assets | Buildable skeleton with blank window |
| C. Renderer Implementation | Write `renderer.cpp` (`init`, `drawBoard`, `clearRow`, `present`) | Working `GraphicsRenderer` |
| D. Refactor Game Loop | Inject `Renderer*` into main loop, replace ncurses calls | Decoupled logic |
| E. Performance Optimisations | Double buffering, texture caching, frame‑rate cap | Smooth 60 FPS |
| F. Polish & Assets | Replace placeholders with real sprites, UI overlay | Fully visual Tetris |
| G. Docs & Tests | Update README, add basic test for renderer | Documentation + test |
| H. Release | Build Release binary, package assets | Distributable package |

### 4️⃣ Checklist
- [ ] Install graphics library (SDL2/SFML) via vcpkg or conan.
- [ ] Create `renderer.cpp`.
- [ ] Add `assets/` with tetromino PNGs.
- [ ] Update CMakeLists.txt (link library, copy assets).
- [ ] Implement double buffering.
- [ ] Optional: add `IRenderer` abstraction.
- [ ] Update README (this file) and write unit test.

### 5️⃣ Quick‑Start (SDL2 example)
```sh
# From project root
.\\vcpkg install sdl2
# Add to CMakeLists.txt:
# find_package(SDL2 CONFIG REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2)
mkdir assets && echo "Add PNGs here"
```

---

**Happy coding!** 🚀
_The roadmap will guide you from the current console version to a modern, efficient graphics‑based renderer while keeping the existing class structure intact._
