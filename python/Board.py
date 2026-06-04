class Board:
    def __init__(self):
        self.state = [[' ' for _ in range(7)] for _ in range(6) ] #
        self.minRow = 0
        self.maxRow = 5
        self.minCol = 0
        self.maxCol = 6

    def __str__(self):
        display = ""
        display += "\n"  # Add a little breathing room above the board
        for row in reversed(self.state):
            # Join each item in the row with a pipe and surround the edges
            display += f"| {' | '.join(row)} |\n"
        # Print the "floor" of the board
        display += ("-" * 29 + "\n")
        display += "  0   1   2   3   4   5   6  \n"
        display += "\n"  # Add breathing room below
        return display

    def place_piece(self, col, symbol):
        for row in range(len(self.state)):
            if self.state[row][col] == ' ':
                self.state[row][col] = symbol
                return row, col

    def is_col_full(self, col):
        return self.state[self.maxRow][col] != ' '

    def is_pos_valid(self, pos):
        return (self.minRow <= pos[0] <= self.maxRow) and (self.minCol <= pos[1] <= self.maxCol)

    def streak_in_direction(self, pos, direction, symbol):
        streak = 0
        current_pos = list(pos)
        while self.is_pos_valid(current_pos) and streak < 4:
            if self.state[current_pos[0]][current_pos[1]] == symbol:
                streak += 1
                current_pos[0] += direction[0]
                current_pos[1] += direction[1]
            else:
                return streak
        return streak



    def is_4_in_a_row(self, pos: tuple, symbol):
        directions = {
            "vertical": [(1, 0),(-1,0)], # up, down
            "horizontal": [(0, -1),(0, 1)], # left, right
            "down diag": [(1, -1),(-1, 1)], # up left, down right
            "up diag": [(-1, -1),(1, 1)] # down left, up right
        }
        for direction in directions.values():
            streak = -1 # minus 1 for the duplicate starting piece each check
            streak += self.streak_in_direction(pos, direction[0], symbol)
            streak += self.streak_in_direction(pos, direction[1], symbol)
            if streak >= 4:
                return True
        return False

    def is_board_full(self):
        return not (' ' in self.state[self.maxRow])

    def remove_piece(self, pos):
        self.state[pos[0]][pos[1]] = ' '


    def get_window(self, start_pos, direction):
        current_pos = list(start_pos)
        window = []
        for i in range(4):
            if not self.is_pos_valid(current_pos):
                return []
            window.append(self.state[current_pos[0]][current_pos[1]]) # append value at current_pos
            current_pos[0] += direction[0] # update row
            current_pos[1] += direction[1] # update col
        return window
