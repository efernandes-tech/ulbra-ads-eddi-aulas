/*
Exemplo: Escreva um programa que leia dez valores inteiros e armazene em uma lista
simplesmente encadeada com header (insere no início da lista). Depois, remova
o primeiro elemento da lista e leia um novo valor, que deve ser inserido antes do
nodo que contém o maior elemento da lista (escreva uma função para descobrir
o maior elemento da lista). No final, mostre todos os valores armazenados na
lista e então a libere.
*/

#include<stdio.h>   // printf();
#include<conio.h>   // getch();
#include<stdlib.h>  // malloc();

#define max 10

struct aponta_nodo {
	int dados;
	struct aponta_nodo *prox;
};

struct aponta_header {
	struct aponta_nodo *inicio;
	int qtde;
	struct aponta_nodo *fim;
};

// Função que recebe uma lista encadeada e retorna o nodo que tem o maior elemento da lista.
struct aponta_nodo * maior(struct aponta_header *nlista) {
	struct aponta_nodo *p = NULL, *aux;
	if(nlista->qtde == 0)
		return p;
	else {
		aux = nlista->inicio;
		p = aux;
		aux = aux->prox;
		while(aux != NULL) {
			if(aux->dados > p->dados)
				p = aux;
			aux = aux->prox;
		}
	}
}

// Procedimento para criar uma lista simplesmente encadeada com header.
void cria_lista(struct aponta_header **nlista, int *status) {
	struct aponta_header *lista = NULL;
	lista = (struct aponta_header *) malloc(sizeof(struct aponta_header));
	if(lista == NULL)
		*status = 0;
	else {
		lista->inicio = NULL;
		lista->qtde = 0;
		lista->fim = NULL;
		*status = 1;
	}
	// Para retornar o endereço reservado.
	*nlista = lista;
}

// Inserção de um nodo antes do primeiro nodo na lista.
void insere_esquerda(struct aponta_header *nlista, int valor, int *status) {
	struct aponta_nodo *p;
	p = (struct aponta_nodo *) malloc(sizeof(struct aponta_nodo));
	// Se não foi possivel alocar espaço em memória.
	if(p == NULL)
		*status = 0;
	else {
		p->dados = valor;
		p->prox = nlista->inicio;
		nlista->inicio = p;
		if(nlista->qtde == 0)
			nlista->fim = p;
		(nlista->qtde)++;
		*status = 1;
	}
}

// Inserção de nodo antes do nodo endereçado por k.
void insere_antes_de_k(struct aponta_header *nlista, struct aponta_nodo *k, int valor, int *status) {
	struct aponta_nodo *aux, *ant, *p;
	p = (struct aponta_nodo *) malloc(sizeof(struct aponta_nodo));
	// Se não foi possível alocar espaço em memória.
	if(p == NULL)
		*status = 0;
	else {
		p->dados = valor;
		aux = nlista->inicio;
		while(aux != NULL && aux != k) {
			// Percorre a lista até achar o nodo anterior a k.
			ant = aux;
			aux = aux->prox;
		}
		if(aux != NULL) {
			if(k == nlista->inicio) {
				p->prox = k;
				nlista->inicio = p;
			} else {
				ant->prox = p;
				p->prox = k;
			}
			(nlista->qtde)++;
			*status = 1;
		} else {
			free(p);
			status = 0;
		}
	}
}

// Remoção do primeiro nodo.
int remove_esquerda(struct aponta_header *nlista, int *status) {
	struct aponta_nodo *p;
	int valor = 0;
	if(nlista->qtde == 0) {
		// Se a lista estiver vazia.
		*status = 0;
	} else {
		p = nlista->inicio;
		valor = p->dados;
		nlista->inicio = p->prox;
		if(nlista->qtde == 1)
			nlista->fim = NULL;
		free(p);
		nlista->qtde--;
		*status = 1;
	}
	return valor;
}

// Remoção do último nodo.
int remove_direita(struct aponta_header *nlista, int *status) {
	struct aponta_nodo *aux, *p;
	int valor = 0;
	if(nlista->qtde == 0) {
		// Se a lista estiver vazia.
		*status = 0;
	} else {
		if(nlista->qtde == 1) {
			// Lista de um nodo só?
			p = nlista->inicio;
			valor = p->dados;
			free(p);
			nlista->inicio = NULL;
			nlista->fim = NULL;
		} else {
			p = nlista->inicio; // Descobre o último nodo.
			aux = nlista->inicio; // Nodo anterior a "p".
			while(p->prox != NULL) { // Percorre a lista até achar o último nodo.
				// Percorre a lista até achar o último nodo.
				aux = p;
				p = p->prox;
			}
			valor = p->dados;
			aux->prox = NULL;
			nlista->fim = aux;
			free(p);
		}
		nlista->qtde--;
		*status = 1;
	}
	return valor;
}

// Remoção antes do nodo endereçado por k.
int remove_antes_k(struct aponta_header *nlista, struct aponta_nodo *k, int *status) {
	struct aponta_nodo *aux, *p;
	int valor = 0;
	if(nlista->qtde == 0) {
		// Se a lista estiver vazia.
		*status = 0;
	} else if(nlista->inicio == k) {
		*status = 0;
	} else {
		p = nlista->inicio; // Nodo anterior a k.
		aux = nlista->inicio; // Nodo anterior a p.
		while(p->prox != k && p != NULL) {
			// Percorre a lista até achar o nodo k.
			aux = p;
			p = p->prox;
		}
		if(p != NULL) {
			valor = p->dados;
			if(nlista->inicio == p)
				nlista->inicio = k;
			else
				aux->prox = k;
			free(p);
			nlista->qtde--;
			*status = 1;
		} else
			*status = 0;
	}
	return valor;
}

// Mostra valores da lista.
void mostra_lista(struct aponta_header *lista) {
	struct aponta_nodo *aux;
	aux = lista->inicio;
	printf("\nLista ===> ");
	while(aux != NULL) {
		printf("%i - ", aux->dados);
		aux = aux->prox;
	}
	printf("\n");
}

void libera_lista(struct aponta_header *lista) {
    struct aponta_nodo *aux;
    aux = lista->inicio;
    while(aux != NULL) {
        lista->inicio = (lista->inicio)->prox;
        free(aux);
        aux = lista->inicio;
    }
    lista->fim = NULL;
}

int main() {
	struct aponta_header *L;
	int ok, num, x;
	
	// Chama procedimento para criar a lista.
	cria_lista(&L, &ok);
	
	// Lê valores do usuário e armazena na lista.
	printf("Inserindo valores no inicio da lista ...\n");
	for(x = 1; x <= max; x++) {
		printf("Digite um valor qualquer: ");
		scanf("%i", &num);
		fflush(stdin);
		insere_esquerda(L, num, &ok);
		if(ok == 0)
			printf("Problema na alocacao de memoria !!!\n");
	}
	
	// Mostra valores armazenados na lista.
	mostra_lista(L);
	//readln;
	
	// Retira o primeiro nodo da lista e escreve na tela.
	printf("Valor %i - primeiro nodo - foi removido da lista !!!\n", remove_esquerda(L, &ok));
	mostra_lista(L);
	getch();
	
	// Lê novo valor para inserir na lista - valor será armazenado antes do nodo que tem o maior valor.
	printf("Digite um valor qualquer: ");
	scanf("%i", &num);
	fflush(stdin);
	
	// Insere novo elemento na lista.
	insere_antes_de_k(L, maior(L), num, &ok);
	if(ok == 0)
		printf("Problema na alocacao de memoria !!!\n");
	mostra_lista(L);
	getch();
	
	// Retira o último nodo da lista e o escreve na tela.
	printf("Valor %i - ultimo nodo - foi removido da lista !!!\n", remove_direita(L, &ok));
	
	mostra_lista(L);
	libera_lista(L);
	
	getch();
}
