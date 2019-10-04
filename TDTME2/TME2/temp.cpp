#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>

using namespace std;

template <typename K, typename V>
class HashMap {

	struct Entry {
		const K key;
		V value;
		Entry(const K& key, const V& value) : key(key), value(value) {}
	};

	std::vector <std::forward_list <Entry> > buckets;

	V* get(const K& key) {
		size_t h = std::hash <K>()(key);
		h = h % buckets.size();

		for (Entry & ent : buckets[h]) {
			if (ent.key == key) {
				return & ent.value;
			}
		}

		return nullptr;
	}


};

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

	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);
		// word est maintenant "tout propre"
		if (nombre_lu % 100 == 0)
			// on affiche un mot "propre" sur 100
			cout << nombre_lu << ": "<< word << endl;
		nombre_lu++;
	}

	input.close();

	cout << "Finished Parsing War and Peace" << endl;
		auto end = steady_clock::now();
		cout << "Parsing took "
		     << duration_cast<milliseconds>(end - start).count()
		     << "ms.\n";
		cout << "Found a total of " << nombre_lu << " words." << endl;

		return 0;
	}
