#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// struct
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* prox;
} No;

// Variáveis
Item vet[MAX];
int tam = 0;

No* lista = NULL;

int compSeq = 0, compBin = 0;

// Vetor
void inserirVetor() {
    printf("Nome: "); scanf("%s", vet[tam].nome);
    printf("Tipo: "); scanf("%s", vet[tam].tipo);
    printf("Qtd: "); scanf("%d", &vet[tam].quantidade);
    tam++;
}

void listarVetor() {
    for(int i = 0; i < tam; i++)
        printf("%s %s %d\n", vet[i].nome, vet[i].tipo, vet[i].quantidade);
}

void removerVetor() {
    char nome[30];
    printf("Nome: "); scanf("%s", nome);

    for(int i = 0; i < tam; i++) {
        if(strcmp(vet[i].nome, nome) == 0) {
            for(int j = i; j < tam - 1; j++)
                vet[j] = vet[j + 1];
            tam--;
            return;
        }
    }
}

int buscaSeqVetor(char nome[]) {
    compSeq = 0;
    for(int i = 0; i < tam; i++) {
        compSeq++;
        if(strcmp(vet[i].nome, nome) == 0)
            return i;
    }
    return -1;
}

void ordenar() {
    for(int i = 0; i < tam - 1; i++)
        for(int j = 0; j < tam - 1 - i; j++)
            if(strcmp(vet[j].nome, vet[j+1].nome) > 0) {
                Item t = vet[j];
                vet[j] = vet[j+1];
                vet[j+1] = t;
            }
}

int buscarBin(char nome[]) {
    int ini = 0, fim = tam - 1;
    compBin = 0;

    while(ini <= fim) {
        int m = (ini + fim) / 2;
        compBin++;

        int c = strcmp(vet[m].nome, nome);
        if(c == 0) return m;
        if(c < 0) ini = m + 1;
        else fim = m - 1;
    }
    return -1;
}

// Lista
void inserirLista() {
    No* n = malloc(sizeof(No));

    printf("Nome: "); scanf("%s", n->dados.nome);
    printf("Tipo: "); scanf("%s", n->dados.tipo);
    printf("Qtd: "); scanf("%d", &n->dados.quantidade);

    n->prox = lista;
    lista = n;
}

void listarLista() {
    for(No* p = lista; p; p = p->prox)
        printf("%s %s %d\n", p->dados.nome, p->dados.tipo, p->dados.quantidade);
}

void removerLista() {
    char nome[30];
    printf("Nome: "); scanf("%s", nome);

    No *p = lista, *ant = NULL;

    while(p) {
        if(strcmp(p->dados.nome, nome) == 0) {
            if(!ant) lista = p->prox;
            else ant->prox = p->prox;

            free(p);
            return;
        }
        ant = p;
        p = p->prox;
    }
}

No* buscaLista(char nome[]) {
    compSeq = 0;
    for(No* p = lista; p; p = p->prox) {
        compSeq++;
        if(strcmp(p->dados.nome, nome) == 0)
            return p;
    }
    return NULL;
}

// Main
int main() {
    int op, tipo;
    char nome[30];

    printf("1 Vetor 2 Lista: ");
    scanf("%d", &tipo);

    do {
        printf("\n1 Inserir 2 Remover 3 Listar 4 Buscar 5 Ordenar 0 Sair\n");
        scanf("%d", &op);

        if(op == 1)
            tipo == 1 ? inserirVetor() : inserirLista();

        if(op == 2)
            tipo == 1 ? removerVetor() : removerLista();

        if(op == 3)
            tipo == 1 ? listarVetor() : listarLista();

        if(op == 4) {
            printf("Nome: ");
            scanf("%s", nome);

            if(tipo == 1) {
                buscaSeqVetor(nome);
                printf("Seq: %d comp\n", compSeq);

                ordenar(); // necessário para busca binária
                buscarBin(nome);
                printf("Bin: %d comp\n", compBin);
            } else {
                buscaLista(nome);
                printf("Comp: %d\n", compSeq);
            }
        }

        if(op == 5 && tipo == 1)
            ordenar();

    } while(op != 0);

    return 0;
}