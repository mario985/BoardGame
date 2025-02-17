
#ifndef _5X5X_O_H
#define _5X5X_O_H

#include "BoardGame_Classes.h"
template <typename T>
class _5x5_XO_Board:public Board<T> {
    int x_count , o_count ;
public:
    _5x5_XO_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    void count();

};

template <typename T>
class _5x5_XO_Player : public Player<T> {
public:
    _5x5_XO_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class _5x5_XO_Random_Player : public RandomPlayer<T>{
public:
    _5x5_XO_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
using namespace std;
template <typename T>
_5x5_XO_Board<T>::_5x5_XO_Board() {
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
bool _5x5_XO_Board<T>::update_board(int x, int y, T mark) {
    if(this->n_moves >= 24){
        this->board[x][y] = 0;
        return true ;
    }
    // Only update if move is valid
    else if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns || (x == 0 && y==4)) && (this->board[x][y] == 0|| mark == 0)) {
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
void _5x5_XO_Board<T>::display_board() {
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
void _5x5_XO_Board<T>::count(){
    auto counting = [&](int i, int j, int di, int dj) {
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
            counting(i, j, 0, 1);
        }
    }

    // Check columns
    for (int i = 0; i <= this->rows - 3; ++i) {
        for (int j = 0; j < this->columns; ++j) {
            counting(i, j, 1, 0);
        }
    }

    // Check diagonals (top-left to bottom-right)
    for (int i = 0; i <= this->rows - 3; ++i) {
        for (int j = 0; j <= this->columns - 3; ++j) {
            counting(i, j, 1, 1);
        }
    }

    // Check diagonals (top-right to bottom-left)
    for (int i = 0; i <= this->rows - 3; ++i) {
        for (int j = 2; j < this->columns; ++j) {
            counting(i, j, 1, -1);
        }
    }
}
template <typename T>
bool _5x5_XO_Board<T>::is_win() {
    if (this->n_moves == 24){
        count();
    }
     if (this->x_count > this->o_count){
        this->o_count += 50 ;
        return false ;
     }
     else if (this->x_count < this->o_count){
        return true  ;
     }
     return false ;
}
    template <typename T>
bool _5x5_XO_Board<T>::is_draw() {
    return (this->n_moves==24&&(this->x_count == this->o_count));
}
template <typename T>
bool _5x5_XO_Board<T>::game_is_over() {
    return is_draw();
}
template <typename T>
_5x5_XO_Player<T>::_5x5_XO_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void _5x5_XO_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 4) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for _5x5_XO_Random_Player
template <typename T>
_5x5_XO_Random_Player<T>::_5x5_XO_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 5;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void _5x5_XO_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}
#endif //_3X3X_O_H

