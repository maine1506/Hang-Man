Game: HANG MAN

1. Overview:
- This is a version of Hangman where the computer thinks of a secret word and the player must guess it by suggesting letters. The player has a limited number of incorrect guesses before losing the game.

2. How to Play:
- Starting the Game:
  - The computer will randomly select a word and display its length as underscores

- Guessing Letters:
  - Click on letters from the on-screen keyboard to make guesses
  - Correct guesses: The letter will be revealed in its correct position(s)
  - Incorrect guesses: Part of the hangman drawing will appear

- Game Controls:
  - Hint Button: Costs 10 points to reveal a random missing letter (only when score ≥ 10)
  - Home Button: Returns to main menu
  - Play Again/Next: Restarts or continues to next level

- Winning/Losing:
  - Win: Guess all letters before using all attempts (+5 points)
  - Lose: Run out of attempts (7 incorrect guesses maximum)

3. Features:
- Multiple difficulty levels with increasing challenge
- Visual hangman drawing that progresses with wrong guesses
- Category hints for each word
- Score tracking system
- Responsive on-screen keyboard with visual feedback

4. Technical Details
- Programming Language: C++
- Graphics: SDL2 library
- Text Rendering: SDL_ttf
- Image Loading: SDL_image
  
5. Requirements
- SDL2, SDL_image, and SDL_ttf libraries installed
- C++17 compatible compiler

6. Installation
- Clone the repository
- Compile with: g++ main.cpp -o hangman -lSDL2 -lSDL2_image -lSDL2_ttf
- Run: ./hangman

7. Assets
- All game assets (images, fonts) should be placed in an assets/ folder in the same directory as the executable.

8. Future Improvements
- Add sound effects
- Implement high score system
- Add more word categories
- Mobile device support
