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
    // Konstruktor alap�rtelmezett �rt�kekkel
    Pohar(string szin = "�tl�tsz�", double terfogat = 3.0, int evjarat = 2023, int hasznalok_szama = 0)
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

    // a.) Magass�g sz�m�t�sa
    double magassag() const {
        double radius = 3.5; // �tm�r� fele, 7 cm �tm�r� alapj�n
        double terfogat_cm3 = terfogat * 100; // dl -> cm^3 �tv�lt�s
        return terfogat_cm3 / (M_PI * pow(radius, 2)); // t�rfogat = pi * r^2 * h --> h = t�rfogat / (pi * r^2)
    }

    // b.) Rendez�s haszn�l�k sz�ma �s �vj�rat alapj�n
    static void rendezPoharak(Pohar poharak[], int meret) {
        sort(poharak, poharak + meret, [](const Pohar& p1, const Pohar& p2) {
            if (p1.hasznalok_szama == p2.hasznalok_szama) {
                return p1.evjarat < p2.evjarat;
            }
            return p1.hasznalok_szama < p2.hasznalok_szama;
            });
    }

    // Ki�r�s f�ggv�ny a konzolra
    void kiir() const {
        cout << "Poh�r sz�ne: " << szin << ", t�rfogat: " << terfogat << " dl, �vj�rat: " << evjarat
            << ", haszn�l�k sz�ma: " << hasznalok_szama << ", magass�g: " << magassag() << " cm" << endl;
    }
};

int main() {
    // Poh�r p�ld�nyok l�trehoz�sa
    Pohar p1("k�k", 5.0, 2020, 4);
    Pohar p2("piros", 3.5, 2018, 4);
    Pohar p3("z�ld", 4.0, 2019, 3);
    Pohar p4("�tl�tsz�", 3.0, 2021, 2);

    // Poharakat tartalmaz� t�mb
    Pohar poharak[] = { p1, p2, p3, p4 };
    int meret = sizeof(poharak) / sizeof(poharak[0]);

    // a.) Poharak magass�g�nak ki�r�sa
    cout << "Poharak magass�ga:" << endl;
    for (const auto& pohar : poharak) {
        pohar.kiir();
    }
    cout << endl;

    // b.) Poharak rendez�se haszn�l�k sz�ma �s �vj�rat alapj�n
    Pohar::rendezPoharak(poharak, meret);
    cout << "Poharak rendezve:" << endl;
    for (const auto& pohar : poharak) {
        pohar.kiir();
    }

    return 0;
}
