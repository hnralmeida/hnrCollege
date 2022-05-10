/*
AUTORES: 	Henrique Almeida de Oliveira
			Luiz Eduardo Marchiori
Disciplina: Estrutura de Dados
Professor: Vanderson José Idelfonso Silva

Programa em linguagem C que implementa uma Lista aninhada formada em sua camada mais externa por uma lista duplamente encadeada de Cursos.
*/

int menu (){
	int opcao;
	do{
		printf("------------------------\n");
		printf("Bem vindo ao menu!\n");
		printf("Selecione uma opção: \n");
		printf("0 - Sair\n1 - Cursos\n2- Turmas\n3- Alunos\n");
		scanf("%d", &opcao);
	}while ((opcao < 0) || (opcao > 3));
	
	return opcao;
	
	 
}

int menuCurso (){
	int opcao;
	system("CLS");
	do{
		printf("------------------------\n");
		printf("Bem vindo ao menu de Cursos!\n");
		printf("Selecione uma opção: \n");
		printf("0 - Ir para o menu principal\n1 - Inserir Curso\n2- Excluir Curso\n3- Lista todos os cursos\n");
		scanf("%d", &opcao);
	}while ((opcao < 0) || (opcao > 3));
	switch(opcao){
	   case 1: adicionaCurso(); break;
	   case 2: excluirCurso(); break;
	   case 3: listarCurso(); break;
	}
	if (opcao ==0){
		menuPrincipal();
	}
}

int menuTurma(){
	int opcao;
	system("CLS");
	do{
		printf("------------------------\n");
		printf("Bem vindo ao menu de Turma!\n");
		printf("Selecione uma opção: \n");
		printf("0 - Ir para o menu principal\n1 - Inserir Turma\n2- Excluir Turma\n3- Listar todas as turmas\n");
		scanf("%d", &opcao);
	}while ((opcao < 0) || (opcao > 3));
	if (opcao ==0){
		menuPrincipal();
		}	
	switch(opcao){
	   case 1: adicionaTurma(); break;
	   case 2: excluirTurma(); break;
	   case 3: listarTurma(); break;
		}
}

int menuAluno (){
	int opcao;
	system("CLS");
	do{
		printf("------------------------\n");
		printf("Bem vindo ao menu de Alunos!\n");
		printf("Selecione uma opção: \n");
		printf("0 - Ir para o menu principal\n1 - Inserir Aluno\n2- Excluir Aluno\n3- Listar todos os alunos\n");
		scanf("%d", &opcao);
	}while ((opcao < 0) || (opcao > 3));
	if (opcao ==0){
		menuPrincipal();
		}	
	switch(opcao){
	   case 1: adicionaAluno(); break;
	   case 2: excluirAluno(); break;
	   case 3: listarAluno(); break;
	}
}

int menuPrincipal (){
	int op;
	//system("CLS");
		op = menu();
		switch(op){
		   case 1: menuCurso(); break;
		   case 2: menuTurma(); break;
		   case 3: menuAluno(); break;
			}
		if (op == 0){
			exit(0); 
		}		
}

int adicionaCurso(){
	printf("Adicionou Curso\n");
}

int excluirCurso(){
	printf("Excluiu Curso\n");
}
int listarCurso(){
	printf("Listou Curso\n");
}

int adicionaTurma(){
	printf("Adicionou Turma\n");
}
	
int excluirTurma(){
	printf("Excluiu Turma\n");
}

int listarTurma(){
	printf("Listou Turma\n");
}

int adicionaAluno(){
	printf("Adicionou aluno\n");
}

int excluirAluno(){
	printf("Excluiu aluno\n");
}

int listarAluno(){
	printf("Alistou aluno\n");
}
int main (){
	while(1){
		menuPrincipal();
	}
}

typedef char string[40];

typedef struct tipoCurso TCurso;

typedef struct tipoDisciplina TDisciplina;

typedef struct tipoTurma TTurma;

typedef struct tipoTurma {
	TTurma *prox, *ante;
	string nomeTurma;
	string semestreLetivo;
//	TAlunos *alunos;
}TTurma;

typedef struct tipoDisciplina {
	TDisciplina *prox, *ante;
	int cargaHoraria;
	TTurma *turma;
}TDisciplina;

typedef struct tipoCurso {
	TCurso *prox, *ante;
	string nomeCurso;
	string *Disciplina;
}TCurso;

void inicializaCurso(TCurso *curso){
	curso->ante = NULL;
	curso->prox = NULL;
	curso->Disciplina = NULL;
	strcpy(curso->nomeCurso,"0");
}

void adicionaCurso(TCurso *curso, string nomeCurso){	
	TCurso *aux1, *aux2;
	aux1 = curso;
	
	if(!strcpy(aux1->nomeCurso, "0")){
		strcpy(aux1->nomeCurso, nomeCurso);
	}else{
		aux2=aux1->prox;
		while(aux2 != NULL && strcmp(aux1->nomeCurso, aux2->nomeCurso)){
			aux1 = aux2;
			aux2 = aux2->prox;
		};
		
	}
  
  while (atual != NULL){
  	if(atual->valor >= novo->valor){
		inserido = 1;
		
		break;
	}
	
	atual = atual->prox; 
  }
  
  if (!inserido){
	 L->fim->prox = novo;
	 novo->ante = L->fim;
	 L->fim = novo;	
  }
}

void main(){
	TCurso curso;
	inicializaCurso(&curso);
	adicionaCurso(&curso, "nomeCurso");
	printf("\nNome: %s", curso.nomeCurso);
}
