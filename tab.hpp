#ifndef TS_H
#define TS_H
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

/* ---------------------------------------------------------------------------- 
   -------------------------------- CLASSE PAR --------------------------------
   ---------------------------------------------------------------------------- */

class par {
	private:
		int valor;
		string chave;
	public:
		par();
		string getChave();
		void setChave(string ch);
		int getValor();
		void setValor(int v);
};

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

/* ------------------------------------------------------------------------------- 
   ------------------------------ VETOR DESORDENADO ------------------------------ 
   ------------------------------------------------------------------------------- */

class vetorDes {
	private :
		par *v;
		int n;
		int tam;
		void resize(int t);

	public :
		vetorDes(string nome_arquivo);
		~vetorDes();
		void insere(string chave, int valor);
		int rank(string chave);
		int devolve(string chave);
		void remove(string chave);
		string seleciona(int k);
};

vetorDes::vetorDes(string nome_arquivo) {

	n = 0;
	tam = 1;
	v = new par[1];
	fstream file;
	string palavra;
	file.open(nome_arquivo);
	while (file >> palavra) {
		if (palavra != ""){

			if ((palavra.back() < 'a' && palavra.back() > ' ') || palavra.back() > 'z')
				palavra.pop_back();

			if (palavra != "")
				insere(palavra, 1);
		}
	}
	file.close();
}

vetorDes::~vetorDes() {

	if (v != nullptr)
		delete [] v;
}

void vetorDes::resize(int t) {

	par *novo = new par[t];
	for (int i = 0; i < n; i++)
		novo[i] = v[i];
	delete [] v;
	v = novo;
	tam = t;
}

void vetorDes::insere(string chave, int valor) {

	if (n == tam)
		resize(2*n);

	transform(chave.begin(), chave.end(), chave.begin(), ::tolower);

	for (int i = 0; i < n; i++) {
		if (v[i].getChave() == chave) {
			v[i].setValor(v[i].getValor() + 1);
			return;
		}
	}
	v[n].setChave(chave);
	v[n].setValor(valor);
	n++;
}

int vetorDes::rank(string chave) {

	int i, c;
	c = 0;
	for (i = 0; i < n; i++) {
		if (v[i].getChave() < chave)
			c++;
	}
	return c; 
}

int vetorDes::devolve(string chave) {

	int i;
	for(i = 0; i < n; i++)
		if (v[i].getChave() == chave)
			return v[i].getValor();
	return 0;
}
void vetorDes::remove(string chave) {

	int i,j;
	for(i = 0; i < n; i++)
		if (v[i].getChave() == chave) {
			for (j = i; j < n; j++){
				if (j+1 < n)
					v[j] = v[j+1];
			}
			n--;
			return;
		}
}

string vetorDes::seleciona(int k) {
	int i;
	for (i = 0; i < n; i++){
		if (rank(v[i].getChave()) == k){
			return v[i].getChave();
		}
	}
	return "";
}

/* ---------------------------------------------------------------------------- 
   ------------------------------ VETOR ORDENADO ------------------------------ 
   ---------------------------------------------------------------------------- */

class vetorOrd {
	private :
		par *v;
		int n;
		int tam;
		void resize(int t);

	public :
		vetorOrd(string nome_arquivo);
		~vetorOrd();
		void insere(string chave, int valor);
		int rank(string chave);
		int devolve(string chave);
		void remove(string chave);
		string seleciona(int k);
};

vetorOrd::vetorOrd(string nome_arquivo) {

	n = 0;
	tam = 1;
	v = new par[1];
 	fstream file;
	string palavra;
	file.open(nome_arquivo);
	while (file >> palavra) {
		if (palavra != ""){
			/* formatação de string (tira os ultimos caracteres que nao sao letras e mantem os acentos)
			 'a' < x > ' ', significa todos os simbolos (passando pelas letras maiúsculas) */
			if ((palavra.back() < 'a' && palavra.back() > ' ') || palavra.back() > 'z')
				palavra.pop_back();

			if (palavra != "")
				insere(palavra, 1);
		}
	}
	file.close();
}

vetorOrd::~vetorOrd() {

	if (v != nullptr)
		delete [] v;
}

void vetorOrd::resize(int t) {

	par *novo = new par[t];
	for (int i = 0; i < n; i++)
		novo[i] = v[i];
	delete [] v;
	v = novo;
	tam = t;
}

void vetorOrd::insere(string chave, int valor) {

	if (n == tam)
		resize(n*2);

	// transforma a chave em lower case
	transform(chave.begin(), chave.end(), chave.begin(), ::tolower);

	if (n == 0){
		v[0].setValor(valor);
		v[0].setChave(chave);
		n++;
		return;
	}

	int r = rank(chave);
	if (v[r].getChave() == chave) 
		v[r].setValor(v[r].getValor()+1);

	else if (r < n) {
		n++;
		for (int i = n-1; i > r; i--){
			v[i] = v[i-1];
		}
		v[r].setValor(valor);
		v[r].setChave(chave);
	}
	else if (r >= n) {
		v[r].setValor(valor);
		v[r].setChave(chave);
		n++;
	}
}

int vetorOrd::rank(string chave) {

	if (n == 0 || n == 1)
		return 0;

	int ini = 0, fim = n-1, meio = (ini + fim)/2;;

	while (ini <= fim) {

		if (v[meio].getChave() == chave)
			return meio;

		else if (v[meio].getChave() > chave)
			fim = meio-1;

		else 
			ini = meio+1;

		meio = (ini + fim)/2;
	}
	if (fim < 0)
		return 0;

	return meio+1;

}

int vetorOrd::devolve(string chave) {

	int r = rank(chave);

	if (v[r].getChave() == chave)
		return v[r].getValor();
	return 0;
}

void vetorOrd::remove(string chave) {

	int r = rank(chave);
	int j;

	if (v[r].getChave() == chave) {
		for (j = r; j < n; j++){
			if (j+1 < n)
				v[j] = v[j+1];
		}
		n--;
	}
}

string vetorOrd::seleciona(int k) {
	if (k > n)
		return "";

	return v[k].getChave();
}


/* ------------------------------ LISTA LIGADA -------------------------------- 
   ---------------------------------------------------------------------------- 
   ------------------------------- DESORDENADA -------------------------------- */

class nodeLL {
	private:
		par info;
		nodeLL* prox;
		nodeLL* ant;

	public :
		nodeLL();
		~nodeLL();
		par getInfo();
		nodeLL* getProx();
		nodeLL* getAnt();
		void setValor(int valor);
		void setChave(string chave);
		void setProx(nodeLL* next);
		void setAnt(nodeLL* prev);
};

nodeLL::nodeLL() {};

nodeLL::~nodeLL() {};

par nodeLL::getInfo() {
	return info;
}

nodeLL* nodeLL::getProx() {
	return prox;
}
nodeLL* nodeLL::getAnt() {
	return ant;
}

void nodeLL::setValor(int valor) {
	info.setValor(valor);
}

void nodeLL::setChave(string chave) {
	info.setChave(chave);
}

void nodeLL::setProx(nodeLL* next) {
	prox = next;
}

void nodeLL::setAnt(nodeLL* prev) {
	ant = prev;
}

class listaDes {

	private:
		nodeLL *ini;
		nodeLL *fim;
		int n;


	public :
		listaDes(string nome_arquivo);
		~listaDes();
		void insere(string chave, int valor);
		int rank(string chave);
		int devolve(string chave);
		void remove(string chave);
		string seleciona(int k);
};

listaDes::listaDes(string nome_arquivo) {

	ini = nullptr;
	fim = nullptr;
	n = 0;
 	fstream file;
	string palavra;
	file.open(nome_arquivo);
	while (file >> palavra) {
		if (palavra != ""){

			/* formatação de string (tira os ultimos caracteres que nao sao letras e mantem os acentos) */
			if ((palavra.back() < 'a' && palavra.back() > ' ') || palavra.back() > 'z')
				palavra.pop_back();

			if (palavra != "")
				insere(palavra, 1);
		}
	}
	file.close();
	// print();
}

listaDes::~listaDes() {

	nodeLL* aux;
	if (ini != nullptr) {
		aux = ini;
		while (aux != nullptr){
			aux = ini->getProx();
			delete ini;
			ini = aux;
		}
	}
}

void listaDes::insere(string chave, int valor) {

	// transforma a chave em lower case
	transform(chave.begin(), chave.end(), chave.begin(), ::tolower);

	if (ini == nullptr){
		nodeLL* novo = new nodeLL;
		novo->setProx(nullptr);
		novo->setAnt(nullptr);
		novo->setChave(chave);
		novo->setValor(valor);
		ini = fim = novo;
		n++;
		return;
	}

	nodeLL* aux = ini;

	while (aux != nullptr && aux->getInfo().getChave() != chave)
		aux = aux->getProx();

	if (aux != nullptr)
		aux->setValor(aux->getInfo().getValor() + 1);

	else {
		nodeLL* novo = new nodeLL;
		novo->setChave(chave);
		novo->setValor(valor);
		novo->setProx(nullptr);
		novo->setAnt(fim);

		fim->setProx(novo);
		fim = novo;
		n++;
	}
}

int listaDes::rank(string chave) {

	nodeLL *aux = ini;
	int c = 0;
	while(aux != nullptr) {
		if (aux->getInfo().getChave() < chave) {
			c++;
		}
		aux = aux->getProx();
	}
	return c;
}

int listaDes::devolve(string chave) {

	nodeLL* aux = ini;

	while(aux != nullptr) {
		if (aux->getInfo().getChave() == chave)
			return aux->getInfo().getValor();
		aux = aux->getProx();
	}

	return 0;
}

void listaDes::remove(string chave) {

	nodeLL* aux = ini;
	while (aux != nullptr && aux->getInfo().getChave() != chave)
		aux = aux->getProx();

	if (aux != nullptr) {
		aux->getAnt()->setProx(aux->getProx());
		aux->getProx()->setAnt(aux->getAnt());
		delete aux;
		n--;
	}
}

string listaDes::seleciona(int k) {

	nodeLL *aux = ini;
	while (aux != nullptr){
		if (rank(aux->getInfo().getChave()) == k)
			return aux->getInfo().getChave();
		aux = aux->getProx();
	}
	return "";
}

/* ------------------------------ LISTA LIGADA -------------------------------- 
   ---------------------------------------------------------------------------- 
   -------------------------------- ORDENADA ---------------------------------- */


class listaOrd {

	private:
		nodeLL *ini;
		nodeLL *fim;
		int n;


	public :
		listaOrd(string nome_arquivo);
		~listaOrd();
		void insere(string chave, int valor);
		int rank(string chave);
		int devolve(string chave);
		void remove(string chave);
		string seleciona(int k);
		void print();
};

listaOrd::listaOrd(string nome_arquivo) {

	ini = nullptr;
	fim = nullptr;
	n = 0;
 	fstream file;
	string palavra;
	file.open(nome_arquivo);
	while (file >> palavra) {
		if (palavra != ""){

			/* formatação de string (tira os ultimos caracteres que nao sao letras e mantem os acentos) */
			if ((palavra.back() < 'a' && palavra.back() > ' ') || palavra.back() > 'z')
				palavra.pop_back();

			if (palavra != "")
				insere(palavra, 1);
		}
	}
	file.close();
	// print();
}

listaOrd::~listaOrd() {

	nodeLL* aux;
	if (ini != nullptr) {
		aux = ini;
		while (aux != nullptr){
			aux = ini->getProx();
			delete ini;
			ini = aux;
		}
	}
}

void listaOrd::insere(string chave, int valor) {

	// transforma a chave em lower case
	transform(chave.begin(), chave.end(), chave.begin(), ::tolower);

	if (ini == nullptr){
		nodeLL* novo = new nodeLL;
		novo->setProx(nullptr);
		novo->setAnt(nullptr);
		novo->setChave(chave);
		novo->setValor(valor);
		ini = fim = novo;
		n++;
		return;
	}

	nodeLL* aux = ini;
	nodeLL* prox = aux->getProx();

	while(aux != nullptr && chave >= aux->getInfo().getChave()) {

		if (aux->getInfo().getChave() == chave){
			aux->setValor(aux->getInfo().getValor() + 1);
			return;
		}

		aux = prox;
		if (prox != nullptr)
			prox = prox->getProx();
	}

	nodeLL* novo = new nodeLL;
	novo->setValor(valor);
	novo->setChave(chave);
	n++;

	if (aux == nullptr) {
		fim->setProx(novo);
		novo->setAnt(fim);
		novo->setProx(nullptr);
		fim = novo;
		return;
	}

	if (aux == ini) {
		ini->setAnt(novo);
		novo->setProx(ini);
		novo->setAnt(nullptr);
		ini = novo;
		return;
	}

	nodeLL* ant = aux->getAnt();
	novo->setProx(aux);
	novo->setAnt(ant);
	ant->setProx(novo);
	aux->setAnt(novo);

}

int listaOrd::rank(string chave) {

	nodeLL* aux = ini;
	int r = 0;
	while (aux != nullptr && aux->getInfo().getChave() != chave){
		if (aux != nullptr && aux->getInfo().getChave() < chave)
			r++;
		if (aux != nullptr)
			aux = aux->getProx();
	}
	return r;
}	

int listaOrd::devolve(string chave) {

	nodeLL *aux;
	while(aux != nullptr) {
		if (aux->getInfo().getChave() == chave)
			return aux->getInfo().getValor();
		aux = aux->getProx();
	}

	return 0;

}

void listaOrd::remove(string chave) {

	nodeLL* aux = ini;

	while (aux != nullptr && aux->getInfo().getChave() != chave)
		aux = aux->getProx();

	if (aux != nullptr) {

		if (aux == ini) {
			ini = aux->getProx();
			aux->setAnt(nullptr);
		}

		if (aux == fim) {
			fim = aux->getAnt();
			aux->setProx(nullptr);
		}

		if (aux->getAnt() != nullptr)
			aux->getAnt()->setProx(aux->getProx());

		if (aux->getProx() != nullptr)
			aux->getProx()->setAnt(aux->getAnt());

		delete aux;
		n--;
	}
}

string listaOrd::seleciona(int k) {

	if (k < n) {
		nodeLL *aux = ini;
		for(int i = 0; i < k; i++)
			aux = aux->getProx();
		return aux->getInfo().getChave();
	}
	return "";
}

/*  ---------------------------------------------------------------------------- 
	------------------------------ ARVORE BINARIA ------------------------------ 
    ---------------------------------------------------------------------------- */

class nodeBin {

	public:
		string chave;
		int valor;
		nodeBin *esq;
		nodeBin *dir;
		nodeBin();
		~nodeBin();

};

nodeBin::nodeBin(){};

nodeBin::~nodeBin() {};

class arvoreBin {

	private:
		nodeBin *raiz;
		int n;
		void deleteTree(nodeBin* raiz);
		nodeBin* put(nodeBin* raiz, string chave, int valor);
		int get(nodeBin* raiz, string chave);
		int tamanho(nodeBin* raiz);
		nodeBin* maximo(nodeBin* raiz);
		nodeBin* apaga(nodeBin* raiz, string chave);
		nodeBin* select(nodeBin* raiz, int k);

	public:
		arvoreBin(string nome_arquivo);
		~arvoreBin();
		void insere(string chave, int valor);
		int rank(string chave);
		int devolve(string chave);
		void remove(string chave);
		string seleciona(int k);
};

void arvoreBin::deleteTree(nodeBin* raiz) {

	if (raiz == nullptr)
		return;

	deleteTree(raiz->esq);
	deleteTree(raiz->dir);

	delete raiz;
	return;
}

nodeBin* arvoreBin::put(nodeBin* raiz, string chave, int valor) {

	if (raiz == nullptr){

		nodeBin* novo = new nodeBin;
		novo->valor = valor;
		novo->chave = chave;
		novo->esq = nullptr;
		novo->dir = nullptr;
		n++;
		return novo;
	}

	if (raiz->chave == chave) 
		raiz->valor = raiz->valor + 1;

	else if (raiz->chave > chave)
		raiz->esq = put(raiz->esq, chave, valor);

	else
		raiz->dir = put(raiz->dir, chave, valor);

	return raiz;
}	

int arvoreBin::get(nodeBin* raiz, string chave) {

	if (raiz == nullptr)
		return 0;

	if (raiz->chave == chave)
		return raiz->valor;

	if (raiz->chave > chave)
		return get(raiz->esq, chave);

	return get(raiz->dir, chave);
}

int arvoreBin::tamanho(nodeBin* raiz) {

	if (raiz == nullptr) 
		return 0;
	int tam = 0;
	tam = tamanho(raiz->dir) + 1 + tamanho(raiz->esq);
	return tam;
}

nodeBin* arvoreBin::maximo(nodeBin* raiz) {

	if (raiz == nullptr || raiz->dir == nullptr)
		return raiz;

	return maximo(raiz->dir);
}

nodeBin* arvoreBin::apaga(nodeBin* raiz, string chave) {

	nodeBin* aux;
	if (raiz == nullptr)
		return raiz;

	if (raiz->chave > chave) 
		raiz->esq = apaga(raiz->esq, chave);

	else if (raiz->chave < chave)
		raiz->dir = apaga(raiz->dir, chave);

	else {
		if (raiz->esq == nullptr){
			aux = raiz->dir;
			delete raiz;
			return aux;
		}

		else if (raiz->dir == nullptr) {
			aux = raiz->esq;
			delete raiz;
			return aux;
		}
		else {
			aux = maximo(raiz->esq);
			raiz->valor = aux->valor;
			raiz->chave = aux->chave;
			raiz->esq = apaga(raiz->esq, aux->chave);
		}
		n--;
	}	
	return raiz;

}

nodeBin* arvoreBin::select(nodeBin* raiz, int k) {

	if (raiz == nullptr)
		return nullptr;

	if (rank(raiz->chave) == k)
		return raiz;

	if (rank(raiz->chave) > k)
		return select(raiz->esq, k);

	return select(raiz->dir, k);
}


arvoreBin::arvoreBin(string nome_arquivo) {

	raiz = nullptr;
	n = 0;
 	fstream file;
	string palavra;
	file.open(nome_arquivo);
	while (file >> palavra) {
		if (palavra != ""){

			/* formatação de string (tira os ultimos caracteres que nao sao letras e mantem os acentos) */
			if ((palavra.back() < 'a' && palavra.back() > ' ') || palavra.back() > 'z')
				palavra.pop_back();

			if (palavra != ""){
				insere(palavra, 1);
			}
		}
	}
	file.close();
}

arvoreBin::~arvoreBin() {

	deleteTree(raiz);
}

void arvoreBin::insere(string chave, int valor) {

	// transforma a chave em lower case
	transform(chave.begin(), chave.end(), chave.begin(), ::tolower);

	raiz = put(raiz, chave, valor);
}

int arvoreBin::rank(string chave) {

	int r = 0;
	nodeBin* aux = raiz;
	nodeBin* ant;
	if (raiz == nullptr)
		return 0;
	while (aux != nullptr && aux->chave != chave) {

		ant = aux;
		if (aux->chave > chave){
			aux = aux->esq;
		}
		else if (aux->chave < chave) {
			r += 1 + tamanho(aux->esq);
			aux = aux->dir;
		}
	}
	// caso a palavra nao esteja na lista
	if (aux == nullptr)
		return r + tamanho(ant->esq);
	return r + tamanho(aux->esq);
}

int arvoreBin::devolve(string chave) {

	return get(raiz, chave);
}

void arvoreBin::remove(string chave) {

	raiz = apaga(raiz, chave);
}

string arvoreBin::seleciona(int k) {

	// temons n posicoes comecando do 0
	if (k > n-1)
		return "";

	return select(raiz, k)->chave;

}

class nodeTp {
	private:

	public:
		nodeTp();
		~nodeTp();
		nodeTp* dir;
		nodeTp* esq;
		string chave;
		int valor;
		int prio;
}

class treap {
	private:
		nodeTp* raiz;
		int n;
		nodeTp* rotDir(nodeTp* raiz);
		nodeTp* rotEsq(nodeTp* raiz);
		void deleteTree(nodeTp* raiz);
		nodeTp* put(nodeTp* raiz, string chave, int valor);
		int get(nodeTp* raiz, string chave);
		int tamanho(nodeTp* raiz);
		nodeTp* maximo(nodeTp* raiz);
		nodeTp* apaga(nodeTp* raiz, string chave);
		nodeTp* select(nodeTp* raiz, int k);


	public:
		arvoreBin(string nome_arquivo);
		~arvoreBin();
		void insere(string chave, int valor);
		int rank(string chave);
		int devolve(string chave);
		void remove(string chave);
		string seleciona(int k);

};

#endif