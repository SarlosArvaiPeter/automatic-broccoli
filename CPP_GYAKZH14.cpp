#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#define M_PI 3.14159265358979323846

using namespace std;

class Pohar {
private:
    string szin;
    double terfogat; // dl-ben
    int evjarat;
    int hasznalok_szama;

public:
    // Konstruktor alapértelmezett értékekkel
    Pohar(string szin = "átlátszó", double terfogat = 3.0, int evjarat = 2023, int hasznalok_szama = 0)
        : szin(szin), terfogat(terfogat), evjarat(evjarat), hasznalok_szama(hasznalok_szama) {}

    // Getters
    string getSzin() const { return szin; }
    double getTerfogat() const { return terfogat; }
    int getEvjarat() const { return evjarat; }
    int getHasznalokSzama() const { return hasznalok_szama; }

    // Setters
    void setSzin(const string& szin) { this->szin = szin; }
    void setTerfogat(double terfogat) { this->terfogat = terfogat; }
    void setEvjarat(int evjarat) { this->evjarat = evjarat; }
    void setHasznalokSzama(int hasznalok_szama) { this->hasznalok_szama = hasznalok_szama; }

    // a.) Magasság számítása
    double magassag() const {
        double radius = 3.5; // átmérõ fele, 7 cm átmérõ alapján
        double terfogat_cm3 = terfogat * 100; // dl -> cm^3 átváltás
        return terfogat_cm3 / (M_PI * pow(radius, 2)); // térfogat = pi * r^2 * h --> h = térfogat / (pi * r^2)
    }

    // b.) Rendezés használók száma és évjárat alapján
    static void rendezPoharak(Pohar poharak[], int meret) {
        sort(poharak, poharak + meret, [](const Pohar& p1, const Pohar& p2) {
            if (p1.hasznalok_szama == p2.hasznalok_szama) {
                return p1.evjarat < p2.evjarat;
            }
            return p1.hasznalok_szama < p2.hasznalok_szama;
            });
    }

    // Kiírás függvény a konzolra
    void kiir() const {
        cout << "Pohár színe: " << szin << ", térfogat: " << terfogat << " dl, évjárat: " << evjarat
            << ", használók száma: " << hasznalok_szama << ", magasság: " << magassag() << " cm" << endl;
    }
};

int main() {
    // Pohár példányok létrehozása
    Pohar p1("kék", 5.0, 2020, 4);
    Pohar p2("piros", 3.5, 2018, 4);
    Pohar p3("zöld", 4.0, 2019, 3);
    Pohar p4("átlátszó", 3.0, 2021, 2);

    // Poharakat tartalmazó tömb
    Pohar poharak[] = { p1, p2, p3, p4 };
    int meret = sizeof(poharak) / sizeof(poharak[0]);

    // a.) Poharak magasságának kiírása
    cout << "Poharak magassága:" << endl;
    for (const auto& pohar : poharak) {
        pohar.kiir();
    }
    cout << endl;

    // b.) Poharak rendezése használók száma és évjárat alapján
    Pohar::rendezPoharak(poharak, meret);
    cout << "Poharak rendezve:" << endl;
    for (const auto& pohar : poharak) {
        pohar.kiir();
    }

    return 0;
}
