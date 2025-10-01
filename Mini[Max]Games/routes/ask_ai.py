from flask import Blueprint, render_template, request, redirect, url_for, session

ask_ai_bp = Blueprint("ask_ai", __name__, url_prefix="/ask_ai")

@ask_ai_bp.route("/", methods=["GET", "POST"])
def ask_ai():
    """Ask user if they want to play against AI or a friend"""
    # When the user chooses to play a friend or an ai,
    if request.method == "POST":
        game = session.get("game")
        playing_ai = request.form.get("playing_ai", "true").lower() == "true"

        # Update session and redirect to the game page
        session["playing_ai"] = playing_ai
        return redirect(url_for(game + "." + game))
    
    # Ask the user whether they want to play against an AI or a friend
    return render_template("ask_ai.html")