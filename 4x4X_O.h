
#ifndef _4X4X_O_H
#define _4X4X_O_H

#include "BoardGame_Classes.h"
    int px , py ;
template <typename T>
class _4x4_X_O_Board:public Board<T> {
public:
    _4x4_X_O_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class _4x4_X_O_Player : public Player<T> {
public:
    _4x4_X_O_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class _4x4_X_O_Random_Player : public RandomPlayer<T>{
public:
    _4x4_X_O_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for _4x4_X_O_Board
template <typename T>
_4x4_X_O_Board<T>::_4x4_X_O_Board() {
    this->rows = this->columns = 4;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
    this->board[0][0] = 'O';
    this->board[0][1] = 'X';
    this->board[0][2] = 'O';
    this->board[0][3] = 'X';
    this->board[3][0] = 'X';
    this->board[3][1] = 'O';
    this->board[3][2] = 'X';
    this->board[3][3] = 'O';
}

template <typename T>
bool _4x4_X_O_Board<T>::update_board(int x, int y, T mark) {
    bool isVerticalOrHorizontal = 
    (x == px && abs(y - py) == 1) ||(y == py && abs(x - px) == 1);
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0) && (this->board[px][py] == toupper(mark)) &&(isVerticalOrHorizontal)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
            this->board[px][py] = 0 ;
        }

        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void _4x4_X_O_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool _4x4_X_O_Board<T>::is_win() {
    // Check rows
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j <= this->columns - 3; j++) { // Ensure no out-of-bounds access
            if (this->board[i][j] != 0 &&
                this->board[i][j] == this->board[i][j + 1] &&
                this->board[i][j] == this->board[i][j + 2]) {
                return true;
            }
        }
    }

    // Check columns
    for (int j = 0; j < this->columns; j++) {
        for (int i = 0; i <= this->rows - 3; i++) { // Ensure no out-of-bounds access
            if (this->board[i][j] != 0 &&
                this->board[i][j] == this->board[i + 1][j] &&
                this->board[i][j] == this->board[i + 2][j]) {
                return true;
            }
        }
    }

    // Check diagonals (top-left to bottom-right)
    for (int i = 0; i <= this->rows - 3; i++) {
        for (int j = 0; j <= this->columns - 3; j++) {
            if (this->board[i][j] != 0 &&
                this->board[i][j] == this->board[i + 1][j + 1] &&
                this->board[i][j] == this->board[i + 2][j + 2]) {
                return true;
            }
        }
    }

    // Check diagonals (top-right to bottom-left)
    for (int i = 0; i <= this->rows - 3; i++) {
        for (int j = 2; j < this->columns; j++) {
            if (this->board[i][j] != 0 &&
                this->board[i][j] == this->board[i + 1][j - 1] &&
                this->board[i][j] == this->board[i + 2][j - 2]) {
                return true;
            }
        }
    }

    return false;
}

template <typename T>
bool _4x4_X_O_Board<T>::is_draw() {
    // A draw occurs if all moves are done, and no winner exists
    return (this->n_moves == this->rows * this->columns && !is_win());
}

template <typename T>
bool _4x4_X_O_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for _4x4_X_O_Player
template <typename T>
_4x4_X_O_Player<T>::_4x4_X_O_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void _4x4_X_O_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter the token you want to move: ";
    cin >> px >> py;
    cout << "\nPlease enter your move x and y (0 to 3) separated by spaces: ";
    cin >> x >> y;
}
template <typename T>
_4x4_X_O_Random_Player<T>::_4x4_X_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    Symbol=symbol;
    this->dimension =4 ;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}
template <typename T>
void _4x4_X_O_Random_Player<T>::getmove(int& x, int& y) {
    px = rand() % this->dimension;
    py = rand() % this->dimension;
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}







#endif //_3X3X_O_H

