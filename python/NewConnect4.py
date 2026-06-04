from Player import HumanPlayer, AI
from GameLogic import Game

player1 = HumanPlayer('player1', 'O')
mode = int(input("input 1 for single player (against AI) or 2 for multiplyer (1v1): "))
if mode == 2:
    player2 = HumanPlayer('player2', 'X')
else:
    player2 = AI('AI-basic MiniMax', 'X', 1, player1.symbol)
mygame = Game(player1, player2)
while not mygame.isGameOver:
    print(mygame.board)
    column = mygame.current_player.get_move(mygame.board)
    try:
        mygame.play_move(column)
        mygame.print_results()
        mygame.switch_turn()
    except IndexError as e:
        print(e)
        continue
print(mygame.board)