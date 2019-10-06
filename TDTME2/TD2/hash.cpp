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

	struct Entry {
		const K key;
		V value;
		Entry(const K& key, const V& value) : key(key), value(value) {}
	};
	std::vector <std::forward_list<Entry>> buckets;
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

		buckets[h].push_front(Entry(key, value));
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

		for (int i = 0; i < former_size ; i++) {
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

};

int main()
{
	HashMap<int,int> test;

	test.put(1,15);
	cout << *(test.get(1)) << endl;
	cout << test.nb_buckets() << endl;
	cout << test.size() << endl;
	test.grow();
	cout << test.nb_buckets() << endl;
	cout << test.size() << endl;
	cout << *(test.get(1)) << endl;
	test.put(2,16);
	cout << test.size() << endl;
	return 0;
}
