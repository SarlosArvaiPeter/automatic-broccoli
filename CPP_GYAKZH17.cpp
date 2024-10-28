#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

// Pilota oszt�ly defini�l�sa
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

    // Setter �s getter f�ggv�nyek
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

    // Akt�v �vek kisz�m�t�sa
    int aktivEvek() const { return veg_ev - kezdo_ev + 1; }

    // Ki�r� f�ggv�ny
    void display(ostream& out) const {
        out << sorszam << ";" << nev << ";" << pont << ";" << kezdo_ev << "-" << veg_ev;
        if (kezdo_ev >= 2001) out << ";*";  // Csillag hozz�ad�sa, ha 2001-ben vagy k�s�bb kezdett
        out << endl;
    }
};

// Pil�t�k beolvas�sa a f�jlb�l
void readPilots(const string& filename, vector<Pilota>& pilotak) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cerr << "Hiba: nem lehet megnyitni a f�jlt: " << filename << endl;
        return;
    }

    string line;
    getline(inFile, line); // Fejl�c �tugr�sa

    while (getline(inFile, line)) {
        stringstream ss(line);
        string nev, pont_str, ev_str;
        int pont, kezdo_ev, veg_ev;

        // Sorszam �tugr�sa
        getline(ss, nev, ';');
        getline(ss, nev, ';');  // Pil�ta neve
        getline(ss, pont_str, ';');  // Pontsz�m
        getline(ss, ev_str, ';');  // Akt�v �vek

        pont = stoi(pont_str);
        stringstream ev_ss(ev_str);
        string kezdo_str, veg_str;
        getline(ev_ss, kezdo_str, '-');
        getline(ev_ss, veg_str, '-');
        kezdo_ev = stoi(kezdo_str);
        veg_ev = stoi(veg_str);

        Pilota p(0, nev, pont, kezdo_ev, veg_ev);  // Sorsz�m k�s�bb ker�l hozz�rendel�sre
        pilotak.push_back(p);
    }
}

// Pil�t�k rendez�se pontok szerint �s ki�r�s f�jlba
void sortAndWriteByPoints(vector<Pilota>& pilotak, const string& outputFile) {
    ofstream outFile(outputFile);

    // Pontok szerinti rendez�s
    sort(pilotak.begin(), pilotak.end(), [](const Pilota& a, const Pilota& b) { return a.getPont() > b.getPont(); });

    // Sorsz�m be�ll�t�sa �s ki�r�s
    for (size_t i = 0; i < pilotak.size(); ++i) {
        pilotak[i].setSorszam(i + 1);
        pilotak[i].display(cout);
        pilotak[i].display(outFile);
    }
}

// Pil�t�k rendez�se akt�v �vek szerint �s ki�r�s f�jlba
void sortAndWriteByActiveYears(vector<Pilota>& pilotak, const string& outputFile) {
    ofstream outFile(outputFile);

    // Akt�v �vek szerinti rendez�s
    sort(pilotak.begin(), pilotak.end(), [](const Pilota& a, const Pilota& b) { return a.aktivEvek() > b.aktivEvek(); });

    // Sorsz�m be�ll�t�sa �s ki�r�s
    for (size_t i = 0; i < pilotak.size(); ++i) {
        pilotak[i].setSorszam(i + 1);
        pilotak[i].display(cout);
        pilotak[i].display(outFile);
    }
}

int main() {
    vector<Pilota> pilotak;

    // Pil�t�k beolvas�sa
    readPilots("forma1.csv", pilotak);

    // Rendez�s pontok szerint �s f�jlba �r�s
    cout << "Pontok szerinti rendez�s:" << endl;
    sortAndWriteByPoints(pilotak, "pilotak_pontok_szerint.csv");

    // Rendez�s akt�v �vek szerint �s f�jlba �r�s
    cout << "\nAkt�v �vek szerinti rendez�s:" << endl;
    sortAndWriteByActiveYears(pilotak, "pilotak_aktiv_evek_szerint.csv");

    return 0;
}
