#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <map>

using namespace std;

// Prize Money Based on Difficulty
map<string, int> difficultyPrize = {
    {"Easy", 100},
    {"Medium", 500},
    {"Hard", 1000}
};

// Class for the Game
class GuessingGame {
private:
    int numberToGuess;
    int maxAttempts;
    int maxRange;
    string difficulty;
    int attemptsUsed;
    vector<int> guesses;

public:
    GuessingGame(string level) {
        difficulty = level;
        attemptsUsed = 0;
        setDifficultyParams();
        generateNumber();
    }

    void setDifficultyParams() {
        if (difficulty == "Easy") {
            maxRange = 10;
            maxAttempts = 5;
        } else if (difficulty == "Medium") {
            maxRange = 50;
            maxAttempts = 7;
        } else if (difficulty == "Hard") {
            maxRange = 100;
            maxAttempts = 10;
        } else {
            cout << "Invalid difficulty level. Defaulting to Easy.\n";
            difficulty = "Easy";
            maxRange = 10;
            maxAttempts = 5;
        }
    }

    void generateNumber() {
        srand(time(0));
        numberToGuess = rand() % maxRange + 1;
    }

    void playGame() {
        int guess;
        cout << "\n=== Guess the Number Game ===\n";
        cout << "Difficulty: " << difficulty << "\n";
        cout << "Guess the number between 1 and " << maxRange << "\n";
        cout << "You have " << maxAttempts << " attempts.\n\n";

        while (attemptsUsed < maxAttempts) {
            cout << "Attempt " << (attemptsUsed + 1) << ": ";
            cin >> guess;

            // Input validation
            if (guess < 1 || guess > maxRange) {
                cout << "Invalid guess. Please guess a number between 1 and " << maxRange << ".\n";
                continue;
            }

            guesses.push_back(guess);
            attemptsUsed++;

            if (guess == numberToGuess) {
                cout << " Congratulations! You guessed the number in " << attemptsUsed << " attempts.\n";
                cout << "You win ₹" << difficultyPrize[difficulty] << "!\n";
                return;
            } else if (guess < numberToGuess) {
                cout << "Too low!\n";
            } else {
                cout << "Too high!\n";
            }
        }

        cout << "\n You've used all your attempts.\n";
        cout << "The correct number was: " << numberToGuess << "\n";
        cout << "Better luck next time!\n";
    }

    void showGuessHistory() {
        cout << "\n Your guesses were: ";
        for (int g : guesses) {
            cout << g << " ";
        }
        cout << "\n";
    }
};

int main() {
    string level;
    cout << "Welcome to the Guessing Game!\n";
    cout << "Choose difficulty (Easy / Medium / Hard): ";
    cin >> level;

    GuessingGame game(level);
    game.playGame();
    game.showGuessHistory();

    return 0;
}
