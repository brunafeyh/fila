#include <stdio.h>
#include <stdlib.h>

struct no {
    int num;
    struct no *prox;
};

struct fila {
    int n;
    struct no *primeiro;
    struct no *ultimo;
};

void limpar_fila(struct fila *f) {
    if (f->primeiro != NULL) {
        struct no *aux = f->primeiro->prox;
        free(f->primeiro);
        f->primeiro = aux;
        limpar_fila(f);
    }

    f->n = 0;
    f->primeiro = NULL;
    f->ultimo = NULL;
}

struct fila *iniciar_fila() {
    struct fila *fila = (struct fila *)malloc(sizeof(struct fila));
    fila->n = 0;
    fila->primeiro = NULL;
    fila->ultimo = NULL;
    return fila;
}

int vazia(struct fila *f) {
    return (f->primeiro == NULL && f->ultimo == NULL);
}

void enqueue(struct fila *f, int num) {
    struct no *aux = (struct no *)malloc(sizeof(struct no));

    aux->num = num;
    aux->prox = NULL;

    if (vazia(f)) {
        f->primeiro = aux;
    } else {
        f->ultimo->prox = aux;
    }

    f->n = f->n + 1;
    f->ultimo = aux;
}

void dequeue(struct fila *f) {
    if (!vazia(f)) {
        struct no *temp = f->primeiro;
        if (f->primeiro == f->ultimo) {
            f->ultimo = NULL;
        }
        f->primeiro = f->primeiro->prox;
        f->n = f->n - 1;
        free(temp);
    }
}

void imprimir(struct fila *f) {
    if (!vazia(f)) {
        struct no *atual = f->primeiro;
        printf("Elementos da fila: ");
        while (atual != NULL) {
            printf(" %d", atual->num);
            atual = atual->prox;
        }
    }
    printf("\n");
}

void inverte(struct fila *f) {
    if (vazia(f)) {
        printf("A fila está vazia\n");
        return;
    }

    struct no *current = f->primeiro;
    struct no *temp;

    struct no *pilha = NULL;

    while (current != NULL) {
        temp = current->prox;
        current->prox = pilha;
        pilha = current;
        current = temp;
    }

    f->ultimo = f->primeiro;
    f->primeiro = pilha;
}

int main() {
    struct fila *fila1 = iniciar_fila();

    printf("Número de elementos da fila 1 = %d\n\n", fila1->n);
    printf("A fila 1 é vazia? RESPOSTA = %d\n\n", vazia(fila1));

    enqueue(fila1, 10);
    enqueue(fila1, 20);
    enqueue(fila1, 30);
    enqueue(fila1, 40);
    enqueue(fila1, 50);
    enqueue(fila1, 60);

    imprimir(fila1);

    inverte(fila1);

    imprimir(fila1);

    printf("\nNúmero de elementos da fila 1 = %d\n\n", fila1->n);

    dequeue(fila1);
    dequeue(fila1);
    dequeue(fila1);

    printf("Número de elementos da fila 1 = %d\n\n", fila1->n);

    imprimir(fila1);

    printf("A fila 1 é vazia? RESPOSTA = %d\n\n", vazia(fila1));

    limpar_fila(fila1);

    printf("A fila 1 é vazia? RESPOSTA = %d\n\n", vazia(fila1));
    return 0;
}
