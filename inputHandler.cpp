// Implementation of the InputHandler component.
//
// Uses _kbhit() and _getch() from <conio.h> — Windows only.
// This file ONLY maps keys to GameAction values.
// It does NOT touch gameBoard, Tetromino, or any game state.

#include "inputHandler.hpp"
#include <conio.h>   // _kbhit(), _getch()

// ---------------------------------------------------------------------------
// Windows _getch() arrow-key sequences
//
// Arrow keys on Windows send TWO bytes through _getch():
//   First byte  : 0 or 224 (0xE0)  — signals an extended / function key
//   Second byte : identifies the specific key
//
// Common second-byte values:
//   72  -> Up arrow
//   80  -> Down arrow
//   75  -> Left arrow
//   77  -> Right arrow
// ---------------------------------------------------------------------------
static const int EXTENDED_KEY_PREFIX_1 = 0;    // some keyboards
static const int EXTENDED_KEY_PREFIX_2 = 224;  // most standard keyboards (0xE0)

static const int ARROW_UP    = 72;
static const int ARROW_DOWN  = 80;
static const int ARROW_LEFT  = 75;
static const int ARROW_RIGHT = 77;

static const int KEY_ESC   = 27;
static const int KEY_SPACE = 32;

// ---------------------------------------------------------------------------
// initialize
// No special terminal setup is required when using _kbhit/_getch on Windows.
// Provided for API completeness and potential future use.
// ---------------------------------------------------------------------------
void InputHandler::initialize() {
    // Nothing to do on Windows with _kbhit/_getch.
}

// ---------------------------------------------------------------------------
// shutdown
// Mirrors initialize(); nothing to tear down on Windows.
// ---------------------------------------------------------------------------
void InputHandler::shutdown() {
    // Nothing to do on Windows with _kbhit/_getch.
}

// ---------------------------------------------------------------------------
// pollAction
//
// Step-by-step:
//   1. Call _kbhit() — returns non-zero immediately if a key is waiting in
//      the console input buffer, 0 otherwise.  This is the non-blocking gate.
//   2. If no key is waiting, return GameAction::None right away.
//   3. Call _getch() to consume the waiting key byte.
//   4. If the byte is 0 or 224, this is the FIRST byte of a two-byte arrow
//      (or function) key sequence.  Call _getch() again to read the SECOND
//      byte, which identifies the specific arrow key.
//   5. Map the byte(s) to the appropriate GameAction.
//   6. If the key is unrecognised, return GameAction::None.
// ---------------------------------------------------------------------------
GameAction InputHandler::pollAction() {

    // Step 1 & 2: non-blocking check
    if (!_kbhit()) {
        return GameAction::None;
    }

    // Step 3: read the waiting key
    int key = _getch();

    // Step 4: handle extended (arrow / function) keys
    if (key == EXTENDED_KEY_PREFIX_1 || key == EXTENDED_KEY_PREFIX_2) {

        // Read the second byte to find out which arrow key it is
        int extKey = _getch();

        switch (extKey) {
            case ARROW_LEFT:
                return GameAction::MoveLeft;

            case ARROW_RIGHT:
                return GameAction::MoveRight;

            case ARROW_DOWN:
                return GameAction::SoftDrop;

            case ARROW_UP:
                return GameAction::Rotate;

            default:
                return GameAction::None;
        }
    }

    // Step 5: handle regular character keys
    switch (key) {

        // Move left
        case 'A':
        case 'a':
            return GameAction::MoveLeft;

        // Move right
        case 'D':
        case 'd':
            return GameAction::MoveRight;

        // Soft drop
        case 'S':
        case 's':
            return GameAction::SoftDrop;

        // Rotate
        case 'W':
        case 'w':
            return GameAction::Rotate;

        // Hard drop
        case KEY_SPACE:
            return GameAction::HardDrop;

        // Restart
        case 'R':
        case 'r':
            return GameAction::Restart;

        // Quit
        case 'Q':
        case 'q':
        case KEY_ESC:
            return GameAction::Quit;

        // Unrecognised key — ignore it
        default:
            return GameAction::None;
    }
}