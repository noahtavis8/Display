from flask import Blueprint, render_template, request, redirect, url_for, session
from helpers import minesweeper as ms

minesweeper_bp = Blueprint("minesweeper", __name__, url_prefix="/minesweeper")


@minesweeper_bp.route("/", methods=["GET", "POST"])
def minesweeper():
    """Minesweeper game page"""

    def reveal_neighbors(cell, game, revealed, ai):
        """
        Recursively reveals all connected safe cells starting from a given cell
        """
        i, j = cell

        if cell in revealed or cell in ai.mines:
            return

        if game.is_mine(cell):
            return

        # Mark the cell as revealed
        revealed.add(cell)
        nearby = game.nearby_mines(cell)
        ai.add_knowledge(cell, nearby)

        # If there are no nearby mines, reveal all adjacent cells
        # Recursively reveales all connected safe cells
        if nearby == 0:
            for di in [-1, 0, 1]:
                for dj in [-1, 0, 1]:
                    if di == 0 and dj == 0:
                        continue
                    ni, nj = i + di, j + dj
                    if 0 <= ni < game.height and 0 <= nj < game.width:
                        neighbor = (ni, nj)
                        if neighbor not in revealed:
                            reveal_neighbors(neighbor, game, revealed, ai)

    def reset_game(difficulty):
        """
        Reset game state with given difficulty
        """
        if difficulty == "easy":
            height = 8
            width = 8 
            mines = 8
        elif difficulty == "medium":
            height = 14
            width = 18
            mines = 40
        elif difficulty == "hard":
            height = 20
            width = 24
            mines = 99
        session["board"] = ms.Minesweeper(height, width, mines)
        session["ai"] = ms.MinesweeperAI(height, width)
        session["revealed"] = []
        session["flags"] = []
        session["lost"] = False

    # Crucial: set session game type
    session["game"] = "minesweeper"

    # Ask user what difficulty they want
    if "difficulty" not in session:
        return redirect(url_for("difficulty.difficulty"))
    difficulty = session["difficulty"]

    # After user info gathered, remove main from layout.html (to avoid scrollbar)
    session["remove_main"] = True
    
    if "board" not in session:
        reset_game(difficulty)

    board = session["board"]
    ai = session["ai"]
    revealed = set(session.get("revealed", []))
    flags = set(session.get("flags", []))
    lost = session.get("lost", False)

    if request.method == "POST": 
        action = request.form["action"]

        # If user resets the game
        if action == "reset":
            reset_game(difficulty)
            return redirect(url_for("minesweeper.minesweeper"))
        
        if not lost:
            # If user asks for AI move
            if action == "ai_move":
                move = ai.make_safe_move() or ai.make_random_move()
                if move:
                    if board.is_mine(move):
                        lost = True
                    else:
                        reveal_neighbors(move, board, revealed, ai)

            # User left-clicks to reveal square
            elif action.startswith("reveal-"):
                _, cell = action.split("-", 1)
                i, j = map(int, cell.split(","))
                if (i, j) not in flags:
                    if board.is_mine((i, j)):
                        lost = True
                    else:
                        reveal_neighbors((i, j), board, revealed, ai)

            # User toggles flag for square
            elif action.startswith("flag-"):
                _, cell = action.split("-", 1)
                i, j = map(int, cell.split(","))
                if (i, j) in flags:
                    flags.remove((i, j))
                else:
                    flags.add((i, j))
            
            # Win detection
            if not lost:
                total_cells = board.height * board.width
                num_revealed = len(revealed)
                num_mines = len(board.mines)
                if num_revealed == total_cells - num_mines:
                    lost = True  # Use 'lost' to indicate game over
                    session["won"] = True
                else:
                    session["won"] = False

    session["board"] = board
    session["ai"] = ai
    session["revealed"] = list(revealed)
    session["flags"] = list(flags)
    session["lost"] = lost

    flags_left = len(board.mines) - len(flags)

    return render_template("minesweeper.html", board=board,
                        revealed=revealed, flags=flags,
                        lost=lost, difficulty=difficulty, flags_left=flags_left)



