from flask import Blueprint, render_template, request, redirect, url_for, session

difficulty_bp = Blueprint("difficulty", __name__, url_prefix="/difficulty")

@difficulty_bp.route("/", methods=["GET", "POST"])
def difficulty():
    """Ask user if they want to play against AI or a friend"""
    # When the user chooses a difficulty level,
    if request.method == "POST":
        game = session.get("game")
        valid_difficulties = ["easy", "medium", "hard"]

        # Gather the difficulty level from the form
        difficulty = request.form.get("difficulty", "easy").lower()

        # Validate and default, then pass to session
        if difficulty in valid_difficulties:
            session["difficulty"] = difficulty
        else:
            session["difficulty"] = "easy"

        return redirect(url_for(game + "." + game))
    
    # Ask the user whether they want to play against an AI or a friend
    return render_template("difficulty.html")