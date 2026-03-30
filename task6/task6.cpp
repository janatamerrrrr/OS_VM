#include <iostream>
#include <filesystem>
#include <map>
using namespace std;
namespace fs = filesystem;

int main() {
    string folder;
    int binSize;

    cout << "Enter folder path: ";
    cin >> folder;

    cout << "Enter bin size: ";
    cin >> binSize;

    map<int, int> bins;

    for (auto file : fs::recursive_directory_iterator(folder)) {

        if (!fs::is_regular_file(file)) continue;

        int size = fs::file_size(file);

        int binNumber = size / binSize;

        bins[binNumber]++;
    }

    cout << "\nHistogram:\n";

    for (auto pair : bins) {
        int start = pair.first * binSize;
        int end = start + binSize - 1;

        cout << start << " - " << end << " : " << pair.second << endl;
    }

    return 0;
}