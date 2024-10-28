#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>

using namespace std;

int main() {
    ifstream inFile("vers.txt");
    ofstream outFile("vers_word_lengths.txt");
    map<int, int> word_lengths; // Szóhossz és annak darabszáma
    string line, word;

    // Minden sor beolvasása a fájlból
    while (getline(inFile, line)) {
        stringstream ss(line); // Szavak szétbontása stringstream-mel
        // Szavak feldolgozása a sorban
        while (ss >> word) {
            int length = word.length();
            word_lengths[length]++; // Szóhossz számláló növelése
        }
    }

    // Eredmények kiírása konzolra és fájlba
    cout << "Szohosszusagok szama:" << endl;
    for (const auto& entry : word_lengths) {
        cout << "Hossz " << entry.first << ": " << entry.second << " szo" << endl;
        outFile << "Hossz " << entry.first << ": " << entry.second << " szo" << endl;
    }

    // Fájlok bezárása
    inFile.close();
    outFile.close();

    return 0;
}

