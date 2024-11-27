#ifndef Four_IN_Row_H
#define Four_IN_Row_H
#include "BoardGame_Classes.h"
template <typename T>
class FourInRow_Board:public Board<T> {
    private:
    int RowCount[7];
public:
    FourInRow_Board();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class FourINRow_Player : public Player<T> {
public:
    FourINRow_Player (string name, T symbol);
    void getmove(int& x, int& y) ;
    ~FourINRow_Player()=default;

};

template <typename T>
class FourInRow_Random_Player : public RandomPlayer<T>{
public:
    FourInRow_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};

#include <iostream>
#include <iomanip>
#include <cctype> 
#include "Four_IN_Row.h"
#include "BoardGame_Classes.h"
using namespace std;
template <typename T>
FourInRow_Board<T>::FourInRow_Board() {
    this->rows = 6;
    this->columns=7;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    for(int i=0;i<7;i++)this->RowCount[i]=0;
    this->n_moves = 0;
}
template <typename T>
bool FourInRow_Board<T>::update_board(int x, int y, T mark) {
    if (!(x < 0 || x >= this->columns) &&RowCount[x]<6  &&(this->board[RowCount[x]][x] == 0|| mark == 0) ) {
        if (mark == 0){
            this->n_moves--;
            this->board[RowCount[x]++][x] = 0;
        }
        else {
            this->n_moves++;
            this->board[RowCount[x]++][x] = toupper(mark);
        }

        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void FourInRow_Board<T>::display_board() {
    for (int i = 5; i >= 0; i--) {
        // Print the horizontal separator
        for (int j = 0; j < 7; j++) {
            cout << "+---";
        }
        cout << "+" << endl;

        // Print the cells with vertical separators
        for (int j = 0; j < 7; j++) {
            cout << "| ";
            if (this->board[i][j] != 0) { // Non-empty cell
                cout << this->board[i][j] << " ";
            } else { // Empty cell
                cout << "  ";
            }
        }
        cout << "|" << endl;
    }

    // Print the bottom border
    for (int j = 0; j < 7; j++) {
        cout << "+---";
    }
    cout << "+" << endl;
}


// Returns true if there is any winner
template <typename T>
bool FourInRow_Board<T>::is_win() {
    // Check rows and columns
        for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 7; ++col) {
            if (this->board[row][col] !=0) {
                if (col + 3 < 7 && this->board[row][col + 1] == this->board[row][col] && this->board[row][col + 2] ==this->board[row][col] && this->board[row][col + 3] == this->board[row][col])
                    return true;
                    
                if (row + 3 < 6 && this->board[row + 1][col] == this->board[row][col] && this->board[row + 2][col] == this->board[row][col] && this->board[row + 3][col] ==this->board[row][col])
                    return true;
                if (row + 3 < 6 && col + 3 < 7 && this->board[row + 1][col + 1] == this->board[row][col]&& this->board[row + 2][col + 2] == this->board[row][col] && this->board[row + 3][col + 3] == this->board[row][col])
                    return true;

                if (row - 3 >= 0 && col + 3 < 7 && this->board[row - 1][col + 1] == this->board[row][col] && this->board[row - 2][col + 2] ==this->board[row][col] && this->board[row - 3][col + 3] ==this->board[row][col])
                    return true;
            }
        }
    }
    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool FourInRow_Board<T>::is_draw() {
    return (this->n_moves == 42 && !is_win());
}

template <typename T>
bool FourInRow_Board<T>::game_is_over() {
    return is_win() || is_draw();
}
template <typename T>
FourINRow_Player<T>::FourINRow_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void FourINRow_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move X(0 to 6): ";
    cin >> x;
}

// Constructor for X_O_Random_Player
template <typename T>
FourInRow_Random_Player<T>::FourInRow_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 6;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void FourInRow_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2

}



#endif