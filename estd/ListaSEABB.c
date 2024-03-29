/*
=========================================================================================
AUTORES: 	Henrique Almeida de Oliveira
			Luiz Eduardo Marchiori
Disciplina: Estrutura de Dados
Professor: Vanderson José Idelfonso Silva
Programa em linguagem C que implementa uma lista simplesmente encadeada com as seguintes informações: matricula, nome e sexo (além do campo prox, é claro).

Uma árvore binária de busca (ABB) deverá permitir uma busca não linear por nome nessa mesma lista. Ou seja, qualquer procura por um elemento da lista com nome = "Jose da Silva", por exemplo, deverá começar pela árvore binária de busca.
Uma vez encontrado um nodo com esse nome, deve-se utilizar o campo enderecoLista (contendo um ponteiro para a Lista) para acessar o registro (struct) da Lista.

Sempre que um elemento for inserido na Lista um nodo correspondente deverá ser inserido na árvore de modo a apontar (endereçar) o referido elemento.

Quando um elemento for removido da Lista o nodo referente na árvore também deverá ser eliminado.

=========================================================================================
*/

#include<stdio.h>
#include<string.h>
#include<locale.h>
#include<stdlib.h>

/*
=========================================================================================
			Tipo Abstrato de Dados
*/

typedef struct tipoPerson TPerson;

typedef struct NoTree TTree;

typedef char string[40];

typedef struct tipoPerson {
	TPerson *prox;
	string nome;
	char genero;
	string matricula;
}TPerson;

typedef struct NoTree {
	TTree *esq;
	TTree *dir;
	string nome;
	TPerson *nodo;
}TTree;

typedef struct tipoLista {
	int total;
	TTree* raiz;
	TPerson *ini;
	TPerson *fim;
}TLista;

// Funções padrão
int menu();
void limparBuffer();

// Função de Lista SEABB
void inicializaLista(TLista *L);
void inserePessoa(TLista *L);
void listaMatricula(TLista *L);
void listaNome(TLista *L);
void procuraNome(TLista *L);
void removerLista(TLista *L);
void automatico(TLista *L);

/*
=========================================================================================
			Função Principal
*/

int main(){
	int op;
	TLista lista;
	setlocale(LC_ALL, "Portuguese");

	inicializaLista(&lista);

	do {
		op = menu();

		switch(op){
		   case 1: inserePessoa(&lista); break;
		   case 2: listaMatricula(&lista); break;
		   case 3: listaNome(&lista); break;
		   case 4: procuraNome(&lista); break;
		   case 5: removerLista(&lista); break;
		   case 222: automatico(&lista); break;
		}//switch
		printf("\nPressione qualquer tecla para continuar. . .");
		limparBuffer();
		char c = getchar();
	    system("@cls||clear");

	} while(op != 0);

}

/*
=========================================================================================
			Implementação
*/

void limparBuffer(){
    char c;
    while((c= getchar()) != '\n' && c != EOF);
}

int menu(){
	int opcao;
    printf("\n================| MENU |================\n\n");
    printf("0 - SAIR (Encerrar Programa).\n\n");
    printf("1 - Inserir pessoa.\n");
    printf("2 - Listar Pessoas por ordem crescente de matrícula.\n");
    printf("3 - Listar Pessoas por ordem crescente alfabética de nome.\n");
    printf("4 - Consultar Pessoa por Nome.\n");
    printf("5 - Remover pessoa.\n");
    printf("================================================\n");

    printf("\n\tInforme OPCAO desejada: ");
    scanf("%d",&opcao);
    printf("\n================================================\n");

    if (opcao == 222){
		return opcao;
	}

	if ((opcao > 5) || (opcao < 0)){
		printf("\n\n\n");
		printf("\n\t+------------------------+");
		printf("\n\t|   ERRO:                |");
		printf("\n\t|                        |");
		printf("\n\t|   OPCAO INVALIDA!!!    |");
		printf("\n\t|                        |");
		printf("\n\t|   Tente outra vez.     |");
		printf("\n\t+------------------------+");
		system("PAUSE");
	}
	return opcao;
}

void inicializaLista(TLista *L){
	L->ini = NULL;
	L->fim = NULL;
	L->raiz = NULL;
	L->total = 0;
}

void inicializaPerson(TPerson* no, string nome, char gender, string reg){
	no->prox = NULL;
	strcpy(no->nome, nome);
	no->genero = gender;
	strcpy(no->matricula, reg);
}

// subfunção de inseraNaArvore, modifica os ponteiros
TTree *inicializaTree(TPerson* add, string nome){
	TTree *no = (TTree *)malloc(sizeof(TTree));
	no->esq = NULL;
	no->dir = NULL;
	no->nodo = add;
	strcpy(no->nome, nome);
	return no;
}

// subfunção de inseraNaLista,
TTree *insereNaArvore(TTree **node, TPerson* add){
	if((*node)==NULL){
		(*node) = inicializaTree(add, add->nome);
	}else if(strcmp(add->nome, (*node)->nodo->nome)>0){
		(*node)->dir = insereNaArvore(&(*node)->dir, add);
	}else {
		(*node)->esq = insereNaArvore(&(*node)->esq, add);
	}
	return (*node);
}

// subfunção de inserePessoa, implementa automatização como função direta
void insereNaLista(TLista *L, string nome, char genero, string matricula){
	TPerson *no = (TPerson *)malloc(sizeof(TPerson));
	inicializaPerson(no, nome, genero, matricula);
	L->total++;

	if(L->ini==NULL){
		L->ini = no;
		L->fim = no;

		// essa segunda parte tenta adicionar à arvore o nó
		// os dois print fazem parte do debug da tentativa de correção
		L->raiz = insereNaArvore(&(L->raiz), no);
	}else{
		TPerson *aux = L->ini;
		TPerson *ant;
		while( (aux!=NULL)&&(strcmp(matricula, aux->matricula)>0)){
			ant = aux;
			aux = aux->prox;
		}

		if(aux == NULL&&(ant!=L->ini)){
			ant->prox = no;
			L->fim = no;
		}else if(aux == L->ini){
			no->prox = aux;
			L->ini = no;
		}else{
			no->prox = aux;
			ant->prox = no;
		}
		L->raiz = insereNaArvore(&L->raiz, no);
	}
}

// Inserir Pessoa
void inserePessoa(TLista *L){
	string nome, matricula;
	char genero;

	printf("\nDigite o nome do aluno: ");
	limparBuffer();
	scanf("%[^\n40]s", nome);

	printf("\nDigite o genero do aluno: ");
	limparBuffer();
	scanf("%c", &genero);

	printf("\nDigite o matricula do aluno: ");
	limparBuffer();
	scanf("%[^\n40]s", matricula);

	insereNaLista(L, nome, genero, matricula);
}

// Subfunção de listaMatricula, entra na árvore para imprimir em ordem
void digTree(TTree* node){
	if(node==NULL) return;
	digTree(node->esq);
	TPerson *aux = node->nodo;
	printf("\n%s \t %s", aux->matricula, aux->nome);
	digTree(node->dir);
}

// Listar Pessoas por ordem crescente de matrícula
void listaNome(TLista *L){
	TTree *aux = L->raiz;

	printf("\n============================");
	printf("\n\tLista de Pessoas (A-Z)");
	printf("\n============================");

	digTree(aux);

}

// Listar Pessoas por ordem crescente alfabética de nome
void listaMatricula(TLista *L){
	TPerson* aux;
	aux = L->ini;
	int i, max = L->total;
	printf("\n============================");
	printf("\n\tLista de Pessoas (123)");
	printf("\n============================");
	for (i=0; i<max; i++){
		printf("\n%s \t %s", aux->matricula, aux->nome);
		aux = aux->prox;
	}
}

// Subfunção de procuraNome, recursiva, retorna struct Person encontrada
TPerson *digThrowTree(TTree* node, string name){
	TPerson *x;
	if(node!=NULL) x = node->nodo;

	if (node==NULL){
		return NULL;
	}else if(!strcmp(x->nome, name)){
		return x;
	}else if(strcmp(x->nome, name)>0){
		digThrowTree(node->esq, name);
	}else{
		digThrowTree(node->dir, name);
	}
}

// Consultar Pessoa por Nome
void procuraNome(TLista *L){

	TTree *aux = L->raiz;
	if(aux == NULL){
		printf("\nArvore Vazia!");
	}else{
		printf("\nQual pessoa deseja procurar?\n> ");
		string nome;
		limparBuffer();
		scanf("%[^\n40]s", nome);
		TPerson *x = digThrowTree(aux, nome);
		if (x==NULL){
			printf("\nNão encontrado!");
		}else{
			printf("\nEncontrado!");
			printf("\n%s \t %s", x->matricula, x->nome);
		}
	}
}

//subfuncao de removerGeral utilizada para pegar o nó mais a direita da subarvore esquerda do nó que será removido
TTree *raizDireita(TTree **no){
	if ((*no)->dir != NULL){
		return raizDireita(&(*no)->dir);
	} else {
		TTree *aux1 = *no;
		if ((*no)->esq != NULL)
			*no = (*no)->esq;
		else
			*no = NULL;
	return aux1;
	}
}

//subfuncao de removerLista, remove da árvore a pessoa
void removerArvore(TLista *L, TTree **raiz, string apagar){
	int resposta = 0;
	if (*raiz == NULL){
		printf("\nNome não encontrado!\n\n");
		return;
	}

	if (strcmp(apagar, (*raiz)->nome) < 0){
		removerArvore(L, &(*raiz)->esq, apagar);
	} else if (strcmp(apagar, (*raiz)->nome) > 0){
        removerArvore(L, &(*raiz)->dir, apagar);
    } else {
        printf("\n============================");
        printf("\n   Apagar %s?\n   1 - Sim\n   0 - Nao\n\n-> ", (*raiz)->nome);
        scanf("%i", &resposta);
        printf("\n============================");
        if (resposta){
            TTree *aux = (*raiz);
            if (((*raiz)->esq == NULL) && ((*raiz)->dir == NULL)){
                free(aux);
                (*raiz) = NULL;
                if (L->raiz == (*raiz)) (L->raiz)=NULL;
            } else if ((*raiz)->esq == NULL){
                if (L->raiz == (*raiz)) (L->raiz)=(*raiz)->dir;
                (*raiz) = (*raiz)->dir;
                aux->dir = NULL;
                free(aux);
                aux = NULL;
            }else if ((*raiz)->dir == NULL){
                    if (L->raiz == (*raiz)) (L->raiz)=(*raiz)->esq;
                    (*raiz) = (*raiz)->esq;
                    aux->esq = NULL;
                    free(aux);
                    aux = NULL;
            }else {
                if (L->raiz == (*raiz)) (L->raiz)=aux;
                aux = raizDireita(&(*raiz)->esq);
                aux->esq = (*raiz)->esq;
                aux->dir = (*raiz)->dir;
                free((*raiz));
                (*raiz) = aux;
            }
            printf("\n   %s apagado(a) !\n\n", apagar);
        } else {
            printf("\n============================");
            printf("\n%s não apagado (a)", apagar);
        }
    }
}

void removerPessoa(TLista *l, string nome){
    if(l->ini==NULL){
		printf("\nLista Vazia: não há nada para excluir");
		return;
	}else{
		TPerson *aux = l->ini;
		TPerson *ante = NULL;
		if(aux == NULL){
			printf("\nNão há pessoas para remover na lista");
		}else{
			while(aux->prox!=NULL&&(strcmp(nome, aux->nome))){
                ante = aux;
                aux = aux->prox;
			}

			if(aux==NULL){
				printf("\nPessoa não encontrado: revise informações antes de prosseguir");
			}else if(aux->prox == l->fim){ //verificar se remover o ultimo
				ante->prox = NULL;
				l->fim = ante;
				free(aux);
			}else if(ante == NULL){ // verificar se remover o primeiro;
				ante = aux->prox;
				l->ini = ante;
				free(aux);
			}else{ // caso remover algum do meio qualquer
				ante->prox = aux->prox;
				free(aux);
			}
		}
	}
}

// Remover Pessoa das estruturas
void removerLista(TLista *L){

	TTree *aux = L->raiz;

	if(aux == NULL){
		printf("\nLista Vazia!");
	}else{
		printf("\nQual pessoa deseja remover?\n> ");
		string nome;
		limparBuffer();
		scanf("%[^\n40]s", nome);
		removerArvore(L, &aux, nome);
		removerPessoa(L, nome);
		L->total--;
	}
}

void automatico(TLista *L){
	string nome[10] = {"Yuri Duarte","Luiz Felipe Nascimento", "Calebe Fernandes" ,
						"Maria Vitória Pires", "Diogo da Mota","Yasmin da Paz" ,
						"Maria Julia Sales","Juliana Duarte", "Kaique da Rocha",
						"Lucas Gabriel Sales"};

	char genero[10] = "HHHMHMMMHH";

	string matricula[10] = {"0x01", "0x02", "0x03", "0x04", "0x05", "0x06", "0x07",
							"0x08", "0x09", "0x0A"};
	int i;
	for (i=0; i<10; i++)
		insereNaLista(L, nome[i], genero[i], matricula[i]);
}
