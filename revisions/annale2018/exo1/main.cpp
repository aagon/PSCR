#include "List.h"
#include <string>
#include <iostream>
#include <cstring>

using namespace std;
using namespace pr;

int main () {

	std::string abc = "abc";

	// FAUTE de mémoire : pour écrire un string de n caractères ASCII à la
	// C, il faut allouer n+1 octets, de manière à pouvoir terminer la
	// chaine par le caractère de terminaison \0
	char * str = new char [4];
	str[0] = 'a';
	str[1] = 'b';
	str[2] = 'c';
	str[3] = '\0';
	size_t i = 0;

	if (!strcmp(str, abc.c_str())) {
		cout << "Equal !" << endl;
	}

	pr::List list;
	list.push_front(abc);
	list.push_front(abc);

	cout << "Liste : " << list << endl;
	cout << "Taille : " << list.size() << endl;

	// Affiche à l'envers
	// FAUTE : i est un entier non signé. Quand on le fait passer en-dessous
	// de 0, il devient égal à 2^(la taille du mot mémoire en bits) - 1
	// Donc il reste positif, la condition i >= 0 est vraie, et on essaie
	// d'accéder à list[2^(taille du mot mémoire) - 1], ce qui donne une
	// erreur de segmentation.
	// Soit on change le type de i vers entier signé, soit on change la
	// condition d'arrêt, et donc la portée de la variable d'itération.
	// On a pris la deuxième solution ici.
	for (i = list.size() ; i > 0 ; --i) {
		std::cout << "elt " << i-1 << ": " << list[i-1] << std::endl;
	}

	printf("On est là\n");

	// liberer les char de la chaine
	// FAUTE : on libère les mêmes octets deux fois, la première quand on
	// libère à la main chacun des octets, puis la deuxième quand on les
	// libère tous d'un coup. La bonne manière de faire, c'est de libérer
	// tous les octets d'un coup : ils ont en effet été alloués ensemble.
	// On supprime donc la boucle.
	// for (char *cp = str ; *cp ; cp++) {
	// 	delete cp;
	// }
	// et la chaine elle meme
	// FAUTE : on a alloué un tableau de 4 caractères avec new, on désalloue
	// avec delete[] et non pas delete
	delete[] str;

}
