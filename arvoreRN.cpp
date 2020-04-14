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

nodeRN* arvoreRN::rotDir(nodeRN* raiz) {

	if (raiz == nullptr)
		return nullptr;

	nodeRN* p = raiz, *pai = p->pai;
	pai->esq = p->dir;
	if (pai->pai != nullptr){
		if (pai == pai->pai->esq)
			pai->pai->esq = p;
		else
			pai->pai->dir = p;
	}
	if (p->dir != nullptr)
		p->dir->pai = pai;
	p->dir = pai;
	p->pai = pai->pai;
	pai->pai = p;

	return p;
}

nodeRN* arvoreRN::rotEsq(nodeRN* raiz) {

	if (raiz == nullptr)
		return nullptr;

	nodeRN* p = raiz, *pai = p->pai;
	pai->dir = p->esq;
	if (pai->pai != nullptr){
		if (pai == pai->pai->dir)
			pai->pai->dir = p;
		else
			pai->pai->esq = p;
	}
	if (p->esq != nullptr)
		p->esq->pai = pai;
	p->esq = pai;
	p->pai = pai->pai;
	pai->pai = p;
	
	return p;
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
		p->valor++;
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

		// rotacao para direita com os dois no mesmo laod
			if (avo->esq == p && filho == p->esq) {
				p = rotDir(p);
				p->cor = PRETO;
				avo->cor = VERMELHO;
				if (avo == raiz)
					raiz = p;
				break;
			}
			
		// rotacao para esquerda com os dois de lados diferentes
			else if (avo->esq == p && filho == p->dir) {
				filho = rotEsq(filho);
				p = avo->esq;
				filho = filho->esq;
			}

		// rotacao para esquerda com os dois do mesmo lado
			else if (avo->dir == p && filho == p->dir) {

				p = rotEsq(p);
				p->cor = PRETO;
				avo->cor = VERMELHO;
				if (avo == raiz)
					raiz = p;
				break;
			}

		// rotacao para direita com os dois de lados diferentes
			else if (avo->dir == p && filho == p->esq) {

				filho = rotDir(filho);
				p = avo->dir;
				filho = filho->dir;

			}
		}

	}

	return raiz;

}

nodeRN* arvoreRN::get(nodeRN* raiz, string chave) {

	if (raiz == nullptr)
		return raiz;

	if (raiz->chave == chave)
		return raiz;

	if (raiz->chave > chave)
		return get(raiz->esq, chave);

	return get(raiz->dir, chave);
}

int arvoreRN::tamanho(nodeRN* raiz) {

	if (raiz == nullptr) 
		return 0;
	return tamanho(raiz->dir) + 1 + tamanho(raiz->esq);
}

nodeRN* arvoreRN::maximo(nodeRN* raiz) {

	if (raiz == nullptr || raiz->dir == nullptr)
		return raiz;

	return maximo(raiz->dir);
}

nodeRN* arvoreRN::apaga(nodeRN* raiz, string chave) {

	if (raiz == nullptr)
		return raiz;

	if (raiz->chave > chave)
		raiz->esq = apaga(raiz->esq, chave);

	else if (raiz->chave < chave)
		raiz->dir = apaga(raiz->dir, chave);

	else { // raiz->chave = chave
		nodeRN* aux;
		if (raiz->esq == nullptr){
			aux = raiz->dir;
			if (aux != nullptr)
				aux->pai = raiz->pai;
			delete raiz;
			n--;
			raiz = nullptr;
			return aux;
		}

		else if (raiz->dir == nullptr) {
			aux = raiz->esq;
			if (aux != nullptr)
				aux->pai = raiz->pai;
			delete raiz;
			raiz = nullptr;
			n--;
			return aux;
		}

		else {
			aux = maximo(raiz->esq);
			raiz->valor = aux->valor;
			raiz->chave = aux->chave;
			raiz->esq = apaga(raiz->esq, aux->chave);
			return raiz;
		}

		nodeRN* irmao;
		if (raiz->pai->dir == raiz)
			irmao = raiz->pai->esq;
		else 
			irmao = raiz->pai->dir;
		if (raiz->cor == PRETO || raiz->cor == DUPLO_PRETO) {

			if (irmao->cor == PRETO){		
				if ((irmao->dir->cor == PRETO && irmao->dir->cor == PRETO) ||
					(irmao->dir == nullptr || irmao->esq == nullptr)) {
					irmao->cor = VERMELHO;
					raiz->pai->cor = DUPLO_PRETO;
					delete raiz;
					n--;
					raiz = nullptr;
					if (raiz->pai->pai == nullptr)
						raiz->pai->cor = PRETO;
					raiz->pai = apaga(raiz->pai, raiz->pai->chave);
				}
				if (raiz == raiz->pai->esq) {
					if(irmao->dir->cor == VERMELHO) {
						irmao->cor = irmao->dir->cor;
						irmao->dir->cor = PRETO;
						irmao = rotDir(irmao);
						raiz = apaga(raiz, raiz->chave);
					}
					else if (irmao->dir->cor == PRETO && irmao->esq->cor == VERMELHO) {
						int x = irmao->cor;
						raiz->pai->cor = irmao->cor;
						irmao->cor = x;
						raiz->pai = rotEsq(raiz->pai);
						raiz->pai->dir->cor = VERMELHO;
						raiz->cor = PRETO;
						return raiz;
					}
				}
				else {
					if(irmao->esq->cor == VERMELHO) {
						irmao->cor = irmao->esq->cor;
						irmao->esq->cor = PRETO;
						irmao = rotDir(irmao);
						raiz = apaga(raiz, raiz->chave);
					}
					else if (irmao->esq->cor == PRETO && irmao->dir->cor == VERMELHO) {
						int x = irmao->cor;
						raiz->pai->cor = irmao->cor;
						irmao->cor = x;
						raiz->pai = rotEsq(raiz->pai);
						raiz->pai->esq->cor = VERMELHO;
						raiz->cor = PRETO;
						return raiz;
					}

				}

			}
			else if (irmao->cor == VERMELHO) {

				raiz->pai->cor = VERMELHO;
				irmao->cor = PRETO;

				if (raiz->pai->dir == raiz)
					raiz->pai = rotDir(raiz->pai);

				else 
					raiz->pai = rotEsq(raiz->pai);
				raiz->cor = DUPLO_PRETO;
				raiz = apaga(raiz, raiz->chave);
			}

		}

	}

	return raiz;

}

nodeRN* arvoreRN::select(nodeRN* raiz, int k) {

	if (raiz == nullptr)
		return nullptr;

	if (rank(raiz->chave) == k)
		return raiz;

	if (rank(raiz->chave) > k)
		return select(raiz->esq, k);

	return select(raiz->dir, k);
}

arvoreRN::arvoreRN(string nome_arquivo) {

	raiz = nullptr;
	n = 0;
 	fstream file;
	string palavra;
	file.open(nome_arquivo);
	while (file >> palavra) {
		if (palavra != ""){

			// transforma a chave em lower case
			transform(palavra.begin(), palavra.end(), palavra.begin(), ::tolower);
			 // formatação de string (tira os ultimos caracteres que nao sao letras e mantem os acentos) 
			if ((palavra.back() < 'a' && palavra.back() > ' ') || palavra.back() > 'z')
				palavra.pop_back();
			if (palavra != ""){
				insere(palavra, 1);
			}
		}
	}
	file.close();
	print(raiz);
	cout << "Temos " << n << " palavras diferentes na tabela" << endl << endl;;
}

arvoreRN::~arvoreRN() {
	deleteTree(raiz);
}

void arvoreRN::insere (string chave, int valor) {
	raiz = put(raiz, chave, valor);
}

int arvoreRN::rank(string chave) {

	int r = 0;
	nodeRN* aux = raiz;
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

int arvoreRN::devolve(string chave) {

	nodeRN* aux = get(raiz, chave);
	if (aux == nullptr)
		return 0;
	return aux->valor;

}

void arvoreRN::remove(string chave) {
	raiz = apaga(raiz, chave);
	print(raiz);
	cout << "Agora temos " << n << " palavras diferentes" << endl;
}

string arvoreRN::seleciona(int k) {

	// temons n posicoes comecando do 0
	if (k > n-1)
		return "";

	return select(raiz, k)->chave;

}

void arvoreRN::print(nodeRN* raiz) {
	if (raiz == nullptr)
		return;
	if (raiz->cor == PRETO)
		cout << "PRETO : ";
	else if (raiz->cor == DUPLO_PRETO)
		cout << "DUPLO_PRETO : ";
	else 
		cout << "VERMELHO : ";

	cout << "\"" << raiz->chave << "\"";
	if (raiz->pai != nullptr){
		cout << " FILHO DE ";
		cout << "\'" << raiz->pai->chave << "\'"<< endl;
	}
	else 
		cout << endl;
 
	print(raiz->esq);
	print(raiz->dir);
}