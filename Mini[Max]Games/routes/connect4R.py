from flask import Blueprint, render_template, request, session, redirect, url_for
from helpers import connect4 as c4

connect4_bp = Blueprint("connect4", __name__, url_prefix="/connect4")

@connect4_bp.route("/", methods=["GET", "POST"])
def connect4():
    """Connect 4 game page"""
    session["game"] = "connect4"

    # Ask user whether they want to play against AI or a friend
    if "playing_ai" not in session:
        return redirect(url_for("ask_ai.ask_ai"))   
    playing_ai = session["playing_ai"]
    
    # I recycled tic-tac-toe logic, so players are "X" and "O". User starts
    playing_as = "X"

    # After user info gathered, remove main from layout.html (to avoid scrollbar)
    session["remove_main"] = True

    # Initialize the board if not already set
    board = session.get("board")
    if board is None:
        board = c4.initial_state()
        session["board"] = board

    player = c4.player(board)
    game_over = c4.terminal(board)
    winner = c4.winner(board)
    tie = game_over and winner is None

    if not playing_ai: 

        # User move
        if request.method == "POST":
            move = int(request.form.get("col"))

            if move in c4.actions(board):
                board = c4.result(board, move)
                session["board"] = board

                player = c4.player(board)
                game_over = c4.terminal(board)
                winner = c4.winner(board)
                tie = game_over and winner is None

            return render_template("connect4.html", 
                                   board=board, 
                                   game_over=game_over, 
                                   winner=winner, 
                                   player=player, 
                                   playing_as=playing_as,
                                   playing_ai=playing_ai,
                                   tie=tie)

    else:

        # Player move
        if player == playing_as and request.method == "POST":
            move = int(request.form.get("col"))
            if move in c4.actions(board):
                board = c4.result(board, move)
                session["board"] = board

                # Check if game is over after your move
                if c4.terminal(board):
                    return render_template("connect4.html", 
                                           board=board, 
                                           game_over=True, 
                                           winner=c4.winner(board), 
                                           player=player, 
                                           playing_as=playing_as,
                                           playing_ai=playing_ai,
                                           tie=(game_over and winner is None))

                # AI moves immediately after you
                ai_move = c4.minimax(board)
                board = c4.result(board, ai_move)
                session["board"] = board

            return render_template("connect4.html", 
                                    board=board, 
                                    game_over=c4.terminal(board),
                                    winner=c4.winner(board),
                                    player=c4.player(board),
                                    playing_as=playing_as,
                                    playing_ai=playing_ai,
                                    tie=(game_over and winner is None))
        
    return render_template("connect4.html", 
                        board=board, 
                        game_over=game_over, 
                        winner=winner, 
                        player=player, 
                        playing_as=playing_as,
                        playing_ai=playing_ai,
                        tie=tie)
    
@connect4_bp.route("/replay", methods=["GET", "POST"])
def replay():
    """Reset the game board and session variables."""
    session.pop("board", None)
    return redirect(url_for("connect4.connect4"))