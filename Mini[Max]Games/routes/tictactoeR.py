from flask import Blueprint, render_template, request, redirect, url_for, session
from helpers import tictactoe as ttt

tictactoe_bp = Blueprint("tictactoe", __name__, url_prefix="/tictactoe")

@tictactoe_bp.route("/", methods=["GET", "POST"])
def tictactoe():
    """Tic Tac Toe game page"""
    # Crucial: set session game type (for reuse of ask_ai and such)
    session["game"] = "tictactoe"

    # Ask user whether they want to play against AI or a friend
    if "playing_ai" not in session:
        return redirect(url_for("ask_ai.ask_ai"))
    playing_ai = session.get("playing_ai")
    
    # Gather user's choice of playing as X or O
    if playing_ai:
        if "playing_as" not in session:
            return redirect(url_for("playing_as_xo.playing_as_xo"))
        playing_as = session.get("playing_as")
    
    # After user info gathered, remove main from layout.html (to avoid scrollbar)
    session["remove_main"] = True

    # Initialize the board if not already set
    board = session.get("board")
    if board is None:
        board = ttt.initial_state()
        session["board"] = board

    # FRIENDS MODE
    if not playing_ai:

        # When the user clicks a square
        if request.method == "POST":
            # Gather the move, validate, and update the board
            move = tuple(map(int, request.form.get("move").split(",")))
            if move in ttt.actions(board):
                board = ttt.result(board, move)
                session["board"] = board
            return redirect(url_for("tictactoe.tictactoe"))

        # Get the current player and check if the game is over
        player = ttt.player(board)
        game_over = ttt.terminal(board)
        winner = ttt.winner(board)

        if game_over:
            session.pop("board", None)

        return render_template("tictactoe.html", board=board, game_over=game_over, winner=winner, player=player)

    # AI MODE
    else:

        game_over = ttt.terminal(board)
        winner = ttt.winner(board)
        up_next = ttt.player(board)

        if game_over:
            session.pop("board", None)
            return render_template("tictactoe.html", board=board, game_over=game_over, winner=winner)

        # Player move
        if up_next.lower() == playing_as:
            if request.method == "POST":
                move = tuple(map(int, request.form.get("move").split(",")))
                if move in ttt.actions(board):
                    board = ttt.result(board, move)
                    session["board"] = board
                return redirect(url_for("tictactoe.tictactoe"))

        # AI move
        elif request.method == "GET":
            move = ttt.minimax(board)
            board = ttt.result(board, move)
            session["board"] = board
            return redirect(url_for("tictactoe.tictactoe"))

        return render_template("tictactoe.html", board=board, player=up_next)
        