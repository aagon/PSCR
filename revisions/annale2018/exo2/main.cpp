#include "RDV.h"

#include <vector>
#include <thread>
#include <iostream>
#include <chrono>

// Fichier à completer

// La fonction à faire exécuter par les threads
void worker(pr::RendezVous *rdv, int ordre) {
	for (int i = 0; i < 3; ++i) {
		// On affiche début et son ordre de création
		std::cout << "Début : " << ordre << std::endl;

		// On dort pour une durée aléatoire comprise entre 0.1 et 1 seconde
		// Ici le corrigé est faux (même si en vrai on s'en fout) :
		// Il demande une durée aléatoire entre 1 et 1000 ms, alors qu'on veut
		// une durée entre 100 et 1000 ms
		// Par ailleurs, la fonction std::chrono::milliseconds demande
		// l'inclusion de l'en-tête chrono
		// Dans ce cas, on va dormir *au moins* entre 100 et 1000 millisecondes
		std::this_thread::sleep_for(std::chrono::milliseconds(100 + (rand() % 901)));

		// La prise de rendez vous
		rdv->meet();

		// Une fois que le rendez-vous est terminé et qu'on est libéré, on finit :
		std::cout << "Fin : " << ordre << std::endl;
	}
}


int main () {
	// a faire varier
	const int N = 4;

	// construire un RendezVous pour N participants
	pr::RendezVous rdv(N);

	// instancier des threads
	// On créé le vecteur des threads
	std::vector<std::thread> threads;
	// On ajuste la taille du vecteur au nombre de threads qu'on veut
	threads.reserve(N-1);
	// On instancie bien les threads avec la fonction de travail
	for (int i = 0; i < N-1; ++i) {
		threads.emplace_back(std::thread(worker, &rdv, i));
	}

	// participer au rendez vous trois fois
	// Donc les threads doivent aussi participer trois fois
	for (int i = 0; i < 3; ++i) {
		rdv.meet();
	}

	// sortie propre
	for (int i = 0; i < N-1 ; ++i) {
		threads[i].join();
	}

	std::cout << "fini tous les threads" << std::endl;

	return 0;
}
