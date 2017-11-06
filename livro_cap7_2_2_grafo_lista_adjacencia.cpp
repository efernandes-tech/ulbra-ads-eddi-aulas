// Grafos por Lista de Adjacência.

#include<stdio.h>  // printf();
#include<conio.h>  // getch();
#include<stdlib.h> // malloc();

struct adjacente {
    struct adjacente *prox;
    int a;
}; // Lista de adjacentes.

struct vertice {
    struct vertice *prox_v;
    int v;
    struct adjacente *prox_a;
}; // Lista de vértices.

struct vertice *grafo;

// Aloca um nodo do tipo vértice.
struct vertice * aloca_vertice(int v) {
    struct vertice * novo;
    novo = (struct vertice *) malloc(sizeof(struct vertice));
    novo->v = v; // Atribui o vértice origem para v.
    novo->prox_v = NULL;
    novo->prox_a = NULL;
    return novo;
}

// Aloca um nodo do tipo adjacente.
struct adjacente * aloca_adjacente(int a) {
    struct adjacente * novo;
    novo = (struct adjacente *) malloc(sizeof(struct adjacente));
    novo->a = a; // Atribui o vértice adjacente para a.
    novo->prox = NULL;
    return novo;
}

void conecta(struct vertice **grafo, int v1, int v2);

void desconecta(struct vertice *grafo, int v1, int v2);
