#include "tabeladesimbolos.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;


void arvore23::deleteTree(node23* raiz) {

	if (raiz == nullptr)
		return;

	deleteTree(raiz->ap3);
	deleteTree(raiz->ap1);
	deleteTree(raiz->ap2);

	delete raiz;
}

node23* arvore23::put(node23* raiz, string chave, int valor, bool &cresceu) {

	if (raiz == nullptr) {
		node23* novo = new node23;
		novo->info1.setChave(chave);
		novo->info1.setValor(valor);
		novo->doisno = true;
		cresceu = true;
		n++;
		return novo; 
	}	

	// /* caso ja esteja na tabela */

	if (raiz->info1.getChave() == chave) {
		raiz->info1.setValor(raiz->info1.getValor() + 1);
		cresceu = false;
		return raiz;
	}

	if (!raiz->doisno && raiz->info2.getChave() == chave) {
		raiz->info2.setValor(raiz->info2.getValor() + 1);
		cresceu = false;
		return raiz;
	}
	/* ------------------------ */

	// caso nao esteja na tabela

	if (raiz->ehFolha()) {
		n++;
		if (raiz->doisno) {
			if (raiz->info1.getChave() < chave) {
				raiz->info2.setChave(chave);
				raiz->info2.setValor(valor);
			}
			else if (raiz->info1.getChave() > chave){
				raiz->info2.setChave(raiz->info1.getChave());
				raiz->info2.setValor(raiz->info1.getValor());

				raiz->info1.setChave(chave);
				raiz->info1.setValor(valor);
			}

			raiz->doisno = false;
			cresceu = false;
			return raiz;
		}

		else { // eh tres-no e folha

			node23* maior = new node23;
			node23* meio = new node23;

			// descobre quem eh o meio, maior e menor

			if (chave > raiz->info2.getChave()) {
				maior->info1.setChave(chave);
				maior->info1.setValor(valor);

				meio->info1.setChave(raiz->info2.getChave());
				meio->info1.setValor(raiz->info2.getValor());
			}

			else if (chave < raiz->info2.getChave()){

				maior->info1.setChave(raiz->info2.getChave());
				maior->info1.setValor(raiz->info2.getValor());

				if (chave > raiz->info1.getChave()) {
					meio->info1.setChave(chave);
					meio->info1.setValor(valor);
				}
				else if (chave < raiz->info1.getChave()){
					meio->info1.setChave(raiz->info1.getChave());
					meio->info1.setValor(raiz->info1.getValor());

					raiz->info1.setChave(chave);
					raiz->info1.setValor(valor);
				}
			}

			maior->doisno = true;
			maior->pai = meio;

			meio->doisno = true;
			meio->pai = raiz->pai;
			meio->ap1 = raiz;
			meio->ap2 = maior;

			raiz->doisno = true;
			raiz->ap1 = raiz->ap2 = raiz->ap3 = nullptr;
			raiz->pai = meio;

			cresceu = true;
			return meio;
		}

	}
	else {
		if (raiz->info1.getChave() > chave) {
			node23* p = put(raiz->ap1, chave, valor, cresceu);

			if (!cresceu) {
				raiz->ap1 = p;
				p->pai = raiz;
				return raiz;
			}
			else {
				if (raiz->doisno) {
					// como p veio da sub esq, ele eh menor então ocupa a info 1
					raiz->doisno = false;
					raiz->info2.setChave(raiz->info1.getChave());
					raiz->info2.setValor(raiz->info1.getValor());

					raiz->info1.setChave(p->info1.getChave());
					raiz->info1.setValor(p->info1.getValor());

					raiz->ap3 = raiz->ap2;
					raiz->ap1 = p->ap1;
					raiz->ap2 = p->ap2;
					p->ap1->pai = raiz;
					p->ap2->pai = raiz;
					cresceu = false;

					delete p;
					return raiz;
				}
				else { // cresceu e eh tres no e eu sei que p eh o menor

					node23* maior = new node23;

					maior->info1.setChave(raiz->info2.getChave());
					maior->info1.setValor(raiz->info2.getValor());

					maior->doisno = true;
					maior->ap1 = raiz->ap2;
					maior->ap2 = raiz->ap3;
					maior->ap1->pai = maior;
					maior->ap2->pai = maior;

					raiz->doisno = true;
					raiz->ap1 = p;
					p->pai = raiz;
					raiz->ap2 = maior;
					maior->pai = raiz;
					raiz->ap3 = nullptr;

					cresceu = true;
					return raiz;
				}
			}
		}
		else {

			if (raiz->doisno || raiz->info2.getChave() > chave) {
				node23* p = put(raiz->ap2, chave, valor, cresceu);
				if (!cresceu) {
					raiz->ap2 = p;
					p->pai = raiz;
					return raiz;
				}
				else {
					if (raiz->doisno) {
						raiz->doisno = false;
						raiz->info2.setChave(p->info1.getChave());
						raiz->info2.setValor(p->info1.getValor());
					
						raiz->ap2 = p->ap1;
						raiz->ap3 = p->ap2;
						p->ap1->pai = raiz;
						p->ap2->pai = raiz;
						cresceu = false;
						delete p;
						return raiz;				
					}
					else {
						node23* maior = new node23;
						maior->info1.setChave(raiz->info2.getChave());
						maior->info1.setValor(raiz->info2.getValor());
						maior->doisno = true;
						maior->ap1 = p->ap2;
						maior->ap2 = raiz->ap3;
						maior->ap2->pai = maior;
						maior->ap1->pai = maior;

						raiz->doisno = true;
						raiz->ap2 = p->ap1;
						raiz->ap3 = nullptr;

						p->pai = raiz->pai;
						p->ap1 = raiz;
						raiz->pai = p;
						p->ap2 = maior;
						maior->pai = p;

						cresceu = true;
						return p;
					}
				}			
			}

			else if (!raiz->doisno && raiz->info2.getChave() < chave) {

				node23* p = put(raiz->ap3, chave, valor, cresceu);
				if (!cresceu) {
					raiz->ap3 = p;
					p->pai = raiz;
					return raiz;
				}
				else {
					node23* meio = new node23;

					meio->info1.setChave(raiz->info2.getChave());
					meio->info1.setValor(raiz->info2.getValor());

					meio->doisno = true;
					meio->ap1 = raiz;
					meio->pai = raiz->pai;
					raiz->pai = meio;

					meio->ap2 = p;
					p->pai = meio;

					raiz->doisno = true;
					raiz->ap3 = nullptr;

					cresceu = true;
					return meio;				
				}
			}

		}
	}
	return raiz;
}

node23* arvore23::apaga(node23* raiz, string chave) {

	if (raiz == nullptr)
		return raiz;

	node23* p;
	// parte da recursão, quando acha quem tem q deletar ele eh guardado em p
	if (!raiz->doisno) {
		if (raiz->info1.getChave() > chave) {
			p = apaga(raiz->ap1, chave);
			if (p->pai != nullptr)
				return p->pai;
			return p;
		}

		else if (raiz->info1.getChave() < chave && raiz->info2.getChave() > chave) {
			p = apaga(raiz->ap2, chave);
			if (p->pai != nullptr)
				return p->pai;
			return p;
		}

		else if (raiz->info2.getChave() < chave) {
			p = apaga(raiz->ap3, chave);
			if (p->pai != nullptr)
				return p->pai;
			return p;
		}

		else if (!raiz->ehFolha() && raiz->info1.getChave() == chave) {
			p = minimo(raiz->ap2);
			if (p->doisno){
				raiz->info1.setChave(p->info1.getChave());
				raiz->info1.setValor(p->info1.getValor());
			}
			else {
				raiz->info1.setChave(p->info1.getChave());
				raiz->info1.setValor(p->info1.getValor());
				p->info1.setChave(p->info2.getChave());
				p->info1.setValor(p->info2.getValor());
				p->doisno = true;
				return raiz;
			}
		}
		else if (raiz->ehFolha() && raiz->info1.getChave() == chave)
			p = raiz;

		else if (!raiz->ehFolha() && raiz->info2.getChave() == chave) {
			p = minimo(raiz->ap3);

			// o minimo ja esta na info1
			if (p->doisno) {
				raiz->info1.setChave(p->info1.getChave());
				raiz->info1.setValor(p->info1.getValor());
			}
			else {
				raiz->info2.setChave(p->info1.getChave());
				raiz->info2.setValor(p->info1.getValor());
				p->info1.setChave(p->info2.getChave());
				p->info1.setValor(p->info2.getValor());
				p->doisno = true;
				return raiz;				
			}
		}

		else if (raiz->ehFolha() && raiz->info2.getChave() == chave)
			p = raiz;
	}
	else {
		if (raiz->info1.getChave() > chave){
			p = apaga(raiz->ap1, chave);
			if (p->pai != nullptr)
				return p->pai;
			return p;
		}
		else if (raiz->info1.getChave() < chave) {
			p = apaga(raiz->ap2, chave);
			if (p->pai != nullptr)
				return p->pai;
			return p;
		}

		else if (raiz->info1.getChave() == chave && !raiz->ehFolha()) {
			p = minimo(raiz->ap2);
			if (p->doisno){
				raiz->info1.setChave(p->info1.getChave());
				raiz->info1.setValor(p->info1.getValor());
			}
			else {
				raiz->info1.setChave(p->info1.getChave());
				raiz->info1.setValor(p->info1.getValor());
				p->info1.setChave(p->info2.getChave());
				p->info1.setValor(p->info2.getValor());
				p->doisno = true;
				return raiz;
			}
		}	
		else if (raiz->ehFolha() && raiz->info1.getChave() == chave)
			p = raiz;
	}

	/* -------------------------------------------------------- */

	if (!p->doisno) { // se eh 3-no soh retira do no o respectivo elem
		if (p->info1.getChave() == chave){
			p->info1.setChave(p->info2.getChave());
			p->info1.setValor(p->info2.getValor());
			p->doisno = true;
		}
		else if (p->info2.getChave() == chave){
			p->doisno = true;
		}
		return raiz;
	}

	else { // 2 no
		node23* irmao;
		if (p->pai->ap1 == p) {

			if (p->pai->ap2->doisno == false) { // se o irmao eh 3-no
				irmao = p->pai->ap2;
				cout << (p->info1.getChave()) << endl;
				cout << (p == raiz) << endl;

				p->info1.setValor(p->pai->info1.getValor());
				p->info1.setChave(p->pai->info1.getChave());

				p->pai->info1.setChave(irmao->info1.getChave());
				p->pai->info1.setValor(irmao->info1.getValor());

				irmao->info1.setChave(irmao->info2.getChave());
				irmao->info1.setValor(irmao->info2.getValor());

				irmao->doisno = true;
				if (p == raiz)
					raiz = p->pai;
			}
			else { // se p == p->pai->ap2 

				if (!p->pai->doisno) { // se o pai eh 3 no retira do no e troca com o pai
					irmao = p->pai->ap2;
					irmao->info2.setChave(irmao->info1.getChave());
					irmao->info2.setValor(irmao->info1.getValor());

					irmao->info1.setChave(p->pai->info1.getChave());
					irmao->info1.setValor(p->pai->info1.getValor());

					p->pai->info1.setChave(p->pai->info2.getChave());
					p->pai->info1.setValor(p->pai->info2.getValor());

					p->pai->ap1 = irmao;
					irmao->pai = p->pai;
					p->pai->ap2 = p->pai->ap3;
					p->pai->ap3 = nullptr;
					p->pai->doisno = true;
					irmao->doisno = false;
					if (p == raiz)
						raiz = p->pai;
					delete p;
				}
			// se o pai eh 2 no empresta do irmao ate achar alguem pra tocar, ou ir ate a raiz
				else if (p->pai->doisno) { 
					node23* aux;

					irmao = p->pai->ap2;
					irmao->info2.setChave(irmao->info1.getChave());
					irmao->info2.setValor(irmao->info1.getValor());
					irmao->info1.setChave(p->pai->info1.getChave());
					irmao->info1.setValor(p->pai->info1.getValor());
					irmao->doisno = false;
					aux = p->pai;
					delete p;
					p = aux;

					while (p->pai != nullptr) {	

						if (!p->pai->doisno) {
							 if (p == p->pai->ap1) {
								p->pai->ap2->info2.setChave(p->pai->ap2->info1.getChave());
								p->pai->ap2->info2.setValor(p->pai->ap2->info1.getValor());

								p->pai->ap2->info1.setChave(p->pai->info1.getChave());
								p->pai->ap2->info1.setValor(p->pai->info1.getValor());

								p->pai->info1.setChave(p->pai->info2.getChave());
								p->pai->info1.setValor(p->pai->info2.getValor());

								p->pai->doisno = true;
								p->pai->ap2->doisno = false;

								p->pai->ap2->ap3 = p->pai->ap2->ap2;
								p->pai->ap2->ap2 = p->pai->ap2->ap1;
								p->pai->ap2->ap1 = irmao;

								irmao->pai = p->pai->ap2;
								p->pai->ap1 = p->pai->ap2;
								p->pai->ap2 = p->pai->ap3;
								p->pai->ap3 = nullptr;
							}

							else if (p == p->pai->ap2) {

								p->pai->ap1->info2.setChave(p->pai->info1.getChave());
								p->pai->ap1->info2.setValor(p->pai->info1.getValor());

								p->pai->info1.setChave(p->pai->info2.getChave());
								p->pai->info1.setValor(p->pai->info2.getValor());

								p->pai->doisno = true;
								p->pai->ap1->doisno = false;

								p->pai->ap1->ap3 = irmao;
								irmao->pai = p->pai->ap1;
								p->pai->ap2 = p->pai->ap3;
								p->pai->ap3 = nullptr;

							}

							else if (p == p->pai->ap3) {

								p->pai->ap2->info2.setChave(p->pai->info2.getChave());
								p->pai->ap2->info2.setValor(p->pai->info2.getValor());

								p->pai->ap2->ap3 = irmao;
								irmao->pai = p->pai->ap2;								

								p->pai->doisno = true;
								p->pai->ap2->doisno = false;

								p->pai->ap3 = nullptr;
							}
							aux = p->pai;
							delete p;
							return aux;
						}

						if (p->pai->ap1 == p){
							p->pai->ap1 = irmao;
							irmao = p->pai->ap2;
							p->pai->ap1->pai = irmao;
							irmao->ap3 = irmao->ap2;
							irmao->ap2 = irmao->ap1;
							irmao->ap1 = p->pai->ap1;
							irmao->info2.setChave(irmao->info1.getChave());
							irmao->info2.setValor(irmao->info1.getValor());

							irmao->info1.setChave(p->pai->info1.getChave());
							irmao->info1.setValor(p->pai->info1.getValor());

						}
						else if (p->pai->ap2 == p){
							p->pai->ap2 = irmao;
							irmao = p->pai->ap1;
							p->pai->ap2->pai = irmao;
							irmao->ap3 = p->pai->ap2;
							irmao->info2.setChave(p->pai->info1.getChave());
							irmao->info2.setValor(p->pai->info1.getValor());
						}

						irmao->doisno = false;

						aux = p->pai;

						delete p;

						p = aux;
					}
					raiz = irmao;
					delete p;
					raiz->pai = nullptr;
				}
			}
			

		}
		else if (p->pai->ap2 == p) { // analogo ao 1 if, mas com o ap do meio
			if (p->pai->ap1->doisno == false){

				irmao = p->pai->ap1;
				p->info1.setChave(p->pai->info1.getChave());
				p->info1.setValor(p->pai->info1.getValor());

				p->pai->info1.setChave(irmao->info2.getChave());
				p->pai->info1.setValor(irmao->info2.getValor());

				if (p == raiz)
					raiz = p->pai;
			}
			else if (!p->pai->doisno) {
				if (p->pai->ap3->doisno == false){

					irmao = p->pai->ap3;
					p->info1.setChave(p->pai->info1.getChave());
					p->info1.setValor(p->pai->info1.getValor());

					p->pai->info1.setChave(irmao->info1.getChave());
					p->pai->info1.setValor(irmao->info1.getValor());

					if (p == raiz)
						raiz = p->pai;
				}
				else if (p->pai->ap1->doisno == false){
					irmao = p->pai->ap1;
					irmao->info2.setChave(p->pai->info1.getChave());
					irmao->info2.setValor(p->pai->info1.getValor());

					p->pai->info1.setChave(p->pai->info2.getChave());
					p->pai->info1.setValor(p->pai->info2.getValor());
		

					p->pai->ap2 = p->pai->ap3;
					p->pai->ap3 = nullptr;
					p->pai->doisno = true;
					delete p;

				}
				else {
					irmao = p->pai->ap1;

					irmao->info2.setChave(p->pai->info1.getChave());
					irmao->info2.setValor(p->pai->info1.getValor());


					p->pai->info1.setChave(p->pai->info2.getChave());
					p->pai->info1.setValor(p->pai->info2.getValor());

					p->pai->doisno = true;
					irmao->doisno = false;
					if (p->ap2 != nullptr) {
						irmao->ap3 = p->ap2;
						p->ap2->pai = irmao;
					}
					else if (p->ap1 != nullptr){
						irmao->ap3 = p->ap1;
						p->ap1->pai = irmao;
					}

					p->pai->ap2 = p->pai->ap3;
					p->pai->ap3 = nullptr;
					if (p == raiz)
						raiz = p->pai;
					delete p;

				}
			}
			else if (p->pai->doisno) {

				node23* aux;

				irmao = p->pai->ap1;
				irmao->info2.setChave(p->pai->info1.getChave());
				irmao->info2.setValor(p->pai->info1.getValor());
				irmao->doisno = false;
				aux = p->pai;
				delete p;
				p = nullptr;
				p = aux;

				while (p->pai != nullptr) {	

					if (!p->pai->doisno) {

						if (p == p->pai->ap1) {
							p->pai->ap2->info2.setChave(p->pai->ap2->info1.getChave());
							p->pai->ap2->info2.setValor(p->pai->ap2->info1.getValor());

							p->pai->ap2->info1.setChave(p->pai->info1.getChave());
							p->pai->ap2->info1.setValor(p->pai->info1.getValor());

							p->pai->info1.setChave(p->pai->info2.getChave());
							p->pai->info1.setValor(p->pai->info2.getValor());

							p->pai->doisno = true;
							p->pai->ap2->doisno = false;

							p->pai->ap2->ap2 = p->pai->ap2->ap1;
							p->pai->ap2->ap3 = p->pai->ap2->ap2;
							p->pai->ap2->ap1 = irmao;
							irmao->pai = p->pai->ap2;
							p->pai->ap1 = p->pai->ap2;
							p->pai->ap2 = p->pai->ap3;
							p->pai->ap3 = nullptr;

						}
						else if (p == p->pai->ap2) {

							p->pai->ap1->info2.setChave(p->pai->info1.getChave());
							p->pai->ap1->info2.setValor(p->pai->info1.getValor());

							p->pai->info1.setChave(p->pai->info2.getChave());
							p->pai->info1.setValor(p->pai->info2.getValor());

							p->pai->ap1->ap3 = irmao;
							irmao->pai = p->pai->ap1;
							cout << irmao->info2.getChave() << endl;

							p->pai->doisno = true;
							p->pai->ap1->doisno = false;
							p->pai->ap2 = p->pai->ap3;
							p->pai->ap3 = nullptr;

						}
						else if (p == p->pai->ap3) {

							p->pai->ap2->info2.setChave(p->pai->info2.getChave());
							p->pai->ap2->info2.setValor(p->pai->info2.getValor());

							p->pai->ap2->ap3 = irmao;
							irmao->pai = p->pai->ap2;								

							p->pai->doisno = true;
							p->pai->ap2->doisno = false;

							p->pai->ap3 = nullptr;
						}
						aux = p->pai;
						delete p;
						return aux;
					}

					if (p->pai->ap1 == p){

						p->pai->ap1 = irmao; // irmao do loop anterior (recem 3no)
						irmao = p->pai->ap2;
						p->pai->ap1->pai = irmao;
						irmao->ap3 = irmao->ap2;
						irmao->ap2 = irmao->ap1;
						irmao->ap1 = p->pai->ap1;
						irmao->info2.setChave(irmao->info1.getChave());
						irmao->info2.setValor(irmao->info1.getValor());

						irmao->info1.setChave(p->pai->info1.getChave());
						irmao->info1.setValor(p->pai->info1.getValor());
					}
					else if (p->pai->ap2 == p){

						p->pai->ap2 = irmao; // irmao do loop anterior (recem 3no)
						irmao = p->pai->ap1;
						p->pai->ap2->pai = irmao;
						irmao->ap3 = p->pai->ap2;
						irmao->info2.setChave(p->pai->info1.getChave());
						irmao->info2.setValor(p->pai->info1.getValor());
					}

					irmao->doisno = false;

					aux = p->pai;

					delete p;

					p = aux;
				}

				raiz = irmao;
				delete p;
				raiz->pai = nullptr;
			}

		}
		else if (p->pai->ap3 == p) { // se eh 2no nao tem ap3 entao nao cai no caso do while
			if (p->pai->ap2->doisno == false) {

				irmao = p->pai->ap2;
				p->info1.setChave(p->pai->info2.getChave());
				p->info1.setValor(p->pai->info2.getValor());

				p->pai->info2.setChave(irmao->info2.getChave());
				p->pai->info2.setValor(irmao->info2.getValor());	
				if (p == raiz)
					raiz = p->pai;

			}
			else if(!p->pai->doisno) {

				irmao = p->pai->ap2;
				irmao->info2.setChave(p->pai->info2.getChave());
				irmao->info2.setValor(p->pai->info2.getValor());

				p->pai->doisno = true;
				p->pai->ap3 = nullptr;

				delete p;
			}
		}
	}

	return raiz;
}

node23* arvore23::busca(node23* raiz, string chave) {

	if (raiz == nullptr)
		return nullptr;

	cout << raiz->info1.getChave() << endl;
	if (raiz->doisno) {
		if (raiz->info1.getChave() == chave)
			return raiz;
		else if (raiz->info1.getChave() > chave)
			return busca(raiz->ap1, chave);
		else
			return busca(raiz->ap2, chave);
	}
	else {
		if (raiz->info1.getChave() == chave || raiz->info2.getChave() == chave)
			return raiz;
		else if (raiz->info1.getChave() > chave)
			return busca(raiz->ap1, chave);
		else if (raiz->info1.getChave() < chave && raiz->info2.getChave() > chave)
			return busca(raiz->ap2, chave);
		else 
			return busca(raiz->ap3, chave);
	}

}

int arvore23::tamanho(node23* raiz) {
	if (raiz == nullptr)
		return 0;
	if (raiz->doisno){
		return tamanho(raiz->ap1) + 1 + tamanho(raiz->ap2);
	}
	else {
		return tamanho(raiz->ap1) + tamanho(raiz->ap2) + tamanho(raiz->ap3) + 2;
	}
}

node23* arvore23::minimo(node23* raiz) {

	if (raiz == nullptr || raiz->ap1 == nullptr)
		return raiz;

	return minimo(raiz->ap1);
}

arvore23::arvore23(string nome_arquivo) {

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

arvore23::~arvore23() {
	deleteTree(raiz);
}

void arvore23::insere(string chave, int valor) {
	bool cresceu = 0;
	raiz = put(raiz, chave, valor, cresceu);
}

int arvore23::rank(string chave) {

	if(raiz == nullptr)
		return 0;
	node23* aux = raiz;
	int r = 0;
	while (aux != nullptr) {
		if (aux->info1.getChave() == chave){
			return r + tamanho(aux->ap1);
		}

		if (aux->info1.getChave() > chave){
			aux = aux->ap1;
		}

		else if (aux->doisno && aux->info1.getChave() < chave){
			r += tamanho(aux->ap1) + 1;
			aux = aux->ap2;
		}
		else if (!aux->doisno) {
			if (aux->info2.getChave() == chave){
				return r + tamanho(aux->ap1) + tamanho(aux->ap2) + 1;
			}
			else if (aux->info2.getChave() > chave){
				r += tamanho(aux->ap1) + 1;
				aux = aux->ap2;
			}
			else if (aux->info2.getChave() < chave) {
				r += tamanho(aux->ap1) + tamanho(aux->ap2) + 2;
				aux = aux->ap3;
			}
		}
	}
	return r;
}

int arvore23::devolve(string chave) {
	node23* ret = busca(raiz, chave);
	if (ret == nullptr)
		return 0;	

	if (chave == ret->info1.getChave())
		return ret->info1.getValor();
	return ret->info2.getValor();
}

void arvore23::remove(string chave) {
	raiz = apaga(raiz, chave);
}

string arvore23::seleciona(int k) {
	if (raiz == nullptr)
		return "";
	int r, r2;
	node23* aux = raiz;
	while (aux != nullptr) {
		r = rank(aux->info1.getChave());
		if (r == k)
			return aux->info1.getChave();

		if (r > k)
			aux = aux->ap1;

		else if (aux->doisno && r < k)
			aux = aux->ap2;
		
		else if (!aux->doisno) {
			r2 = rank(aux->info2.getChave());
			if (r2 == k)
				return aux->info2.getChave();
			
			else if (r2 > k)
				aux = aux->ap2;
			
			else if (r2 < k) 
				aux = aux->ap3;
			
		}
	}
		return "";
}
