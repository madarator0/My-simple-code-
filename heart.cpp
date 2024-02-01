#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

void rotate(vector<vector<string>>& m) {
    int s = m.size();
    vector<vector<string>> n(s, vector<string>(s));
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < s; j++) {
            n[i][j] = m[j][s-1-i];
        }
    }
    m = move(n); 
}

int main() {
    const int sizeX = 62;
    const int sizeY = 64;
    vector<vector<string>> p(sizeX, vector<string>(sizeY, " "));
    for (float t = 0; t < 2 * M_PI; t += 0.005) {
        float x = (16 * pow(sin(t), 3))*1.75;
        float y = (13*cos(t) - 5*cos(2*t) - 2*cos(3*t) - cos(4*t))*1.48;
        int nx = round(x) + 30;
        int ny = round(y) + 30;
        if (nx >= 0 && nx < sizeX && ny >= 0 && ny < sizeY) {
            p[nx][ny] = "x";
        }
    }
    
    rotate(p);
    
    for (const auto& row : p) {
        for (const auto& elem : row) {
            cout << elem;
        }
        cout << '\n';
    }
    return 0;
}