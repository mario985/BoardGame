#ifndef _3X3SUS_H
#define _3X3SUS_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include <ctime>

char choice;
template <typename T>
class SUS_Board : public Board<T> {
public:
    SUS_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    int count_sus();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    void reset_scores();

    int player1_score;
    int player2_score;

private:
    int count_line_for_sus(int startX, int startY, int dx, int dy);
};

template <typename T>
class SUS_Player : public Player<T> {
public:
    SUS_Player(std::string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class SUS_Random_Player : public RandomPlayer<T> {
public:
    SUS_Random_Player(T symbol);
    void getmove(int& x, int& y);
};

// --------------------------------------- IMPLEMENTATION

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
    player1_score = 0;
    player2_score = 0;
}

// Update the board and count points
template <typename T>
bool SUS_Board<T>::update_board(int x, int y, T mark) {
    if (this->n_moves == 9){
        return true ;
    }
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == 0) {
        this->board[x][y] = toupper(choice);
        this->n_moves++;

        // Update scores after each move
        int current_score = count_sus();
        if (mark == 1) {
            player1_score = current_score;
        } else {
            player2_score = current_score;
        }
        return true;
    }
    return false;
}

// Display the board and scores
template <typename T>
void SUS_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------" << endl;
    }
}

// Count all "S-U-S" sequences on the board
template <typename T>
int SUS_Board<T>::count_sus() {
    int total_sus = 0;

    // Check rows, columns, and diagonals
    for (int i = 0; i < this->rows; i++) {
        total_sus += count_line_for_sus(i, 0, 0, 1); // Rows
    }
    for (int i = 0; i < this->columns; i++) {
        total_sus += count_line_for_sus(0, i, 1, 0); // Columns
    }
    total_sus += count_line_for_sus(0, 0, 1, 1); // Diagonal (top-left to bottom-right)
    total_sus += count_line_for_sus(0, this->columns - 1, 1, -1); // Diagonal (top-right to bottom-left)

    return total_sus;
}

// Helper function to count "S-U-S" in a line
template <typename T>
int SUS_Board<T>::count_line_for_sus(int startX, int startY, int dx, int dy) {
    int count = 0;
    for (int i = 0; i < this->rows; i++) {
        int x1 = startX + i * dx;
        int y1 = startY + i * dy;
        if (x1 + 2 * dx < this->rows && y1 + 2 * dy < this->columns && y1 + 2 * dy >= 0) {
            if (this->board[x1][y1] == 'S' && this->board[x1 + dx][y1 + dy] == 'U' && this->board[x1 + 2 * dx][y1 + 2 * dy] == 'S') {
                count++;
            }
        }
    }
    return count;
}

template <typename T>
bool SUS_Board<T>::is_draw() {
    return ((this->n_moves == 9))&&(player1_score == player2_score);
}

template <typename T>
bool SUS_Board<T>::is_win() {
    if((player1_score > player2_score)&&(this->n_moves == 9)){
        return true ;
    }
    else if ((player2_score > player1_score)&&(this->n_moves == 9)){
        player1_score += 15 ;
        
        return false ;
    }
    return false ;
}

template <typename T>
bool SUS_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

// --------------------------------------

// Constructor for SUS_Player
template <typename T>
SUS_Player<T>::SUS_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void SUS_Player<T>::getmove(int& x, int& y) {
    cout << "\n"<< "enter your move (x y): ";
    cin >> x >> y;
    cout << "Enter character (S or U): ";
    cin >> choice;
    choice = toupper(choice);
}

// Constructor for SUS_Random_Player
template <typename T>
SUS_Random_Player<T>::SUS_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void SUS_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
    choice = (rand() % 2 == 0) ? 'S' : 'U';
}

#endif //_3X3SUS_H
