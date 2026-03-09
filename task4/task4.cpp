#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main() {
    ifstream file("list.txt");

    int p, r;
    file >> p >> r;

    vector<int> E(r);
    vector<vector<int>> C(p, vector<int>(r));
    vector<vector<int>> R(p, vector<int>(r));

    for(int i = 0; i < r; i++)
        file >> E[i];

    for(int i = 0; i < p; i++)
        for(int j = 0; j < r; j++)
            file >> C[i][j];

    for(int i = 0; i < p; i++)
        for(int j = 0; j < r; j++)
            file >> R[i][j];
g++
    file.close();

    vector<int> A(r);
    for(int j = 0; j < r; j++) {
        int sum = 0;
        for(int i = 0; i < p; i++)
            sum += C[i][j];
        A[j] = E[j] - sum;
    }

    vector<bool> finished(p, false);
    bool progress;

    do {
        progress = false;
        for(int i = 0; i < p; i++) {
            if(!finished[i]) {
                bool canFinish = true;
                for(int j = 0; j < r; j++) {
                    if(R[i][j] > A[j])
                        canFinish = false;
                }
                if(canFinish) {
                    for(int j = 0; j < r; j++)
                        A[j] += C[i][j];
                    finished[i] = true;
                    progress = true;
                }
            }
        }
    } while(progress);

    bool deadlock = false;
    cout << "Deadlocked processes: ";
    for(int i = 0; i < p; i++) {
        if(!finished[i]) {
            cout << i << " ";
            deadlock = true;
        }
    }
    if(!deadlock)
        cout << "None";

    cout << endl;
    return 0;
}