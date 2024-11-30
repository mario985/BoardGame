#include <iostream>
#include "BoardGame_Classes.h"
#include "3x3X_O.h"
#include "MinMaxPlayer.h"
#include "Four_IN_Row.h"
#include "Numerical_Tic_Tac_Toe.h"
#include "5x5X_O.h"
#include "Misere.h"
using namespace std;
int main() {
    int gameChoice;
    Player<int>* numPlayers[2];
    Player<char>* charPlayers[2];
    Board<int>* numBoard = nullptr;
    Board<char>* charBoard = nullptr;

    cout << "Welcome to FCAI BoardGame. :)\n";
    cout << "Choose a game to play:\n";
    cout << "1. Four-In-Row\n";
    cout << "2. Numerical Tic-Tac-Toe\n";
    cout << "3. 5x5 XO\n";
    cout << "4. Misere Tic-Tac-Toe\n";
    cin >> gameChoice;
     if (gameChoice == 1) {
        charBoard = new FourInRow_Board<char>();
        string player1Name, player2Name;
        int choice;

        // Set up Player 1
        cout << "Enter Player 1 name: ";
        cin >> player1Name;
        cout << "Choose Player 1 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;

        switch (choice) {
            case 1:
                charPlayers[0] = new FourINRow_Player<char>(player1Name, 'X');
                break;
            case 2:
                charPlayers[0] = new FourInRow_Random_Player<char>('X');
                break;
            default:
                cout << "Invalid choice for Player 1. Exiting the game.\n";
                return 1;
        }

        // Set up Player 2
        cout << "Enter Player 2 name: ";
        cin >> player2Name;
        cout << "Choose Player 2 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;

        switch (choice) {
            case 1:
                charPlayers[1] = new FourINRow_Player<char>(player2Name, 'O');
                break;
            case 2:
                charPlayers[1] = new FourInRow_Random_Player<char>('O');
                break;
            default:
                cout << "Invalid choice for Player 2. Exiting the game.\n";
                return 1;
        }

        // Create the game manager and run Four-In-Row
        GameManager<char> rowGame(charBoard, charPlayers);
        rowGame.run();

        // Clean up
        delete charBoard;
        for (int i = 0; i < 2; ++i) {
            delete charPlayers[i];
        }
    } 
     else if (gameChoice == 2) {
        numBoard = new Numerical_Tic_Tac_Toe_Board<int>();
        string playerXName, player2Name;
        int choice;
        // Set up Player X
        cout << "Enter Player X name: ";
        cin >> playerXName;
        cout << "Choose Player X type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;

        switch (choice) {
            case 1:
                numPlayers[0] = new Numerical_Tic_TAc_Toe_Player<int>(playerXName, 1);
                break;
            case 2:
                numPlayers[0] = new Numerical_Tic_Tac_Toe_Random_Player<int>(1);
                break;
            default:
                cout << "Invalid choice for Player X. Exiting the game.\n";
                return 1;
        }

        // Set up Player 2
        cout << "Enter Player 2 name: ";
        cin >> player2Name;
        cout << "Choose Player 2 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;

        switch (choice) {
            case 1:
                numPlayers[1] = new Numerical_Tic_TAc_Toe_Player<int>(player2Name, 2);
                break;
            case 2:
                numPlayers[1] = new Numerical_Tic_Tac_Toe_Random_Player<int>(2);
                break;
            default:
                cout << "Invalid choice for Player 2. Exiting the game.\n";
                return 1;
        }

        // Create the game manager and run Numerical Tic-Tac-Toe
        GameManager<int> numGame(numBoard, numPlayers);
        numGame.run();

        // Clean up
        delete numBoard;
        for (int i = 0; i < 2; ++i) {
            delete numPlayers[i];
        }
    }
     else if (gameChoice == 3) {
        int choice;
    Player<char>* players[2];
    _5x5_XO_Board<char>* B = new _5x5_XO_Board<char>();
    string playerXName, player2Name;

    cout << "Welcome to 5x5 Tic Tac Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "3. Smart Computer (AI)\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new _5x5_XO_Player<char>(playerXName, 'X');
            break;
        case 2:
            players[0] = new _5x5_XO_Random_Player<char>('X');
            break;
        case 3:
            players[0] = new X_O_MinMax_Player<char>('X');
            players[0]->setBoard(B);
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return 1;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "3. Smart Computer (AI)\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new _5x5_XO_Player<char>(player2Name, 'O');
            break;
        case 2:
            players[1] = new _5x5_XO_Random_Player<char>('O');
            break;
        case 3:
            players[1] = new X_O_MinMax_Player<char>('O');
            players[1]->setBoard(B);
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return 1;
    }

    // Create the game manager and run the game
    GameManager<char> x_o_game(B, players);
    x_o_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    }
     else if (gameChoice == 4) {
        int choice;
    Player<char>* players[2];
    Misere_Board<char>* B = new Misere_Board<char>();
    string playerXName, player2Name;

    cout << "Welcome to Misere Tic Tac Toe Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "3. Smart Computer (AI)\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new Misere_Player<char>(playerXName, 'X');
            break;
        case 2:
            players[0] = new Misere_Random_Player<char>('X');
            break;
        case 3:
            players[0] = new X_O_MinMax_Player<char>('X');
            players[0]->setBoard(B);
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return 1;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "3. Smart Computer (AI)\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new Misere_Player<char>(player2Name, 'O');
            break;
        case 2:
            players[1] = new Misere_Random_Player<char>('O');
            break;
        case 3:
            players[1] = new X_O_MinMax_Player<char>('O');
            players[1]->setBoard(B);
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return 1;
    }

    // Create the game manager and run the game
    GameManager<char> x_o_game(B, players);
    x_o_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    }
    else {
        cout << "Invalid game choice. Exiting.\n";
        return 1;
    }
        cout << "\nEEEEE  X   X  III  TTTTT   TTTTT  III  N   N   GGG  "<<endl;
        cout << "E      X   X   I     T       T     I   NN  N  G     "<<endl;
        cout << "EEE     X X    I     T       T     I   N N N  G  GG "<<endl;
        cout << "E        X     I     T       T     I   N  NN  G   G "<<endl;
        cout << "EEEEE   X  X  III    T       T    III  N   N   GGG  "<<endl;
    return 0;
}


