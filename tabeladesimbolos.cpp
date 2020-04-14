#include "tabeladesimbolos.hpp"
using namespace std;
/* ----------------- PAR -----------------*/

par::par() : valor(0), chave("") {};

string par::getChave() {
	return chave;
}

void par::setChave(string ch) {
	chave = ch;
}

int par::getValor() {
	return valor;
}

void par::setValor(int v) {
	
	if (v) 
		valor = v;
}
/* ----------------- node lista ligada ----------------- */
nodeLL::nodeLL() {};

nodeLL::~nodeLL() {};

int nodeLL::getValor() {
	return valor;
}

string nodeLL::getChave () {
	return chave;
}

nodeLL* nodeLL::getProx() {
	return prox;
}
nodeLL* nodeLL::getAnt() {
	return ant;
}

void nodeLL::setValor(int val) {
	valor = val;
}

void nodeLL::setChave(string ch) {
	chave = ch;
}

void nodeLL::setProx(nodeLL* next) {
	prox = next;
}

void nodeLL::setAnt(nodeLL* prev) {
	ant = prev;
}
/* ----------------- node arvore binaria ----------------- */

nodeBin::nodeBin(){};

nodeBin::~nodeBin() {};

/* ----------------- node treap ----------------- */

nodeTR::nodeTR(){};

nodeTR::~nodeTR() {};

/* ----------------- node 23 ----------------- */

node23::node23() : ap1(nullptr), ap2(nullptr), ap3(nullptr), pai(nullptr){};

node23::~node23() {};

bool node23::ehFolha() {
	return (ap1 == nullptr && ap2 == nullptr && ap3 == nullptr);
}

nodeRN::nodeRN() : dir(nullptr), esq(nullptr), pai(nullptr) {};

nodeRN::~nodeRN() {}
