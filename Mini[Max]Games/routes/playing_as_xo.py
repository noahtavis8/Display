from flask import Blueprint, render_template, request, redirect, url_for, session

playing_as_xo_bp = Blueprint("playing_as_xo", __name__, url_prefix="/playing_as_xo")

@playing_as_xo_bp.route("/", methods=["GET", "POST"])
def playing_as_xo():

    # When the user chooses to play a friend or an ai,
    if request.method == "POST":
        playing_as = request.form.get("playing_as")

        # Update session and redirect to the game page
        session["playing_as"] = playing_as
        return redirect(url_for("tictactoe.tictactoe"))
    
    # Ask the user whether they want to play against an AI or a friend
    return render_template("playing_as_xo.html")