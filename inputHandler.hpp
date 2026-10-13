// Header file for InputHandler component
// Translates raw keyboard input into GameAction values.
// Does NOT touch gameBoard, Tetromino, or any game state.

#pragma once

// ---------------------------------------------------------------------------
// GameAction
// Represents every discrete action the player can trigger.
// The game loop reads these values and applies them to game state.
// ---------------------------------------------------------------------------
enum class GameAction {
    None,       // No key was pressed this tick
    MoveLeft,   // A / Left arrow
    MoveRight,  // D / Right arrow
    SoftDrop,   // S / Down arrow
    HardDrop,   // Space
    Rotate,     // W / Up arrow
    Restart,    // R
    Quit        // Q / ESC
};

// ---------------------------------------------------------------------------
// InputHandler
// Non-blocking keyboard reader using <conio.h> (_kbhit / _getch).
// Windows-only; no ncurses or termios required.
//
// Typical usage in a game loop:
//
//   InputHandler input;
//   input.initialize();
//
//   while (running) {
//       GameAction action = input.pollAction();
//       // ... apply action to game state ...
//   }
//
//   input.shutdown();
// ---------------------------------------------------------------------------
class InputHandler {
public:
    // Call once before the game loop starts.
    // On Windows with _kbhit/_getch no special setup is needed,
    // but initialize() is provided for API completeness and future use.
    void initialize();

    // Call once after the game loop ends.
    // Mirrors initialize(); safe to call even if nothing was set up.
    void shutdown();

    // Non-blocking poll: returns the GameAction for the key currently
    // pressed, or GameAction::None if no key is waiting.
    // Must be called every game tick.
    GameAction pollAction();
};