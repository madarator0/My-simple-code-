#include <iostream>
#include <cstdlib>
using namespace std;

const int BOARD_SIZE = 8;
int W = 12, B = 12;

const int DR = 1;
const int DL = 2;
const int UR = 3;
const int UL = 4;

const int WHITE = -1;
const int BLACK = 1;

struct ChessPiece {
    int team = 0;
    bool king = false;
};

ChessPiece zero;
ChessPiece pole[BOARD_SIZE][BOARD_SIZE];

void print() {
    cout << "\033[2J\033[1;1H";
    cout << "  ";
    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << i << " ";
    }
    cout << endl;
    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << i << " ";
        for (int j = 0; j < BOARD_SIZE; j++) {
            char piece = ' ';
            if (pole[i][j].team == WHITE) {
                piece = 'w';
                if(pole[i][j].king) 
                    piece = 'W';
                }
            else if (pole[i][j].team == BLACK) {
                piece = 'b';
                if(pole[i][j].king) 
                    piece = 'B';
            }
            cout << piece << " ";
        }
        if (i==1) {
            cout << "            W = " << W;
        }
        if (i==6) {
            cout << "            B = " << B;
        }
        
        cout << endl;
    }
}

void gen() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if ((i + j) % 2 != 0) {
                if (i < 3) pole[i][j].team = WHITE;
                else if (i > 4) pole[i][j].team = BLACK;
            }
        }
    }
}

void checkKingPromotion(int x, int y) {
    if ((pole[x][y].team == WHITE && x == BOARD_SIZE - 1) || (pole[x][y].team == BLACK && x == 0)) {
        pole[x][y].king = true;
        cout << "Piece promoted to king!" << endl;
    }
}

bool eat_chaek(int x, int y, int ch, int player) {
    int nx = 2, ny = 2;

    if (ch == DL || ch == UL) {
        ny *= -1;
    }
    if (ch == UR || ch == UL) {
        nx *= -1;
    }
    
    if (x + nx >= 0 && x + nx < BOARD_SIZE && y + ny >= 0 && y + ny < BOARD_SIZE) {
        if (player == (pole[x + nx / 2][y + ny / 2].team * -1) && pole[x + nx][y + ny].team == 0) {
            return true;
        } else {
            return false;
        }
    }

    return false;
}

void eat(int x, int y, int ch, int player, bool king) {
    int nx = 2, ny = 2;
    if (ch == DL || ch == UL) {
        ny *= -1;
    } 
    if (ch == UR || ch == UL) {
        nx *= -1;
    }

        if (eat_chaek(x, y, ch, player)) {
            pole[x + nx][y + ny] = pole[x][y];
            pole[x][y] = zero;
            pole[x + (nx / 2)][y + (ny / 2)] = zero;
            
            if (player == BLACK) {
                W--;
            } else if (player == WHITE){
                B--;
            }
        }
    
    
    print();
    
    bool dr = false;
    bool dl = false;
    bool ur = false;
    bool ul = false;

    int choice;

    if (eat_chaek((x + nx), (y + ny), DR, player)) {
        cout << "1. Eat a chip (" << x + 1 << ", " << y + 1 << ")" << endl;
        cout << "Move to (" << x + 2 << ", " << y + 2 << ")" << endl;
        dr = true;
    }

    if (eat_chaek((x + nx), (y + ny), DL, player)) {
        cout << "2. Eat a chip (" << x + 1 << ", " << y - 1 << ")" << endl;
        cout << "Move to (" << x + 2 << ", " << y - 2 << ")" << endl;
        dl = true;
    }

    if (eat_chaek((x + nx), (y + ny), UR, player)) {
        cout << "3. Eat a chip (" << x - 1 << ", " << y + 1 << ")" << endl;
        cout << "Move to (" << x - 2 << ", " << y + 2 << ")" << endl;
        ur = true;
    }

    if (eat_chaek((x + nx), (y + ny), UL, player)) {
        cout << "4. Eat a chip (" << x - 1 << ", " << y - 1 << ")" << endl;
        cout << "Move to (" << x - 2 << ", " << y - 2 << ")" << endl;
        ul = true;
    }
    
    if (!dr && !dl && !ur && !ul) {
        cout << "5. No move" << endl;
    }

    bool validChoice = true;

    while(validChoice && !king) {
        cin >> choice;

        switch (choice) {
            case 1:
                if (dr) {
                    eat((x + nx), (y + ny), DR, player, false);
                    validChoice = false;
                }
                break;
            case 2:
                if (dl) {
                    eat((x + nx), (y + ny), DL, player, false);
                    validChoice = false;
                }
                break;
            case 3:
                if (ur) {
                    eat((x + nx), (y + ny), UR, player, false);
                    validChoice = false;
                }
                break;
            case 4:
                if (ul) {
                    eat((x + nx), (y + ny), UL, player, false);
                    validChoice = false;
                }
                break;
            case 5:
                validChoice = true;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
                break;
        }
    }
}

int chaek_step_K(int x, int y, int ch, int player) {
    int nx = 1, ny = 1, co = 0;
    if (ch == DL || ch == UL) {
        ny *= -1;
    } 
    if (ch == UR || ch == UL) {
        nx *= -1;
    }
    int dx = nx, dy = ny;
    while((x+dx) >= 0 && (y+dy) >= 0 && (x+dx) < BOARD_SIZE && (y+dy) < BOARD_SIZE) {
        if (player == pole[x + dx][y + dy].team) {
            break;
        }
        if(player == (pole[x + dx][y + dy].team * -1)) {
            if (eat_chaek((x+dx-nx), (y+dy-ny), ch, player)) {
                cout << "Eat a chip (" << x + dx << ", " << y + dy << ")" << endl;
            }
            else {
                break;
            }
        }
        dx += nx;
        dy += ny;
        co++;
    }
    return co;
}

int chaek(int x, int y, int player) {
    bool nom = false;
    bool dr = false;
    bool dl = false;
    bool ur = false;
    bool ul = false;
    bool pv = false;

    cout << "Choose an action:" << endl;
    int choice;
    do {
        if (player == -1 || pole[x][y].king) {
            if (pole[x][y].king) {
                int co = chaek_step_K(x, y, DR, player);
                if (co > 0) {
                    cout << "1. Move between (" << x << ", " << y << ") before (" << x + co << ", " << y + co << ")" << endl;
                    dr = true;
                }
            }
            else if ((x + 1) < BOARD_SIZE && (y + 1) < BOARD_SIZE) {
                if (pole[x + 1][y + 1].team == 0) {
                    cout << "1. Move to (" << x + 1 << ", " << y + 1 << ")" << endl;
                    dr = true;
                } 
                else if (eat_chaek(x, y, DR, player)) {
                    cout << "1. Eat a chip (" << x + 1 << ", " << y + 1 << ")" << endl;
                    cout << "Move to (" << x + 2 << ", " << y + 2 << ")" << endl;
                    dr = true;
                }
            }
            if (pole[x][y].king) {
                int co = chaek_step_K(x, y, DL, player);
                if (co > 0) {
                    cout << "2. Move between (" << x << ", " << y << ") before (" << x + co << ", " << y - co << ")" << endl;
                    dl = true;
                }
            }
            else if ((x + 1) < BOARD_SIZE && (y - 1) >= 0) {
                if (pole[x + 1][y - 1].team == 0) {
                    cout << "2. Move to (" << x + 1 << ", " << y - 1 << ")" << endl;
                    dl = true;
                } 
                else if (eat_chaek(x, y, DL, player)) {
                    cout << "2. Eat a chip (" << x + 1 << ", " << y - 1 << ")" << endl;
                    cout << "Move to (" << x + 2 << ", " << y - 2 << ")" << endl;
                    dl = true;
                }
            }
        }

        if (player == 1 || pole[x][y].king) {
            if (pole[x][y].king) {
                int co = chaek_step_K(x, y, UR, player);
                if (co > 0) {
                    cout << "3. Move between (" << x << ", " << y << ") before (" << x - co << ", " << y + co << ")" << endl;
                    ur = true;
                }
            }
            else if ((x - 1) >= 0 && (y + 1) < BOARD_SIZE) {
                if (pole[x - 1][y + 1].team == 0) {
                    cout << "3. Move to (" << x - 1 << ", " << y + 1 << ")" << endl;
                    ur = true;
                } 
                else if (eat_chaek(x, y, UR, player)) {
                    cout << "3. Eat a chip (" << x - 1 << ", " << y + 1 << ")" << endl;
                    cout << "Move to (" << x - 2 << ", " << y + 2 << ")" << endl;
                    ur = true;
                }
            }
            if (pole[x][y].king) {
                int co = chaek_step_K(x, y, UL, player);
                if (co > 0) {
                    cout << "4. Move between (" << x << ", " << y << ") before (" << x - co << ", " << y - co << ")" << endl;
                    ul = true;
                }
            }
            else if ((x - 1) >= 0 && (y - 1) >= 0) {
                if (pole[x - 1][y - 1].team == 0) {
                    cout << "4. Move to (" << x - 1 << ", " << y - 1 << ")" << endl;
                    ul = true;
                } 
                else if (eat_chaek(x, y, UL, player)) {
                    cout << "4. Eat a chip (" << x - 1 << ", " << y - 1 << ")" << endl;
                    cout << "Move to (" << x - 2 << ", " << y - 2 << ")" << endl;
                    ul = true;
                }
            }
        }

        if (!dr && !dl && !ur && !ul) {
            cout << "5. No move" << endl;
            nom = true;
        }

        cin >> choice;
        if (choice == 1) {
            if (dr) {
                pv = true;
            }
        } 
        else if (choice == 2) {
            if (dl) {
                pv = true;
            }
        } 
        else if (choice == 3) {
            if (ur) {
                pv = true;
            }
        } 
        else if (choice == 4) {
            if (ul) {
                pv = true;
            }
        } 
        else if (choice == 5) {
            if (nom) {
                pv = true;
            }
        } 
        else {
            cout << "Invalid choice" << endl;
        }

    } while (!pv);

    return choice;
}

int step(int x, int y, int player) {
    if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) {
        cout << "Error" << endl;
        return 0;
    }

    if (player != pole[x][y].team) {
        cout << "Wrong choice" << endl;
        return 0;
    }
    
    int choice = chaek(x, y, player);
    int nx, ny;
    if (!pole[x][y].king) {

        switch (choice) {
            case 1:
                nx = x + 1;
                ny = y + 1;
                break;
            case 2:
                nx = x + 1;
                ny = y - 1;
                break;
            case 3:
                nx = x - 1;
                ny = y + 1;
                break;
            case 4:
                nx = x - 1;
                ny = y - 1;
                break;
            default:
                return 0;
        }

        if (pole[nx][ny].team == 0) {
            pole[nx][ny] = pole[x][y];
            pole[x][y] = zero;
            checkKingPromotion(nx, ny);
            return 1;
        } 
        else if (pole[x][y].team == pole[nx][ny].team ) {
            return 0;
        }
        else {
            eat(x, y, choice, player, false);
        }

        return 1;
    }
    else {
        int co = chaek_step_K(x, y, choice, player);
        int nx = co, ny = co;
        int fx = 1, fy = 1;
        if (choice == DL || choice == UL) {
            ny *= -1;
            fy *= -1;
        } 
        if (choice == UR || choice == UL) {
            nx *= -1;
            fx *= -1;
        }
        bool ggaa = true;
        int dx, dy;
        do {
            cout << "Enter x: " << endl;
            cin >> dx;
            cout << "Enter y: " << endl;
            cin >> dy;
            if((nx + ny)%2==0) {
                switch (choice) {
                    case 1:
                        if (dx > x && dx <= (x+nx) && dy > y && dy <= (y+ny))
                            ggaa = false;
                        break;
                    case 2:
                        if (dx > x && dx <= (x+nx) && dy < y && dy >= (y+ny))
                            ggaa = false;
                        break;
                    case 3:
                        if (dx < x && dx >= (x+nx) && dy > y && dy <= (y+ny))
                            ggaa = false;
                        break;
                    case 4:
                        if (dx < x && dx >= (x+nx) && dy < y && dy >= (y+ny))
                            ggaa = false;
                        break;
                    default:
                        return 0;
               }
            }
        } while (ggaa);
        do {
            pole[x+fx][y+fy] = zero;
            fx += (fx>0) ? 1 : -1;
            fy += (fy>0) ? 1 : -1;
        } while(dx != x + fx && dy != y + fy);
        pole[x+fx][y+fy] = pole[x][y];
        pole[x][y] = zero;
        return 1;
    }
}

int main() {
    gen();
    print();

    int player = BLACK;

    while (B > 0 && W > 0) {
        cout << (player == BLACK ? "Black's turn" : "White's turn") << endl;

        int x, y;
        cout << "Enter the coordinates (x y) of the piece to move: ";
        cin >> x >> y;

        if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE || pole[x][y].team != player) {
            cout << "Invalid piece. Try again." << endl;
            continue;
        }

        if (step(x, y, player) == 0) {
            continue;
        }

        print();

        if (B == 0) {
            cout << "White wins!" << endl;
            break;
        } 
        else if (W == 0) {
            cout << "Black wins!" << endl;
            break;
        }

        player *= -1;
    }

    return 0;
}