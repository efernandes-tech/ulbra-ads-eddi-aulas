/*
Exemplo: Escreva um programa que leia dez valores inteiros e armazene em uma lista
simplesmente encadeada. Depois remova o primeiro elemento da lista e leia um
novo valor, que deve ser inserido antes do nodo que contém o maior elemento
da lista (escreva uma função para descobrir o maior elemento da lista). No final,
mostre todos os valores armazenados na lista e então a libere.
*/

#include<stdio.h>   // printf();
#include<conio.h>   // getch();
#include<stdlib.h>  // malloc();

#define max 10

struct nodo {
	int dados;
	struct nodo *proximo;
};

void cria_lista(struct nodo **inicio, struct nodo **fim) {
	*inicio = NULL;
	*fim = NULL;
}

void insere_esquerda(struct nodo **inicio, struct nodo **fim, int valor, int *status) {
	// Utilizaremos a variável p representando um ponteiro.
	struct nodo *p;
	p = (struct nodo *) malloc(sizeof(struct nodo));
	if(p == NULL) {
		// Se não foi possível alocar espaço em memória.
		*status = 0;
	} else {
		p->dados = valor;
		p->proximo = *inicio;
		if (*inicio == NULL)
			*fim = p;
		*inicio = p;
		*status = 1;
	}
}

void insere_antes_de_k(struct nodo **inicio, struct nodo *k, int valor, int *status) {
	struct nodo *ant, *aux, *p;
	*status = 0;
	if(*inicio) {
		// Se a lista não está vazia.
		aux = *inicio;
		while((aux != NULL) && (aux != k)) {
			// Percorre a lista até achar o nodo k ou até chegar ao fim da lista.
			ant = aux;
			aux = aux->proximo;
		}
		if(aux) {
			p = (struct nodo *) malloc(sizeof(struct nodo));
			if(p != NULL) {
				p->dados = valor;
				if(k == *inicio) {
					p->proximo = *inicio;
					*inicio = p;
				} else {
					ant->proximo = p;
					p->proximo = k;
				}
				*status = 1;
			}
		}
	}
}

struct nodo * maior(struct nodo *inicio) {
	struct nodo *p, *aux;
	int m;
	if(inicio != NULL) {
		aux = inicio;
		m = aux->dados;
		p = aux;
		aux = aux->proximo;
		while(aux != NULL) {
			if(aux->dados > m) {
				m = aux->dados;
				p = aux;
			}
			aux = aux->proximo;
		}
		return p;
	} else return NULL;
}

void mostra_lista(struct nodo *inicio) {
	struct nodo *aux;
	aux = inicio;
	printf("\n");
	printf("Lista ===> ");
	while(aux != NULL) {
		printf("%i - ", aux->dados, "-");
		aux = aux->proximo;
	}
}

void libera_lista(struct nodo **inicio, struct nodo **fim) {
}

int remove_esquerda(struct nodo **inicio, struct nodo **fim, int *status) {
}

int main() {
	struct nodo *ptri, *ptrf;
	int x, num, ok;
	
	// Chama procedimento para criar a lista.
	cria_lista(&ptri, &ptrf);
	
	// Lê valores do usuário e armazena na lista.
	for(x = 1; x <= max; x++) {
		printf("Digite um valor qualquer: ");
		scanf("%i", &num); fflush(stdin);
		insere_esquerda(&ptri, &ptrf, num, &ok);
		if (ok == 0) printf("Problema na alocação de memória !!!\n");
	}
	
	// Retira o primeiro nodo da lista e escreve na tela.
	printf("Elemento %i foi removido!!!\n", remove_esquerda(&ptri, &ptrf, &ok));
	
	// Lê novo valor para inserir na lista.
	printf("Digite um valor qualquer: ");
	scanf("%i", &num); fflush(stdin);
	
	// Insere novo elemento na lista.
	insere_antes_de_k(&ptri, maior(ptri), num, &ok);
	if (ok == 0) printf("Problema na alocação de memória !!!\n");
	getch();
	mostra_lista(ptri);
	scanf("%i", &num);
	libera_lista(&ptri, &ptrf);
	return 0;
}
