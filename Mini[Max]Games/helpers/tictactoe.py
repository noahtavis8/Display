"""
Tic Tac Toe Player
"""

import math
import random

X = "X"
O = "O"
EMPTY = None


def initial_state():
    """
    Returns starting state of the board.
    """
    return [[EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY]]


def player(board):
    """
    Returns player who has the next turn on a board.
    """
    if terminal(board):
        return EMPTY

    x_count = 0
    o_count = 0

    # Count the number of Xs and Os on the board
    for row in board:
        for spot in row:
            if spot == X:
                x_count += 1
            elif spot == O:
                o_count += 1

    # If there are the same number of Xs and Os, its Xs turn
    if o_count == x_count:
        return X
    else:
        return O


def actions(board):
    """
    Returns set of all possible actions (i, j) available on the board.
    """

    if terminal(board):
        return EMPTY

    # Iterate over every spot (i, j). If current spot is empty, its a valid action.
    actions = set()

    for i in range(3):
        for j in range(3):
            if board[i][j] == EMPTY:
                actions.add((i, j))

    return actions


def result(board, action):
    """
    Returns the board that results from making move (i, j) on the board.
    """

    i, j = action

    if i not in range(3) or j not in range(3):
        raise Exception

    if board[i][j] != EMPTY:
        raise Exception

    new_board = [row[:] for row in board]
    new_board[i][j] = player(board)

    return new_board


def winner(board):
    """
    Returns the winner of the game, if there is one.
    """

    # Check rows
    for row in range(3):
        if board[row][0] == board[row][1] == board[row][2] != EMPTY:
            return board[row][0]

    # Check columns
    for col in range(3):
        if board[0][col] == board[1][col] == board[2][col] != EMPTY:
            return board[0][col]

    # Check left-right diagonal
    if board[0][0] == board[1][1] == board[2][2] != EMPTY:
        return board[0][0]

    # Check other diagonal
    if board[0][2] == board[1][1] == board[2][0] != EMPTY:
        return board[0][2]

    # No winner
    return None


def terminal(board):
    """
    Returns True if game is over, False otherwise.
    """

    if winner(board) is not None:
        return True

    for row in board:
        for spot in row:
            if spot == EMPTY:
                return False

    return True


def utility(board):
    """
    Returns 1 if X has won the game, -1 if O has won, 0 otherwise.
    """
    winning_player = winner(board)

    if winning_player == X:
        return 1
    elif winning_player == O:
        return -1

    return 0

def max_value(board, alpha, beta):
    if terminal(board):
        return utility(board)
    v = -math.inf
    for action in actions(board):
        v = max(v, min_value(result(board, action), alpha, beta))
        alpha = max(alpha, v)
        if beta <= alpha:
            break
    return v


def min_value(board, alpha, beta):
    if terminal(board):
        return utility(board)
    v = math.inf
    for action in actions(board):
        v = min(v, max_value(result(board, action), alpha, beta))
        beta = min(beta, v)
        if beta <= alpha:
            break
    return v

def minimax(board):
    """
    Returns the optimal action for the current player on the board.
    """
    # If the game is already over, return None
    if terminal(board):
        return None

    current = player(board)
    valid_moves = actions(board)
    best_score = -math.inf if current == X else math.inf
    best_actions = []

    for action in valid_moves:
        next_board = result(board, action)
        score = min_value(next_board, -math.inf, math.inf) if current == X \
            else max_value(next_board, -math.inf, math.inf)

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
