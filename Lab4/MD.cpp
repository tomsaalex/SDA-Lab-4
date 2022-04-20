#include "MD.h"
#include "IteratorMD.h"
#include <exception>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int MD::aloca()
{
	int i = this->primLiber;
	primLiber = this->urm[this->primLiber];
	return i;
}

void MD::dealoca(int i)
{
	this->urm[i] = this->primLiber;
	this->primLiber = i;
}

void MD::resize()
{
	int doubleCapacity = 2 * this->cp;
	TElem* substituteE = new TElem[doubleCapacity];
	int* substituteUrm = new int[doubleCapacity];
	int i = this->prim;

	while (i != -1)
	{
		substituteUrm[i] = this->urm[i];
		substituteE[i] = this->e[i];
		i = this->urm[i];
	}

	int prevUrm = 0;

	delete[] this->e;
	delete[] this->urm;

	this->urm = substituteUrm;
	this->e = substituteE;

	for (int i = this->cp; i < doubleCapacity; i++)
		this->urm[i] = i + 1;

	this->urm[doubleCapacity - 1] = -1;
	this->primLiber = this->cp;

	this->cp = doubleCapacity;
}



MD::MD() {
	this->cp = INITIAL_SIZE;
	this->e = new TElem[INITIAL_SIZE];
	this->urm = new int[INITIAL_SIZE];
	
	for (int i = 0; i < INITIAL_SIZE; i++)
		this->urm[i] = i + 1;

	this->urm[INITIAL_SIZE - 1] = -1;

	this->primLiber = 0;
	this->prim = -1;
}

int MD::creeazaNod(TCheie c, TValoare v) {
	if (this->primLiber == -1)
	{
		resize();
	}

	TElem nod = make_pair(c, v);
	int i = this->aloca();
	this->e[i] = nod;
	this->urm[i] = -1;

	return i;
}

int MD::findIndex(TCheie c, TValoare v)
{
	int i = this->prim;
	
	while (i != -1)
	{
		if (this->e[i].first == c && this->e[i].second == v)
			return i;
		i = this->urm[i];
	}
	return -1;
}

void MD::adauga(TCheie c, TValoare v)
{
	int nou = creeazaNod(c, v);

	this->urm[nou] = this->prim;
	this->prim = nou;
	this->len++;
}

bool MD::sterge(TCheie c, TValoare v) {
	int p = findIndex(c, v);
	
	if (p == -1)
		return false;

	TElem elem = this->e[p];

	if (p == this->prim)
	{
		this->prim = this->urm[p];
		this->len--;
		return true;
	}
	else
	{
		int q = this->prim;
		while (this->urm[q] != p)
			q = this->urm[q];
		this->urm[q] = this->urm[p];
	}

	dealoca(p);
	
	this->len--;
	return true;
}


vector<TValoare> MD::cauta(TCheie c) const {
	vector<TValoare> foundElems;
	int i = this->prim;
	while (i != -1)
	{
		if (this->e[i].first == c)
		{
			foundElems.push_back(this->e[i].second);
		}

		i = this->urm[i];
	}

	return foundElems;
}


int MD::dim() const {
	return this->len;
}


bool MD::vid() const {
	return this->len == 0;
}

IteratorMD MD::iterator() const {
	return IteratorMD(*this);
}

/*
	Subalgoritm ceaMaiFrecventaValoare(md)
		{Verificam daca dictionarul este vid, caz in care returnam NULL_TVALOARE}
		{
			values: vector de intregi
			
		}
		
		Daca dim(md) = 0 atunci
			ceaMaiFrecventaValoare = NULL_TVALOARE
		SfDaca

		{In caz contrar, daca dictionarul contine un singur element, il returnam}
		Daca dim(md) = 1 atunci
			ceaMaiFrecventaValoare = e[i].second
		SfDaca

		{Copiem valorile din dictionar intr-un vector}
		i <- prim

		Cattimp i =/= -1 executa
			@Adaugam elementul e[i] in vector
			i <- urm[i]
		SfCattimp
		
		@Sortam vectorul de valori
		contor <- 1, value <- values[0], maxContor <- 0, maxValue <- 0;
		
		{Parcurgem vectorul sortat de valori, contorizam frecventa fiecarui element, si memoram elementul cu frecventa cea mai mare}
		Pentru i <- 1, size(values) executa
			Daca values[i] =/= values[i - 1] atunci
				Daca contor > maxContor atunci
					maxcontor <- contor
					maxValue <- value
				SfDaca
				contor <- 1
				value <- values[i]
			SfDaca
			Altfel
				contor <- contor + 1
		SfPentru
		
		Daca contor > maxContor atunci
			maxContor <- contor
			maxValue <- value
		SfDaca

		ceaMaiFrecventaValoare = maxValue
	SfSubalgoritm
*/
TValoare MD::ceaMaiFrecventaValoare() const
{
	vector<int> values;

	if (this->dim() == 0)
		return NULL_TVALOARE;

	if (this->dim() == 1)
		return this->e[this->prim].second;

	int i = this->prim;
	while (i != -1)
	{
		values.push_back(this->e[i].second);
		
		i = this->urm[i];
	}
	for (int i = 0; i < values.size()-1; i++)
	{
		for (int j = i + 1; j < values.size(); j++)
		{
			if (values.at(i) > values.at(j))
			{
				swap(values.at(i), values.at(j));
			}
		}
	}

	//sort(values.begin(), values.end());
	int contor = 1, value = values.at(0), maxContor = 0, maxValue = 0;
	for (int i = 1; i < values.size(); i++)
	{
		if (values.at(i) != values.at(i - 1))
		{
			if (contor > maxContor)
			{
				maxContor = contor;
				maxValue = value;
			}
			contor = 1;
			value = values.at(i);
		}
		else
			contor++;
	}

	if (contor > maxContor)
	{
		maxContor = contor;
		maxValue = value;
	}

	return maxValue;
}


MD::~MD() {
	delete[] this->urm;
	delete[] this->e;
}

