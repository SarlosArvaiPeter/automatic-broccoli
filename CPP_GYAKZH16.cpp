#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cstdlib>  // a stod és stoi függvények miatt

using namespace std;

class Csavar {
public:
    string DIN;
    string megnevezes;
    string anyag;
    double d1;
    double L;
    string egyseg_csomag;
    bool keszleten;
    int darabszam;

    // Konstruktor a CSV fájl egy sorából való beolvasáshoz
    Csavar(string din, string megnevezes, string anyag, double d1, double L, string egyseg_csomag, string keszleten_jeloles, int darabszam = 1)
        : DIN(din), megnevezes(megnevezes), anyag(anyag), d1(d1), L(L), egyseg_csomag(egyseg_csomag), darabszam(darabszam) {
        keszleten = (keszleten_jeloles.find('*') != string::npos);
    }

    // Csavar kiírása a konzolra
    void kiir() const {
        cout << "DIN: " << DIN << ", Megnevezés: " << megnevezes << ", Anyag: " << anyag
            << ", d1: " << d1 << ", L: " << L << ", Egység csomag: " << egyseg_csomag
            << ", Darabszám: " << darabszam << ", Készleten: " << (keszleten ? "Igen" : "Nem") << endl;
    }

    // Csavar kiírása fájlba
    void kiir_fajlba(ofstream& outFile) const {
        outFile << "DIN: " << DIN << ", Megnevezés: " << megnevezes << ", Anyag: " << anyag
            << ", d1: " << d1 << ", L: " << L << ", Egység csomag: " << egyseg_csomag
            << ", Darabszám: " << darabszam << ", Készleten: " << (keszleten ? "Igen" : "Nem") << endl;
    }
};

// Rendezési függvény d1 és L szerint csökkenõ sorrendben
bool csavar_rendezes(const Csavar& c1, const Csavar& c2) {
    if (c1.d1 == c2.d1) {
        return c1.L > c2.L; // Másodlagos rendezés L szerint csökkenõ sorrendben
    }
    return c1.d1 > c2.d1; // Elsõdleges rendezés d1 szerint csökkenõ sorrendben
}

int main() {
    ifstream inFile("Csavarok.csv");
    ofstream outFile("Csavarok_rendezett.txt");
    vector<Csavar> csavarok;
    string line;

    // Elso sor átugrása (fejlécek)
    getline(inFile, line);

    // CSV fájl beolvasása
    while (getline(inFile, line)) {
        stringstream ss(line);
        string DIN, megnevezes, anyag, d1_str, L_str, egyseg_csomag, keszleten_jeloles, darabszam_str;
        int darabszam = 1; // alapértelmezett érték

        // Sor feldarabolása
        getline(ss, DIN, ';');
        getline(ss, megnevezes, ';');
        getline(ss, anyag, ';');
        getline(ss, d1_str, ';');
        getline(ss, L_str, ';');
        getline(ss, egyseg_csomag, ';');
        getline(ss, keszleten_jeloles, ';');
        getline(ss, darabszam_str, ';'); // opcionális darabszám beolvasása

        double d1 = 0.0;
        double L = 0.0;

        // Kivételkezelés a `stod` függvényhez
        try {
            d1 = stod(d1_str);
        }
        catch (const invalid_argument&) {
            d1 = 0.0;
        }
        catch (const out_of_range&) {
            d1 = 0.0;
        }

        try {
            L = stod(L_str);
        }
        catch (const invalid_argument&) {
            L = 0.0;
        }
        catch (const out_of_range&) {
            L = 0.0;
        }

        // Darabszám beállítása, ha elérhetõ adat
        try {
            if (!darabszam_str.empty()) {
                darabszam = stoi(darabszam_str);
            }
            else {
                cout << "Nincs darabszám megadva, alapértelmezett érték: 1\n";
            }
        }
        catch (const invalid_argument&) {
            darabszam = 1;
        }
        catch (const out_of_range&) {
            darabszam = 1;
        }

        Csavar csavar(DIN, megnevezes, anyag, d1, L, egyseg_csomag, keszleten_jeloles, darabszam);
        csavarok.push_back(csavar);
    }

    // Rendezés d1 és L szerint csökkenõ sorrendben
    sort(csavarok.begin(), csavarok.end(), csavar_rendezes);

    // Csavarok kiírása konzolra és fájlba
    cout << "Rendezett csavarok:" << endl;
    for (const auto& csavar : csavarok) {
        csavar.kiir();
        csavar.kiir_fajlba(outFile);
    }

    // Készleten lévõ csavarok kiírása és összesítése
    int osszes_darabszam = 0;
    cout << "\nKészleten lévõ csavarok:" << endl;
    outFile << "\nKészleten lévõ csavarok:" << endl;
    for (const auto& csavar : csavarok) {
        if (csavar.keszleten) {
            csavar.kiir();
            csavar.kiir_fajlba(outFile);
            osszes_darabszam += csavar.darabszam;
        }
    }

    /* Készleten lévõ csavarok teljes darabszámának kiírása
    cout << "\nÖsszes készleten lévõ csavar darabszáma: " << osszes_darabszam << endl;
    outFile << "\nÖsszes készleten lévõ csavar darabszáma: " << osszes_darabszam << endl;*/

    inFile.close();
    outFile.close();s

    return 0;
}

