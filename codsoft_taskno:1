#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

int getRandomNumber(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// Function to safely take integer input
int getValidInput() {
    int value;

    while (true) {
        cin >> value;

        if (cin.fail()) {
            cin.clear(); // clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number: ";
        } else {
            return value;
        }
    }
}

void playGame() {
    int choice;
    int maxNumber, attemptsLimit;

    cout << "\n=== Choose Difficulty ===\n";
    cout << "1. Easy (1-50, unlimited attempts)\n";
    cout << "2. Medium (1-100, 10 attempts)\n";
    cout << "3. Hard (1-200, 7 attempts)\n";
    cout << "Enter choice: ";

    choice = getValidInput();

    switch (choice) {
        case 1:
            maxNumber = 50;
            attemptsLimit = -1; // unlimited
            break;
        case 2:
            maxNumber = 100;
            attemptsLimit = 10;
            break;
        case 3:
            maxNumber = 200;
            attemptsLimit = 7;
            break;
        default:
            cout << "Invalid choice! Defaulting to Medium.\n";
            maxNumber = 100;
            attemptsLimit = 10;
    }

    int secretNumber = getRandomNumber(1, maxNumber);
    int guess;
    int attempts = 0;

    cout << "\nI have selected a number between 1 and " << maxNumber << ".\n";

    while (true) {
        if (attemptsLimit != -1 && attempts >= attemptsLimit) {
            cout << "You've used all attempts! The number was: " << secretNumber << endl;
            break;
        }

        cout << "Enter your guess: ";
        guess = getValidInput();
        attempts++;

        if (guess > secretNumber) {
            cout << "Too high!" << endl;
        }
        else if (guess < secretNumber) {
            cout << "Too low!" << endl;
        }
        else {
            cout << "Correct! You guessed it in " << attempts << " attempts." << endl;
            break;
        }

        if (attemptsLimit != -1) {
            cout << "Attempts left: " << (attemptsLimit - attempts) << endl;
        }
    }
}

int main() {
    srand(time(0));

    char playAgain;

    cout << "=== Welcome to the Guessing Game ===\n";

    do {
        playGame();

        cout << "\nDo you want to play again? (y/n): ";
        cin >> playAgain;

    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "Thanks for playing!\n";

    return 0;
}
