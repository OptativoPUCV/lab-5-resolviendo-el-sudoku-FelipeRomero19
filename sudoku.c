#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
  int fila, columna, p, k ;

  for(fila = 0; fila < 9 ; fila++)
  {
    int revisados[10] = {0};
    for(columna = 0; columna < 9; columna++)
    {
      int numero = n->sudo[fila][columna];
      if (numero != 0)
      {
        if(revisados[numero]== 1) return 0;
        revisados[numero] = 1;
      }
    }
  }

  for(columna = 0; columna < 9; columna++)
  {
    int revisados[10] = {0};
    for(fila = 0; fila < 9; fila++)
    {
      int numero = n->sudo[fila][columna];
      if(numero != 0)
      {
        if(revisados[numero] == 1)return 0;
        revisados[numero] = 1 ;
      }
    }
  }

  for(k = 0; k < 9; k++) 
  {
    int vistos[10] = {0};
    for(p = 0; p < 9; p++) 
    {
      int i = 3 * (k / 3) + (p / 3);
      int j = 3 * (k % 3) + (p % 3);
      int numero = n->sudo[i][j];
        if(numero != 0) 
        {
          if(vistos[numero] == 1) return 0;
          vistos[numero] = 1;
        }
    }
  }

    return 1;
}


List* get_adj_nodes(Node* n){
    List* list = createList();
    
    int i, j;
    int encontrado = 0;
    for(i = 0; i < 9 && !encontrado; i++){
        for(j = 0; j < 9 && !encontrado; j++){
            if(n->sudo[i][j] == 0){
                encontrado = 1;
                break;
            }
        }
        if(encontrado) break;
    }
    
    if(encontrado){
        for(int k = 1; k <= 9; k++){
            Node* new_node = copy(n);
            new_node->sudo[i][j] = k;
            if(is_valid(new_node)){
                pushBack(list, new_node);
            } else {
                free(new_node);
            }
        }
    }

    
    return list;
}


int is_final(Node* n){
  int fila, columna;

  for(fila = 0; fila < 9; fila++)
  {
    for(columna = 0; columna < 9; columna++)
    {
      if(n->sudo[fila][columna] == 0)
      {
        return 0;
      }
    }
  }
    return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack* pila = createStack();
  *cont = 0 ;

  push(pila, initial);

  while(top(pila) != NULL)
  {
    (*cont)++;

    Node* actual = (Node*) top(pila);
    pop(pila);

    if(is_final(actual))
    {
      while(top(pila) != NULL)
      {
        Node *aux = (Node*) top(pila);
        pop(pila);
        free(aux);
      }
      free(pila);
      return actual;
    }

    List *adyacen = get_adj_nodes(actual);

    Node* nodo_ady = (Node*) first(adyacen);
    while(nodo_ady != NULL)
    {
      push(pila, nodo_ady);
      nodo_ady = (Node*) next(adyacen);
    }
    free(adyacen);
    free(actual);
  }
  free(pila);
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/