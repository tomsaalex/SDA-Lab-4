#pragma once
#include<vector>
#include<utility>

#define NULL_TVALOARE -1
#define INITIAL_SIZE 10

using namespace std;

typedef int TCheie;
typedef int TValoare;

typedef std::pair<TCheie, TValoare> TElem;

class IteratorMD;

class MD
{
	friend class IteratorMD;

private:
	/* aici e reprezentarea */
	int cp;
	int primLiber = 0, prim = -1;
	int len = 0;

	TElem* e;
	int* urm;

	//Theta(cp)
	void resize();

	//Theta(1)
	int aloca();

	//Theta(1)
	void dealoca(int i);

	//Theta(1) amortizat
	int creeazaNod(TCheie c, TValoare v);

	//O(cp)
	int findIndex(TCheie c, TValoare v);

public:
	// constructorul implicit al MultiDictionarului
	MD();

	//Theta(1) amortizat
	// adauga o pereche (cheie, valoare) in MD	
	void adauga(TCheie c, TValoare v);

	//Theta(cp)
	//cauta o cheie si returneaza vectorul de valori asociate
	vector<TValoare> cauta(TCheie c) const;

	//O(cp)
	//sterge o cheie si o valoare 
	//returneaza adevarat daca s-a gasit cheia si valoarea de sters
	bool sterge(TCheie c, TValoare v);

	//Theta(1)
	//returneaza numarul de perechi (cheie, valoare) din MD 
	int dim() const;

	//Theta(1)
	//verifica daca MultiDictionarul e vid 
	bool vid() const;

	//Theta(1)
	// se returneaza iterator pe MD
	IteratorMD iterator() const;

	//O(cp^2) / O(cp*log(cp))
	//Returneaza valoarea care apare cel mai frecvent in multidictionar.
	TValoare ceaMaiFrecventaValoare() const;

	//Theta(1)
	// destructorul MultiDictionarului	
	~MD();
};

