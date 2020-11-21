#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

int turn = 0;
int computer, human;
int board[9] = { 0 };
int l_moves[9] = { -1 };
int the_winner = -1;

void display_tutorial() {
    cout << "Welcome in the 'Tic-Tac-Toe' game" << endl
        << "This game is a duel between" << endl
        << "human brain and a computer" << endl << endl;
    cout << "Layout:" << endl
        << "0 | 1 | 2" << endl
        << "---------" << endl
        << "3 | 4 | 5" << endl
        << "---------" << endl
        << "6 | 7 | 8" << endl;
}

bool ask_yes_or_no(string que) {
    string str = "";
    cout << que << endl;
    cin >> str;
    while (str[0] != "Y"[0] && str[0] != "y"[0] && str[0] != "N"[0] && str[0] != "n"[0]) {
        cin >> str;
    }
    cout << endl;
    if (str[0] == "Y"[0] || str[0] == "y"[0]) {
        return true;
    }
    else {
        return false;
    }
}

int ask_number(string que, int low, int high) {
    cout << que << endl;
    int nmb;
    cin >> nmb;
    while (!(nmb <= high && nmb >= low)) {
        cout << endl;
        cin >> nmb;
    }
    return nmb;
}

void pieces() {
    if (ask_yes_or_no("Do you want to start? (y/n)")) {
        system("cls");
        cout << "Then start.." << endl;
        human = 1;
        computer = 2;
        turn = 1;
    }
    else {
        system("cls");
        cout << "You're breave! I'm starting" << endl;
        human = 2;
        computer = 1;
        turn = 1;
    }
    Sleep(418);
}

void new_board() {
    for (int x = 0; x < 9; x++) {
         board[x] = 0;
    }
}

string returnChar(int nmb) {
    if (nmb == 1) {
        return "X";
    } else if (nmb == 2) {
        return "O";
    } else {
        return " ";
    }
}

void display_board() {
    cout << returnChar(board[0]) << " | " << returnChar(board[1]) << " | " << returnChar(board[2]) << endl
        << "---------" << endl
        << returnChar(board[3]) << " | " << returnChar(board[4]) << " | " << returnChar(board[5]) << endl
        << "---------" << endl
        << returnChar(board[6]) << " | " << returnChar(board[7]) << " | " << returnChar(board[8]) << endl;
}

void legal_moves() {
    int nmb = 0;
    for (int x = 0; x < 9; x++) {
        l_moves[x] = -1;
    }
    for (int x = 0; x < 9; x++) {
        if (board[x] == 0) {
            l_moves[nmb] = x;
            nmb++;
        }
    }
}

int winner() {
    int ways_to_win[8][3] = {
        {0,1,2},
        {3,4,5},
        {6,7,8},
        {0,3,6},
        {1,4,7},
        {2,5,8},
        {0,4,8},
        {2,4,6}
    };
    for (int x = 0; x < 8; x++) {
        int to3 = 0;
        for (int y = 0; y < 3; y++) {
            if (board[ways_to_win[x][y]] == 1) {
                to3++;
            }
        }
        if (to3 == 3) {
            return 1;
        }
    }
    for (int a = 0; a < 8; a++) {
        int to3 = 0;
        for (int y = 0; y < 3; y++) {
            if (board[ways_to_win[a][y]] == 2) {
                to3++;
            }
        }
        if (to3 == 3) {
            return 2;
        }
    }
    return 0;
}

int human_move() {
    legal_moves();
    bool isLegal = false;
    for (int x = 0; x < 9; x++) {
        if (l_moves[x] != -1) {
            isLegal = true;
        }
    }
    bool isMoveLegal = false;
    int where;
    if (isLegal) {
        while (!isMoveLegal) {
            cout << "Where will you move? (0-8)";
            cin >> where;
            while (where < 0 || where > 8) {
                cin >> where;
            }
            // check if is legal
            for (int x = 0; x < 9; x++) {
                if (l_moves[x] == where) {
                    isMoveLegal = true;
                }
            }
        }
        return where;
    }
    else {
        return -1;
    }
}

int computer_move() {
    legal_moves();
    bool isLegal = false;
    for (int x = 0; x < 9; x++) {
        if (l_moves[x] != -1) {
            isLegal = true;
        }
    }
    bool isMoveLegal = false;
    if (isLegal) {
        int best_moves[9] = { 4,0,2,6,8,1,3,5,7 };
        cout << "I choose: ";
        while (!isMoveLegal) {
            for (int x = 0; x < 9; x++) {
                if (board[best_moves[x]] == 0) {
                    cout << best_moves[x];
                    return best_moves[x];
                }
            }
        }
    } else {
        return -1;
    }
}

void congrat_winner() {
    if (the_winner != -1) {
        if (the_winner == 1) {
            cout << "Human won";
        }
        else {
            cout << "Computer won";
        }
    }
    else {
        cout << "Tie.";
    }
    cout << endl;
    if (the_winner == 1) {
        cout << "You beat me!";
    } else if (the_winner == 2) {
        cout << "AI will take over the world soon.";
    }
    cout << endl << endl;
    system("pause");
}

int main() {
    /*setlocale(LC_ALL, "pl_PL");*/
    display_tutorial();
    pieces();
    new_board();
    system("cls");
    while (winner() == 0) {
        display_board();
        if ((turn == 1 && human == 1) || (turn == 2 && human == 2)) {
            //human
            board[human_move()] = 1;
        }
        else {
            //computer
            board[computer_move()] = 2;
            Sleep(1234); 
        }
        system("cls");
        the_winner = winner();
        if (the_winner == 1 || the_winner == 2) {
            congrat_winner();
        } else {
            if (turn == 1) {
                turn = 2;
            }
            else {
                turn = 1;
            }
        }
    }
    return 0;
}