from flask import Blueprint, render_template, session

video_card_bp = Blueprint("video_card", __name__, url_prefix="/video_card")

@video_card_bp.route("/")
def video_card():
    """Video card page """
    session.clear()
    session["remove_main"] = True
    return render_template("video_card.html")