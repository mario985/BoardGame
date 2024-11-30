#ifndef _MISERE_H
#define _MISERE_H

#include "BoardGame_Classes.h"

template <typename T>
class Misere_Board:public Board<T> {
private:
    bool game_over;  // Flag to track if the game is over
    T last_player_symbol;  // Track the last symbol to identify the losing player
public:
    Misere_Board();
    bool update_board(int x, int y, T symbol);
    bool is_win();
    bool is_draw();
    void display_board () ;
    bool game_is_over();
};

template <typename T>
class Misere_Player : public Player<T> {
    string name2 ;
public:
    Misere_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class Misere_Random_Player : public RandomPlayer<T>{
public:
    Misere_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for Misere_Board
template <typename T>
Misere_Board<T>::Misere_Board() : game_over(false), last_player_symbol(0) {
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
bool Misere_Board<T>::update_board(int x, int y, T mark) {
    if (game_over) {
        return false;  // Prevent further moves if game is already over
    }

    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || mark == 0)) {
        if (mark == 0) {
            this->n_moves--;
            this->board[x][y] = 0;
        } else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
            last_player_symbol = toupper(mark);

            // Check immediately if this move causes a loss
            if (is_win()) {
                game_over = true;
            }
        }
        return true;
    }
    return false;
}

template <typename T>
bool Misere_Board<T>::is_win() {
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0)) {
            return this->board[i][0] == last_player_symbol;
        }
    }

    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)) {
        return this->board[1][1] == last_player_symbol;
    }

    return false;
}

template <typename T>
bool Misere_Board<T>::is_draw() {
    return (this->n_moves == 9 && !game_over);
}

template <typename T>
bool Misere_Board<T>::game_is_over() {
    return game_over || is_draw();
}
template <typename T>
void Misere_Board<T>::display_board() {
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
// Constructor for Misere_Player
template <typename T>
Misere_Player<T>::Misere_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Misere_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for Misere_Random_Player
template <typename T>
Misere_Random_Player<T>::Misere_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void Misere_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}







#endif //_3X3X_O_H

