#include <iostream>
using namespace std;

char board[3][3];
char currentPlayer;
int scoreX = 0, scoreO = 0;

// Initialize board
void initializeBoard() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
}

// Display board
void displayBoard() {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << " " << board[i][0] << " | " << board[i][1] << " | " << board[i][2] << "\n";
        if (i < 2)
            cout << "---+---+---\n";
    }
    cout << "\n";
}

// Display score
void displayScore() {
    cout << "Score:\n";
    cout << "Player X: " << scoreX << "\n";
    cout << "Player O: " << scoreO << "\n\n";
}

// Check win
bool checkWin() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == currentPlayer &&
            board[i][1] == currentPlayer &&
            board[i][2] == currentPlayer)
            return true;

        if (board[0][i] == currentPlayer &&
            board[1][i] == currentPlayer &&
            board[2][i] == currentPlayer)
            return true;
    }

    if (board[0][0] == currentPlayer &&
        board[1][1] == currentPlayer &&
        board[2][2] == currentPlayer)
        return true;

    if (board[0][2] == currentPlayer &&
        board[1][1] == currentPlayer &&
        board[2][0] == currentPlayer)
        return true;

    return false;
}

// Check draw
bool checkDraw() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return false;
    return true;
}

// Switch player
void switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

// Game logic
void playGame() {
    int row, col;
    currentPlayer = 'X';
    initializeBoard();

    while (true) {
        displayScore();
        displayBoard();

        cout << "Player " << currentPlayer << ", enter row and column (1-3 1-3): ";
        cin >> row >> col;

        row--; col--;

        if (row < 0 || row > 2 || col < 0 || col > 2) {
            cout << "Invalid position! Try again.\n";
            continue;
        }

        if (board[row][col] != ' ') {
            cout << "Cell already taken! Try again.\n";
            continue;
        }

        board[row][col] = currentPlayer;

        if (checkWin()) {
            displayBoard();
            cout << "🎉 Player " << currentPlayer << " wins!\n";

            if (currentPlayer == 'X')
                scoreX++;
            else
                scoreO++;

            break;
        }

        if (checkDraw()) {
            displayBoard();
            cout << "It's a draw!\n";
            break;
        }

        switchPlayer();
    }
}

int main() {
    char choice;

    do {
        playGame();
        cout << "\nCurrent ";
        displayScore();

        cout << "Do you want to play again? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    cout << "\nFinal ";
    displayScore();
    cout << "Thanks for playing!\n";

    return 0;
}
