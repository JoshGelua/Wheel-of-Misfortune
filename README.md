# Wheel of Misfortune

This game showcases dynamic memory allocation and structs.

Wheel of Misfortune is a single player game in which the user must guess the word chosen by the computer in dictionary.txt. The twist is that the computer changes the word that is chosen to maximize the chance of winning. It does this by iteratively selecting a maximum subset of words within the set of guessable words that ensures the player's guess is the least effective.

To play:

1. Clone repo and open it in your terminal.
2. type "make all" to compile the game
3. type "./wheel dictionary.txt", and then the game will prompt the user the length of the words that they want to guess. 
*** NOTE: You can choose a word length from 2-24 or 28-29.
4. the game will then prompt the user the number of guesses they would like to have in the game. 
*** NOTE: Due to the size of the dictionary, the likeliness of winning a game with less than 26 guesses (the entire alphabet, A-Z) is extremely low.
5. Play by inputting letters. It will take any string of letters, but will count each individual character as a guess. ("abc" will register as a total of 3 guesses: 'a', 'b', 'c') If you try to guess the same letter twice, it will not count as a guess.
6. Once the game is over, the game will ask if you would like to play again. If you want to play again, type "y", otherwise any other string will exit.
