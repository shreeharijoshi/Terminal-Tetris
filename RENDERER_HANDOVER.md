# Renderer Handover

## 1. Purpose and current status

This project is a C++ object-oriented Tetris implementation targeting a
Windows CLI/terminal environment. The Renderer is responsible only for
presentation. It must observe game state and display it; it must not implement
gameplay rules or mutate gameplay objects.

The Game-side integration is already prepared. The current Renderer interface
is declared in `renderer.hpp`, and `Game` owns a `Renderer` object and calls
its methods from `Game::run()`.

There is currently no `renderer.cpp`. The interface has no function
definitions yet, so the source can be compiled but the complete executable
does not link until the Renderer teammate implements these methods.

## 2. Existing Renderer interface

The current interface is:

```cpp
class gameBoard;
class Tetromino;
class Score;

class Renderer{
public:
    void render(const gameBoard& board,
                const Tetromino& activePiece,
                const Tetromino& nextPiece,
                const Score& score);

    void renderGameOver(const Score& score);

    void renderControls();
};
```

The header uses forward declarations and keeps the Renderer interface
lightweight.

### `render(...)`

```cpp
void render(const gameBoard& board,
            const Tetromino& activePiece,
            const Tetromino& nextPiece,
            const Score& score);
```

This receives the current Board, active piece, next piece, and Score by const
reference. It should read those objects and draw:

- the playfield,
- locked cells,
- the active piece,
- the next-piece preview,
- score,
- cleared lines,
- level.

It must not modify any of the arguments.

### `renderGameOver(...)`

```cpp
void renderGameOver(const Score& score);
```

This receives only the Score and is called after Game has detected game over.
It should display a game-over message and final score information. It is not
responsible for detecting game over.

Because it receives no Board or Tetromino objects, it cannot currently redraw
the final board or active/next pieces through this method.

### `renderControls()`

```cpp
void renderControls();
```

This displays the controls/instructions. Game calls it once when
`Game::run()` starts, before the loop begins.

## 3. Game integration already completed

`Game` currently owns:

```cpp
Renderer renderer;
```

`Game::run()` follows this order:

```text
initialize InputHandler
        ↓
renderControls()
        ↓
poll input
        ↓
handleAction()
        ↓
calculate elapsed time
        ↓
updateGravity()
        ↓
render current state
        ↓
repeat
        ↓
shutdown InputHandler
```

The normal render call is:

```cpp
renderer.render(board, *activePiece, *nextPiece, score);
```

It occurs after input and gravity have been processed for the iteration.

When Game reaches game over:

```text
gameOver
   ↓
renderGameOver(score) once
   ↓
remain in loop
   ↓
Quit exits the game
```

`Game::handleAction()` continues to process Quit after game over, while other
gameplay actions are ignored. `Game::updateGravity()` also stops processing
when game over is true. The Renderer implementation must not change this
lifecycle.

## 4. Renderer responsibilities

The Renderer teammate should implement terminal presentation for:

1. The 10 x 20 playfield.
2. Locked blocks.
3. The active Tetromino.
4. The next Tetromino preview.
5. Current score.
6. Total cleared lines.
7. Current level.
8. Controls and instructions.
9. Game-over message and final score.
10. Terminal redraw and clear behavior.

These are presentation concerns. Board movement, collision, locking, row
clearing, scoring, spawning, promotion, gravity, and game-over detection
remain outside Renderer.

## 5. Available read-only state

### Board APIs

`gameBoard` exposes:

```cpp
int getLength() const;
int getBreadth() const;
vector<coords> used_spaces;
coords getPivot() const;
coords toBoardCoordinate(const coords& localOffset) const;
```

Their meanings are:

- `getLength()` returns the Board height, currently `20`.
- `getBreadth()` returns the Board width, currently `10`.
- `used_spaces` contains locked cells in absolute Board coordinates.
- `getPivot()` returns P2, the Board-space position of the active piece's
  conceptual local pivot P1.
- `toBoardCoordinate()` adds the current Board pivot to a local offset.

`used_spaces` is public and can be read directly. The Renderer must not write
to it.

### Tetromino APIs

The const-safe accessor is:

```cpp
const coords* getCoords() const;
```

It returns the four existing local offsets without copying them. These offsets
are relative to the conceptual local pivot:

```text
P1 = (0, 0)
```

The Renderer must not modify the returned coordinates.

For the active piece, absolute cells can be calculated as:

```text
absolute cell = Board P2 + local offset
```

The Renderer can either perform this addition using `getPivot()` and
`getCoords()`, or call `toBoardCoordinate()` for each local offset.

The next piece has no Board placement controlled by Renderer. Its four local
coordinates are preview geometry.

### Score APIs

`Score` exposes:

```cpp
int getScore() const;
int getLines() const;
int getLevel() const;
```

Use these existing getters for display. Do not add Renderer-specific score
state.

## 6. Coordinate model

Each Tetromino stores local offsets relative to P1:

```text
P1 = (0, 0)
```

The Board stores P2, which is the Board-space position of P1:

```text
P2 = Board pivot
```

The absolute Board coordinate of a piece cell is:

```text
absolute = P2 + localOffset
```

To render the active piece:

1. Read Board P2 with `board.getPivot()`.
2. Read the four local offsets with `activePiece.getCoords()`.
3. Calculate four absolute Board cells.
4. Draw them together with `board.used_spaces`.

Renderer must not:

- modify P2,
- modify `pos[]`,
- call movement methods,
- call rotation,
- call hard drop,
- call soft drop.

Renderer only observes state.

Example:

```text
P2 = (4, 1)
local offset = (-1, 0)
absolute cell = (3, 1)
```

## 7. Next-piece preview

`nextPiece` is owned by Game but is not placed on the Board by the Renderer.
Use its local offsets as preview geometry.

The Renderer may choose a fixed visual offset or a small preview box and draw
the four local cells there. That offset is presentation-only and must not be
written back to the Tetromino or Board.

The current APIs do not provide a direct Tetromino type identifier. If future
symbols or colors need to distinguish I/J/L/O/S/Z/T, do not silently redesign
another subsystem; discuss the smallest type-identification API with the team
first. RTTI checks are possible but are not the preferred presentation
contract.

## 8. Renderer must not do

Renderer must not:

- move pieces,
- rotate pieces,
- perform gravity,
- perform hard drop,
- perform soft drop,
- lock pieces,
- clear rows,
- calculate score,
- calculate level,
- spawn pieces,
- promote pieces,
- create random pieces,
- handle keyboard input,
- decide game over,
- modify `gameBoard::used_spaces`,
- modify Board P2,
- modify Tetromino coordinates,
- modify Score,
- own the active/next Tetromino lifecycle.

The Renderer is strictly a reader and presenter.

## 9. Terminal rendering approach

The project target is CLI/terminal output. The Renderer teammate may choose an
appropriate terminal presentation method compatible with the project
environment, such as:

- ANSI escape sequences,
- a terminal library such as ncurses or PDCurses if permitted by the
  environment.

Do not add a graphical library such as raylib unless project requirements
explicitly change. Do not redesign `InputHandler` to make rendering easier.

The normal implementation boundary is:

```text
renderer.hpp   already prepared
renderer.cpp   implement the three declared methods
```

Avoid modifying unrelated files.

## 10. Frame rendering

`Game::run()` calls:

```cpp
renderer.render(board, *activePiece, *nextPiece, score);
```

on every normal loop iteration. The Renderer must therefore redraw the current
state repeatedly.

The Renderer owns presentation details such as:

- clearing or redrawing the previous frame,
- cursor handling if needed,
- borders,
- block characters,
- spacing and formatting,
- preview layout,
- score labels,
- control text.

The current Game loop has no rendering implementation to constrain the exact
visual style.

## 11. Suggested visual layout

The exact design belongs to the Renderer teammate. A possible layout is:

```text
+----------------------+
|       TETRIS         |
|                      |
|   PLAYFIELD      NEXT|
|                  +---+
|   10 x 20        |   |
|                  |   |
|                  +---+
|                      |
|                  SCORE
|                  LINES
|                  LEVEL
+----------------------+

Controls:
A/D or Left/Right : Move
S/Down             : Soft drop
W/Up               : Rotate
Space              : Hard drop
Q/Escape           : Quit
```

This is only a presentation suggestion. It does not change gameplay
architecture.

## 12. Game-over limitation

The current game-over interface is intentionally small:

```cpp
void renderGameOver(const Score& score);
```

It receives only:

```cpp
const Score& score
```

It does not receive:

- Board,
- active Tetromino,
- next Tetromino.

Therefore it should currently be treated as a game-over message and final
score display. Do not change the interface merely to redraw the final Board.
The Game integration has already been completed against this contract.

## 13. Implementation boundary

The Renderer teammate's normal implementation work should primarily be:

```text
renderer.cpp
```

The declarations in `renderer.hpp` are already prepared. If an API genuinely
appears to be missing during implementation, document the issue and discuss it
with the team before changing another subsystem.

Do not add a second game loop, input system, gravity system, scoring system,
row-clearing logic, locking logic, or spawning logic to Renderer.

## 14. Acceptance criteria

The Renderer implementation should:

- compile cleanly with the current project,
- link successfully with Game,
- draw the 10 x 20 Board,
- show locked cells,
- show the active piece at its current Board position,
- show the next-piece preview,
- display score, lines, and level,
- display controls,
- display game-over information,
- avoid mutating gameplay state,
- avoid introducing a second game loop,
- avoid introducing another input system,
- avoid introducing another gravity/timing system,
- avoid performing spawning, locking, row clearing, or scoring.

## 15. Handover summary

Game-side Renderer integration is complete. The Renderer interface is already
defined and Game already calls it. The remaining work is the terminal
presentation implementation inside Renderer.

The Renderer teammate owns the visual design and terminal-specific
implementation. The Game-side lifecycle and gameplay architecture should
remain unchanged.
