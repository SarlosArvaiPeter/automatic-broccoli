#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

// Idoszakok oszt�ly defini�l�sa
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
    // Konstruktor alap�rtelmezett �rt�kekkel
    Idoszakok(string idoszak = "", int intezmenyek = 0, int karok = 0, int nappali = 0, int esti = 0,
        int levelezo = 0, int tavoktatas = 0, int osszes_hallgato = 0, int oktatok = 0)
        : idoszak(idoszak), intezmenyek(intezmenyek), karok(karok), nappali(nappali), esti(esti),
        levelezo(levelezo), tavoktatas(tavoktatas), osszes_hallgato(osszes_hallgato), oktatok(oktatok) {}

    // Setter �s getter f�ggv�nyek
    string getIdoszak() const { return idoszak; }
    int getKarok() const { return karok; }
    int getOktatok() const { return oktatok; }
    int getNappaliEsEstiOsszesen() const { return nappali + esti; }
    bool hasTavoktatas() const { return tavoktatas > 0; }

    // Sz�m�tott �rt�k: nappali �s esti hallgat�k ar�nya az �sszes hallgat�hoz k�pest
    double getNappaliEstiArany() const {
        return osszes_hallgato > 0 ? ((double)(nappali + esti) / osszes_hallgato) * 100 : 0;
    }

    // Ki�r�s a konzolra �s f�jlba
    void display(ostream& out, bool markTavoktatas = false) const {
        out << idoszak << ";" << intezmenyek << ";" << karok << ";" << nappali << ";" << esti << ";"
            << levelezo << ";" << tavoktatas << ";" << osszes_hallgato << ";" << oktatok;
        if (markTavoktatas && hasTavoktatas()) out << ";*";  // Csillag hozz�ad�sa t�voktat�s eset�n
        out << endl;
    }
};

// F�jl beolvas�sa �s adatok t�rol�sa Idoszakok t�mbben
void readIdoszakok(const string& filename, vector<Idoszakok>& idoszakok) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cerr << "Hiba: nem lehet megnyitni a f�jlt: " << filename << endl;
        return;
    }

    string line;
    getline(inFile, line); // Fejl�c �tugr�sa

    while (getline(inFile, line)) {
        stringstream ss(line);
        string idoszak;
        int intezmenyek, karok, nappali, esti, levelezo, tavoktatas, osszes_hallgato, oktatok;

        // Adatok beolvas�sa
        getline(ss, idoszak, ';');
        ss >> intezmenyek >> karok >> nappali >> esti >> levelezo >> tavoktatas >> osszes_hallgato >> oktatok;

        // Idoszak p�ld�ny l�trehoz�sa �s hozz�ad�sa a vektorhoz
        Idoszakok id(idoszak, intezmenyek, karok, nappali, esti, levelezo, tavoktatas, osszes_hallgato, oktatok);
        idoszakok.push_back(id);
    }
}

// Feladat 1: Sz�r�s karok sz�ma �s oktat�k sz�ma alapj�n, majd rendez�s
void filterAndSortByKarok(vector<Idoszakok>& idoszakok, const string& outputFile) {
    ofstream outFile(outputFile);

    // Sz�r�si felt�telek: karok > 151 �s oktat�k < 22600
    vector<Idoszakok> filtered;
    for (const auto& id : idoszakok) {
        if (id.getKarok() > 151 && id.getOktatok() < 22600) {
            filtered.push_back(id);
        }
    }

    // Debug: Ellen�rz�s, h�ny elem felel meg a felt�teleknek
    cout << "Megfelel� elemek sz�ma a sz�r�s ut�n: " << filtered.size() << endl;

    // Ellen�rz�s, hogy a sz�r�s ut�n maradtak-e elemek
    if (filtered.empty()) {
        cout << "Nincs olyan id�szak, amely megfelelne a felt�teleknek." << endl;
        outFile << "Nincs olyan id�szak, amely megfelelne a felt�teleknek." << endl;
        return;
    }

    // Rendez�s karok sz�ma szerint
    sort(filtered.begin(), filtered.end(), [](const Idoszakok& a, const Idoszakok& b) { return a.getKarok() > b.getKarok(); });

    // Eredm�nyek ki�r�sa konzolra �s f�jlba
    for (const auto& id : filtered) {
        id.display(cout, true);
        id.display(outFile, true);
    }
}

// Feladat 2: Rendez�s nappali �s esti hallgat�k sz�ma alapj�n, majd ki�r�s sz�zal�kos ar�nnyal
void sortAndDisplayByNappaliEsti(vector<Idoszakok>& idoszakok, const string& outputFile) {
    ofstream outFile(outputFile);

    // Rendez�s a nappali + esti hallgat�k sz�ma szerint
    sort(idoszakok.begin(), idoszakok.end(), [](const Idoszakok& a, const Idoszakok& b) {
        return a.getNappaliEsEstiOsszesen() > b.getNappaliEsEstiOsszesen();
        });

    // Eredm�nyek ki�r�sa konzolra �s f�jlba
    for (const auto& id : idoszakok) {
        id.display(cout);
        id.display(outFile);
        cout << "Nappali �s esti hallgat�k ar�nya: " << id.getNappaliEstiArany() << "%" << endl;
        outFile << "Nappali �s esti hallgat�k ar�nya: " << id.getNappaliEstiArany() << "%" << endl;
    }
}

int main() {
    vector<Idoszakok> idoszakok;

    // F�jl beolvas�sa
    readIdoszakok("oktatas.csv", idoszakok);

    // Feladat 1: Sz�r�s �s rendez�s karok sz�ma alapj�n, majd ki�r�s
    cout << "Feladat 1 - Karok sz�ma �s oktat�k sz�ma alapj�n rendezve:" << endl;
    filterAndSortByKarok(idoszakok, "idoszakok_karok_szerint.csv");

    // Feladat 2: Rendez�s nappali �s esti hallgat�k sz�ma alapj�n, majd ki�r�s sz�zal�kos ar�nnyal
    cout << "\nFeladat 2 - Nappali �s esti hallgat�k sz�ma alapj�n rendezve:" << endl;
    sortAndDisplayByNappaliEsti(idoszakok, "idoszakok_nappali_esti_szerint.csv");

    return 0;
}
