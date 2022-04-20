#include "IteratorMD.h"
#include "MD.h"

using namespace std;

IteratorMD::IteratorMD(const MD& _md): md(_md) {
	this->poz = md.prim;
}

TElem IteratorMD::element() const{
	return this->md.e[this->poz];
}

bool IteratorMD::valid() const {
	return this->poz >= 0;
}

void IteratorMD::urmator() {
	this->poz = this->md.urm[poz];
}

void IteratorMD::prim() {
	this->poz = md.prim;
}

