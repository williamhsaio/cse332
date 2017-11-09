Halley Cummings - Lab 2 README.txt

This program takes in an input of a game name - TicTacToe - and allows a user to play tictactoe. Two users, X and O, 
alternate entering coordinates in the form col,row. If the input is well-formed, the next player is prompted to go.
The game ends when a player quits, when someone wins, or if there are no valid turns left and there is a draw. 

ERRORS ENCOUNTERED:

I ran into indexing issues with the vector of game pieces because I was using both row,col and col,row coordinates in different parts of the code.
I had errors occur where Visual studio couldn't write to the .exe file, which I was able to fix by consistently exiting my program before 
	writing to it.

TEST CASES:

Player X : (3,2), (2,1), (1,2)
Player O : (1,1), (2,2), (3,3)

  X O
X O
O X

Returns: Player O won the game after 6 turns.

__________________________________________

Player X: (1,1), (1,3), (2,2), (3,2)
Player O : (2,1), (1,2), (1,3), (3,3)

O X O
O X 
X O X

Returns: A draw occured after 8 turns -- no valid moves remain.

__________________________________________

input: Lab2 TicTacToe
quit

Returns: Player X has ended the game.
Game ended after 0 turns.

