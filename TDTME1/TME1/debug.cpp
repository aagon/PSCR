#include <iostream>

using namespace std;

int main()
{
	int tab[10];

	for (int i = 0; i < 10; ++i) {
		tab[i] = i;
	}

	for (size_t i=9; i >= 0 ; i--) {

		if (tab[i] - tab[i-1] != 1) {
			cout << "probleme !";
		}
	}

	return 0;
}
