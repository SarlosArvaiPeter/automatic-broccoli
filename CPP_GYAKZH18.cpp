#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

// Idoszakok osztály definiálása
class Idoszakok {
private:
    string idoszak;
    int intezmenyek;
    int karok;
    int nappali;
    int esti;
    int levelezo;
    int tavoktatas;
    int osszes_hallgato;
    int oktatok;

public:
    // Konstruktor alapértelmezett értékekkel
    Idoszakok(string idoszak = "", int intezmenyek = 0, int karok = 0, int nappali = 0, int esti = 0,
        int levelezo = 0, int tavoktatas = 0, int osszes_hallgato = 0, int oktatok = 0)
        : idoszak(idoszak), intezmenyek(intezmenyek), karok(karok), nappali(nappali), esti(esti),
        levelezo(levelezo), tavoktatas(tavoktatas), osszes_hallgato(osszes_hallgato), oktatok(oktatok) {}

    // Setter és getter függvények
    string getIdoszak() const { return idoszak; }
    int getKarok() const { return karok; }
    int getOktatok() const { return oktatok; }
    int getNappaliEsEstiOsszesen() const { return nappali + esti; }
    bool hasTavoktatas() const { return tavoktatas > 0; }

    // Számított érték: nappali és esti hallgatók aránya az összes hallgatóhoz képest
    double getNappaliEstiArany() const {
        return osszes_hallgato > 0 ? ((double)(nappali + esti) / osszes_hallgato) * 100 : 0;
    }

    // Kiírás a konzolra és fájlba
    void display(ostream& out, bool markTavoktatas = false) const {
        out << idoszak << ";" << intezmenyek << ";" << karok << ";" << nappali << ";" << esti << ";"
            << levelezo << ";" << tavoktatas << ";" << osszes_hallgato << ";" << oktatok;
        if (markTavoktatas && hasTavoktatas()) out << ";*";  // Csillag hozzáadása távoktatás esetén
        out << endl;
    }
};

// Fájl beolvasása és adatok tárolása Idoszakok tömbben
void readIdoszakok(const string& filename, vector<Idoszakok>& idoszakok) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cerr << "Hiba: nem lehet megnyitni a fájlt: " << filename << endl;
        return;
    }

    string line;
    getline(inFile, line); // Fejléc átugrása

    while (getline(inFile, line)) {
        stringstream ss(line);
        string idoszak;
        int intezmenyek, karok, nappali, esti, levelezo, tavoktatas, osszes_hallgato, oktatok;

        // Adatok beolvasása
        getline(ss, idoszak, ';');
        ss >> intezmenyek >> karok >> nappali >> esti >> levelezo >> tavoktatas >> osszes_hallgato >> oktatok;

        // Idoszak példány létrehozása és hozzáadása a vektorhoz
        Idoszakok id(idoszak, intezmenyek, karok, nappali, esti, levelezo, tavoktatas, osszes_hallgato, oktatok);
        idoszakok.push_back(id);
    }
}

// Feladat 1: Szûrés karok száma és oktatók száma alapján, majd rendezés
void filterAndSortByKarok(vector<Idoszakok>& idoszakok, const string& outputFile) {
    ofstream outFile(outputFile);

    // Szûrési feltételek: karok > 151 és oktatók < 22600
    vector<Idoszakok> filtered;
    for (const auto& id : idoszakok) {
        if (id.getKarok() > 151 && id.getOktatok() < 22600) {
            filtered.push_back(id);
        }
    }

    // Debug: Ellenõrzés, hány elem felel meg a feltételeknek
    cout << "Megfelelõ elemek száma a szûrés után: " << filtered.size() << endl;

    // Ellenõrzés, hogy a szûrés után maradtak-e elemek
    if (filtered.empty()) {
        cout << "Nincs olyan idõszak, amely megfelelne a feltételeknek." << endl;
        outFile << "Nincs olyan idõszak, amely megfelelne a feltételeknek." << endl;
        return;
    }

    // Rendezés karok száma szerint
    sort(filtered.begin(), filtered.end(), [](const Idoszakok& a, const Idoszakok& b) { return a.getKarok() > b.getKarok(); });

    // Eredmények kiírása konzolra és fájlba
    for (const auto& id : filtered) {
        id.display(cout, true);
        id.display(outFile, true);
    }
}

// Feladat 2: Rendezés nappali és esti hallgatók száma alapján, majd kiírás százalékos aránnyal
void sortAndDisplayByNappaliEsti(vector<Idoszakok>& idoszakok, const string& outputFile) {
    ofstream outFile(outputFile);

    // Rendezés a nappali + esti hallgatók száma szerint
    sort(idoszakok.begin(), idoszakok.end(), [](const Idoszakok& a, const Idoszakok& b) {
        return a.getNappaliEsEstiOsszesen() > b.getNappaliEsEstiOsszesen();
        });

    // Eredmények kiírása konzolra és fájlba
    for (const auto& id : idoszakok) {
        id.display(cout);
        id.display(outFile);
        cout << "Nappali és esti hallgatók aránya: " << id.getNappaliEstiArany() << "%" << endl;
        outFile << "Nappali és esti hallgatók aránya: " << id.getNappaliEstiArany() << "%" << endl;
    }
}

int main() {
    vector<Idoszakok> idoszakok;

    // Fájl beolvasása
    readIdoszakok("oktatas.csv", idoszakok);

    // Feladat 1: Szûrés és rendezés karok száma alapján, majd kiírás
    cout << "Feladat 1 - Karok száma és oktatók száma alapján rendezve:" << endl;
    filterAndSortByKarok(idoszakok, "idoszakok_karok_szerint.csv");

    // Feladat 2: Rendezés nappali és esti hallgatók száma alapján, majd kiírás százalékos aránnyal
    cout << "\nFeladat 2 - Nappali és esti hallgatók száma alapján rendezve:" << endl;
    sortAndDisplayByNappaliEsti(idoszakok, "idoszakok_nappali_esti_szerint.csv");

    return 0;
}
