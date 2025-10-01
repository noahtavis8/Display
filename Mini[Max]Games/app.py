from flask import Flask, render_template, session
from flask_session import Session
from routes import all_blueprints

# Configure application
app = Flask(__name__)

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Register each Blueprint
for blueprint in all_blueprints:
    app.register_blueprint(blueprint)


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/resources")
def resources():
    """Resources page """
    session.clear()
    session["remove_main"] = True
    return render_template("resources.html")


@app.route("/about")
def about():
    """About page """
    session.clear()
    session["remove_main"] = True
    return render_template("about.html")


@app.route("/")
def index():
    """Home page """
    session.clear()
    return render_template("index.html")


if __name__ == "__main__":
    app.run(debug=True)