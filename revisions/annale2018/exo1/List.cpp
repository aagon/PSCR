
// FAUTE : On n'a pas inclu le fichier d'en-tête
// les déclarations ne sont donc pas connues du compilateur
#include "List.h"

namespace pr {

// ******************* Chainon

	Chainon::Chainon (const std::string & data, Chainon * next):data(data),next(next) {};

	size_t Chainon::length() {
		size_t len = 1;
		if (next != nullptr) {
			len += next->length();
		}
		// FAUTE : Si on part du principe que le but de size est de
		// rendre le nombre de chaînons (ce qui n'est dit nulle part
		// dans la consigne), alors remplacer length() par len fait
		// ce qui est demandé.
		return len;
	}

	// FAUTE : la déclaration de la méthode print de l'objet chainon était const
	void Chainon::print (std::ostream & os) const {
		os << data ;
		// FAUTE : on veut que le print sur le prochain chainon soit
		// bien conditionné à ce que la prochain chainon n'est pas le
		// pointeur nul
		if (next != nullptr) {
			os << ", ";
			next->print(os);
		}
	}

// ******************  List
	const std::string & List::operator[] (size_t index) const  {
		auto it = begin();
		for (size_t i=0; i < index ; i++) {
			++it;
		}
		return *it;
	}

	void List::push_back (const std::string& val) {
		if (tete == nullptr) {
			tete = new Chainon(val);
		} else {
			Chainon * fin = tete;
			while (fin->next) {
				fin = fin->next;
			}
			fin->next = new Chainon(val);
		}
	}

	void List::push_front (const std::string& val) {
		tete = new Chainon(val,tete);
	}

	// FAUTE : on doit préciser au compilateur qu'on définit la méthode
	// empty *de l'objet List* (il n'a aucun moyen de le deviner)
	bool List::empty() {
		return tete == nullptr;
	}

	size_t List::size() const {
		if (tete == nullptr) {
			return 0;
		} else {
			return tete->length();
		}
	}

	// FAUTE : on veut quand même que l'opérateur soit dans le namespace pr,
	// sinon l'éditeur de liens ne pourra pas résoudre quand on l'invoquera
	std::ostream & operator<< (std::ostream & os, const pr::List & vec)
	{
		os << "[";
		if (vec.tete != nullptr) {
			vec.tete->print (os) ;
		}
		os << "]";
		return os;
	}

} // namespace pr
