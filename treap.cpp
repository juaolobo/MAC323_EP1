#include "tabeladesimbolos.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

nodeTR* treap::rotDir(nodeTR* raiz) {

	if (raiz == nullptr)
		return nullptr;

	if (raiz->esq == nullptr)
		return raiz;

	nodeTR* p = raiz->esq;
	raiz->esq = p->dir;
	p->dir = raiz;
	return p;
}

nodeTR* treap::rotEsq(nodeTR* raiz) {

	if (raiz == nullptr)
		return nullptr;

	if (raiz->dir == nullptr)
		return raiz;

	nodeTR* p = raiz->dir;
	raiz->dir = p->esq;
	p->esq = raiz;
	return p;
}

void treap::deleteTree(nodeTR* raiz) {

	if (raiz == nullptr)
		return;

	deleteTree(raiz->esq);
	deleteTree(raiz->dir);

	delete raiz;
	return;
}

nodeTR* treap::put(nodeTR* raiz, string chave, int valor) {

	if (raiz == nullptr){

		nodeTR* novo = new nodeTR;
		novo->prio = rand();
		novo->valor = valor;
		novo->chave = chave;
		novo->esq = nullptr;
		novo->dir = nullptr;
		n++;
		return novo;
	}

	if (raiz->chave > chave) {
		raiz->esq = put(raiz->esq, chave, valor);
		if (raiz->esq->prio > raiz->prio) 
			raiz = rotDir(raiz);
	}

	else if (raiz->chave < chave) {
		raiz->dir = put(raiz->dir, chave, valor);
		if (raiz->dir->prio > raiz->prio)
			raiz = rotEsq(raiz);
	}

	else
		raiz->valor += 1;

	return raiz;

}

int treap::get(nodeTR* raiz, string chave) {

	if (raiz == nullptr)
		return 0;

	if (raiz->chave == chave)
		return raiz->valor;

	if (raiz->chave > chave)
		return get(raiz->esq, chave);

	return get(raiz->dir, chave);
}

int treap::tamanho(nodeTR* raiz) {

	if (raiz == nullptr) 
		return 0;
	return tamanho(raiz->dir) + 1 + tamanho(raiz->esq);
}

nodeTR* treap::maximo(nodeTR* raiz) {

	if (raiz == nullptr || raiz->dir == nullptr)
		return raiz;

	return maximo(raiz->dir);
}

nodeTR* treap::apaga(nodeTR* raiz, string chave) {

	nodeTR* aux;
	if (raiz == nullptr)
		return raiz;

	if (raiz->chave > chave) 
		raiz->esq = apaga(raiz->esq, chave);

	else if (raiz->chave < chave)
		raiz->dir = apaga(raiz->dir, chave);

	else {
		n--;
		if (raiz->esq == nullptr){
			aux = raiz->dir;
			delete raiz;
			raiz = nullptr;
			return aux;
		}

		else if (raiz->dir == nullptr) {
			aux = raiz->esq;
			delete raiz;
			raiz = nullptr;
			return aux;
		}
		else {
			if (raiz->esq->prio > raiz->dir->prio){
				raiz = rotDir(raiz);
				raiz->esq = apaga(raiz->esq, chave);
			}
			else {
				raiz =  rotEsq(raiz);
				raiz->dir = apaga(raiz->dir, chave);
			}
		}
	}	
	return raiz;

}

nodeTR* treap::select(nodeTR* raiz, int k) {

	if (raiz == nullptr)
		return nullptr;

	if (rank(raiz->chave) == k)
		return raiz;

	if (rank(raiz->chave) > k)
		return select(raiz->esq, k);

	return select(raiz->dir, k);
}


treap::treap(string nome_arquivo) {

	raiz = nullptr;
	n = 0;
 	fstream file;
	string palavra;
	file.open(nome_arquivo);
	while (file >> palavra) {
		if (palavra != ""){

			// transforma a chave em lower case
			transform(palavra.begin(), palavra.end(), palavra.begin(), ::tolower);

			/* formatação de string (tira os ultimos caracteres que nao sao letras e mantem os acentos) */
			if ((palavra.back() < 'a' && palavra.back() > ' ') || palavra.back() > 'z')
				palavra.pop_back();

			if (palavra != ""){
				insere(palavra, 1);
			}
		}
	}
	file.close();
	cout << n << endl;
}

treap::~treap() {

	deleteTree(raiz);
}

void treap::insere(string chave, int valor) {

	raiz = put(raiz, chave, valor);
}

int treap::rank(string chave) {

	int r = 0;
	nodeTR* aux = raiz;
	if (raiz == nullptr)
		return 0;
	while (aux != nullptr && aux->chave != chave) {

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
		return r;
	return r + tamanho(aux->esq);
}

int treap::devolve(string chave) {

	return get(raiz, chave);
}

void treap::remove(string chave) {

	raiz = apaga(raiz, chave);
}

string treap::seleciona(int k) {

	// temons n posicoes comecando do 0
	if (k > n-1)
		return "";

	return select(raiz, k)->chave;

}