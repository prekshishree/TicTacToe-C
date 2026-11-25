
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 9

char board[SIZE];

// Function declarations
void resetBoard();
void displayBoard();
int checkWin(char player);
int isBoardFull();
int getValidMove();
int findWinningMove(char player);
int easyMove();
int mediumMove();
int hardMove();
int minimax(int depth, char player);
void computerMove(int difficulty);
void humanVsHuman();
void humanVsComputer();
void playGame();
void clearInput();

// Clear invalid input
void clearInput()
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

// Reset board
void resetBoard()
{
    for (int i = 0; i < SIZE; i++)
    {
        board[i] = '1' + i;
    }
}

// Display board
void displayBoard()
{
    printf("\n");
    printf(" %c | %c | %c \n", board[0], board[1], board[2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[3], board[4], board[5]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[6], board[7], board[8]);
    printf("\n");
}

// Check win
int checkWin(char player)
{
    int wins[8][3] = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8},
        {0, 3, 6},
        {1, 4, 7},
        {2, 5, 8},
        {0, 4, 8},
        {2, 4, 6}
    };

    for (int i = 0; i < 8; i++)
    {
        if (board[wins[i][0]] == player &&
            board[wins[i][1]] == player &&
            board[wins[i][2]] == player)
        {
            return 1;
        }
    }

    return 0;
}

// Check whether board is full
int isBoardFull()
{
    for (int i = 0; i < SIZE; i++)
    {
        if (board[i] != 'X' && board[i] != 'O')
            return 0;
    }

    return 1;
}

// Get a valid move from human
int getValidMove()
{
    int move;

    while (1)
    {
        printf("Enter position (1-9): ");

        if (scanf("%d", &move) != 1)
        {
            printf("Invalid input! Enter a number.\n");
            clearInput();
            continue;
        }

        clearInput();

        if (move < 1 || move > 9)
        {
            printf("Choose a position between 1 and 9.\n");
            continue;
        }

        if (board[move - 1] == 'X' || board[move - 1] == 'O')
        {
            printf("That position is already occupied!\n");
            continue;
        }

        return move - 1;
    }
}

// Find winning or blocking move
int findWinningMove(char player)
{
    for (int i = 0; i < SIZE; i++)
    {
        if (board[i] != 'X' && board[i] != 'O')
        {
            char original = board[i];

            board[i] = player;

            if (checkWin(player))
            {
                board[i] = original;
                return i;
            }

            board[i] = original;
        }
    }

    return -1;
}

// Easy mode: random move
int easyMove()
{
    int available[SIZE];
    int count = 0;

    for (int i = 0; i < SIZE; i++)
    {
        if (board[i] != 'X' && board[i] != 'O')
        {
            available[count] = i;
            count++;
        }
    }

    return available[rand() % count];
}

// Medium mode: win, block or random
int mediumMove()
{
    int move;

    // Check if computer can win
    move = findWinningMove('O');

    if (move != -1)
        return move;

    // Check if human needs to be blocked
    move = findWinningMove('X');

    if (move != -1)
        return move;

    // Otherwise choose random move
    return easyMove();
}

// Minimax algorithm
int minimax(int depth, char player)
{
    if (checkWin('O'))
        return 10 - depth;

    if (checkWin('X'))
        return depth - 10;

    if (isBoardFull())
        return 0;

    int bestScore;

    // Computer tries to maximise score
    if (player == 'O')
    {
        bestScore = -1000;

        for (int i = 0; i < SIZE; i++)
        {
            if (board[i] != 'X' && board[i] != 'O')
            {
                char original = board[i];
                board[i] = 'O';

                int score = minimax(depth + 1, 'X');

                board[i] = original;

                if (score > bestScore)
                    bestScore = score;
            }
        }
    }

    // Human tries to minimise computer's score
    else
    {
        bestScore = 1000;

        for (int i = 0; i < SIZE; i++)
        {
            if (board[i] != 'X' && board[i] != 'O')
            {
                char original = board[i];
                board[i] = 'X';

                int score = minimax(depth + 1, 'O');

                board[i] = original;

                if (score < bestScore)
                    bestScore = score;
            }
        }
    }

    return bestScore;
}

// Hard mode: choose best Minimax move
int hardMove()
{
    int bestScore = -1000;
    int bestMove = -1;

    for (int i = 0; i < SIZE; i++)
    {
        if (board[i] != 'X' && board[i] != 'O')
        {
            char original = board[i];

            board[i] = 'O';

            int score = minimax(0, 'X');

            board[i] = original;

            if (score > bestScore)
            {
                bestScore = score;
                bestMove = i;
            }
        }
    }

    return bestMove;
}

// Computer chooses its move
void computerMove(int difficulty)
{
    int move;

    if (difficulty == 1)
        move = easyMove();

    else if (difficulty == 2)
        move = mediumMove();

    else
        move = hardMove();

    board[move] = 'O';

    printf("Computer chose position %d.\n", move + 1);
}

// Human vs Human mode
void humanVsHuman()
{
    char currentPlayer = 'X';

    resetBoard();

    while (1)
    {
        displayBoard();

        printf("Player %c's turn.\n", currentPlayer);

        int move = getValidMove();

        board[move] = currentPlayer;

        if (checkWin(currentPlayer))
        {
            displayBoard();
            printf("Player %c wins!\n", currentPlayer);
            return;
        }

        if (isBoardFull())
        {
            displayBoard();
            printf("It's a draw!\n");
            return;
        }

        if (currentPlayer == 'X')
            currentPlayer = 'O';
        else
            currentPlayer = 'X';
    }
}

// Human vs Computer mode
void humanVsComputer()
{
    int difficulty;

    resetBoard();

    printf("\nChoose difficulty:\n");
    printf("1. Easy\n");
    printf("2. Medium\n");
    printf("3. Hard\n");

    while (1)
    {
        printf("Enter difficulty (1-3): ");

        if (scanf("%d", &difficulty) != 1)
        {
            printf("Invalid input!\n");
            clearInput();
            continue;
        }

        clearInput();

        if (difficulty >= 1 && difficulty <= 3)
            break;

        printf("Choose between 1 and 3.\n");
    }

    printf("\nYou are X. Computer is O.\n");

    while (1)
    {
        // Human's turn
        displayBoard();

        printf("Your turn (X).\n");

        int move = getValidMove();

        board[move] = 'X';

        if (checkWin('X'))
        {
            displayBoard();
            printf("Congratulations! You win!\n");
            return;
        }

        if (isBoardFull())
        {
            displayBoard();
            printf("It's a draw!\n");
            return;
        }

        // Computer's turn
        printf("\nComputer's turn...\n");

        computerMove(difficulty);

        if (checkWin('O'))
        {
            displayBoard();
            printf("Computer wins!\n");
            return;
        }

        if (isBoardFull())
        {
            displayBoard();
            printf("It's a draw!\n");
            return;
        }
    }
}

// Main menu
void playGame()
{
    int mode;

    printf("\n====== TIC TAC TOE ======\n");
    printf("1. Human vs Human\n");
    printf("2. Human vs Computer\n");

    while (1)
    {
        printf("Choose mode (1-2): ");

        if (scanf("%d", &mode) != 1)
        {
            printf("Invalid input!\n");
            clearInput();
            continue;
        }

        clearInput();

        if (mode == 1 || mode == 2)
            break;

        printf("Choose 1 or 2.\n");
    }

    if (mode == 1)
        humanVsHuman();

    else
        humanVsComputer();
}

// Main function
int main()
{
    int again;

    srand(time(NULL));

    do
    {
        playGame();

        printf("\nDo you want to play again?\n");
        printf("1. Yes\n");
        printf("2. No\n");

        while (1)
        {
            printf("Enter choice: ");

            if (scanf("%d", &again) != 1)
            {
                printf("Invalid input!\n");
                clearInput();
                continue;
            }

            clearInput();

            if (again == 1 || again == 2)
                break;

            printf("Enter 1 or 2 only.\n");
        }

    } while (again == 1);

    printf("\nThank you for playing!\n");

    return 0;
}
