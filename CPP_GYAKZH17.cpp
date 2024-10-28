#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

// Pilota osztály definiálása
class Pilota {
private:
    int sorszam;
    string nev;
    int pont;
    int kezdo_ev;
    int veg_ev;

public:
    Pilota(int sorszam = 0, string nev = "", int pont = 0, int kezdo_ev = 0, int veg_ev = 0)
        : sorszam(sorszam), nev(nev), pont(pont), kezdo_ev(kezdo_ev), veg_ev(veg_ev) {}

    // Setter és getter függvények
    void setSorszam(int s) { sorszam = s; }
    int getSorszam() const { return sorszam; }

    void setNev(string n) { nev = n; }
    string getNev() const { return nev; }

    void setPont(int p) { pont = p; }
    int getPont() const { return pont; }

    void setKezdoEv(int k) { kezdo_ev = k; }
    int getKezdoEv() const { return kezdo_ev; }

    void setVegEv(int v) { veg_ev = v; }
    int getVegEv() const { return veg_ev; }

    // Aktív évek kiszámítása
    int aktivEvek() const { return veg_ev - kezdo_ev + 1; }

    // Kiíró függvény
    void display(ostream& out) const {
        out << sorszam << ";" << nev << ";" << pont << ";" << kezdo_ev << "-" << veg_ev;
        if (kezdo_ev >= 2001) out << ";*";  // Csillag hozzáadása, ha 2001-ben vagy késõbb kezdett
        out << endl;
    }
};

// Pilóták beolvasása a fájlból
void readPilots(const string& filename, vector<Pilota>& pilotak) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cerr << "Hiba: nem lehet megnyitni a fájlt: " << filename << endl;
        return;
    }

    string line;
    getline(inFile, line); // Fejléc átugrása

    while (getline(inFile, line)) {
        stringstream ss(line);
        string nev, pont_str, ev_str;
        int pont, kezdo_ev, veg_ev;

        // Sorszam átugrása
        getline(ss, nev, ';');
        getline(ss, nev, ';');  // Pilóta neve
        getline(ss, pont_str, ';');  // Pontszám
        getline(ss, ev_str, ';');  // Aktív évek

        pont = stoi(pont_str);
        stringstream ev_ss(ev_str);
        string kezdo_str, veg_str;
        getline(ev_ss, kezdo_str, '-');
        getline(ev_ss, veg_str, '-');
        kezdo_ev = stoi(kezdo_str);
        veg_ev = stoi(veg_str);

        Pilota p(0, nev, pont, kezdo_ev, veg_ev);  // Sorszám késõbb kerül hozzárendelésre
        pilotak.push_back(p);
    }
}

// Pilóták rendezése pontok szerint és kiírás fájlba
void sortAndWriteByPoints(vector<Pilota>& pilotak, const string& outputFile) {
    ofstream outFile(outputFile);

    // Pontok szerinti rendezés
    sort(pilotak.begin(), pilotak.end(), [](const Pilota& a, const Pilota& b) { return a.getPont() > b.getPont(); });

    // Sorszám beállítása és kiírás
    for (size_t i = 0; i < pilotak.size(); ++i) {
        pilotak[i].setSorszam(i + 1);
        pilotak[i].display(cout);
        pilotak[i].display(outFile);
    }
}

// Pilóták rendezése aktív évek szerint és kiírás fájlba
void sortAndWriteByActiveYears(vector<Pilota>& pilotak, const string& outputFile) {
    ofstream outFile(outputFile);

    // Aktív évek szerinti rendezés
    sort(pilotak.begin(), pilotak.end(), [](const Pilota& a, const Pilota& b) { return a.aktivEvek() > b.aktivEvek(); });

    // Sorszám beállítása és kiírás
    for (size_t i = 0; i < pilotak.size(); ++i) {
        pilotak[i].setSorszam(i + 1);
        pilotak[i].display(cout);
        pilotak[i].display(outFile);
    }
}

int main() {
    vector<Pilota> pilotak;

    // Pilóták beolvasása
    readPilots("forma1.csv", pilotak);

    // Rendezés pontok szerint és fájlba írás
    cout << "Pontok szerinti rendezés:" << endl;
    sortAndWriteByPoints(pilotak, "pilotak_pontok_szerint.csv");

    // Rendezés aktív évek szerint és fájlba írás
    cout << "\nAktív évek szerinti rendezés:" << endl;
    sortAndWriteByActiveYears(pilotak, "pilotak_aktiv_evek_szerint.csv");

    return 0;
}
