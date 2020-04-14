#include "tabeladesimbolos.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

vetorDes::vetorDes(string nome_arquivo) {

	n = 0;
	tam = 1;
	v = new par[1];
	fstream file;
	string palavra;
	file.open(nome_arquivo);
	while (file >> palavra) {
		if (palavra != ""){

			transform(palavra.begin(), palavra.end(), palavra.begin(), ::tolower);

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
