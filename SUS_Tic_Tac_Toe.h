
#ifndef _3X3SUS_H
#define _3X3SUS_H

#include "BoardGame_Classes.h"
char choice;
template <typename T>
class SUS_Board:public Board<T> {
public:
    SUS_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class SUS_Player : public Player<T> {
public:
    SUS_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class SUS_Random_Player : public RandomPlayer<T>{
public:
    SUS_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for SUS_Board
template <typename T>
SUS_Board<T>::SUS_Board() {
    this->rows = this->columns = 3;
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
bool SUS_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) &&((this->board[x][y] == 0) &&(choice=='S' ||choice=='U' ||choice=='s' ||choice=='u'))) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(choice);
        }

        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void SUS_Board<T>::display_board() {
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
bool SUS_Board<T>::is_win() {
    // Check rows for "SUS"
    for (int i = 0; i < this->rows; i++) {
        if (this->board[i][0] == 'S' && this->board[i][1] == 'U' && this->board[i][2] == 'S') {
            return true;
        }
    }

    // Check columns for "SUS"
    for (int i = 0; i < this->columns; i++) {
        if (this->board[0][i] == 'S' && this->board[1][i] == 'U' && this->board[2][i] == 'S') {
            return true;
        }
    }

    // Check diagonals for "SUS"
    if ((this->board[0][0] == 'S' && this->board[1][1] == 'U' && this->board[2][2] == 'S') || 
        (this->board[0][2] == 'S' && this->board[1][1] == 'U' && this->board[2][0] == 'S')) {
        return true;
    }

    return false; // No "SUS" found
}


// Return true if 9 moves are done and no winner
template <typename T>
bool SUS_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool SUS_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for SUS_Player
template <typename T>
SUS_Player<T>::SUS_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void SUS_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
    cout<<"\nPlease enter your character(S or U): ";
    cin>>choice;
    
}

// Constructor for SUS_Random_Player
template <typename T>
SUS_Random_Player<T>::SUS_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
    
}

template <typename T>
void SUS_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
    int random_value = rand() % 2;
    (random_value==0)?choice='S':choice='U';
}







#endif //_3X3SUS_H

