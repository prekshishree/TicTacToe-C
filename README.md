
# 🎮 Tic Tac Toe | C Programming

A console-based Tic Tac Toe game built using C, featuring two game modes and three levels of computer difficulty.

## ✨ Features

- 👥 Human vs Human gameplay
- 🤖 Human vs Computer gameplay
- 🟢 Easy Mode – Random moves
- 🟡 Medium Mode – Winning and blocking strategy
- 🔴 Hard Mode – Minimax algorithm
- 🔄 Replay option
- 🛡️ Input validation
- 🏆 Win and draw detection

## 🎯 Game Modes

### Human vs Human
Two players take turns playing as X and O on the same board.

### Human vs Computer
Play against the computer with three difficulty levels:

| Difficulty | AI Strategy |
|---|---|
| Easy | Random moves |
| Medium | Tries to win or block the player |
| Hard | Uses the Minimax algorithm to choose optimal moves |

## 🧠 AI Logic

The computer uses different strategies depending on the difficulty level.

- Easy: Selects a random available position.
- Medium: Prioritises winning moves, then blocking the player's winning move, and otherwise chooses randomly.
- Hard: Uses Minimax to evaluate possible game outcomes and select the best move.

## 🖥️ Technologies Used

- C Programming Language
- GCC Compiler
- Git
- GitHub

## 🚀 How to Run

### 1. Clone the repository

```bash
git clone https://github.com/prekshishree/TicTacToe-C.git
```

### 2. Open the project folder

```bash
cd TicTacToe-C
```

### 3. Compile the program

```bash
gcc tic_tac_toe.c -o tic_tac_toe
```

### 4. Run the game

```bash
./tic_tac_toe
```

## 🎮 How to Play

- The board contains 9 positions numbered 1 to 9.
- Player X plays first.
- In Human vs Human, Player O is the second player.
- In Human vs Computer, the computer plays as O.
- Enter a position number to place your symbol.
- The first player to get three symbols in a row, column or diagonal wins.
- If all positions are occupied without a winner, the game ends in a draw.


## 👩‍💻 Developer

**Prekshi Shree**

A beginner C programming project exploring loops, functions, arrays, conditionals, input validation and AI decision-making.

---

⭐ If you like this project, consider giving it a star!
