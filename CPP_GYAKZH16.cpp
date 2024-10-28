#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cstdlib>  // a stod �s stoi f�ggv�nyek miatt

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

    // Konstruktor a CSV f�jl egy sor�b�l val� beolvas�shoz
    Csavar(string din, string megnevezes, string anyag, double d1, double L, string egyseg_csomag, string keszleten_jeloles, int darabszam = 1)
        : DIN(din), megnevezes(megnevezes), anyag(anyag), d1(d1), L(L), egyseg_csomag(egyseg_csomag), darabszam(darabszam) {
        keszleten = (keszleten_jeloles.find('*') != string::npos);
    }

    // Csavar ki�r�sa a konzolra
    void kiir() const {
        cout << "DIN: " << DIN << ", Megnevez�s: " << megnevezes << ", Anyag: " << anyag
            << ", d1: " << d1 << ", L: " << L << ", Egys�g csomag: " << egyseg_csomag
            << ", Darabsz�m: " << darabszam << ", K�szleten: " << (keszleten ? "Igen" : "Nem") << endl;
    }

    // Csavar ki�r�sa f�jlba
    void kiir_fajlba(ofstream& outFile) const {
        outFile << "DIN: " << DIN << ", Megnevez�s: " << megnevezes << ", Anyag: " << anyag
            << ", d1: " << d1 << ", L: " << L << ", Egys�g csomag: " << egyseg_csomag
            << ", Darabsz�m: " << darabszam << ", K�szleten: " << (keszleten ? "Igen" : "Nem") << endl;
    }
};

// Rendez�si f�ggv�ny d1 �s L szerint cs�kken� sorrendben
bool csavar_rendezes(const Csavar& c1, const Csavar& c2) {
    if (c1.d1 == c2.d1) {
        return c1.L > c2.L; // M�sodlagos rendez�s L szerint cs�kken� sorrendben
    }
    return c1.d1 > c2.d1; // Els�dleges rendez�s d1 szerint cs�kken� sorrendben
}

int main() {
    ifstream inFile("Csavarok.csv");
    ofstream outFile("Csavarok_rendezett.txt");
    vector<Csavar> csavarok;
    string line;

    // Elso sor �tugr�sa (fejl�cek)
    getline(inFile, line);

    // CSV f�jl beolvas�sa
    while (getline(inFile, line)) {
        stringstream ss(line);
        string DIN, megnevezes, anyag, d1_str, L_str, egyseg_csomag, keszleten_jeloles, darabszam_str;
        int darabszam = 1; // alap�rtelmezett �rt�k

        // Sor feldarabol�sa
        getline(ss, DIN, ';');
        getline(ss, megnevezes, ';');
        getline(ss, anyag, ';');
        getline(ss, d1_str, ';');
        getline(ss, L_str, ';');
        getline(ss, egyseg_csomag, ';');
        getline(ss, keszleten_jeloles, ';');
        getline(ss, darabszam_str, ';'); // opcion�lis darabsz�m beolvas�sa

        double d1 = 0.0;
        double L = 0.0;

        // Kiv�telkezel�s a `stod` f�ggv�nyhez
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

        // Darabsz�m be�ll�t�sa, ha el�rhet� adat
        try {
            if (!darabszam_str.empty()) {
                darabszam = stoi(darabszam_str);
            }
            else {
                cout << "Nincs darabsz�m megadva, alap�rtelmezett �rt�k: 1\n";
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

    // Rendez�s d1 �s L szerint cs�kken� sorrendben
    sort(csavarok.begin(), csavarok.end(), csavar_rendezes);

    // Csavarok ki�r�sa konzolra �s f�jlba
    cout << "Rendezett csavarok:" << endl;
    for (const auto& csavar : csavarok) {
        csavar.kiir();
        csavar.kiir_fajlba(outFile);
    }

    // K�szleten l�v� csavarok ki�r�sa �s �sszes�t�se
    int osszes_darabszam = 0;
    cout << "\nK�szleten l�v� csavarok:" << endl;
    outFile << "\nK�szleten l�v� csavarok:" << endl;
    for (const auto& csavar : csavarok) {
        if (csavar.keszleten) {
            csavar.kiir();
            csavar.kiir_fajlba(outFile);
            osszes_darabszam += csavar.darabszam;
        }
    }

    /* K�szleten l�v� csavarok teljes darabsz�m�nak ki�r�sa
    cout << "\n�sszes k�szleten l�v� csavar darabsz�ma: " << osszes_darabszam << endl;
    outFile << "\n�sszes k�szleten l�v� csavar darabsz�ma: " << osszes_darabszam << endl;*/

    inFile.close();
    outFile.close();s

    return 0;
}

