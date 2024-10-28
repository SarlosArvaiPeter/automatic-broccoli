#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

// Tanul� oszt�ly, amely a nevet �s az �tlagot t�rolja
class Tanulo {
public:
    string nev;
    double atlag;

    Tanulo(string nev, double atlag) : nev(nev), atlag(atlag) {}

    // Oper�tor t�lterhel�s a rendez�shez
    bool operator<(const Tanulo& other) const {
        return atlag > other.atlag; // Cs�kken� sorrend
    }
};

// F� f�ggv�ny
int main() {
    ifstream inputFile("TanAtlag.txt");
    ofstream outputFile("Tanulok_Atlaga.txt");

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cerr << "Hiba a f�jl megnyit�sakor!" << endl;
        return 1;
    }

    map<string, pair<int, int>> tanulok; // tanul�k n�v, �sszes�tett (kredit * jegy) �s kredit �sszeg

    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string nev, targy;
        int kredit, jegy;

        ss >> nev >> targy >> kredit >> jegy;

        // Ellen�rizz�k, hogy a n�v nem �res, miel�tt feldolgozzuk
        if (nev.empty()) continue;

        if (tanulok.find(nev) == tanulok.end()) {
            tanulok[nev] = { 0, 0 }; // Ha �j tanul�, inicializ�ljuk
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

    // Sorba rendez�s cs�kken� �tlag alapj�n
    sort(tanuloLista.begin(), tanuloLista.end());

    // Ki�r�s a konzolra �s f�jlba
    for (const auto& t : tanuloLista) {
        cout << t.nev << ": " << t.atlag << endl;
        outputFile << t.nev << ": " << t.atlag << endl;
    }

    outputFile.close();

    return 0;
}


