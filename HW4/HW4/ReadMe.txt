Halley Cummings and Ifeoma Ufondu :: Lab 4
______________________
Compilation Problems

Issues compelling the instance function:
	-Error LNK2019: Unresolved External Symbol in Visual Studio [duplicate]
	-To fix this complication error I had to go back and make sure that the function returned a scoped GameBase::game instead of just game.

Saving the Game:
	-When saving the game there were issue with formatting the displayChar and the empty spaces so that when they were reloaded they were placed in the right spot. This gave me a lot of out of bounds errors because it wasn't interpreting spaces the right way. To fix this compilation error, I had to go and change every single space to a '- 'when I saved a file and the back into a space when I put it back on the board.

GameBase Exceptions:
	-For a time I had to have a catch statement to catch string because I was unable to figure out why my file was breaking in the GameBase. It turned out that the error stemmed from inconsistencies in file naming conventions so the input wasn\'92t corresponding to the proper input. 

Unsigned/Signed Errors:
	-As usual there were some signed/unsigned issues wherever I did for-loops. But these are simple fixes and they cleaned the code up significantly.
_______________

Division of Work

Halley worked on creating the new Sudoku game, reading in the provided file, and saving the sudoku game in that format. Ifeoma worked on updating parts of the previous lab to save the TicTacToe and Gomoku games. She also added the static instance variable of the game. 

_______________

Format of Saved files for TicTacToe and Gomoku

(For Sudoku, the same format as the provided input was used to save the output. Permanent values from the initial game set up were saved as negatives.)

Each saved file is formatted with the 'Name' of the Game and the 'GamePieces' all listed in order (i.e. indexed in the vector). So for TicTacToe, there are 25 spaces to fill (9 of which are playing field) and for Gomoku there are (19*19).  After all the gamePieces is a line that indicated who's turn it is when the game restarts. All the values of the game pieces are printed in a line, using '-' for empty spaces.

_______________

Copy Control Decisions

We decided there was no reason to use a copy constructor or copy assignment operator becuase there is never a reason to copy a game object. Only one game can be played at a time; the other games will be saved in txt files while not being played. Within the structure of our program, no copying of GameBase objects was ever needed. As far as the move constructor, we also did not have a need for it because there is no reason to have more than one lvalue instance of a game to call methods on. Therefore, we did not define either the move constructor or move assignement operator.

We used shared_ptrs to store the game objects. These will take care of reallocating space when the game object needs to be destructed; the default destructor is sufficient for our needs. There is no special functionality needed to destruct the game object. 

We cannot enforce how these decisions would affect others using our gameBase object; however, for the purpose of our program, these design decisions are valid.

_______________

Test cases run

Trial 1: Tried different commandline inputs. For anything besides TicTacToe, Gomoku, or Sudoku, the usage message prints to advise the user on a proper input.

Trial 2: For each game, I played it to the end so that one player wins (no draws). For each, the player who won is output, as well as the number of turns it took to get to a done state. When the games are won, the saved file is reset to contain "No Save", indicating the next play should start from a blank board.

Trial 3: In Sudoku, which was the new game we added, I tested the inputs for coordinates: (The same prompt method was used for the other 2 games as well)
	trial	result
	9,9	"Please enter a coordinate value between 0 and 8."
	1,4	Accepted the value; prompted for a value input for that space.
	0,-1	"Please enter a coordinate value between 0 and 8."
	000	"Please enter a comma between coordinates"
	4,k	"Please enter a coordinate value between 0 and 8."
	4	"Insert a comma between coordinates."
If the user selects a space filled by the initial game output, the program alerts the user this space has a permanent value and prompts for a new coordinate.

Trial 4: In Sudoku, I tested prompt value:
	trial	result
	k	"enter a valid value between 1 and 9"
	85 	"
	7	Accepted value and moved on to prompting for next coordinate.

Trial 5:
I tested that all the games saved properly by playing a few moves, then responding "Yes" after entering "quit". When I then reload the game by calling it from the command line, the same values are displayed and the proper player is selected to have a turn. If I then respond "No" to the save prompt, the file is rewritten to display "No Save" and the next game is played from the beginning. If the input file for Sudoku is improperly formatted, it should return the fileReadError. For example, when I tested an input with 10 lines of numbers, this error was returned. I also tested an example with too many column values per row; the same error is returned. I assumed the values input into the sudoko0.txt file are correct for the game.