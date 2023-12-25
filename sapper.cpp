#include <iostream>

using namespace std;

const int SIZE = 10;
int BOMBS = 8;

struct obj {
    bool boom = false;
    bool ispol = false;
    bool flag = false;
    int boomb = 0;
    char vid = 'X';
};

obj m[SIZE][SIZE];

int gen() {
    srand(time(0));
    for (int i = 0; i < BOMBS; i++) {
        m[rand() % SIZE][rand() % SIZE].boom = true;
    }
    return 0;
}

int pole() {
    cout << "\033[2J\033[1;1H";
    cout << "  ";
    for (int i = 0; i < SIZE; i++) {
        cout << i << " ";
    }
    cout << endl;

    for (int i = 0; i < SIZE; i++) {
        cout << i << " ";
        for (int j = 0; j < SIZE; j++) {
            cout << m[i][j].vid << " ";
        }
        cout << endl;
    }
    return 0;
}

int cba(int x, int y) {
    int o = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int a = x + i;
            int s = y + j;
            if (a >= 0 && a < SIZE && s >= 0 && s < SIZE) {
                if (m[a][s].boom) {
                    o++;
                }
            }
        }
    }
    return o;
}

bool wins() {
    bool winr = true;
    for (int i = 0; i < SIZE && winr; i++) {
        for (int j = 0; j < SIZE && winr; j++) {
            if (m[i][j].boom && !m[i][j].flag) {
                winr = false;
            }
        }
    }
    return winr;
}

int Flag(int x, int y, int flag) {
    if (m[x][y].flag == false) {
        if (flag > 0) {
            m[x][y].vid = 'F';
            m[x][y].flag = true;
            flag--;
        }
        else {
            cout << "У вас закончились флаги!" << endl;
        }
    }
    else {
        cout << "На этом месте уже есть флаг!\n";
        int u;
        cout << "Оставить как есть? (1 - да, 0 - убрать флаг): ";
        cin >> u;
        if (u == 0) {
            m[x][y].flag = false;
            m[x][y].vid = 'X';
            flag++;
        }
    }
    if (wins())
        return 1;
    else
        return 0;
}

int tap(int x, int y) {
    if (m[x][y].ispol) {
        return 0;
    } else if (m[x][y].boom) {
        return -1;
    } else {
        m[x][y].ispol = true;
        int a = cba(x, y);
        m[x][y].vid = (a == 0) ? ' ' : (a + '0');
        m[x][y].boomb = a;

        if (a == 0) {
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    int a = x + i;
                    int s = y + j;
                    if (a >= 0 && a < SIZE && s >= 0 && s < SIZE) {
                        tap(a, s);
                    }
                }
            }
        }

        if (wins()) 
            return 1;
        else
            return 0;
    }
}


int main() {
    setlocale(LC_ALL, "RU");
    int command = 0, i = 0, j = 0, result = 1, flag = BOMBS;
    gen();

    do {
        pole();
        cout << "Введите команду (0 для установки флага, 1 для выбора): ";
        cin >> command;

        if (command == 0) {
            cout << "Введите координаты (i, j): ";
            cin >> i >> j;
            result = Flag(i, j, flag);
        } else {
            cout << "Введите координаты (i, j): ";
            cin >> i >> j;
            result = tap(i, j);
        }
    } while (result != -1 && result != 1);

    pole();

    if (result == -1) {
        cout << "Вы проиграли :(\n";
    } else {
        cout << "Вы выиграли!!!\n";
    }
     cout << "  ";
    for (int i = 0; i < SIZE; i++) {
        cout << i << " ";
    }
    cout << endl;

    for (int i = 0; i < SIZE; i++) {
        cout << i << " ";
        for (int j = 0; j < SIZE; j++) {
            if (m[i][j].boom) {
                cout << "B ";
            }
            else {
                cout << "  ";
            }
        }
        cout << endl;
    }
    return 0;
}
    