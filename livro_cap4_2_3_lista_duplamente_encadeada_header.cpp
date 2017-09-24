/*
Exemplo: Escreva um programa que leia dez valores inteiros e armazene em uma lista
duplamente encadeada com header (insere no início da lista). Após, remova o
primeiro elemento da lista e leia um novo valor, que deve ser inserido antes do
nodo que contém o maior elemento da lista (escreva uma função para descobrir
o maior elemento da lista). No final, mostre todos os valores armazenados na
lista e então libere a lista.
*/

#include<stdio.h>   // printf();
#include<conio.h>   // getch();
#include<stdlib.h>  // malloc();

#define max 5

struct aponta_nodo {
	struct aponta_nodo *ant;
	int dados;
	struct aponta_nodo *prox;
};

struct aponta_header {
	struct aponta_nodo *inicio;
	int qtde;
	struct aponta_nodo *fim;
};

// Procedimento para criar o header.
void cria_header(struct aponta_header **lista) {
	*lista = (struct aponta_header *) malloc(sizeof(struct aponta_header));
	(*lista)->inicio = NULL;
	(*lista)->qtde = NULL;
	(*lista)->fim = NULL;
}

// Inserção de um nodo antes do primeiro nodo da lista (com header).
void insere_esquerda(struct aponta_header *lista, int valor, int *status) {
	struct aponta_nodo *p;
	*status = 0;
	if(lista != NULL) {
		p = (struct aponta_nodo *) malloc(sizeof(struct aponta_nodo));
		if(p != NULL) {
			p->dados = valor;
			p->ant = NULL;
			p->prox = lista->inicio;
			if(lista->inicio == NULL)
				lista->fim = p;
			else
				(lista->inicio)->ant = p;
			lista->inicio = p;
			lista->qtde = lista->qtde + 1;
			*status = 1;
		}
	}
}

void insere_direita(struct aponta_header *lista, int valor, int *status) {
	struct aponta_nodo *p;
	*status = 0;
	if(lista != NULL) {
		p = (struct aponta_nodo *) malloc(sizeof(struct aponta_nodo));
		if(p != NULL) {
			p->dados = valor;
			p->prox = NULL;
			p->ant = lista->fim;
			if(lista->inicio == NULL)
				lista->inicio = p;
			else
				(lista->fim)->prox = p;
			lista->fim = p;
			lista->qtde = lista->qtde + 1;
			*status = 1;
		}
	}
}

// Remove o último nodo da lista.
int remove_direita(struct aponta_header *lista, int *status) {
	struct aponta_nodo *aux;
	int valor;
	*status = 0;
	if((lista != NULL) && (lista->qtde > 0)) {
		aux = lista->fim;
		lista->fim = aux->ant;
		if(lista->fim == NULL)
			lista->inicio = NULL;
		else
			(lista->fim)->prox = NULL;
		valor = aux->dados;
		free(aux);
		lista->qtde = lista->qtde - 1;
		*status = 1;
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
	int num, ok, x;
	
	// Chama procedimento para criar a lista.
	cria_header(&L);
	
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
	getch();
	
	// Retira o último nodo da lista e escreve na tela.
	printf("Valor %i - ultimo nodo - foi removido da lista !!!\n", remove_direita(L, &ok));
	mostra_lista(L);
	getch();
	
	// Lé novo valor para inserir na lista.
	printf("Digite um valor qualquer: ");
	scanf("%i", &num);
	fflush(stdin);
	
	// Insere novo elemento na lista.
	insere_direita(L, num, &ok);
	if(ok == 0)
		printf("Problema na alocacao de memoria !!!\n");
	else
		printf("Valor %i inserido do final da lista !\n", num);
	mostra_lista(L);
	libera_lista(L);
	getch();
}
