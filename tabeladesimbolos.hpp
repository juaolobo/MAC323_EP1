#ifndef TS_H
#define TS_H

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> // formatacao de string
using namespace std;
// #include "vetorOrd.hpp"
// #include "listaDes.hpp"
// #include "listaOrd.hpp"
// #include "arvoreBin.hpp"

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



// // /* ------------------------------------------------------------------------------- 
// //    ------------------------------ VETOR DESORDENADO ------------------------------ 
// //    ------------------------------------------------------------------------------- */

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

// /* ---------------------------------------------------------------------------- 
//    ------------------------------ VETOR ORDENADO ------------------------------ 
//    ---------------------------------------------------------------------------- */

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

// /* ------------------------------ LISTA LIGADA -------------------------------- 
//    ---------------------------------------------------------------------------- 
//    ------------------------------- DESORDENADA -------------------------------- */

class nodeLL {
	private:
		string chave;
		int valor;
		nodeLL* prox;
		nodeLL* ant;

	public :
		nodeLL();
		~nodeLL();
		int getValor();
		string getChave();
		nodeLL* getProx();
		nodeLL* getAnt();
		void setValor(int valor);
		void setChave(string chave);
		void setProx(nodeLL* next);
		void setAnt(nodeLL* prev);
};


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

// /* ------------------------------ LISTA LIGADA -------------------------------- 
//    ---------------------------------------------------------------------------- 
//    -------------------------------- ORDENADA ---------------------------------- */


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

// /*  ---------------------------------------------------------------------------- 
// 	------------------------------ ARVORE BINARIA ------------------------------ 
//     ---------------------------------------------------------------------------- */

class nodeBin {

	public:
		string chave;
		int valor;
		nodeBin *esq;
		nodeBin *dir;
		nodeBin();
		~nodeBin();

};

class arvoreBin {

	private:
		nodeBin *raiz;
		int n;
		void deleteTree(nodeBin* raiz);
		nodeBin* put(nodeBin* raiz, string chave, int valor);
		nodeBin* get(nodeBin* raiz, string chave);
		int tamanho(nodeBin* raiz);
		nodeBin* maximo(nodeBin* raiz);
		nodeBin* apaga(nodeBin* raiz, string chave);
		nodeBin* select(nodeBin* raiz, int k);
		void print(nodeBin* raiz);

	public:
		arvoreBin(string nome_arquivo);
		~arvoreBin();
		void insere(string chave, int valor);
		int rank(string chave);
		int devolve(string chave);
		void remove(string chave);
		string seleciona(int k);
};


class nodeTR {
	private:

	public:
		nodeTR();
		~nodeTR();
		nodeTR* dir;
		nodeTR* esq;
		string chave;
		int valor;
		int prio;
};

class treap {
	private:
		nodeTR* raiz;
		int n;
		nodeTR* rotDir(nodeTR* raiz);
		nodeTR* rotEsq(nodeTR* raiz);
		void deleteTree(nodeTR* raiz);
		nodeTR* put(nodeTR* raiz, string chave, int valor);
		nodeTR* get(nodeTR* raiz, string chave);
		int tamanho(nodeTR* raiz);
		nodeTR* maximo(nodeTR* raiz);
		nodeTR* apaga(nodeTR* raiz, string chave);
		nodeTR* select(nodeTR* raiz, int k);

	public:
		treap(string nome_arquivo);
		~treap();
		void insere(string chave, int valor);
		int rank(string chave);
		int devolve(string chave);
		void remove(string chave);
		string seleciona(int k);

};

class node23 {
	private:
	public:
		node23();
		~node23();
		bool ehFolha();
		par info1;
		par info2;
		bool doisno;
		node23* pai;
		node23* ap1;
		node23* ap2;
		node23* ap3;
};

class arvore23 {

	private:
		node23* raiz;
		int n;
		void deleteTree(node23* raiz);
		node23* put(node23* raiz, string chave, int valor, bool& cresceu);
		int tamanho(node23* raiz);
		node23* apaga(node23* raiz, string chave);
		node23* get(node23* raiz, string chave);
		node23* minimo(node23* raiz);

	public:
		arvore23(string nome_arquivo);
		~arvore23();
		void insere(string chave, int valor);
		int rank(string chave);
		int devolve(string chave);
		void remove(string chave);
		string seleciona(int k);

};

#define VERMELHO 0
#define PRETO 1
#define DUPLO_PRETO 2

class nodeRN {
	private:
	public:
		nodeRN();
		~nodeRN();
		int valor;
		string chave;
		nodeRN* pai;
		nodeRN* esq;
		nodeRN* dir;
		int cor;
};

class arvoreRN {

	private:
		nodeRN* raiz;
		int n;
		void deleteTree(nodeRN* raiz);
		nodeRN* rotDir(nodeRN* raiz);
		nodeRN* rotEsq(nodeRN* raiz);
		nodeRN* put(nodeRN* raiz, string chave, int valor);
		nodeRN* get(nodeRN* raiz, string chave);
		int tamanho(nodeRN* raiz);
		nodeRN* maximo(nodeRN* raiz);
		nodeRN* apaga(nodeRN* raiz, string chave);
		nodeRN* select(nodeRN* raiz, int k);
		void print(nodeRN* raiz);

	public:
		arvoreRN(string nome_arquivo);
		~arvoreRN();
		void insere(string chave, int valor);
		int rank(string chave);
		int devolve(string chave);
		void remove(string chave);
		string seleciona(int k);

};

#endif