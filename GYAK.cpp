#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>  // sz�ks�ges a getline m�k�d�s�hez

using namespace std;

// Hat�rozatlan n�vel� meghat�roz�sa magyarul
string indefinite_article(const string& word) {
    char first_letter = tolower(word[0]);
    // Mag�nhangz�khoz 'az', m�ssalhangz�khoz 'a'
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

    // �llatok beolvas�sa a f�jlb�l
    while (getline(inFile, animal)) {
        animals.push_back(animal);
    }

    // �llatok �b�c�rendbe rendez�se
    sort(animals.begin(), animals.end());

    // Ki�r�s konzolra �s f�jlba hat�rozatlan n�vel�kkel
    cout << "Sorbarendezett �llatok n�vel�vel:" << endl;
    for (const auto& ani : animals) {
        string with_article = indefinite_article(ani);
        cout << with_article << endl;      // Konzolra �r�s
        outFile << with_article << endl;   // F�jlba �r�s
    }

    // F�jlok bez�r�sa
    inFile.close();
    outFile.close();

    return 0;
}
