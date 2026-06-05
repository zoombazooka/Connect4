from Board import Board
import time
import random

class Player:
    def __init__(self, name, symbol):
        self.symbol = symbol
        self.name = name

    def get_move(self, board: Board):
        raise NotImplementedError("must implement get_move method!")

class HumanPlayer(Player):
    def get_move(self, board: Board):
        while True:
            try:
                player_col = int(input("please input the col index (0-6):"))
            except ValueError:
                print("invalid input! please only input numbers!")
            else:
                return player_col


class AI(Player):
    def __init__(self, name, symbol, level, opp_symbol):
        super().__init__(name, symbol)
        self.level = level
        self.opp_symbol = opp_symbol


    def get_move(self, board: Board):
        # possible_cols = [col for col in range(board.maxCol + 1) if not board.is_col_full(col)]
        # # winning
        # for col in possible_cols:
        #     piece_pos = board.place_piece(col, self.symbol)
        #     if board.is_4_in_a_row(piece_pos, self.symbol):
        #         print("I Win!")
        #         board.remove_piece(piece_pos)
        #         return col1
        #     board.remove_piece(piece_pos)
        #
        # # blocking
        # for col in possible_cols:
        #     piece_pos = board.place_piece(col, self.opp_symbol)
        #     if board.is_4_in_a_row(piece_pos, self.opp_symbol):
        #         print("Blocked!")
        #         board.remove_piece(piece_pos)
        #         return col
        #     board.remove_piece(piece_pos)
        start_time = time.time()

        possible_cols = [col for col in range(board.maxCol + 1) if not board.is_col_full(col)]
        highest_score = -1000000
        best_col = -1
        alpha = -1000000
        beta = 1000000
        for col in possible_cols:
            pos = board.place_piece(col, self.symbol)
            score = self.minimax(board, is_maxing=False, depth=0, max_depth=4, last_pos=pos, alpha=alpha, beta=beta)
            board.remove_piece(pos)
            if score > highest_score:
                highest_score = score
                best_col = col
            alpha = max(alpha, score)

        end_time = time.time()
        time_taken = end_time - start_time

        print(f"{self.name} chose column {best_col} in {time_taken:.5f} seconds!\n")
        return best_col


        # heu_move = self.get_heuristic_move(board)
        # if heu_move != -1:
        #     return heu_move
        # return self.get_random_move(board)


    def get_random_move(self, board: Board):
        possible_moves = [col for col in range(board.maxCol + 1) if not board.is_col_full(col)]
        move = random.choice(possible_moves)
        return move


    def score_window(self, window):
        my_pieceC = 0
        opp_pieceC = 0
        if self.symbol in window and self.opp_symbol in window:
            return 0
        for piece in window:
            if piece == self.symbol:
                my_pieceC += 1
            elif piece == self.opp_symbol:
                opp_pieceC += 1
        if my_pieceC == 4:
            return 10000
        if opp_pieceC == 4:
            return -10000
        return (my_pieceC ** 2) - (opp_pieceC ** 2)

    def score_board(self, board: Board):
        directions = {
            "up": (1, 0),
            "right": (0, 1),
            "down right": (-1, 1),
            "up right": (1, 1)
        }


        current_score = 0
        if board.is_board_full():
            return 0
        for row in range(board.maxRow + 1):
            for col in range(board.maxCol + 1):
                for direction in directions.values():
                    window = board.get_window((row, col), direction)
                    if not window:
                        continue
                    current_score += self.score_window(window)

        return current_score

    def get_heuristic_move(self, board: Board):
        highest_score = - 100000
        best_col = 0
        for col in range(board.maxCol + 1):
            if board.is_col_full(col):
                continue
            placed_pos = board.place_piece(col, self.symbol)
            score = self.score_board(board)
            board.remove_piece(placed_pos)
            if score > highest_score:
                highest_score = score
                best_col = col
        print(highest_score)
        print(best_col)
        return best_col

    def minimax(self, board: Board, is_maxing, depth, max_depth, last_pos, alpha, beta):

        if board.is_4_in_a_row(last_pos, self.symbol):
            return 100000 - depth
        if board.is_4_in_a_row(last_pos, self.opp_symbol):
            return -100000 + depth
        if depth == max_depth or board.is_board_full():
            return self.score_board(board)

        highest_score = -1000000
        lowest_score = 1000000
        possible_cols = [col for col in range(board.maxCol + 1) if not board.is_col_full(col)]
        if is_maxing:
            for col in possible_cols:
                pos = board.place_piece(col, self.symbol)
                score = self.minimax(board, is_maxing=False, depth=(depth + 1), max_depth=max_depth, last_pos=pos, alpha=alpha, beta=beta)
                board.remove_piece(pos)
                highest_score = max(highest_score, score)
                if highest_score >= beta:
                    break
                else:
                    alpha = max(highest_score, alpha)


        elif not is_maxing:
            for col in possible_cols:
                pos = board.place_piece(col, self.opp_symbol)
                score = self.minimax(board, is_maxing=True, depth=(depth + 1), max_depth=max_depth, last_pos=pos, alpha=alpha, beta=beta)
                board.remove_piece(pos)
                lowest_score = min(lowest_score, score)
                if lowest_score <= alpha:
                    break
                else:
                     beta = min(lowest_score, beta)
        if is_maxing:
            return highest_score
        else:
            return lowest_score
