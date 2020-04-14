#include "tabeladesimbolos.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

listaOrd::listaOrd(string nome_arquivo) {

	ini = nullptr;
	fim = nullptr;
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

	while(aux != nullptr && chave >= aux->getChave()) {

		if (aux->getChave() == chave){
			aux->setValor(aux->getValor() + 1);
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
	while (aux != nullptr && aux->getChave() != chave){
		if (aux != nullptr && aux->getChave() < chave)
			r++;
		if (aux != nullptr)
			aux = aux->getProx();
	}
	return r;
}	

int listaOrd::devolve(string chave) {

	nodeLL *aux = ini;
	while(aux != nullptr) {
		if (aux->getChave() == chave)
			return aux->getValor();
		aux = aux->getProx();
	}

	return 0;

}

void listaOrd::remove(string chave) {

	nodeLL* aux = ini;

	while (aux != nullptr && aux->getChave() != chave)
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
		return aux->getChave();
	}
	return "";
}

