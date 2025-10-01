from flask import Blueprint, render_template, request, redirect, url_for, session

get_training_games_bp = Blueprint("get_training_games", __name__, url_prefix="/get_training_games")

@get_training_games_bp.route("/", methods=["GET", "POST"])
def get_training_games():
    """Ask user how many games they want to train the AI with"""

    if request.method == "POST":
        # Ensure bot knowledge is reset when re-training
        session.pop("nim-q", None)
        session.pop("connect4-q", None)
        game = session.get("game")
        
        # Gather and validate the number of training games
        try:
            training_games = int(request.form.get("training_games"))
            if training_games < 0 or training_games > 10000:
                training_games = 1000  # Default value if input is invalid
        except ValueError:
            training_games = 1000

        # Update session and redirect to the game page
        session["training_games"] = training_games
        return redirect(url_for(game + "." + game))
    
    # Ask the user how many games they want to train the AI with
    return render_template("get_training_games.html")