#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>

using namespace std;

int main() {
    ifstream inFile("vers.txt");
    ofstream outFile("vers_word_lengths.txt");
    map<int, int> word_lengths; // Sz�hossz �s annak darabsz�ma
    string line, word;

    // Minden sor beolvas�sa a f�jlb�l
    while (getline(inFile, line)) {
        stringstream ss(line); // Szavak sz�tbont�sa stringstream-mel
        // Szavak feldolgoz�sa a sorban
        while (ss >> word) {
            int length = word.length();
            word_lengths[length]++; // Sz�hossz sz�ml�l� n�vel�se
        }
    }

    // Eredm�nyek ki�r�sa konzolra �s f�jlba
    cout << "Szohosszusagok szama:" << endl;
    for (const auto& entry : word_lengths) {
        cout << "Hossz " << entry.first << ": " << entry.second << " szo" << endl;
        outFile << "Hossz " << entry.first << ": " << entry.second << " szo" << endl;
    }

    // F�jlok bez�r�sa
    inFile.close();
    outFile.close();

    return 0;
}

