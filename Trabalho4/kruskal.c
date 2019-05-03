#include<stdio.h>
#include<stdlib.h>

typedef struct v{
    int rank;
    int valor;
    struct v *pai;
}v;

int peso_total=0;
v** lista_vertices;

void union_find(v* no1, v* no2, int peso);
v* find(v* v);

int main(){
    int n_vertices, n_arestas, i;
    char* linha = (char*) calloc(1000, sizeof(char));
    scanf("%d %d", &n_vertices, &n_arestas);
        
    lista_vertices = (v**) calloc(n_vertices, sizeof(v));

    for(i=0;i<n_vertices;i++){
        v* vertice = (v*) calloc(1, sizeof(v));
        vertice->rank = 1;
        vertice->valor = i + 1;
        vertice->pai = vertice;
        lista_vertices[i] = vertice;
    }

    for(i=0;i<n_arestas;i++){
        int v1, v2, peso;
        scanf("%d %d %d", &v1, &v2, &peso);
        union_find(lista_vertices[v1-1], lista_vertices[v2-1], peso);
    }

    printf("%d\n", peso_total);
    return 0;
}

void union_find(v* no1, v* no2, int peso){
    v* raiz_no1 = find(no1);
    v* raiz_no2 = find(no2);

    if(raiz_no1->valor != raiz_no2->valor){
        if(raiz_no1->rank > raiz_no2->rank){
            raiz_no2->pai = raiz_no1;
        }else{
            raiz_no1->pai = raiz_no2;
        }
        if(raiz_no1->rank == raiz_no2->rank){
            raiz_no2->rank++;
        }
        peso_total += peso;
    }

}

v* find(v* v){
    if(v->pai->valor != v->valor){
        v->pai = find(v->pai);
    }
    return v->pai;  
}
