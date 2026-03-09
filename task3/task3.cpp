#include <iostream>
#include <fstream>
using namespace std;

int main() {

    int pages[1000];
    int n = 0;

    ifstream file("pages.txt");


    while (file >> pages[n]) {
        n++;
    }

    cout << "Frames   Faults per 1000 references\n";

    for (int frames = 1; frames <= 5; frames++) {

        int memory[10];
        int counter[10];
        int ref[10];
        int faults = 0;


        for (int i = 0; i < frames; i++) {
            memory[i] = -1;
            counter[i] = 0;
            ref[i] = 0;
        }

        for (int i = 0; i < n; i++) {

            int page = pages[i];
            bool found = false;


            for (int j = 0; j < frames; j++) {
                if (memory[j] == page) {
                    ref[j] = 1;
                    found = true;
                }
            }

            if (!found) {

                faults++;

                int smallest = 0;

                for (int j = 1; j < frames; j++) {
                    if (counter[j] < counter[smallest]) {
                        smallest = j;
                    }
                }

                memory[smallest] = page;
                counter[smallest] = 0;
                ref[smallest] = 1;
            }

            for (int j = 0; j < frames; j++) {

                counter[j] = counter[j] >> 1;

                if (ref[j] == 1)
                    counter[j] = counter[j] + 128;

                ref[j] = 0;
            }
        }

        double result = (faults * 1000.0) / n;

        cout << frames << "        " << result << endl;
    }

    return 0;
}