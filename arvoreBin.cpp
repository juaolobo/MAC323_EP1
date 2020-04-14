#include "tabeladesimbolos.hpp"
#include <iostream>
#include <fstream>
using namespace std;

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

nodeBin* arvoreBin::get(nodeBin* raiz, string chave) {

	if (raiz == nullptr)
		return raiz;

	if (raiz->chave == chave)
		return raiz;

	if (raiz->chave > chave)
		return get(raiz->esq, chave);

	return get(raiz->dir, chave);
}

int arvoreBin::tamanho(nodeBin* raiz) {

	if (raiz == nullptr) 
		return 0;
	return tamanho(raiz->dir) + 1 + tamanho(raiz->esq);
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
		n--;
		cout << chave << endl;
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
			aux = maximo(raiz->esq);
			raiz->valor = aux->valor;
			raiz->chave = aux->chave;
			raiz->esq = apaga(raiz->esq, aux->chave);
		}
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
	cout <<  n << endl;
}

arvoreBin::~arvoreBin() {

	deleteTree(raiz);
}

void arvoreBin::insere(string chave, int valor) {

	raiz = put(raiz, chave, valor);
}

int arvoreBin::rank(string chave) {

	int r = 0;
	nodeBin* aux = raiz;
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

int arvoreBin::devolve(string chave) {

	nodeBin* aux = get(raiz, chave);
	if (aux == nullptr)
		return 0;
	return aux->valor;
}

void arvoreBin::remove(string chave) {

	raiz = apaga(raiz, chave);
	print(raiz);
}

string arvoreBin::seleciona(int k) {

	// temons n posicoes comecando do 0
	if (k > n-1)
		return "";

	return select(raiz, k)->chave;

}

void arvoreBin::print(nodeBin* raiz) {

	if (raiz == nullptr)
		return ;
	cout << raiz->chave << endl;
	print(raiz->dir);
	print(raiz->esq);
}