#include "tabeladesimbolos.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

void arvoreRN::deleteTree(nodeRN* raiz) {

	if (raiz == nullptr)
		return;

	deleteTree(raiz->dir);
	deleteTree(raiz->esq);

	delete raiz;
}

nodeRN* rotEsq(nodeRN* &raiz) {
	nodeRN* p = raiz->pai;
	p->dir = raiz->esq;
	if (raiz->dir != nullptr)
		raiz->dir->pai = p;
	raiz->esq = p;
	raiz->pai = p->pai;
	p->pai = raiz;
	return raiz;
}

nodeRN* rotDir(nodeRN* &raiz) {
	nodeRN* p = raiz->pai;
	p->esq = raiz->dir;
	if (raiz->esq != nullptr)
		raiz->esq->pai = p;
	raiz->dir = p;
	raiz->pai = p->pai;
	p->pai = raiz;
	return raiz;	
}

nodeRN* arvoreRN::put(nodeRN* raiz, string chave, int valor) {

	if (raiz == nullptr) {
		nodeRN *novo = new nodeRN;
		novo->chave = chave;
		novo->valor = valor;
		novo->cor = VERMELHO;
		n++;
		return novo;
	}

	nodeRN* p = raiz;
	bool achou = false;

	while (!achou) {

		if (p->chave > chave && p->esq != nullptr)
			p = p->esq;

		else if (p->chave > chave && p->esq == nullptr)
			achou = true;

		else if (p->chave < chave && p->dir != nullptr)
			p = p->dir;

		else if (p->chave < chave && p->dir == nullptr)
			achou = true;

		else achou = true;
	}

	if (p->chave == chave){
		p->valor += 1;
		return raiz;
	}

	nodeRN* novo = new nodeRN;
	novo->chave = chave;
	novo->valor = valor;
	novo->pai = p;
	novo->cor = VERMELHO;

	n++;

	if (p != nullptr && p->chave > chave)
		p->esq = novo;

	else if (p != nullptr && p->chave < chave)
		p->dir = novo;

	nodeRN* filho = novo;
	nodeRN* avo;
	nodeRN* tio;

	while (p != nullptr) {

		if (p->cor == PRETO)
			break;

		avo = p->pai;

		if (avo == nullptr) {
			p->cor = PRETO;
			break;
		}

		if (p == avo->esq)
			tio = avo->dir;
		else
			tio = avo->esq;

		if (tio != nullptr && tio->cor == VERMELHO) {
			p->cor = tio->cor = PRETO;
			avo->cor = VERMELHO;
			p = avo->pai;
			filho = avo;
		}

		else if (tio == nullptr || tio->cor == PRETO) {

			if (avo->esq == p && filho == p->esq) {
				avo->esq = p->dir;
				if (avo->pai != nullptr) {
					if (avo == avo->pai->esq)
						avo->pai->esq = p;
					else 
						avo->pai->dir = p;
				}

				if (p->dir != nullptr)
					p->dir->pai = avo;
				p->dir = avo;
				p->pai = avo->pai;
				avo->pai = p;
				p->cor = PRETO;
				avo->cor = VERMELHO;
				if (avo == raiz)
					raiz = p;
				break;
			}
			
			else if (avo->esq == p && filho == p->dir) {

				p->dir = filho->esq;
				if (filho->esq != nullptr)
					filho->esq->pai = p;
				filho->esq = p;
				p->pai = filho;
				filho->pai = avo;
				avo->esq = filho;
				p->pai = filho;
				p = avo->esq;
				filho = filho->esq;

			}

			else if (avo->dir == p && filho == p->dir) {
				avo->dir = p->esq;
				if (avo->pai != nullptr) {
					if (avo == avo->pai->esq)
						avo->pai->esq = p;
					else 
						avo->pai->dir = p;
				}
				if (p->esq != nullptr)
					p->esq->pai = avo;
				p->esq = avo;
				p->pai = avo->pai;
				avo->pai = p;
				p->cor = PRETO;
				avo->cor = VERMELHO;
				if (avo == raiz)
					raiz = p;
				break;
			}

			else if (avo->dir == p && filho == p->esq) {

				p->esq = filho->dir;
				if (filho->dir != nullptr)
					filho->dir->pai = p;
				filho->dir = p;
				p->pai = filho;
				filho->pai = avo;
				avo->dir = filho;
				p = filho;
				p = avo->dir;
				filho = filho->dir;

			}
		}

	}

	return raiz;

}

void arvoreRN::insere (string chave, int valor) {
	raiz = put(raiz, chave, valor);
}

arvoreRN::arvoreRN(string nome_arquivo) {

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
	cout << n << endl;
}

arvoreRN::~arvoreRN() {
	deleteTree(raiz);
}