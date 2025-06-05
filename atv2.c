#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX 20

int x = 0;
char cidades[MAX][30];
int grafo[MAX][MAX];

int indCidade(char nome[]){
    for (int i = 0; i < x ; i++){
        if (strcmp(nome, cidades[i]) == 0){
            return i;
        }
    }
    return -1;
}

void cadastroCidade(){
    if (x >= MAX){
        printf("Numero maximo de cidades cadastrados\n");
        return;
    }

    printf("Digite o nome da cidade: \n");
    scanf("%s", cidades[x]);
    x++;
    printf("Cidade foi cadastrada \n");
}

void cadastroRota(){
    char origem[30];
    char destino[30];
    int peso;

    printf("Digite a cidade origem: \n");
    scanf("%s", origem);

    printf("Digite o destino desejado: \n");
    scanf("%s", destino);

    printf("Digite o peso da rota: \n");
    scanf("%d", &peso);

    int i = indCidade(origem);
    int j = indCidade(destino);

    if (i == -1 || j == -1){
        printf("Cidade de origem ou destino nao existe n\n");
        return;
    }

    grafo[i][j] = peso;
    grafo[j][i] = peso;
    printf("Rota cadastrada \n");
}

void imprimirCaminho(int anterior[], int destino) {
    int caminho[MAX];
    int tamanho = 0;
    int atual = destino;

    while (atual != -1) {
        caminho[tamanho++] = atual;
        atual = anterior[atual];
    }

    for (int i = tamanho - 1; i >= 0; i--) {
        printf("%s", cidades[caminho[i]]);
        if (i > 0){
            printf(" --> ");
        } 
    }
}

int minDistancia(int dist[], int visitado[]) {
    int min = INT_MAX, min_index = -1;
    for (int v = 0; v < x; v++) {
        if (!visitado[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void dijkstra(int origem) {
    int dist[MAX], visitado[MAX], anterior[MAX];

    for (int i = 0; i < x; i++) {
        dist[i] = INT_MAX;
        visitado[i] = 0;
        anterior[i] = -1;
    }

    dist[origem] = 0;

    for (int count = 0; count < x - 1; count++) {
        int u = minDistancia(dist, visitado);
        if (u == -1){
            break;
        }

        visitado[u] = 1;

        for (int v = 0; v < x; v++) {
            if (!visitado[v] && grafo[u][v] && dist[u] != INT_MAX && dist[u] + grafo[u][v] < dist[v]) {
                dist[v] = dist[u] + grafo[u][v];
                anterior[v] = u;
            }
        }
    }

    printf("\nCidade\tDistancia\tCaminho\n");
    printf("--------------------------------------------\n");
    for (int i = 0; i < x; i++) {
        if (dist[i] == INT_MAX) {
            printf("%s sem caminho\n", cidades[i]);
        } else {
            printf("%s\t\t%d\t\t", cidades[i], dist[i]);
            imprimirCaminho(anterior, i);
            printf("\n");
        }
    }
}

void listaCidades(){
    for(int i = 0; i < x; i++){
        printf("\n%s \n", cidades[i]);
    }
}

void mostrarRotas(){
    printf("Rotas: ");
    for (int i = 0; i < x; i++){
        printf("%s\t", cidades[i]);
    }
    printf("\n");

    for (int i = 0; i< x; i++){
        printf("%s\t", cidades[i]);
        for (int j = 0; j < x; j++){
            printf("%d\t", grafo[i][j]);
        }
        printf("\n");
    }
}

int main(){
    int opcao;

    for (int i = 0; i < MAX; i++){
        for (int j = 0; j < MAX; j++){
            grafo[i][j] = 0;
        }   
    }

    do{
        printf("1. Cadastrar cidade\n");
        printf("2. Cadastrar rota entre cidades\n");
        printf("3. Calcular menor caminho\n");
        printf("4. Listar cidades\n");
        printf("5. Mostrar matriz de rotas\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                cadastroCidade();
                break;
            case 2:
                cadastroRota();
                break;
            case 3:{
                char nOrigem[30];
                int origem;

                printf("Digite a cidade de origem: ");
                scanf("%s ", nOrigem);
                origem = indCidade(nOrigem);
                if(origem == -1){
                    printf("Cidade nao existe\n");
                } else{
                    dijkstra(origem);
                }
                break;
            }
            case 4:
                listaCidades();
                break;
            case 5:
                mostrarRotas();
                break;
            case 0:
                break;
            default:
                printf("Opcao nao existe\n");
        }

    }while(opcao != 0);

    return 0;
}