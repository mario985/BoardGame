
#ifndef _5X5X_O_H
#define _5X5X_O_H

#include "BoardGame_Classes.h"

template <typename T>
class X_O_Board:public Board<T> {
private :
    int x_count , o_count ;
public:
    X_O_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class X_O_Player : public Player<T> {
public:
    X_O_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class X_O_Random_Player : public RandomPlayer<T>{
public:
    X_O_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
using namespace std;
template <typename T>
X_O_Board<T>::X_O_Board() {
    this->x_count = 0 ; this->o_count = 0 ;
    this->rows = this->columns = 5;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}
template <typename T>
bool X_O_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns || (x == 0 && y==4)) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    return false;
}
template <typename T>
void X_O_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            if (i == 0 && j == 4){
            cout << setw(2) << this->board[i][j] << " |";    
                continue;
            }
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}
template <typename T>
bool X_O_Board<T>::is_win() {
    int x_count = 0, o_count = 0;

    auto count_sequence = [&](int i, int j, int di, int dj) {
        char mark = this->board[i][j];
        if (mark != 0 && 
            this->board[i + di][j + dj] == mark &&
            this->board[i + 2 * di][j + 2 * dj] == mark) {
            if (mark == 'X') x_count++;
            else if (mark == 'O') o_count++;
        }
    };

    // Check rows
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j <= this->columns - 3; ++j) {
            count_sequence(i, j, 0, 1);
        }
    }

    // Check columns
    for (int i = 0; i <= this->rows - 3; ++i) {
        for (int j = 0; j < this->columns; ++j) {
            count_sequence(i, j, 1, 0);
        }
    }

    // Check diagonals (top-left to bottom-right)
    for (int i = 0; i <= this->rows - 3; ++i) {
        for (int j = 0; j <= this->columns - 3; ++j) {
            count_sequence(i, j, 1, 1);
        }
    }

    // Check diagonals (top-right to bottom-left)
    for (int i = 0; i <= this->rows - 3; ++i) {
        for (int j = 2; j < this->columns; ++j) {
            count_sequence(i, j, 1, -1);
        }
    }

    // Determine the winner based on counts
    if (this->n_moves == 24) { // All moves played
        return x_count > o_count; // X wins if they have more sequences
    }

    return false; // No win condition met yet
}
    template <typename T>
bool X_O_Board<T>::is_draw() {
    return (this->n_moves==24&&(this->x_count == this->o_count));
}
template <typename T>
bool X_O_Board<T>::game_is_over() {
    return is_win();
}
template <typename T>
X_O_Player<T>::X_O_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void X_O_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 4) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for X_O_Random_Player
template <typename T>
X_O_Random_Player<T>::X_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 5;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void X_O_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}
#endif //_3X3X_O_H

