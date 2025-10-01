import math
import random

ROWS = 6
COLS = 7
X = "X"
O = "O"
EMPTY = None
MAX_DEPTH = 4

# This is a minimax algorithm for connect four. I adapted it from the 
# minimax logic for tic tac toe, but I made some adjustments and
# improvements. I added depth limiting and alpha-beta pruning to to
# this bot, and to do so, I added a more in-depth board evaluation 
# strategy, prioritizing pieces in a row and center column control.


def initial_state():
    """
    Returns starting state of the board.
    """
    return [[EMPTY for _ in range(COLS)] for _ in range(ROWS)]


def player(board):
    """
    Returns player who has the next turn on a board.
    """
    x_count = sum(row.count(X) for row in board)
    o_count = sum(row.count(O) for row in board)
    return X if x_count == o_count else O


def actions(board):
    """
    Returns set of all possible actions (i, j) available on the board.
    """
    return [col for col in range(COLS) if board[0][col] == EMPTY]


def result(board, action):
    """
    Returns the board that results from making move "col" on the board.
    """
    col = action
    new_board = [row[:] for row in board]
    for row in reversed(range(ROWS)):
        if new_board[row][col] == EMPTY:
            new_board[row][col] = player(board)
            return new_board
    raise Exception("Invalid move")


def winner(board):
    """
    Returns the winner of the game, if there is one.
    """
    for row in range(ROWS):
        for col in range(COLS):
            piece = board[row][col]
            if piece is None:
                continue

            # Horizontal
            if col <= COLS - 4 and all(board[row][col + i] == piece for i in range(4)):
                return piece

            # Vertical
            if row <= ROWS - 4 and all(board[row + i][col] == piece for i in range(4)):
                return piece

            # Diagonal down-right
            if row <= ROWS - 4 and col <= COLS - 4 and all(board[row + i][col + i] == piece for i in range(4)):
                return piece

            # Diagonal up-right
            if row >= 3 and col <= COLS - 4 and all(board[row - i][col + i] == piece for i in range(4)):
                return piece
    return None


def terminal(board):
    """
    Returns True if game is over, False otherwise.
    """
    return winner(board) is not None or all(board[0][col] != EMPTY for col in range(COLS))


def utility(board):
    """
    Returns 1,000,000 if X has won the game, -1,000,000 if O has won, 
    0 otherwise.
    """
    win = winner(board)
    if win == X:
        return 1_000_000
    elif win == O:
        return -1_000_000
    return 0


def score_window(window, piece):
    """
    Returns reward for having different numbers of pieces in a row,
    given a line on the board as the window and a piece ("X" or "O") to
    check for
    """
    opp = O if piece == X else X
    score = 0
    if window.count(piece) == 4:
        score += 100
    elif window.count(piece) == 3 and window.count(EMPTY) == 1:
        score += 5
    elif window.count(piece) == 2 and window.count(EMPTY) == 2:
        score += 2
    if window.count(opp) == 3 and window.count(EMPTY) == 1:
        score -= 4
    return score


def evaluate_board(board, piece):
    """
    Evalutates the board. 

    Checks every row and column for the number of pieces in a row. 

    Score gets added to when the bot has pieces in a row or pieces in
    the center column.

    Score gets subtracted from when the opponent has 3 pieces in a
    row. 
    """
    score = 0

    # Center column preference
    center = [board[r][COLS // 2] for r in range(ROWS)]
    score += center.count(piece) * 3

    # Score horizontal
    for row in range(ROWS):
        for col in range(COLS - 3):
            window = [board[row][col + i] for i in range(4)]
            score += score_window(window, piece)

    # Score vertical
    for col in range(COLS):
        for row in range(ROWS - 3):
            window = [board[row + i][col] for i in range(4)]
            score += score_window(window, piece)

    # Score diagonal down-right
    for row in range(ROWS - 3):
        for col in range(COLS - 3):
            window = [board[row + i][col + i] for i in range(4)]
            score += score_window(window, piece)

    # Score diagonal up-right
    for row in range(3, ROWS):
        for col in range(COLS - 3):
            window = [board[row - i][col + i] for i in range(4)]
            score += score_window(window, piece)

    return score


def max_value(board, depth, alpha, beta):
    if terminal(board) or depth == 0:
        return utility(board) if terminal(board) else evaluate_board(board, X)
    v = -math.inf
    for action in actions(board):
        v = max(v, min_value(result(board, action), depth - 1, alpha, beta))
        alpha = max(alpha, v)
        if beta <= alpha:
            break
    return v


def min_value(board, depth, alpha, beta):
    if terminal(board) or depth == 0:
        return utility(board) if terminal(board) else evaluate_board(board, O)
    v = math.inf
    for action in actions(board):
        v = min(v, max_value(result(board, action), depth - 1, alpha, beta))
        beta = min(beta, v)
        if beta <= alpha:
            break
    return v


def minimax(board):
    """
    Returns the optimal action for the current player on the board.
    """
    if terminal(board):
        return None

    current = player(board)
    valid_moves = actions(board)
    best_score = -math.inf if current == X else math.inf
    best_actions = []

    for action in valid_moves:
        next_board = result(board, action)
        score = min_value(next_board, MAX_DEPTH - 1, -math.inf, math.inf) if current == X \
            else max_value(next_board, MAX_DEPTH - 1, -math.inf, math.inf)

        # MAX player (X)
        if current == X:
            if score > best_score:
                best_score = score
                best_actions = [action]
            elif score == best_score:
                best_actions.append(action)

        # MIN player (O)
        else:
            if score < best_score:
                best_score = score
                best_actions = [action]
            elif score == best_score:
                best_actions.append(action)

    return random.choice(best_actions)
