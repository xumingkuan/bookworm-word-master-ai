# Bookworm Word Master AI

## Overview

Bookworm Word Master AI is a program that can play the mini-game [*Word Master*](https://bookwormadvs.fandom.com/wiki/Word_Master) in the game [*Bookworm Adventures*](https://en.wikipedia.org/wiki/Bookworm_Adventures) (either Vol.1 or Vol.2) infinitely.

It should also be able to play [*Wordle*](https://www.powerlanguage.co.uk/wordle/) with a 100% winning rate after some small modifications, but I haven't got time to implement it yet -- contribution welcomed!

## How to Run (Play)

1. Simply download the release package (or build from scratch in the following section).
   - Make sure all files are in the same folder, and preferably do not put any other files in this folder.
   - The release package only works with 64-bit Windows systems. If you are using a 32-bit Windows system, please build from scratch in the next section.
2. Open the mini-game *Word Master* in the game *Bookworm Adventures*, and choose not to display "helpful tooltips" when popped out.
3. Run `bookworm_ai.exe`, and enter how many words you would like to guess in the game. You can enter `-1` to play infinitely, or enter a small number (the number must not exceed 9,223,372,036,854,775,807) to let the game end in a reasonable time.
   - When running the program for the first time or when the colors of some pixels changes (e.g., the game window is dragged), the program needs to initialize the colors of all initial letters. This should take less than 1 minute.
4. If you want to terminate the program, press and hold `Esc` until the mouse is not moving on its own. Then close the command prompt of `bookworm_ai.exe`.
   - All processes related to the Bookworm Word Master AI should be terminated in 30 seconds. Please wait at least 30 seconds to run the program again.
   - If the program guessed as many words as you entered in the previous step, all processes related to the program will be terminated immediately, and you do not need to wait to run the program again.
6. Note that the high score will not be saved by the game *Bookworm Adventures* unless there are 5 wrong guesses to a word. If you want to save your score, please make wrong guesses manually to end the game.

## How to Build

1. Make sure you have g++ and [AutoHotkey](https://github.com/Lexikos/AutoHotkey_L) on Windows. This program only supports Windows platform.
2. Find `AutoHotkey.exe` in the installation directory of AutoHotkey, copy it to the same directory as the `.ahk` files here, and rename it to `ahk.exe`.
3. Run `g++.exe bookworm_ai.cpp bookworm_ai_impl.cpp ahk_interactions.cpp --std=c++17 -o bookworm_ai.exe -O3`.

