#include "tabeladesimbolos.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

listaDes::listaDes(string nome_arquivo) {

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

	while (aux != nullptr && aux->getChave() != chave)
		aux = aux->getProx();

	if (aux != nullptr)
		aux->setValor(aux->getValor() + 1);

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
		if (aux->getChave() < chave) {
			c++;
		}
		aux = aux->getProx();
	}
	return c;
}

int listaDes::devolve(string chave) {

	nodeLL* aux = ini;

	while(aux != nullptr) {
		if (aux->getChave() == chave)
			return aux->getValor();
		aux = aux->getProx();
	}

	return 0;
}

void listaDes::remove(string chave) {

	nodeLL* aux = ini;
	while (aux != nullptr && aux->getChave() != chave)
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
		if (rank(aux->getChave()) == k)
			return aux->getChave();
		aux = aux->getProx();
	}
	return "";
}