#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

// Tanuló osztály, amely a nevet és az átlagot tárolja
class Tanulo {
public:
    string nev;
    double atlag;

    Tanulo(string nev, double atlag) : nev(nev), atlag(atlag) {}

    // Operátor túlterhelés a rendezéshez
    bool operator<(const Tanulo& other) const {
        return atlag > other.atlag; // Csökkenõ sorrend
    }
};

// Fõ függvény
int main() {
    ifstream inputFile("TanAtlag.txt");
    ofstream outputFile("Tanulok_Atlaga.txt");

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cerr << "Hiba a fájl megnyitásakor!" << endl;
        return 1;
    }

    map<string, pair<int, int>> tanulok; // tanulók név, összesített (kredit * jegy) és kredit összeg

    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string nev, targy;
        int kredit, jegy;

        ss >> nev >> targy >> kredit >> jegy;

        // Ellenõrizzük, hogy a név nem üres, mielõtt feldolgozzuk
        if (nev.empty()) continue;

        if (tanulok.find(nev) == tanulok.end()) {
            tanulok[nev] = { 0, 0 }; // Ha új tanuló, inicializáljuk
        }

        tanulok[nev].first += kredit * jegy;
        tanulok[nev].second += kredit;
    }

    inputFile.close();

    vector<Tanulo> tanuloLista;
    for (const auto& t : tanulok) {
        double atlag = static_cast<double>(t.second.first) / t.second.second;
        tanuloLista.push_back(Tanulo(t.first, atlag));
    }

    // Sorba rendezés csökkenõ átlag alapján
    sort(tanuloLista.begin(), tanuloLista.end());

    // Kiírás a konzolra és fájlba
    for (const auto& t : tanuloLista) {
        cout << t.nev << ": " << t.atlag << endl;
        outputFile << t.nev << ": " << t.atlag << endl;
    }

    outputFile.close();

    return 0;
}


