from flask import Blueprint, render_template, request, session, redirect, url_for
from helpers import nim as nm

nim_bp = Blueprint("nim", __name__, url_prefix="/nim")


@nim_bp.route("/", methods=["GET", "POST"])
def nim():
    """Nim game page"""
    session["game"] = "nim"

    # Ask user whether they want to play against AI or a friend
    if "playing_ai" not in session:
        return redirect(url_for("ask_ai.ask_ai"))
    playing_ai = session["playing_ai"]

    # If playing against AI, 
    ai = None
    if playing_ai:

        # If we haven't asked the user how many games to train on, gather that info
        if "training_games" not in session:
            return redirect(url_for("get_training_games.get_training_games"))
        training_games = session["training_games"]

        # If we haven't trained the AI yet, train it
        if "nim-q" not in session:
            ai = nm.train(training_games)
            session["nim-q"] = ai.q

        # If we have trained the AI, load its knowledgebase
        else:
            ai = nm.NimAI()
            ai.q = session["nim-q"]

    # After user info gathered, remove main from layout.html (to avoid scrollbar)
    session["remove_main"] = True

    # Game setup
    if "nim_game" not in session:
        session["nim_game"] = [1, 3, 5, 7]
        session["player"] = 0
        session["winner"] = None

    piles = session["nim_game"]
    player = session["player"]

    error = None

    # User move
    if request.method == "POST":
        pile = int(request.form["pile"])
        count = int(request.form["count"])

        # Attempt to make a move
        try:
            game = nm.Nim(piles)
            game.player = player
            game.move((pile, count))
            session["nim_game"] = game.piles
            session["player"] = game.player
            session["winner"] = game.winner
        except Exception as e:
            error = str(e)

    # AI move if it's AI's turn
    if session["winner"] is None and playing_ai and session["player"] == 1:
        game = nm.Nim(session["nim_game"])
        game.player = session["player"]
        action = ai.choose_action(game.piles, epsilon=False)
        game.move(action)
        session["nim_game"] = game.piles
        session["player"] = game.player
        session["winner"] = game.winner

    return render_template("nim.html",
                           piles=session["nim_game"],
                           player=session["player"],
                           winner=session["winner"],
                           playing_ai=playing_ai,
                           error=error)

@nim_bp.route("/replay", methods=["GET", "POST"])
def replay():
    """Reset the Nim game"""
    session.pop("nim_game", None)
    session.pop("player", None)
    session.pop("winner", None)
    return redirect(url_for("nim.nim"))