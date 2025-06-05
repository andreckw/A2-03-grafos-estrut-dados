#include <stdio.h>

#define MAX_VERTICES 100

typedef struct {
    int itens[MAX_VERTICES];
    int frente;
    int tras;
} Fila;


typedef struct Rede {
	int n_vertices;
	int matriz_adj[MAX_VERTICES][MAX_VERTICES];
} Rede;


typedef struct No {
    int vertice;
    struct No* prox;
} No;

void inicializarFila(Fila *f) {
    f->frente = -1;
    f->tras = -1;
}

int estaVazia(Fila *f) {
    return f->frente == -1;
}

void enfileirar(Fila *f, int valor) {
    if (f->tras == MAX_VERTICES - 1) {
        printf("Fila cheia\n");
        return;
    }
    if (f->frente == -1)
        f->frente = 0;
    f->tras++;
    f->itens[f->tras] = valor;
}

int desenfileirar(Fila *f) {
    if (estaVazia(f)) {
        printf("Fila vazia\n");
        return -1;
    }
    int valor = f->itens[f->frente];
    f->frente++;
    if (f->frente > f->tras)
        f->frente = f->tras = -1;
    return valor;
}

void BFS(Rede *grafo, int n, int inicio) {
    int visitado[MAX_VERTICES] = {0};
    Fila f;
    inicializarFila(&f);

    visitado[inicio] = 1;
    enfileirar(&f, inicio);


    while (!estaVazia(&f)) {
        int atual = desenfileirar(&f);

        for (int i = 0; i < n; i++) {
            if (grafo->matriz_adj[atual][i] == 1 && !visitado[i]) {
                enfileirar(&f, i);
                printf("Sugestão de amizade: %d", i);
                visitado[i] = 1;
            }
        }
        
        printf("\n");
    }
}


Rede criarRede(int n_vertices) {
	
	Rede grafo;
	
	grafo.n_vertices = n_vertices;
	int i = 0;
	int j = 0;
	for (i = 0; i < n_vertices; i++) {
		for (j = 0; j < n_vertices; j++) {
			grafo.matriz_adj[i][j] = -1;
		}
	}
	
	return grafo;
}


void adicionarAresta(Rede *grafo, int vertice_i, int vertice_j) {
	grafo->matriz_adj[vertice_i][vertice_j] = 1;
	grafo->matriz_adj[vertice_j][vertice_i] = 1;
}

void adicionarUsuario(Rede *grafo) {
    int vertice = -1;
    
    printf("Qual o id do usuário? ");
    scanf("%d", &vertice);
    
    // 0 = usuario adicionado
    grafo->matriz_adj[vertice][vertice] = 0;
}

void adicionarConexao(Rede *grafo) {
    int v_i = -1;
    int v_j = -1;
    
    printf("Qual o id do usuário 1? ");
    scanf("%d", &v_i);
    
    if (grafo->matriz_adj[v_i][v_i] == -1) {
        printf("Usuario não existe\n");
        return;
    }
    
    printf("Qual o id do usuário 2? ");
    scanf("%d", &v_j);
    
    if (grafo->matriz_adj[v_j][v_j] == -1) {
        printf("Usuario não existe\n");
        return;
    }
    
    
    adicionarAresta(grafo, v_i, v_j);
}

void verAmizades(Rede *grafo) {
    int i = -1;
    
    printf("Digite o id do usuário: ");
    scanf("%d", &i);
    
    for (int j = 0; j < MAX_VERTICES; j++) {
        if (grafo->matriz_adj[i][j] == 1) {
            printf("Usuário %d tem amizade %d\n", i, j);
        }
    }
}

void sugestaoAmizades(Rede *grafo) {
    int i = -1;
    
    printf("Digite o id do usuário: ");
    scanf("%d", &i);
    
    BFS(grafo, MAX_VERTICES, i);
}


int main() {
	
	Rede grafo = criarRede(MAX_VERTICES);
	int escolha = 0;
	
	do {
	    
	    printf("[1] Adicionar usuário\n");
	    printf("[2] Adicionar conexões de usuário\n");
	    printf("[3] Ver amizades de um usuario\n");
	    printf("[4] Sugestão de amizades\n");
	    scanf("%d", &escolha);
	    
	    switch (escolha) {
	        case 1:
	            adicionarUsuario(&grafo);
	            break;
	        case 2:
	            adicionarConexao(&grafo);
	            break;
	       case 3:
	            verAmizades(&grafo);
	            break;
	       case 4:
	            sugestaoAmizades(&grafo);
	            break;
	    }
	    
	} while(1);
	
}
