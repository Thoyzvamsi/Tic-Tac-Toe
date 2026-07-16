# Tic-Tac-Toe with Minimax (C++)

A console Tic-Tac-Toe game where you play against an unbeatable AI opponent.
**This project exists purely for learning C++ and the minimax algorithm** — not a polished product, a hands-on exercise in recursion, game trees, and 2D vector manipulation.

## What it does

- 3x3 board, human (`X`) vs computer (`O`).
- Human picks a cell (1-9, numbered left-to-right, top-to-bottom).
- Computer responds using **minimax**, which means it plays perfectly — it can never lose, only win or draw.

## Build & run

```bash
g++ -std=c++17 -O2 tictactoe.cpp -o tictactoe
./tictactoe
```

## How the code works

**Board representation**
`std::vector<std::vector<char>>` — a 3x3 grid of `' '`, `'X'`, `'O'`.

**Game loop (`main`)**
Alternates: human moves → check win/tie → computer moves → check win/tie. Repeats until someone wins or the board fills up.

**`winner(board)`**
Scans all 8 winning lines (3 rows, 3 columns, 2 diagonals). Returns `'X'`, `'O'`, or `'-'` (no winner yet).

**`available_spaces(board)`**
Returns every empty cell as a `Move{row, col}` — the set of legal moves from the current position.

**`minmax(board, maximizingplayer)`** — the core algorithm
This is a recursive tree search over every possible sequence of future moves:

1. **Base cases** — if the board is already a finished game, stop recursing and return a score:
   - `O` wins → `+10` (good for computer)
   - `X` wins → `-10` (bad for computer)
   - Tie → `0`

2. **Recursive case** — if the game isn't over, try every available move:
   - Place a symbol on the board (temporarily).
   - Recurse with `minmax` to see what score that leads to, assuming both sides keep playing optimally afterward.
   - Undo the move (reset the cell to `' '`) — this is critical: minimax explores the tree by mutating one shared board, so every branch must clean up after itself.
   - Keep whichever score is best for the player whose turn it is at this node.

3. **Maximizing vs minimizing** — the two players want opposite outcomes:
   - `maximizingplayer == true` → computer's turn (`'O'`). It picks the move with the **highest** score (`std::max`).
   - `maximizingplayer == false` → human's turn (`'X'`). It picks the move with the **lowest** score, i.e. assumes the human also plays optimally against the computer (`std::min`).

This is the key insight of minimax: the AI doesn't just look for its own best move — it simulates the opponent also playing their best possible move at every step, then picks the path that's best assuming worst-case (optimal) opposition.

**`computer_move(board, computer)`**
This is where minimax actually gets *used* to pick a real move:
- Tries every empty cell.
- For each, temporarily places `'O'`, calls `minmax(board, false)` (next turn belongs to the minimizing human), then undoes the move.
- Tracks whichever cell produced the highest returned score.
- Commits that cell permanently.

`minmax` itself never touches the "real" game state permanently — it only returns a *score* per hypothetical move. `computer_move` is the only place that decides an actual move, by comparing those scores.

## Learning takeaways

- Recursion + backtracking: explore a branch, then undo it before trying the next.
- Game trees: every possible future is just nested function calls.
- Zero-sum reasoning: one player's `+10` is the other's `-10` — same score, opposite goals.
- No pruning yet: this is plain minimax, exploring the *entire* game tree every move (fine for Tic-Tac-Toe's small state space). A natural next step is **alpha-beta pruning**, which skips branches that can't affect the final decision.
