from Board import Board

class Game:
    def __init__(self, player1obj, player2obj):
        self.isGameOver = False
        self.board = Board()
        self.players = [player1obj, player2obj]
        self.current_player = player1obj
        self.last_move = (None, None)

    def switch_turn(self):
        self.current_player = self.players[0] if self.current_player == self.players[1] else self.players[1]

    def is_col_valid(self, col):
        return self.board.minCol <= col <= self.board.maxCol

    def play_move(self, col):
        if not self.is_col_valid(col):
            raise IndexError("Invalid column index! please input 0-6")
        if self.board.is_col_full(col):
            raise IndexError("Column is full! choose a different one!")
        self.last_move = self.board.place_piece(col, self.current_player.symbol)

    def check_win(self):
        return self.board.is_4_in_a_row(self.last_move, self.current_player.symbol)

    def check_draw(self):
        return self.board.is_board_full()

    def print_results(self):
        if self.check_win():
            self.isGameOver = True
            print(f"{self.current_player.name} ({self.current_player.symbol}) Won! GG!")
        elif self.check_draw():
            self.isGameOver = True
            print("It's a draw! GG!")
