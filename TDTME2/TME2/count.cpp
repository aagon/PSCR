#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>

#include <vector>
#include <utility>

using namespace std;
using namespace std::chrono;

int occurences_mot(const string mot, vector <pair<string,int>> tab_mot);

int main ()
{

	ifstream input = ifstream("./WarAndPeace.txt");
	auto start = steady_clock::now();

	cout << "Parsing War and Peace" << endl;

	size_t nombre_lu = 0;
	// prochain mot lu
	string word;
	// une regex qui reconnait les caractères anormaux (négation des lettres)
	regex re( R"([^a-zA-Z])");

	// On met ici le vecteur qui stockera les mots
	vector <pair <string,int>> unique_words_and_count;

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
		for (int i = 0 ; i < unique_words_and_count.size(); i++) {
			if (unique_words_and_count[i].first == word) {
				trouve = true;
				unique_words_and_count[i].second++;
				break;
			}
		}
		if (trouve == false) {
			unique_words_and_count.emplace_back(word,1);
		}

	}

	input.close();

	cout << "Finished Parsing War and Peace" << endl;
	auto end = steady_clock::now();
	cout << "Parsing took "
	     << duration_cast<milliseconds>(end - start).count()
	     << "ms.\n";
	cout << "Found a total of " << nombre_lu << " words." << endl;

	cout << "Found a total of " << unique_words_and_count.size() << " unique words." << endl;

	cout << "Found a total of " << occurences_mot("war", unique_words_and_count) << " occurrences of the world war." << endl;

	cout << "Found a total of " << occurences_mot("peace", unique_words_and_count) << " occurrences of the world peace." << endl;

	cout << "Found a total of " << occurences_mot("napoleon", unique_words_and_count) << " occurrences of the world napoleon." << endl;

	cout << "Found a total of " << occurences_mot("pierre", unique_words_and_count) << " occurrences of the world pierre." << endl;

	return 0;
}

int occurences_mot(const string mot, const vector <pair<string,int>> tab_mot)
{
	for (int i = 0; i < tab_mot.size(); ++i) {
		if (mot == tab_mot[i].first) {
			return tab_mot[i].second;
		}
	}

	return 0;
}
