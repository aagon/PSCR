#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>

#include <vector>
#include <utility>
#include <forward_list>

using namespace std;

template <typename K, typename V>
class HashMap {

public:
	struct Entry {
		const K key;
		V value;
		Entry(const K& key, const V& value) : key(key), value(value) {}
	};

private:
	typedef std::vector<std::forward_list<Entry>> buckets_t;
	buckets_t buckets;
	size_t nb_stored_values;

public:

	HashMap(size_t size) {
		buckets.resize(size);
		nb_stored_values = 0;
	}

	HashMap() {
		buckets.resize(256);
		nb_stored_values = 0;
	}

	size_t nb_buckets() const {
		return buckets.size();
	}

	size_t size() const {
		return nb_stored_values;
	}

	void grow() {
		size_t former_size = buckets.size();

		HashMap nouvelle_map(2 * former_size);

		K temp_key;
		V temp_value;
		size_t temp_nb_values = 0;

		for (size_t i = 0; i < former_size ; i++) {
			while (buckets[i].empty() != 1) {
				temp_key = buckets[i].front().key;
				temp_value = buckets[i].front().value;
				buckets[i].pop_front();
				nb_stored_values--;
				nouvelle_map.put(temp_key, temp_value);
				temp_nb_values++;
			}
		}

		buckets.swap(nouvelle_map.buckets);
		this->nb_stored_values = temp_nb_values;
		nouvelle_map.buckets.clear();
	}


	V* get(const K& key) {
		size_t h = std::hash <K>()(key);
		h = h % buckets.size();

		for (Entry& ent : buckets[h]) {
			if (ent.key == key) {
				return &ent.value;
			}
		}

		return nullptr;
	}

	bool put(const K& key, const V& value) {
		size_t h = std::hash <K>()(key);
		h = h % buckets.size();

		for (Entry& ent : buckets[h]) {
			if (ent.key == key) {
				ent.value = value;
				return true;
			}
		}

		if (((this->size() + 0.0) / (this->nb_buckets() + 0.0)) > 0.8) {
			this->grow();
		}
		buckets[h].push_front(Entry(key, value));
		this->nb_stored_values++;
		return false;
	}

	bool increment(const K& key) {
		size_t h = std::hash <K>()(key);
		h = h % buckets.size();

		for (Entry& ent : buckets[h]) {
			if (ent.key == key) {
				ent.value++;
				return true;
			}
		}

		if (((this->size() + 0.0) / (this->nb_buckets() + 0.0)) > 0.8) {
			this->grow();
		}
		buckets[h].push_front(Entry(key, 1));
		this->nb_stored_values++;
		return false;

	}

	bool del(const K& key) {
		size_t h = std::hash <K>()(key);
		h = h % buckets.size();

		auto prev = buckets[h].before_begin();
		for (auto it = buckets[h].before_begin();
		     it != buckets[h].end();) {
			prev = it;
			if ((++it)->key == key) {
				buckets[h].erase_after(prev);
				nb_stored_values--;
				return true;
			}
		}
		return false;
	}

	struct iterator {
		typename std::vector<std::forward_list<Entry>>::iterator vit;
		typename std::forward_list<Entry>::iterator lit;

		buckets_t *buckets;

		iterator (buckets_t &buckets) : buckets(&buckets) {}

		iterator &operator++() {

			++lit;
			if (lit != vit->begin()) return *this;

			while (++vit -> empty() && vit != buckets->end()) {
				if (vit != buckets->end()) {
					lit = vit->begin();
				}
			}

			return *this;
		}

		bool operator!=(iterator & other) {
			return ((vit != other.vit) || (lit != other.lit));
		}
	};

	iterator begin() {
		auto temp = iterator(&buckets);

		for (size_t i = 0; i < buckets.size() ; ++i) {
			if (buckets[i].empty()) {
				temp.vit = buckets.begin() + i;
				temp.lit = temp.vit->begin();
				break;
			}
		}

		return temp;
	}

	iterator end() {
		auto temp = iterator(&buckets);

		temp.lit = buckets[buckets.size() - 1].end();
		temp.vit = buckets.end();

		return temp;
	}

	size_t count(iterator begin, iterator end) {
		size_t compteur = 0;

		for (auto it = begin; it != end; ++it, ++compteur);

		return compteur;
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

	// On créé la structure qui accueillera les données
	HashMap<string,int> table;

	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);
		// word est maintenant "tout propre"

		// on affiche un mot "propre" sur 100
		if (nombre_lu % 100 == 0) cout << nombre_lu << ": "<< word << endl;

		nombre_lu++;

		table.increment(word);
	}

	cout << "Finished Parsing War and Peace" << endl;
	auto end = steady_clock::now();
	cout << "Parsing took "
	     << duration_cast<milliseconds>(end - start).count()
	     << "ms.\n";
	cout << "Found a total of " << nombre_lu << " words." << endl;
	cout << "Found a total of " << table.size() << " unique words." << endl;

	cout << "We need " << table.nb_buckets() << " buckets" << endl;

	cout << "On trouve " << *(table.get("pierre")) << " occurences du mot pierre" << endl;

	cout << "Il y a " << table.count(table.begin(), table.end()) << " mots" << endl;

	return 0;
}
