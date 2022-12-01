/*
=========================================================================================
AUTOR: 	Henrique Almeida de Oliveira
Disciplina: Tecnicas de Programacao Avancada
Professor: Eduardo Max Amaral
=========================================================================================
*/

#include<stdio.h>
#include<string.h>
#include<locale.h>
#include<stdlib.h>
#include<limits.h>
#include "grafo.h"

#define INFINITY INT_MAX/2

/*
=========================================================================================
			Implementacao
*/

void limparBuffer(){
    char c;
    while((c= getchar()) != '\n' && c != EOF);
}

Tgraph* initializeGraph(Tgraph* graph){
    graph = (Tgraph*)malloc(sizeof(Tgraph));
    graph->item=NULL;
    graph->next=NULL;
    return graph;
}

// procura o vertice com nome passado
Tvertex* searchCity(Tgraph* graph, string name){
    if(graph->item == NULL) return NULL;
	Tgraph* aux = graph;

	while(aux!=NULL){
		if(strcmp(name, (aux->item)->city_name)!=0)
			aux = aux->next;
		else
			return aux->item;
	}
	return NULL;
}

// procura o vertice com nome passado
Tvertex* searchCode(Tgraph* graph, int code){
    if(graph->item == NULL) return NULL;
	Tgraph* aux = graph;

	while(aux!=NULL){
		if(code != aux->item->code)
			aux = aux->next;
		else
			return aux->item;
	}
	return NULL;
}

Tvertex *initializeVertex(string name, int code){
    Tvertex *newCity = (Tvertex *)malloc(sizeof(Tvertex));
	newCity->number_adjacent = 0;
	newCity->adjacent = NULL;
    newCity->code = code;
	strcpy(newCity->city_name, name);
    return newCity;
}

Tgraph *newGraph(string name, int code){
    Tgraph* newNode = (Tgraph *)malloc(sizeof(Tgraph));
	newNode->item = initializeVertex(name, code);
	newNode->next = NULL;
    return newNode;
}

void count(Tgraph** graph){
    Tgraph* aux= *graph;
    int i=0;

    while(aux!=NULL){
        i++;
        aux = aux->next;
    }
    aux= *graph;
    while(aux!=NULL){
        aux->size = i;
        aux = aux->next;
    }
}

Tgraph* insertCity(Tgraph** graph, string name, int code){
    int flag=0;
    if((*graph)->item==NULL){
        // substitui item pelo novo vetor (ja estava inicializado com NULL)
        (*graph) = newGraph(name, code);
        flag=1;
    }else if(strcmp(name, (*graph)->item->city_name)<0){
        Tgraph* newNode = newGraph(name, code);
        newNode->next = (*graph);
        graph = &(newNode);
    }else{
        //Lista auxiliar de busca
        Tgraph *aux = (*graph), *previous=NULL;
        while(aux!=NULL && (strcmp(name, aux->item->city_name)>0)){
            previous = aux;
            aux = aux->next;
        }

        if (aux == NULL)
			previous->next = newGraph(name, code);
		else{
            Tgraph* newNode = newGraph(name, code);
			newNode->next = aux;
			previous->next = newNode;
		}
    }
    count(graph);
    return (*graph);
}

void createCity(Tgraph** graph){
    string name; int code;
	Tvertex* valid = NULL;

	// recebe dados do usuario
	printf("\nDigite o nome da cidade para adicionar: ");
	scanf("%s", name);
    printf("\nDigite o codigo da cidade para adicionar: ");
	scanf("%d", &code);

	// verifica se ja nao existe o valor passado na arvore

	valid = searchCity((*graph), name); 

	if (valid == NULL) (*graph) = insertCity(graph, name, code); // se nao estiver adicionado, adiciona o registro
    else printf("Valor ja existe na lista");
}

void printAdjacent(Tadjacent* adjacent){
    if(adjacent==NULL){
        printf("\n");
    }else{
        printf("\n\t%s (%.2f km)", adjacent->vertex->city_name, adjacent->distance);
        printAdjacent(adjacent->next);
    }
}

void printVertex(Tvertex* vertex){
    if(vertex==NULL){
        printf("\n====================");
    }else{
        printf("\n%s (%d Adjacentes)", vertex->city_name, vertex->number_adjacent);
        printAdjacent(vertex->adjacent);
    }
}

void printGraph(Tgraph* graph){
    Tgraph* aux = graph;
    if(aux->item==NULL) printf("\nCidade Vazia");
    else{
        while(aux!=NULL){
            printVertex(aux->item);
            aux = aux->next;
        }
    }
}

void printCity(Tgraph* graph){
    Tgraph* aux = graph;
    Tvertex* vertex;
    if(aux->item==NULL) printf("\nCidade Vazia");
    else{
        while(aux!=NULL){
            vertex = aux->item;
            if(vertex==NULL){
                printf("\n====================");
            }else{
                printf("\n%d - %s", vertex->code, vertex->city_name);
            }
            aux = aux->next;
        }
    }
}

Tadjacent* initAdjacent(Tvertex* city, float distance){
    Tadjacent* aux = (Tadjacent*)malloc(sizeof(Tadjacent));
    aux->distance = distance;
    aux->vertex = city;
    aux->next=NULL;
    return aux;
}

void insertEdge(Tvertex* city1, Tvertex* city2, float distance){
    // printf("\n%s -> %s", city1->city_name, city2->city_name);
    if(city1==NULL){
        printf("\nCidade Origem n�o existe");
        return;
    }else if(city2==NULL){
        printf("\nCidade Destino n�o existe");
        return;
    }

    if((city1)->adjacent==NULL){
        (city1)->adjacent = initAdjacent(city2, distance);
        (city1)->number_adjacent = 1;
    }else if(strcmp(city2->city_name, (city1)->adjacent->vertex->city_name)<0){
        Tadjacent* aux = initAdjacent(city2, distance);
        aux->next = (city1)->adjacent;
        (city1)->adjacent = aux;
        (city1)->number_adjacent++;
    }else{
        Tadjacent *actual = (city1)->adjacent;
		Tadjacent *previous = NULL;
        (city1)->number_adjacent++;

		while(actual != NULL && strcmp(city2->city_name, actual->vertex->city_name)>0 ){
			previous = actual;
			actual = actual->next;
		}	
		
		if (actual == NULL){
			previous->next = initAdjacent(city2, distance);
		}else{
			previous->next = initAdjacent(city2, distance);
            previous->next->next = actual;
		}
    }
}

void createEdge(Tgraph** graph){
    string name1, name2;
    int distance;
    Tvertex* city1=NULL, * city2=NULL;
	// recebe dados das cidades
    limparBuffer();
	printf("\nDigite o nome da cidade origem: ");
	scanf(" %[^\n]s", name1);

    limparBuffer();
    printf("\nDigite o nome da cidade destino: ");
	scanf(" %[^\n]s", name2);

    printf("\nDigite a distancia entre as cidades: ");
	scanf("%d", &distance);

    city1 = searchCity((*graph), name1); 
	if (city1 != NULL){
        city2 = searchCity((*graph), name2); 
        // se nao estiver adicionado, adiciona o registro
        if (city2 != NULL){
            insertEdge(city1, city2, distance);
            insertEdge(city2, city1, distance);
        }
        else printf("Cidade %s nao existe", name2);
    }
    else printf("Cidade %s nao existe", name1);
}

void search(Tgraph* graph){
    string name;
	Tvertex* valid = NULL;

	// recebe dados do usuario
	printf("\nDigite o nome da cidade a procurar: ");
	limparBuffer();
	scanf(" %[^\n]s", name);

	// verifica se existe
	valid = searchCity((graph), name); 

    if(valid==NULL) printf("\nCidade nao existe");
    else{
        printf("Cidade %s", valid->city_name);
        printAdjacent(valid->adjacent);
    }
}

int hasOpen(int vector[], int size){
    int i, qt=0; 
    for(i=0; i<size; i++){
        if(vector[i]==1) qt++;
    }
    return qt;
}

Tvertex** bestWay(int open[], float dist[], Tvertex** pre, Tvertex* aux1, Tvertex* destiny){
    Tadjacent* aux2 = aux1->adjacent, *shortest;
    if(aux1->code == destiny->code) return pre;
    
    while(aux2!=NULL){
        // se o nodo estiver aberto, deve ser relaxado
        if(open[aux2->vertex->code-1]){
        	// se a distancia armazenada for maior que a no caminho, dever ser relaxado
            if(dist[aux2->vertex->code-1]>(aux2->distance+dist[aux1->code-1])){
                dist[aux2->vertex->code-1]=aux2->distance+dist[aux1->code-1];
                pre[aux2->vertex->code-1]=aux1;
                shortest = aux2;
            }
        }
        aux2=aux2->next;
    }
    
    pre[shortest->vertex->code-1] = aux1;
    dist[shortest->vertex->code-1] = dist[aux1->code-1]+shortest->distance;
    open[shortest->vertex->code-1] = 0;
    return bestWay(open, dist, pre, aux1, destiny);
}

Tvertex** mine(Tgraph* g, Tvertex** way, Tvertex* origin, Tvertex* destiny){
    int n = g->size, i, open[n];
    float dist[n], shortPath=INFINITY;
    Tvertex** pre = (Tvertex**) malloc((g->size)*sizeof(Tvertex*));

    // Inicializar o vetor de abertos, de distancias e precedecessores
    for(i=0; i<n; i++){
        open[i]=1;
        dist[i]=INFINITY;
        pre[i]=NULL;
    }
    dist[origin->code-1]=0;

    return bestWay(open, dist, pre, origin, destiny);
    
}

void djiskra(Tgraph* graph){
    Tvertex** way = (Tvertex**) malloc((graph->size)*sizeof(Tvertex*));
	int i, n;
    Tvertex *origin, *destiny;

    // inicializar o caminho entre as cidades como nodos nulos
	for(i=0; i<graph->size; i++) way[i]=NULL;

    // entrada de cidade
	printf("\nQual o codigo da cidade de origem?\n");
	scanf("%d", &n);
	// verifica se existe a cidade passada de origem
	origin = searchCode((graph), n);

    // entrada de cidade
	printf("\nQual o codigo da cidade de destino?\n");
	scanf("%d", &n);
	// verifica se existe a cidade passada de origem
	destiny = searchCode((graph), n);

    // se existir a cidade, chama a subfuncao que escreve o menor caminho
    if(origin==NULL) printf("\nCidade origem nao existe");
    else if(destiny==NULL) printf("\nCidade destino nao existe");
    else{        
        way = mine(graph, way, origin, destiny);
    }
    i=0;
    while(way[i]!=NULL) i++;
    //way[++i] = destiny;

    // Listar Saida
    printf("\nCidade Percorridas (%d/%d): (", i, graph->size);
    for(i=n-1; i>0; i--){
        if(way[i]!=NULL) printf("%s, ", way[i]->city_name);
    }
    printf("%s)\nDistancia Total: %.2f km", way[0]->city_name, way[destiny->code-1]);
}

Tgraph* initializeCities(Tgraph* graph){
    FILE* file;
    int n_cities, i, j;
    float dist;
    string s;
    char* arrayList[2];
    file = fopen("entrada.txt", "r");
    
    // Pegar o numero N de cidades
    fgets(s, 40, file);
    n_cities = atoi(s);
    char* cities[n_cities];
    char* arr;

    // Loop para registrar as cidades (primeiras N+1 Linhas)
    for (i=0; i<n_cities; i++){
        fgets(s, 40, file);
		arr = strtok(s, ";");
		arrayList[0] = arr;
		arr = strtok(NULL, ";\n");
		arrayList[1] = arr;
		graph = insertCity(&graph, arrayList[1], atoi(arrayList[0]));
        cities[i] = (char*) malloc(40* sizeof(char));
		strcpy(cities[i], arrayList[1]);

	}

	// Loop para registrar as distancias (depois das N+1 Linhas)
	for (i=0; i<n_cities; i++){
        for(j=0; j<n_cities; j++){
            fscanf(file, "%f", &dist);
            fscanf(file, "%c", &arrayList[0]);
		    if(dist!=0) insertEdge(searchCity(graph, cities[i]), searchCity(graph, cities[j]), dist );
            arr = strtok(NULL, ";\n");
        }
	}
    return graph;
}