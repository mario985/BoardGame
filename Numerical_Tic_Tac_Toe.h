#ifndef Numerical_Tic_Tac_Toe_H
#define Numerical_Tic_Tac_Toe_H
#include "BoardGame_Classes.h"
template <typename T>
class Numerical_Tic_Tac_Toe_Board:public Board<T> {
    private:
    vector<vector<int>>XYposition;
    vector<int>Player1Moves;
    vector<int>Player2Moves;
public:
    Numerical_Tic_Tac_Toe_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};
template <typename T>
class Numerical_Tic_TAc_Toe_Player : public Player<T> {
    private:
     T Symbol1;
public:
    Numerical_Tic_TAc_Toe_Player (string name, T symbol);
    void getmove(int& x, int& y) ;
    ~Numerical_Tic_TAc_Toe_Player()=default;

};
template <typename T>
class Numerical_Tic_Tac_Toe_Random_Player : public RandomPlayer<T>{
    private:
    vector<int>RandomPlayer1Moves;
    vector<int>RandomPlayer2Moves;
    T Symbol1;
public:
    Numerical_Tic_Tac_Toe_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
    T getsymbol();
};
#include <iostream>
#include <iomanip>
#include <cctype>  
#include <random>
#include <limits>

using namespace std;

template <typename T>
Numerical_Tic_Tac_Toe_Board<T>::Numerical_Tic_Tac_Toe_Board() {
    Player1Moves= {1 , 3 , 5 , 7 , 9};
    Player2Moves= {2 , 4 , 6 , 8};
    XYposition.resize(9,vector<int>(9,0));
    this->rows = this->columns = 3;
    this->board = new int*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new int[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool Numerical_Tic_Tac_Toe_Board<T>::update_board(int x, int y, T mark) {
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != 0)
        return false;
    vector<T>& moves = (mark & 1) ? Player1Moves : Player2Moves;
    if (mark == ((mark & 1) ? 11 : 22)) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, moves.size() - 1);
        int randomIndex = dis(gen);
        this->board[x][y] = moves[randomIndex];
        moves.erase(moves.begin() + randomIndex);
    } else {
        auto it = find(moves.begin(), moves.end(), mark);
        if (it == moves.end())
            return false;
        this->board[x][y] = mark;
        moves.erase(it);
    }

    this->n_moves++;
    return true;
}


template <typename T>
void Numerical_Tic_Tac_Toe_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            if(this->board[i][j]==0)cout << "(" << i << "," << j << ")"<< setw(2) << this->board[i][j] << " |";
            else cout<< setw(5) << this->board[i][j] << "   |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

template <typename T>
bool Numerical_Tic_Tac_Toe_Board<T>::is_win() {
        for (int i = 0; i < 3; ++i) {
        if (this->board[i][0] != 0 && this->board[i][1] != 0 && this->board[i][2] != 0 && 
            (this->board[i][0] + this->board[i][1] + this->board[i][2] == 15)) {
            return true;
        }
    }
    for (int j = 0; j < 3; ++j) {
        if (this->board[0][j] != 0 && this->board[1][j] != 0 && this->board[2][j] != 0 && 
            (this->board[0][j] + this->board[1][j] + this->board[2][j] == 15)) {
            return true;
        }
    }

    if (this->board[0][0] != 0 && this->board[1][1] != 0 && this->board[2][2] != 0 && 
        (this->board[0][0] + this->board[1][1] + this->board[2][2] == 15)) {
        return true;
    }

    if (this->board[0][2] != 0 && this->board[1][1] != 0 && this->board[2][0] != 0 && 
        (this->board[0][2] + this->board[1][1] + this->board[2][0] == 15)) {
        return true;
    }

    return false;

}

template <typename T>
bool Numerical_Tic_Tac_Toe_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool Numerical_Tic_Tac_Toe_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
Numerical_Tic_TAc_Toe_Player<T>::Numerical_Tic_TAc_Toe_Player(string name, T symbol) : Player<T>(name, symbol) {
    this->Symbol1=symbol;

    
}
template <typename T>
void Numerical_Tic_TAc_Toe_Player<T>::getmove(int& x, int& y) {
    cout << "\nEnter your move (x y): ";
    cin >> x >> y;
    int n;
    if (Symbol1 == 1) {
        cout << "Enter a unique odd number(1 to 9): ";
        while (true) {
            cin >> n;
            if (n & 1) {
                this->symbol = n;
                break;
            }
            cout << "Invalid odd number. Try again: ";
        }
    } else if (Symbol1 == 2) {
        cout << "Enter a unique even number (2 to 8): ";
        while (true) {
            cin >> n;
            if (!(n & 1)) {
                this->symbol = n;
                break;
            }
            cout << "Invalid even number. Try again: ";
        }
    }
}
// Constructor for Ultimate_Tic_Tac_Toe_Random_Player
template <typename T>
Numerical_Tic_Tac_Toe_Random_Player<T>::Numerical_Tic_Tac_Toe_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    RandomPlayer1Moves= {1 , 3 , 5 , 7 , 9};
    RandomPlayer2Moves= {2 , 4 , 6 , 8};
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0))); 
}
template <typename T>
void Numerical_Tic_Tac_Toe_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  
    y = rand() % this->dimension;
}
#endif 

