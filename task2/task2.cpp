#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <map>
using namespace std;

void countWords(string lines[], int start, int end, map<string, int> &wordCount, int thread_number) {
    for (int i = start; i < end; i++) {
        string line = lines[i];
        string word;
        stringstream ss(line);
        while (ss >> word) {
            wordCount[word]++;
        }
    }

    cout << "Thread " << thread_number << " intermediate counts:" << endl;
    for (auto &pair : wordCount) {
        cout << pair.first << ": " << pair.second << endl;
    }
}

int main() {
    ifstream file("sample.txt");
    if (!file.is_open()) {
        cout << "Cannot open file!" << endl;
        return 1;
    }

    string lines[100]; 
    int totalLines = 0;

    while (getline(file, lines[totalLines])) {
        totalLines++;
        if (totalLines >= 100) break; // keep it simple
    }
    file.close();

    int N = 2;
    thread t1, t2;

    map<string, int> count1;
    map<string, int> count2;

    int middle = totalLines / 2;

    // Start threads
    t1 = thread(countWords, lines, 0, middle, ref(count1), 1);
    t2 = thread(countWords, lines, middle, totalLines, ref(count2), 2);

    t1.join();
    t2.join();

    // Merge results
    map<string, int> finalCount = count1;
    for (auto &pair : count2) {
        finalCount[pair.first] += pair.second;
    }

   
    cout << "Final word counts:" << endl;
    for (auto &pair : finalCount) {
        cout << pair.first << ": " << pair.second << endl;
    }

    return 0;
}