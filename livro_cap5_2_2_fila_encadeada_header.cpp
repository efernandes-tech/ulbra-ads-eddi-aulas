// Filas encadeadas com header.

#include<stdio.h>  // printf();
#include<conio.h>  // getch();
#include<stdlib.h> // malloc();

#define max 5

struct tfila {
    int dados;
    struct tfila *proximo;
};

struct header {
    struct tfila *comeco;
    int qtde;
    struct tfila *termino;
};

// Criando e iniciando a fila encadeada.
struct header * cria_fila(int *status) {
  	struct header *f = NULL;
	f = (struct header *) malloc(sizeof(struct header));
	if (f == NULL)
	    status = 0;
	else {
        f->comeco = NULL;
        f->qtde = 0;
        f->termino = NULL;
        *status = 1;
    }
    return f;
}

// Inserir na fila encadeada.
void enfileira(struct header *f, int valor, int *status) {
    struct tfila *aux, *p;
    p = (struct tfila *) malloc(sizeof(struct tfila));
    if (p == NULL)
        *status = 0;
    else {
        p->dados = valor;
        p->proximo = NULL;
        aux = f->termino;
        f->termino = p;
        if (f->comeco == NULL)
            f->comeco = p;
        else
            aux->proximo = p;
        f->qtde++;
        *status = 1;
    }
}

// Retirar da fila encadeada.
int desenfileira(struct header *f, int *status) {
    int valor = 0;
    struct tfila *aux;
    if (f->comeco == NULL)
        *status = 0;
    else {
        aux = f->comeco;
        valor = aux->dados;
        f->comeco = aux->proximo;
        if (aux == f->termino)
            f->termino = NULL;
        free(aux);
        f->qtde--;
        *status = 1;
    }
    return valor;
}

void mostra_fila(struct header *fila) {
	struct tfila *aux;
	aux = fila->comeco;
	printf("\nFila ===> ");
	while(aux != NULL) {
		printf("%i - ", aux->dados);
		aux = aux->proximo;
	}
	printf("\n");
}

void libera_fila(struct header *fila) {
    struct tfila *aux;
    aux = fila->comeco;
    while(aux != NULL) {
        fila->comeco = (fila->comeco)->proximo;
        free(aux);
        aux = fila->comeco;
    }
    fila->termino = NULL;
}

int main() {
    struct header *F;
	int ok, num, x;
	
	// Chama procedimento para criar a fila.
	F = cria_fila(&ok);

	// Lê valores do usuário e armazena na lista.
	printf("Inserindo valores na fila ...\n");
	for(x = 1; x <= max; x++) {
		printf("Digite um valor qualquer: ");
		scanf("%i", &num);
		fflush(stdin);
		enfileira(F, num, &ok);
		if(ok == 0)
			printf("Problema na alocacao de memoria !!!\n");
	}
	
	// Mostra valores armazenados na fila.
	mostra_fila(F);

	// Retira o primeiro da fila e escreve na tela.
	printf("Valor %i - o primeiro foi removido da fila !!!\n", desenfileira(F, &ok));
	mostra_fila(F);
	getch();

	// Lê um novo valor para inserir na fila.
	printf("Digite um valor qualquer: ");
	scanf("%i", &num);
	fflush(stdin);
	
	// Insere novo elemento na fila.
	enfileira(F, num, &ok);
	if(ok == 0)
		printf("Problema na alocacao de memoria !!!\n");
	mostra_fila(F);
	getch();
	
	// Retira da fila e o escreve na tela.
	printf("Valor %i - foi removido da fila !!!\n", desenfileira(F, &ok));
	
	mostra_fila(F);
	libera_fila(F);
	
	getch();
}
