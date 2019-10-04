#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>

#include <vector>


int main ()
{
	using namespace std;
	using namespace std::chrono;

	ifstream input = ifstream("./WarAndPeace.txt");
	auto start = steady_clock::now();

	cout << "Parsing War and Peace" << endl;

	size_t nombre_lu = 0;
	// prochain mot lu
	string word;
	// une regex qui reconnait les caractères anormaux (négation des lettres)
	regex re( R"([^a-zA-Z])");

	// On met ici le vecteur qui stockera les mots
	vector <string> unique_words;

	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);
		// word est maintenant "tout propre"

		// on affiche un mot "propre" sur 100
		if (nombre_lu % 100 == 0) cout << nombre_lu << ": "<< word << endl;

		nombre_lu++;

		bool trouve = false;
		for (int i = 0 ; i < unique_words.size(); i++) {
			if (unique_words[i] == word) {
				trouve = true;
				break;
			}
		}
		if (trouve == false) {
			unique_words.push_back(word);
		}

	}

	input.close();

	cout << "Finished Parsing War and Peace" << endl;
	auto end = steady_clock::now();
	cout << "Parsing took "
	     << duration_cast<milliseconds>(end - start).count()
	     << "ms.\n";
	cout << "Found a total of " << nombre_lu << " words." << endl;
	cout << "Found a total of " << unique_words.size() << " unique words." << endl;

	return 0;
}
