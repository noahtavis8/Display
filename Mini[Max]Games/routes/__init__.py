from flask import Blueprint

# Import route modules
from .tictactoeR import tictactoe_bp
from .minesweeperR import minesweeper_bp
from .nimR import nim_bp
from .connect4R import connect4_bp
from .ask_ai import ask_ai_bp
from .playing_as_xo import playing_as_xo_bp
from .difficulty import difficulty_bp
from .get_training_games import get_training_games_bp
from .how_to_play import how_to_play_bp
from .video_card import video_card_bp

# List of all blueprints to register in app.py
all_blueprints = [tictactoe_bp, 
                    minesweeper_bp,
                    nim_bp,
                    connect4_bp, 
                    ask_ai_bp,
                    playing_as_xo_bp, 
                    difficulty_bp,
                    get_training_games_bp,
                    how_to_play_bp, 
                    video_card_bp]