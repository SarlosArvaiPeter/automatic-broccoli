#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>  // szükséges a getline mûködéséhez

using namespace std;

// Határozatlan névelõ meghatározása magyarul
string indefinite_article(const string& word) {
    char first_letter = tolower(word[0]);
    // Magánhangzókhoz 'az', mássalhangzókhoz 'a'
    if (first_letter == 'a' || first_letter == 'e' || first_letter == 'i' || first_letter == 'o' || first_letter == 'u') {
        return "az " + word;
    }
    return "a " + word;
}

int main() {
    ifstream inFile("allatok.txt");
    ofstream outFile("allatok_sorted.txt");
    vector<string> animals;
    string animal;

    // Állatok beolvasása a fájlból
    while (getline(inFile, animal)) {
        animals.push_back(animal);
    }

    // Állatok ábécérendbe rendezése
    sort(animals.begin(), animals.end());

    // Kiírás konzolra és fájlba határozatlan névelõkkel
    cout << "Sorbarendezett állatok névelõvel:" << endl;
    for (const auto& ani : animals) {
        string with_article = indefinite_article(ani);
        cout << with_article << endl;      // Konzolra írás
        outFile << with_article << endl;   // Fájlba írás
    }

    // Fájlok bezárása
    inFile.close();
    outFile.close();

    return 0;
}
