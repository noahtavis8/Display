from flask import Blueprint, render_template, session

how_to_play_bp = Blueprint("how_to_play_bp", __name__, url_prefix="/how_to_play")

@how_to_play_bp.route("/", methods=["GET", "POST"])
def how_to_play():
    """Tells the user how to play"""
    game = session.get("game")
    return render_template("how_to_play.html", game=game)