#include <stdio.h>

#define MAX_VERTICES 100

typedef struct Rede {
	int n_vertices;
	int matriz_adj[MAX_VERTICES][MAX_VERTICES];
} Rede;


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

int main() {
	
	Rede grafo = criarRede(MAX_VERTICES);
	int escolha = 0;
	
	do {
	    
	    printf("[1] Adicionar usuário\n");
	    printf("[2] Adicionar conexões de usuário\n");
	    scanf("%d", &escolha);
	    
	    switch (escolha) {
	        case 1:
	            adicionarUsuario(&grafo);
	            break;
	        case 2:
	            adicionarConexao(&grafo);
	            break;
	    }
	    
	} while(1);
	
}