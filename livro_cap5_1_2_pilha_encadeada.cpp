// Pilha encadeada.

#include<stdio.h>  // printf();
#include<conio.h>  // getch();
#include<stdlib.h> // malloc();

#define max 5

struct tpilha {
    int dados;
    struct tpilha *proximo;
};

// Empilhar.
void push(struct tpilha **topo, int valor, int *status) {
    struct tpilha *p;
    p = (struct tpilha *) malloc(sizeof(struct tpilha));
    if (p == NULL)
        *status = 0;
    else {
        p->dados = valor;
        p->proximo = *topo;
        *topo = p;
        *status = 1;
    }
}

// Desempilhar.
int pop(struct tpilha **topo, int *status) {
    int valor;
    struct tpilha *p;
    if (*topo == NULL)
        *status = 0;
    else {
        valor = (*topo)->dados;
        p = *topo;
        *topo = (*topo)->proximo;
        free(p);
        *status = 1;
    }
    return valor;
}

void cria_pilha(struct tpilha **topo) {
	*topo = NULL;
}

void mostra_pilha(struct tpilha *topo) {
	struct tpilha *aux;
	aux = topo;
	printf("\n");
	printf("Pilha ===> ");
	while(aux != NULL) {
		printf("%i - ", aux->dados, "-");
		aux = aux->proximo;
	}
}

void libera_pilha(struct tpilha **topo) {
    struct tpilha *aux;
    aux = *topo;
    while(aux != NULL) {
        *topo = (*topo)->proximo;
        free(aux);
        aux = *topo;
    }
}

int main() {
    struct tpilha *topo;
	int num, ok, x;

	// Chama procedimento para criar a pilha.
	cria_pilha(&topo);

	// Lê valores do usuário e armazena na pilha.
	printf("Inserindo valores na pilha ...\n");
	for(x = 1; x <= max; x++) {
		printf("Digite um valor qualquer: ");
		scanf("%i", &num);
		fflush(stdin);
		push(&topo, num, &ok);
		if(ok == 0)
			printf("Problema na alocacao de memoria !!!\n");
	}

	// Mostra valores armazenados na pilha.
	mostra_pilha(topo);
    getch();
	
	// Retira da pilha e escreve na tela.
	printf("\nValor %i - o primeiro da pilha foi removido !!!\n", pop(&topo, &ok));
	mostra_pilha(topo);
	getch();

	// Lé novo valor para inserir na pilha.
	printf("\nDigite um valor qualquer: ");
	scanf("%i", &num);
	fflush(stdin);
	
	// Insere novo elemento na pilha.
	push(&topo, num, &ok);
	if(ok == 0)
		printf("Problema na alocacao de memoria !!!\n");
	else
		printf("\nValor %i inserido na pilha !\n", num);
	mostra_pilha(topo);
	libera_pilha(&topo);
	getch();
}
