#ifndef PYRAMID_BOARD_H
#define PYRAMID_BOARD_H

#include <iostream>
#include <vector>
#include "BoardGame_Classes.h" // Assuming Board class is defined here

using namespace std;

// Pyramid_Board class definition
template <typename T>
class Pyramid_Board : public Board<T> {
public:
    Pyramid_Board();
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;

    // Getter functions
    size_t get_rows() const { return pyramid.size(); }
    size_t get_columns(int row) const { return pyramid[row].size(); }

private:
    vector<vector<T>> pyramid;  // Dynamic size to match pyramid layout
};

// Constructor
template <typename T>
Pyramid_Board<T>::Pyramid_Board() {
    this->rows = 3;
    pyramid = { {0}, {0, 0, 0}, {0, 0, 0, 0, 0} };
    this->n_moves = 0;
}

// Update board
template <typename T>
bool Pyramid_Board<T>::update_board(int x, int y, T symbol) {
    if (x < 0 || x >= this->get_rows() || y < 0 || y >= this->get_columns(x) || pyramid[x][y] != 0)
        return false;

    pyramid[x][y] = symbol;
    this->n_moves++;
    return true;
}

// Display board
template <typename T>
void Pyramid_Board<T>::display_board() {
    for (size_t i = 0; i < pyramid.size(); ++i) {
        cout << string(this->rows - i - 1, ' ');  // Center-align rows

        for (size_t j = 0; j < pyramid[i].size(); ++j) {
            if (pyramid[i][j] == 0) {
                cout << "[" << "(" << i << "," << j << ")" << "]";  // Display coordinate (i, j)
            }
            else {
                cout << "[" << pyramid[i][j] << "]";  // Display symbol (X or O)
            }
        }
        cout << endl;
    }
}

// Check for a win
template <typename T>
bool Pyramid_Board<T>::is_win() {
    // Check rows
    for (const auto& row : pyramid) {
        for (size_t i = 0; i + 2 < row.size(); ++i) {
            if (row[i] && row[i] == row[i + 1] && row[i] == row[i + 2])
                return true;
        }
    }

    // Check diagonals
    if (pyramid[0][0] && pyramid[0][0] == pyramid[1][1] && pyramid[0][0] == pyramid[2][2])
        return true;
    if (pyramid[0][0] && pyramid[0][0] == pyramid[1][0] && pyramid[0][0] == pyramid[2][0])
        return true;

    return false;
}

// Check for a draw
template <typename T>
bool Pyramid_Board<T>::is_draw() {
    return this->n_moves == 9 && !is_win();
}

// Check if the game is over
template <typename T>
bool Pyramid_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

#endif // PYRAMID_BOARD_H
