# Tetris Game

## 1. Project Overview

This project is a console-based version of the classic Tetris game. The game allows players to control falling geometric blocks called Tetriminoes and arrange them inside a two-dimensional board. The main objective is to complete horizontal lines, clear them from the board, and continue playing until there is no space left for new blocks.

The project focuses on basic game development concepts, including matrix-based data processing, real-time keyboard input, collision detection, block movement, line clearing, and game state updates. Although the game uses a simple console interface, it still demonstrates the core logic of an interactive real-time game system.

Main features:

- Generate random Tetrimino blocks
- Move blocks left, right, and downward
- Rotate falling blocks
- Detect collisions with borders and fixed blocks
- Clear completed horizontal lines
- Update the game board continuously
- End the game when no space is available for a new block

## 2. Gameplay and Controls

The game follows the basic rules of Tetris. A block appears at the top of the board and falls automatically over time. The player can move or rotate the block before it reaches the bottom or touches another fixed block. Once the block can no longer move downward, it becomes part of the board.

If a horizontal row is completely filled, the row is removed, and the rows above it move downward. The game continues by generating new blocks until the board becomes full.

Controls:

| Key | Function |
|---|---|
| `A` / `a` | Move the block to the left |
| `D` / `d` | Move the block to the right |
| `W` / `w` | Rotate the block |
| `S` / `s` | Increase the falling speed |
| `X` / `x` | Move the block downward |
| `Q` / `q` | Quit the game |

Basic gameplay flow:

```text
Start game
Generate a new block
Receive player input
Check collision
Update block position
Fix the block when it cannot move down
Clear completed lines
Generate the next block
Repeat until game over
