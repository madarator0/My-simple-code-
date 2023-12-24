#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct obj_arry {
    int vail;
    bool sint = false;
    int krat = 1;
};

void print(obj_arry n[], int size) {
    cout << "-------------------------------------\n";
    for (int i = 0; i < size; i++) {
        cout << n[i].vail << " ";
        if ((i + 1) % 10 == 0) {
            cout << endl;
        }
    }
}

void dilpi(obj_arry m[], int size) {
    for(int i = 0; i < size; i++) {
        for ( int j = i+1; j < size; j++) {
            if(m[i].sint) {
                break;
            }
            else {
                if (m[i].vail == m[j].vail) {
                    m[j].sint = true;
                    m[i].krat++;
                }
            }
        }
    }
}

void b_sort(obj_arry m[], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i+1; j < size; j++) {
            if (m[i].vail > m[j].vail) {
                obj_arry tmp = m[j];
                m[j] = m[i];
                m[i] = tmp;
            }
        }
    }
}

void s_sort(obj_arry m[], int m2[], int size_m2) {
    int c = 0;
    int a = 0;
    while (c != size_m2) {
        if (!m[a].sint) {
            m2[c] = m[a].vail;
            c++;
        }
        a++;
    }
}


int cou(obj_arry m[], int size) {
    int c = 0;
    for (int i = 0; i < size; i++) {
        if (!m[i].sint) {
            c++;
        }
    }
    return c;
}

int main() {
    srand(time(0));
    obj_arry m[200];
    for (int i = 0; i < 200; i++) {
        m[i].vail = 1 + rand() % 100;
    }
    int size_m = sizeof(m) / sizeof(m[0]);

    print(m, size_m);

    dilpi(m, size_m);

    print(m, size_m);

    b_sort(m, size_m);

    print(m, size_m);

    const int size_m2 = cou(m, size_m);
    int m2[size_m2];
    s_sort(m, m2, size_m2);
    
    cout << "-------------------------------------\n";

    for(int i = 0; i < size_m2; i++) {
        cout << m2[i] << " ";
        if((i+1)%10==0) {
            cout << endl;
        }
    }
    
    cout << "\n-------------------------------------\n";
    
    for(int i = 0; i < size_m; i++) {
        if(!m[i].sint) {
            cout << m[i].vail << "---";
            for(int j = 0; j < m[i].krat; j++) {
                cout << "|";
            }
            cout << endl;
        }
    }

    return 0;
}
