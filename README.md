# Canopy Tetris

A **colorful Windows Tetris** built in **C++**. Pieces do not appear from nowhere: a chimpanzee sits on a **rope** (like a vine or tightrope in the scene above the play area) and **drops** them into the well. The match stays honest: **at most 3 pauses**, then game over, and **only one save** per run.

This is a course project for Object Oriented Programming. It is meant to look like a real game, not a black-and-white console homework.

**Platform:** Windows desktop app (a real window you can double-click)  
**Language:** C++  
**Graphics / window / input:** SFML  
**Board:** 10 columns × 20 rows  
**Display:** **color only** (no black-and-white theme)

> Repo folder is still named `Terminal-Tetris`. That name is leftover. The game is **not** a terminal game.

---

## What makes this different

1. **Character drop** — a monkey / chimpanzee (simple 2D art first) sits **on a rope**, not on the well. The rope is decoration in the sky / canopy area. From that rope the character drops each piece **into** the 10×20 well.
2. **Fair-play rules** — pause 3 times and the game ends. Save once; after that you can only **load**, not save again.
3. **Later uniqueness** — timed power-up challenges (clear a line in a few seconds, or lose points). Not in the first demo.

Everything on screen uses **color**: sky, frame, tiles, menus, character. Color-blind help is **stronger colors + patterns on tiles**, never grey or black-and-white.

---

## Two finish lines

| Date | What sir should see |
|---|---|
| **Wednesday 7 Oct 2026** (next class demo) | Playable windowed MVP: menu, full game, colors, pause/save rules, next piece, high scores |
| **17–18 Oct 2026** (final submission) | Better animation, character drop polish, power-up challenges, coins that last forever, extra themes/sounds |

**Hold piece** (park a piece in a side slot) is **not** in the Wednesday build. Next-piece preview **is**.

---

## Plan for today — Friday 2 Oct 2026

Today is setup day. The goal is **not** a finished Tetris tonight. The goal is: *window opens, it already looks like a color game, and tomorrow we only write rules.*

### Tonight (in order)

1. **Keep this README as the team map** — features, keys, rules, folders.
2. **Install tools on this Windows PC**
   - Visual Studio 2022 with “Desktop development with C++”, **or** VS Build Tools + CMake
   - [SFML 2.6 for Visual C++](https://www.sfml-dev.org/download/sfml/2.6.2/) (64-bit, matching your compiler)
3. **Create the window project** (`src/main.cpp` + `GameApp`)
   - 1280×720 window
   - title: Canopy Tetris
   - **colored** background (no black void)
4. **Draw a fake colorful board**
   - 10×20 well in the center
   - bright tile colors
   - side panel: score / next / pauses
   - a **rope** across the upper scene, and a simple character sitting **on that rope** (not on the well rim)
5. **Draw a home menu**
   - **Start** · **High scores** (can be empty) · **Quit**
   - keyboard: Up/Down + Enter, or mouse click if easy
6. **Confirm the share idea**
   - note which `.dll` files must sit next to the `.exe` later

### Done for today when

- You can run an `.exe` (or F5 in Visual Studio)
- You see a **color** menu and a **color** board mock
- Nothing is a black terminal

### Do **not** do tonight

- Perfect monkey animation  
- Power-ups, shop, real money  
- Mouse-dragging pieces  
- Extra tetromino shapes  
- Sound pack (add after the game is playable)

---

## Week plan (one person, best chance of “wow”)

| Day | Build |
|---|---|
| **Fri 2 Oct** | README, SFML window, color menu + fake board |
| **Sat 3 Oct** | Real 10×20 grid, 7 pieces, move, rotate, gravity, lock |
| **Sun 4 Oct** | Line clear, score, level speed-up, next piece, game over |
| **Mon 5 Oct** | High scores file, Esc pause (3 then game over), one save/load |
| **Tue 6 Oct** | Character drop pose, HUD polish, color-blind patterns, zip + DLLs, play on a second PC if you can |
| **Wed 7 Oct** | Demo: 3-minute story + let sir play one game |
| **After demo → 17 Oct** | Power-up timers, coins, shop stub, better art/sound, extra themes |

If a day slips: **never cut “you can play a full game.”** Cut save/load first, then character art.

---

## Features

### Wednesday MVP (must work)

- Home menu: **Start**, **Saved game**, **High scores**, **Color-blind on/off**, **Quit**
- Classic **7 tetrominoes** (I, O, T, L, J, S, Z)
- Each falling piece is **one color**; the next piece can be a **new** color
- Move left / right, **W** rotate, **S** soft drop, **Space** hard drop
- Line clear, score, game over
- **Next piece** preview
- **Pause:** Esc. HUD shows pauses left. **3rd pause = game over**
- **Save:** only from pause, **once** per run (`F5`). After that, save is used even if you load later
- Load from **Saved game** and continue
- High scores stored on disk
- Color graphics + simple decoration **outside** the 10×20 well
- Character **on a rope** above the play area (simple is OK). The well is only where blocks land.

### After Wednesday (final version)

- Timed power-up **challenges** (example: clear a line in 7 seconds)
  - success: pick a power-up with **mouse**, fire with **P**
  - fail: lose points
- Power-ups (examples): blast nearby cells, three single-cell “fillers”, clear bottom 3 rows
- Coins **separate from score**, kept **forever**, used in a store (themes, sounds, drop characters)
- Better drop-character animation, outside-the-well world
- Sound (menu + move + line clear + power-up)
- Extra piece types, mouse to nudge the falling piece
- Real-money shop: **not in this course project** (future idea only)

---

## How to play (MVP)

| Key | What it does |
|---|---|
| **A** or Left arrow | Move piece left |
| **D** or Right arrow | Move piece right |
| **S** or Down arrow | Soft drop (faster fall, a little extra score) |
| **W** or Up arrow | Rotate |
| **Space** | Hard drop (slam down and lock) |
| **Esc** | Pause (uses 1 of 3). Third time: **game over** |
| **F5** | Save, **only on the pause screen**, and **only once** |
| **Enter** | Confirm menu item |

### Pause and save (read this once)

- You get **3 pauses**. The screen shows how many are left.
- After the **third** Esc, there is no pause menu. The match ends.
- You may **save only once**. After you save, that run can still be **loaded** later, but you **cannot save again**.
- Save is for a real interruption, not for thinking about the next piece.

---

## Look and color

- Window about **1280×720**
- **Color everywhere:** background, well, tiles, buttons, rope, character
- The well is a **tinted** panel (not a black hole)
- A **rope** hangs in the scene **above** the well (jungle vine / tightrope). The chimpanzee **sits on the rope** and drops pieces down. It does **not** stand on the well itself.
- Decoration sits **around** the 10×20 grid; the rules still use 10×20
- **Color-blind mode:** same colorful game, plus a **pattern** on each tile (stripes, dots, hash) so pieces stay easy to tell apart

---

## How the program is built (easy architecture)

One loop, about 60 times per second:

1. Read keyboard  
2. Move / rotate / drop the piece **if the rules allow**  
3. If enough time passed, gravity pulls the piece down one cell  
4. If it cannot go down, **lock** it into the grid, **clear** full rows, **score**, spawn the **next** piece (character on the rope plays a short drop)  
5. **Draw** what is true right now  

**Important split (this is the OOP lesson):**

| Part | Job |
|---|---|
| `GameSession` + `Board` + `Tetromino` | Truth: where blocks are, score, pauses, save-used |
| `Renderer` | Only **draws**. It does not decide if a move is legal |
| `Persistence` | Writes / reads save file and high scores |
| `GameApp` | Window + which screen you are on (menu, play, pause, game over) |

Pieces use **inheritance**: one base `Tetromino`, seven child classes. A small **factory** picks a random child and a color.

The playfield is a **10×20 grid** (empty or a color id). That is simpler than a long list of points for collision, line clear, save, and drawing.

### Screens

```text
Home menu
  ├─ Start        → new match → Playing
  ├─ Saved game   → load file → Playing
  ├─ High scores  → list → back to menu
  ├─ Color-blind  → stays on menu, toggles look
  └─ Quit         → close window

Playing
  ├─ Esc (pauses left) → Pause
  ├─ Esc (no pauses left) → Game over
  └─ stack hits the top → Game over

Pause
  ├─ Resume → Playing
  ├─ Save (if not used yet) → write file, back to Playing
  └─ Quit to menu
```

---

## Scoring (MVP)

- Soft drop: **+1** per cell the piece is nudged down  
- Hard drop: **+2** per cell slammed  
- 1 line: **100 × level**  
- 2 lines: **300 × level**  
- 3 lines: **500 × level**  
- 4 lines (Tetris): **800 × level**  
- Level goes up every **10** lines; pieces fall faster  

**Score** and **coins** are different. Coins come **after** a match in the final version and stay on the profile forever. Wednesday demo can show score only.

---

## Project files (now vs next)

**Already in the repo (logic sketches):**

| File | What it is |
|---|---|
| `tetromino.hpp` / `tetromino.cpp` | 7 piece types (good OOP start) |
| `gameBoard.hpp` / `gameBoard.cpp` | 10×20 idea + random spawn (will become a real grid) |
| `renderer.hpp` | Drawing will move to SFML, not ncurses |

**Target layout:**

```text
src/
  main.cpp                 starts the app
  GameApp.cpp / .hpp       window and screens
  states/                  Menu, Play, Pause, GameOver, HighScores
  game/                    Board, pieces, factory, session (rules)
  render/                  color renderer, theme, assets
  persist/                 save + high scores
assets/
  fonts/  sprites/
data/                      created while playing (save + scores)
```

---

## Build and share (Windows)

### On your PC (development)

1. Open the Visual Studio / CMake project (added as we scaffold).  
2. Link SFML: `sfml-graphics`, `sfml-window`, `sfml-system`.  
3. Run. The working directory must see the `assets/` folder.

### Zip for a friend (no Visual Studio on their PC)

Put **one folder** on a USB / Drive:

```text
CanopyTetris/
  Tetris.exe
  sfml-graphics-2.dll
  sfml-window-2.dll
  sfml-system-2.dll
  assets/
```

They double-click `Tetris.exe`. They should **not** need to install C++.

---

## What to say in the Wednesday demo (~3 minutes)

1. “C++ windowed game with SFML. Rules and drawing are different classes.”  
2. “Seven tetromino types use inheritance. The board is a 10×20 grid.”  
3. “Novel rules: three pauses then game over, and one save so the match stays honest.”  
4. “A chimpanzee on a rope drops pieces into the well. The whole game is in color.”  
5. Hand the keyboard to sir. Let **him** play.

Then mention the next step: **timed power-up challenges**.

---

## Libraries

Extra libraries are allowed and expected. We use **SFML** because it gives a window, colors, pictures, keyboard, and later sound, in a style that still looks like C++ classes you can explain in a viva.

We do **not** use a terminal library. We do **not** put the game on a website for this course.

---

## Status

- [x] Design locked (Windows, color, SFML, fair-play pause/save)  
- [x] This README  
- [ ] Color window + menu (today)  
- [ ] Playable MVP (Wednesday)  
- [ ] Full submission (17–18 Oct)
