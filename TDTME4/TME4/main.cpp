#include <thread>
#include <iostream>

#include "Banque.h"

using namespace std;

const int NB_THREAD = 20;
const int K = 100;
const int SOLDEINITIAL = 1000;

// En fait, il fallait bien écrire la fonction ici :

void transferts_aleatoires(pr::Banque *banque) {

	int compteur = 1000;

	for (; compteur > 0; --compteur) {
		auto i = ::rand() % banque->size();
		auto j = ::rand() % banque->size();

		// On part du principe qu'on peut se faire des transferts à soi-même
		auto m = ::rand() % 100;

		// cout << m << endl;

		banque->transfert(i,j,m);

		// On s'endort pendant une durée aléatoire entre 0 et 200ms
		auto r = ::rand() % 20;

		std::this_thread::sleep_for(std::chrono::milliseconds(r));
	}
}

int bilan_naif(pr::Banque *banque)
{
	int bilan = 0;

	for (int i = 0; i < K ; ++i) {
		 bilan += banque->get_solde(i);
	 }

	 return bilan;
 }

int main()
{
	// On fixe la graine
	::srand(::time(nullptr));

	// On créé une instance de banque
	pr::Banque LBP(K, SOLDEINITIAL);
	// On vérifie que le comptable est content
	// cout << LBP.comptabiliser(K * SOLDEINITIAL) << endl;
	cout << bilan_naif(&LBP) << endl;
	// On vérifie qu'un compte random est bien à la bonne valeur
	cout << LBP.get_solde(12) << endl;


	vector<thread> threads;

	// TODO : creer des threads qui font ce qui est demandé
	threads.reserve(NB_THREAD);
	for (int i = 0; i < NB_THREAD; ++i) {
		threads.push_back(thread(transferts_aleatoires, &LBP));
	}
	// Threads créés

	for (auto & t : threads) {
		t.join();
	}

	// Est-ce que le comptable est content ?
	// cout << LBP.comptabiliser(K * SOLDEINITIAL) << endl;
	cout << bilan_naif(&LBP) << endl;
	// Est-ce que notre fonction a vraiment fait qqch ?
	cout << LBP.get_solde(12) << endl;
	cout << LBP.get_solde(37) << endl;
	cout << LBP.get_solde(15) << endl;
	cout << LBP.get_solde(87) << endl;

	// TODO : tester solde = NB_THREAD * JP
	return 0;
}
