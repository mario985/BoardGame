#ifndef Numerical_Tic_Tac_Toe_H
#define Numerical_Tic_Tac_Toe_H
#include "BoardGame_Classes.h"
template <typename T>
class Numerical_Tic_Tac_Toe_Board:public Board<T> {
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
    vector<int>Player1Moves;
    vector<int>Player2Moves;
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
    T Symbol;
public:
    Numerical_Tic_Tac_Toe_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
    T getsymbol();
};
#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include <random>
#include <limits>

using namespace std;

// Constructor for X_O_Board
template <typename T>
Numerical_Tic_Tac_Toe_Board<T>::Numerical_Tic_Tac_Toe_Board() {
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
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0)) {
            this->n_moves++;
            this->board[x][y] = mark;
        return true;
    }
    // this->n_moves++;
    // this->board[x][y] = mark;
    return false;
}

// Display the board and the pieces on it
template <typename T>
void Numerical_Tic_Tac_Toe_Board<T>::display_board() {
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

// Return true if 9 moves are done and no winner
template <typename T>
bool Numerical_Tic_Tac_Toe_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool Numerical_Tic_Tac_Toe_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
Numerical_Tic_TAc_Toe_Player<T>::Numerical_Tic_TAc_Toe_Player(string name, T symbol) : Player<T>(name, symbol) {
    this->Symbol1=symbol;
    Player1Moves= {1 , 3 , 5 , 7 , 9};
    Player2Moves= {2 , 4 , 6 , 8};
}

template <typename T>
void Numerical_Tic_TAc_Toe_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
    if (this->Symbol1 == 1){
        cout<<"Please enter a number from theese number : ";
        for(auto it : Player1Moves){
            cout<<it<<" ";
        }
        cout<<endl;
        int n;
        while(true){
            cin>>n;
            auto it = find(Player1Moves.begin()  , Player1Moves.end() , n);
            if(it==Player1Moves.end()){
                cout<<"Please insert a correct value: ";
            
            }
            else {
                break;
            }
        }
        this->symbol=n;
         for(int i=0;i<Player1Moves.size();i++){
            if(Player1Moves[i]==n){
                Player1Moves.erase(Player1Moves.begin() + i);
            }
        }
    }
    else if(this->Symbol1==2){
        cout<<"Please enter a number from theese number : ";
        for(auto it : Player2Moves){
            cout<<it<<" ";
        }
        cout<<endl;
        int n;
         while(true){
            cin>>n;
            auto it = find(Player2Moves.begin()  , Player2Moves.end() , n);
            if(it==Player2Moves.end()){
                cout<<"Please insert a correct value: ";
            }
        else {
                break;
            }
        }
        this->symbol=n;
        for(int i=0;i<Player2Moves.size();i++){
            if(Player2Moves[i]==n){
                Player2Moves.erase(Player2Moves.begin() + i);
            }
        }

    }
}

// Constructor for X_O_Random_Player
template <typename T>
Numerical_Tic_Tac_Toe_Random_Player<T>::Numerical_Tic_Tac_Toe_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    RandomPlayer1Moves= {1 , 3 , 5 , 7 , 9};
    RandomPlayer2Moves= {2 , 4 , 6 , 8};
    this->Symbol1=symbol;
    
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}
template <typename T>
void Numerical_Tic_Tac_Toe_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
    if (this->Symbol1 == 1) {
    random_device rd; 
    mt19937 gen(rd()); 
    uniform_int_distribution<> dis(0, RandomPlayer1Moves.size() - 1);
    int randomIndex = dis(gen);
    this->Symbol = RandomPlayer1Moves[randomIndex];
    RandomPlayer1Moves.erase(RandomPlayer1Moves.begin() + randomIndex);
}
    else if(this->Symbol1==2){
        random_device rd; 
        mt19937 gen(rd()); 
        uniform_int_distribution<> dis(0, RandomPlayer2Moves.size() - 1);
        int randomIndex = dis(gen);
        this->Symbol = RandomPlayer2Moves[randomIndex];
        RandomPlayer2Moves.erase(RandomPlayer2Moves.begin() + randomIndex);
        for(auto it :RandomPlayer2Moves )cout<<it<<endl;

    }
}
#endif 

