#include <iostream>
#include <vector>
using namespace std;

const int BS = 8;
const int W = 1;
const int B = -1;

const int DR = 1;
const int DL = 2;
const int UR = 3;
const int UL = 4;

struct ChessPiece {
    int team = 0;
    char symbol = ' ';
};

ChessPiece board[BS][BS];

void initBoard() {
    board[0][0] = {W, 'r'};
    board[0][1] = {W, 'n'};
    board[0][2] = {W, 'b'};
    board[0][3] = {W, 'q'};
    board[0][4] = {W, 'k'};
    board[0][5] = {W, 'b'};
    board[0][6] = {W, 'n'};
    board[0][7] = {W, 'r'};
    
    for (int i = 0; i < BS; i++) {
        board[1][i] = {W, 'p'};
        board[6][i] = {B, 'P'};
    }

    board[7][0] = {B, 'R'};
    board[7][1] = {B, 'N'};
    board[7][2] = {B, 'B'};
    board[7][3] = {B, 'Q'};
    board[7][4] = {B, 'K'};
    board[7][5] = {B, 'B'};
    board[7][6] = {B, 'N'};
    board[7][7] = {B, 'R'};
}

void printBoard() {
    cout << "\033[2J\033[1;1H";
    cout << "  0 1 2 3 4 5 6 7\n";
    
    for (int i = 0; i < BS; i++) {
        cout << i << " ";
        
        for (int j = 0; j < BS; j++) {
            cout << board[i][j].symbol << " ";
        }
        
        cout << i << endl;
    }
    
    cout << "  0 1 2 3 4 5 6 7\n";
}

bool checkBoard(int x, int y) {
    return (x >= 0 && x < BS && y >= 0 && y < BS);
}

vector<pair<int, int>> checkD(int x, int y, int ch, int player) {
    vector<pair<int, int>> allMove;
    int nx = 1, ny = 1;
    
    if (ch == DL || ch == UL) {
        ny *= -1;
    }
    
    if (ch == UR || ch == UL) {
        nx *= -1;
    }

    int newX = x + nx;
    int newY = y + ny;

    while (checkBoard(newX, newY) && board[newX][newY].team != player) {
        if ((board[newX][newY].team * -1) == player) {
            break;
        }
        
        allMove.push_back(make_pair(newX - nx, newY - ny));
        newX += nx;
        newY += ny;
    }

    return allMove;
}

vector<pair<int, int>> checkP(int x, int y, int ch, int player) {
    vector<pair<int, int>> allMove;
    int nx = 0, ny = 0;
    
    if (ch == DR || ch == UR) {
        ny = 0;
        
        if (ch == DR) {
            nx = 1;
        } else {
            nx = -1;
        }
    }
    
    if (ch == DL || ch == UL) {
        nx = 0;
        
        if (ch == DL) {
            ny = 1;
        } else {
            ny = -1;
        }
    }

    int newX = x + nx;
    int newY = y + ny;

    while (checkBoard(newX, newY) && board[newX][newY].team != player) {
        if ((board[newX][newY].team * -1) == player) {
            break;
        }
        
        allMove.push_back(make_pair(newX - nx, newY - ny));
        newX += nx;
        newY += ny;
    }

    return allMove;
}

vector<pair<int, int>> allMoves_P(int x, int y, int player) {
    vector<pair<int, int>> allMove;
    
    if (player == W) {
        if (x == 1) {
            allMove.push_back(make_pair(x + 1, y));
            allMove.push_back(make_pair(x + 2, y));
        } else {
            if (checkBoard(x + 1, y) && board[x + 1][y].team == 0) {
                allMove.push_back(make_pair(x + 1, y));
            }
            
            if (checkBoard(x + 1, y + 1) && board[x + 1][y + 1].team == -player) {
                allMove.push_back(make_pair(x + 1, y + 1));
            }
            
            if (checkBoard(x + 1, y - 1) && board[x + 1][y - 1].team == -player) {
                allMove.push_back(make_pair(x + 1, y - 1));
            }
        }
    } else {
        if (x == 6) {
            allMove.push_back(make_pair(x - 1, y));
            allMove.push_back(make_pair(x - 2, y));
        } else {
            if (checkBoard(x - 1, y) && board[x - 1][y].team == 0) {
                allMove.push_back(make_pair(x - 1, y));
            }
            
            if (checkBoard(x - 1, y + 1) && board[x - 1][y + 1].team == -player) {
                allMove.push_back(make_pair(x - 1, y + 1));
            }
            
            if (checkBoard(x - 1, y - 1) && board[x - 1][y - 1].team == -player) {
                allMove.push_back(make_pair(x - 1, y - 1));
            }
        }
    }
    
    return allMove;
}

vector<pair<int, int>> allMoves_R(int x, int y, int player) {
    vector<pair<int, int>> allMove;
    
    for (int i = 1; i <= 4; i++) {
        vector<pair<int, int>> tmp = checkP(x, y, i, player);
        allMove.insert(allMove.end(), tmp.begin(), tmp.end());
    }
    
    return allMove;
}

vector<pair<int, int>> allMoves_N(int x, int y, int player) {
    vector<pair<int, int>> allMove;
    
    if (checkBoard(x + 2, y + 1) && board[x + 2][y + 1].team != player) {
        allMove.push_back(make_pair(x + 2, y + 1));
    }
    
    if (checkBoard(x + 2, y - 1) && board[x + 2][y - 1].team != player) {
        allMove.push_back(make_pair(x + 2, y - 1));
    }
    
    if (checkBoard(x - 2, y + 1) && board[x - 2][y + 1].team != player) {
        allMove.push_back(make_pair(x - 2, y + 1));
    }
    
    if (checkBoard(x - 2, y - 1) && board[x - 2][y - 1].team != player) {
        allMove.push_back(make_pair(x - 2, y - 1));
    }
    
    if (checkBoard(x + 1, y + 2) && board[x + 1][y + 2].team != player) {
        allMove.push_back(make_pair(x + 1, y + 2));
    }
    
    if (checkBoard(x - 1, y + 2) && board[x - 1][y + 2].team != player) {
        allMove.push_back(make_pair(x - 1, y + 2));
    }
    
    if (checkBoard(x + 1, y - 2) && board[x + 1][y - 2].team != player) {
        allMove.push_back(make_pair(x + 1, y - 2));
    }
    
    if (checkBoard(x - 1, y - 2) && board[x - 1][y - 2].team != player) {
        allMove.push_back(make_pair(x - 1, y - 2));
    }
    
    return allMove;
}

vector<pair<int, int>> allMoves_B(int x, int y, int player) {
    vector<pair<int, int>> allMove;
    
    for (int i = 1; i <= 4; i++) {
        vector<pair<int, int>> tmp = checkD(x, y, i, player);
        allMove.insert(allMove.end(), tmp.begin(), tmp.end());
    }
    
    return allMove;
}

vector<pair<int, int>> allMoves_Q(int x, int y, int player) {
    vector<pair<int, int>> allMove;
    
    vector<pair<int, int>> tmpD;
    vector<pair<int, int>> tmpP;
    
    for (int i = 1; i <= 4; i++) {
        tmpD = checkD(x, y, i, player);
        allMove.insert(allMove.end(), tmpD.begin(), tmpD.end());
    }
    
    for (int i = 1; i <= 4; i++) {
        tmpP = checkP(x, y, i, player);
        allMove.insert(allMove.end(), tmpP.begin(), tmpP.end());
    }
    
    return allMove;
}

vector<pair<int, int>> allMoves_K(int x, int y, int player) {
    vector<pair<int, int>> allMove;

    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) {
                continue;
            }

            int newX = x + i;
            int newY = y + j;

            if (checkBoard(newX, newY) && (board[newX][newY].team == 0 || board[newX][newY].team == -player)) {
                allMove.push_back(make_pair(newX, newY));
            }
        }
    }

    return allMove;
}

void updateBoard(int fromX, int fromY, int toX, int toY) {
    board[toX][toY] = board[fromX][fromY];
    board[fromX][fromY] = {0, ' '};
}

bool step(int x, int y, int player) {
    if (board[x][y].team != player) {
        cout << "Invalid move. Choose your own piece." << endl;
        return false;
    }

    vector<pair<int, int>> possibleMoves;

    switch (board[x][y].symbol) {
    case 'p':
    case 'P':
        possibleMoves = allMoves_P(x, y, player);
        break;
    case 'r':
    case 'R':
        possibleMoves = allMoves_R(x, y, player);
        break;
    case 'n':
    case 'N':
        possibleMoves = allMoves_N(x, y, player);
        break;
    case 'b':
    case 'B':
        possibleMoves = allMoves_B(x, y, player);
        break;
    case 'q':
    case 'Q':
        possibleMoves = allMoves_Q(x, y, player);
        break;
    case 'k':
    case 'K':
        possibleMoves = allMoves_K(x, y, player);
        break;
    default:
        cout << "Invalid piece." << endl;
        return false;
    }

    if (possibleMoves.empty()) {
        cout << "Selected piece has no valid moves. Choose another piece." << endl;
        return false;
    }

    pair<int, int> selectedMove;

    while (true) {
        cout << "Possible moves for selected piece: ";
        
        for (const auto& move : possibleMoves) {
            cout << "(" << move.first << ", " << move.second << ") ";
        }
        
        cout << "\nEnter your move (x y): ";
        cin >> selectedMove.first >> selectedMove.second;
        for (const auto& move : possibleMoves) {
            if (selectedMove == move) {
                updateBoard(x, y, selectedMove.first, selectedMove.second);
                return true;
            }
        }

        cout << "Invalid move. Try again." << endl;
    }
}

int main() {
    initBoard();
    printBoard();

    int currentPlayer = W;

    while (true) {
        int x, y;
        
        cout << "Player " << (currentPlayer == W ? "White" : "Black") << "'s turn. Enter the coordinates (x y) of the piece you want to move: ";
        cin >> x >> y;

        if (!checkBoard(x, y) || board[x][y].team != currentPlayer || !step(x, y, currentPlayer)) {
            cout << "Invalid move. Try again." << endl;
            continue;
        }

        printBoard();

        currentPlayer = (currentPlayer == W) ? B : W;
    }

    return 0;
}
