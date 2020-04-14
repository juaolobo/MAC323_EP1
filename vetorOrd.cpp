#include "tabeladesimbolos.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;


vetorOrd::vetorOrd(string nome_arquivo) {

	n = 0;
	tam = 1;
	v = new par[1];
 	fstream file;
	string palavra;
	file.open(nome_arquivo);
	while (file >> palavra) {
		if (palavra != ""){
			
			// transforma a chave em lower case
			transform(palavra.begin(), palavra.end(), palavra.begin(), ::tolower);

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
