#include <iostream>
#include "BoardGame_Classes.h"
#include "3x3X_O.h"
#include "MinMaxPlayer.h"
#include "Four_IN_Row.h"
#include "Numerical_Tic_Tac_Toe.h"
#include "5x5X_O.h"
#include "Misere.h"
#include "ultimate_Tic_Tac_Toe.h"
#include "Pyramid_Board.h"
#include "4x4X_O.h"
#include "WordBoard.h"
#include <algorithm>
#include <iomanip>
#include <vector>
#include <limits>
#include <string>
#include <unordered_set>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;
int main() {
    int gameChoice;
    cout << "Welcome to FCAI BoardGame. :)\n";
    cout << "Choose a game to play:\n";
    cout << "1. Four-In-Row\n";
    cout << "2. Numerical Tic-Tac-Toe\n";
    cout << "3. 5x5 Tic Tac Toe\n";
    cout << "4. Misere Tic-Tac-Toe\n";
    cout << "5. Ultimate_Tic_Tac_Toe\n";
    cout << "6. 4x4 Tic Tac Toe\n";
    cout<< "7. Pyramic_Tic_Tac_Toe\n";
    cout<<"8.Word_Tic_Tac_Toe\n";
    cin >> gameChoice;
     if (gameChoice == 1) {
        Player<char>* charPlayers[2];
         FourInRow_Board<char>* charBoard  = new FourInRow_Board<char>();
        string player1Name, player2Name;
        int choice;
        // Set up Player 1
        cout << "Enter Player 1 name: ";
        cin >> player1Name;
        cout << "Choose Player 1 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cout << "3. Smart Computer (AI)\n";
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
        cout << "3. Smart Computer (AI)\n";
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
         Numerical_Tic_Tac_Toe_Board<int>* numBoard = new Numerical_Tic_Tac_Toe_Board<int>();
            Player<int>* numPlayers[2];
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
                numPlayers[0] = new Numerical_Tic_Tac_Toe_Random_Player<int>(11);
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
                numPlayers[1] = new Numerical_Tic_Tac_Toe_Random_Player<int>(22);
                break;
            default:
                cout << "Invalid choice for Player 2. Exiting the game.\n";
                return 1;
        }

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
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new _5x5_XO_Player<char>(playerXName, 'X');
            break;
        case 2:
            players[0] = new _5x5_XO_Random_Player<char>('X');
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
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new _5x5_XO_Player<char>(player2Name, 'O');
            break;
        case 2:
            players[1] = new _5x5_XO_Random_Player<char>('O');
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
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new Misere_Player<char>(playerXName, 'X');
            break;
        case 2:
            players[1] = new Misere_Random_Player<char>('X');
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
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new Misere_Player<char>(player2Name, 'O');
            break;
        case 2:
            players[0] = new Misere_Random_Player<char>('O');
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
    else if(gameChoice==5){
         Player<char>* charPlayers[2];
         Ultimate_Tic_Tac_Toe_Board<char>* charBoard  = new Ultimate_Tic_Tac_Toe_Board<char>();
        string player1Name, player2Name;
        int choice;
        // Set up Player 1
        cout << "Enter Player 1 name: ";
        cin >> player1Name;
        cout << "Choose Player 1 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cout << "3. Smart Computer (AI)\n";
        cin >> choice;
        switch (choice) {
            case 1:
                charPlayers[0] = new Ultimate_Tic_Tac_Toe_Player<char>(player1Name, 'X');
                charPlayers[0]->setBoard(charBoard);
                break;
            case 2:
                charPlayers[0] = new Ultimate_Tic_Tac_Toe_Random_Player<char>('X');
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
                charPlayers[1] = new Ultimate_Tic_Tac_Toe_Player<char>(player2Name, 'O');
                charPlayers[1]->setBoard(charBoard);
                break;
            case 2:
                charPlayers[1] = new Ultimate_Tic_Tac_Toe_Random_Player<char>('O');
                charPlayers[1]->setBoard(charBoard);
                break;
            default:
                cout << "Invalid choice for Player 2. Exiting the game.\n";
                return 1;
        }
        GameManager<char> rowGame(charBoard, charPlayers);
        rowGame.run();

        // Clean up
        delete charBoard;
        for (int i = 0; i < 2; ++i) {
            delete charPlayers[i];
        }

    }
        else if (gameChoice == 6){
            int choice;
    Player<char>* players[2];
    _4x4_X_O_Board<char>* B = new _4x4_X_O_Board<char>();
    string playerXName, player2Name;

    cout << "Welcome to 4x4 Tic Tac Toe Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new _4x4_X_O_Player<char>(playerXName, 'X');
            break;
        case 2:
            players[0] = new _4x4_X_O_Random_Player<char>('X');
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
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new _4x4_X_O_Player<char>(player2Name, 'O');
            break;
        case 2:
            players[1] = new _4x4_X_O_Random_Player<char>('O');
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
    else if(gameChoice==7){
    Pyramid_Board<char> board;

    // Get player names
    string name1, name2;
    cout << "Enter Player 1 name: ";
    cin >> name1;
    cout << "Enter Player 2 name: ";
    cin >> name2;
    board.display_board();

    // Create players
    X_O_Player<char> player1(name1, 'X');
    X_O_Player<char> player2(name2, 'O');
    Player<char>* players[] = { &player1, &player2 };
    // Game loop
    while (!board.game_is_over()) {
        for (int i = 0; i < 2; ++i) {
            int x, y;

            // Prompt for the current player's move
            cout << players[i]->getname() << "'s turn (" << players[i]->getsymbol() << "). Enter your move (row column): ";

            while (true) {
                cin >> x >> y;

                // Validate input
                if (cin.fail()) {
                    cin.clear(); 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                    cout << "Invalid input! Please enter valid integers for row and column (e.g., 1 2): ";
                }
                else if (x < 0 || x >= board.get_rows() || y < 0 || y >= board.get_columns(x) || !board.update_board(x, y, players[i]->getsymbol())) {
                    cout << "Invalid move! Try again (row column): ";
                }
                else {
                    board.display_board();
                    break; 
                }
            }

            // Check for a winner
            if (board.is_win()) {
                cout << "Congratulations, " << players[i]->getname() << "! You win!\n";
                return 0;
            }

            // Check for a draw
            if (board.is_draw()) {
                cout << "It's a draw!\n";
                return 0;
            }
        }
    }

    }
    else if(gameChoice==8){
        Dictionary dictionary;
    dictionary.load("dic.txt");

    WordBoard board(&dictionary);

    cout << "Enter Player 1 name: ";
    string name1;
    cin >> name1;

    int choice;
    WordPlayer* player1 = nullptr;

    // Validate Player 1 type input
    while (true) {
        cout << "Choose Player 1 type:\n1. Human\n2. Random AI\n";
        cin >> choice;

        // Check if the input is valid
        if (cin.fail() || (choice != 1 && choice != 2)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter 1 or 2.\n";
        }
        else {
            // Valid input
            if (choice == 1) {
                player1 = new HumanPlayer(name1);
            }
            else {
                player1 = new RandomAIPlayer(name1);
            }
            break;
        }
    }

    cout << "Enter Player 2 name: ";
    string name2;
    cin >> name2;

    WordPlayer* player2 = nullptr;

    // Validate Player 2 type input
    while (true) {
        cout << "Choose Player 2 type:\n1. Human\n2. Random AI\n";
        cin >> choice;

        // Check if the input is valid
        if (cin.fail() || (choice != 1 && choice != 2)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter 1 or 2.\n";
        }
        else {
            // Valid input
            if (choice == 1) {
                player2 = new HumanPlayer(name2);
            }
            else {
                player2 = new RandomAIPlayer(name2);
            }
            break;
        }
    }

    Gamemanager gameManager(&board, player1, player2);
    gameManager.run();

    delete player1;
    delete player2;

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


