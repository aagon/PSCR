#ifndef SRC_LIST_H_
#define SRC_LIST_H_

#include <cstddef>
#include <string>
#include <ostream>

namespace pr {

class Chainon {
public :
	std::string data;
	Chainon * next;
	Chainon (const std::string & data, Chainon * next=nullptr);
	std::size_t length() ;
	void print (std::ostream & os) const;
};

class List {
public:

	Chainon * tete;

	List(): tete(nullptr)  {}

	~List() {
		for (Chainon * c = tete ; c ; ) {
			Chainon * tmp = c->next;
			delete c;
			c = tmp;
		}
	}

	const std::string & operator[] (size_t index) const ;

	void push_back (const std::string& val) ;

	// FAUTE : on ne définit qu'une fois une méthode à prototype constant
	// Cette méthode est déjà définie dans List.cpp
	// On choisit de transformer celle-ci plutôt que l'autre en déclaration
	// par convention : déclarations dans .h, implantations dans .cpp
	void push_front (const std::string& val) ;

	bool empty() ;

	size_t size() const ;


	class ConstListIte {
		const Chainon * cur;
	public:
		// default ctor = end()
		ConstListIte (const Chainon * cur=nullptr) : cur(cur) {}

		const std::string & operator* () const {
			return cur->data;
		}
		const std::string * operator-> () const {
			return & cur->data;
		}
		ConstListIte & operator++ () {
			cur = cur->next;
			return *this;
		}
		bool operator!= (const ConstListIte &o) const {
			return cur != o.cur;
		}
	};

	typedef ConstListIte const_iterator;

	const_iterator begin() const {
		return tete;
	}
	const_iterator end() const {
		return nullptr;
	}
};


std::ostream & operator<< (std::ostream & os, const List & vec) ;

} /* namespace pr */

#endif /* SRC_LIST_H_ */
