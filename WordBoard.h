#ifndef WORD_BOARD_H
#define WORD_BOARD_H

#include <iostream>
#include <vector>
#include <unordered_set>
#include <fstream>
#include <limits>
#include <cctype>
#include "BoardGame_Classes.h"

using namespace std;

// Dictionary class
class Dictionary {
private:
    unordered_set<string> words;

public:
    void load(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cerr << "Error: Could not open dictionary file.\n";
            exit(1);
        }

        string word;
        while (file >> word) {
            if (word.length() == 3) {
                words.insert(word);
            }
        }
    }

    bool is_valid(const string& word) const {
        return words.find(word) != words.end();
    }
};

// WordBoard class inheriting from Board
class WordBoard : public Board<char> {
private:
    char board[3][3];
    int n_moves;
    Dictionary* dictionary;

public:
    WordBoard(Dictionary* dict) : n_moves(0), dictionary(dict) {
        this->rows = 3;
        this->columns = 3;

        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                board[i][j] = ' ';
    }

    bool update_board(int x, int y, char symbol) override {
        if (x < 0 || x >= 3 || y < 0 || y >= 3 || board[x][y] != ' ')
            return false;
        board[x][y] = toupper(symbol);
        ++n_moves;
        return true;
    }

    void display_board() override {
        cout << "  0   1   2\n";
        for (int i = 0; i < 3; ++i) {
            cout << i << " ";
            for (int j = 0; j < 3; ++j) {
                cout << board[i][j];
                if (j < 2) cout << " | ";
            }
            cout << "\n";
            if (i < 2) cout << " ---|---|---\n";
        }
    }

    bool is_win() override {
        return check_rows() || check_cols() || check_diagonals();
    }

    bool is_draw() override {
        return n_moves == 9 && !is_win();
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }

private:
    bool check_rows() const {
        for (int i = 0; i < 3; ++i) {
            string word;
            for (int j = 0; j < 3; ++j)
                word += board[i][j];
            if (dictionary->is_valid(word)) return true;
        }
        return false;
    }

    bool check_cols() const {
        for (int j = 0; j < 3; ++j) {
            string word;
            for (int i = 0; i < 3; ++i)
                word += board[i][j];
            if (dictionary->is_valid(word)) return true;
        }
        return false;
    }

    bool check_diagonals() const {
        string diag1, diag2;
        for (int i = 0; i < 3; ++i) {
            diag1 += board[i][i];
            diag2 += board[i][2 - i];
        }
        return dictionary->is_valid(diag1) || dictionary->is_valid(diag2);
    }
};

// WordPlayer class
class WordPlayer {
protected:
    string name;

public:
    WordPlayer(const string& player_name) : name(player_name) {}
    virtual void getMove(int& x, int& y, char& letter) = 0;
    string getName() const { return name; }
    virtual ~WordPlayer() {}
};

// HumanPlayer class inheriting from WordPlayer
class HumanPlayer : public WordPlayer {
public:
    HumanPlayer(const string& player_name) : WordPlayer(player_name) {}

    void getMove(int& x, int& y, char& letter) override {
        while (true) {
            cout << name << ", enter your move (row column letter): ";
            cin >> x >> y >> letter;

            // Validate input
            if (cin.fail() || x < 0 || x >= 3 || y < 0 || y >= 3 || !isalpha(letter)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid row (0-2), column (0-2), and a letter.\n";
                continue;
            }
            letter = toupper(letter);
            break;
        }
    }
};

// RandomAIPlayer class inheriting from WordPlayer
class RandomAIPlayer : public WordPlayer {
public:
    RandomAIPlayer(const string& player_name) : WordPlayer(player_name) {
        srand(time(0));
    }

    void getMove(int& x, int& y, char& letter) override {
        x = rand() % 3;
        y = rand() % 3;
        letter = 'A' + rand() % 26;
        cout << name << " chooses: (" << x << ", " << y << ", " << letter << ")\n";
    }
};

// Gamemanager class
class Gamemanager {
private:
    WordBoard* board;
    WordPlayer* players[2];

public:
    Gamemanager(WordBoard* b, WordPlayer* p1, WordPlayer* p2) : board(b) {
        players[0] = p1;
        players[1] = p2;
    }

    void run() {
        int x, y;
        char letter;
        board->display_board();

        while (!board->game_is_over()) {
            for (int i = 0; i < 2; ++i) {
                players[i]->getMove(x, y, letter);
                while (!board->update_board(x, y, letter)) {
                    cout << "Invalid move. Try again.\n";
                    players[i]->getMove(x, y, letter);
                }

                board->display_board();
                if (board->is_win()) {
                    cout << players[i]->getName() << " wins by forming a word!\n";
                    return;
                }
                if (board->is_draw()) {
                    cout << "It's a draw!\n";
                    return;
                }
            }
        }
    }
};

#endif // WORD_BOARD_H
