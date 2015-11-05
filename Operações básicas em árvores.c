#include<stdio.h>
#include<stdlib.h>

/* No in�cio do programa est�o escritas todas as fun��es que ser�o utilizadas 
ao decorrer do mesmo */




struct arvore{           //criado o tipo de struct que ir� compor nossa �rvore de busca
	int chave;
	struct arvore *esq;
	struct arvore *dir;
};
typedef struct arvore no; //definindo essa struct como n�, para ficar mais r�pido de escrever


void inserir (no **raiz, int k){//fun��o que insere novos n�s na �rvore
	if(*raiz == NULL){
		no *aux = (no *)malloc(sizeof(no)); //cria uma vari�vel auxiliar com aloca��o din�mica de mem�ria
		aux->chave = k;
		aux->dir=aux->esq=NULL;
		*raiz = aux;
		return;
	}
	if((*raiz)->chave > k){        //usando recurs�o fazemos com que o n�, se maior que o elemento analisado � para a direita 
		inserir(&(*raiz)->esq, k);//e se for menor para a esquerda
	}
	if((*raiz)->chave<k){
		inserir(&(*raiz)->dir, k);
	}
}





no  busca (no **raiz, int k) {//fun��o que busca determinado elemento e devolve o n� em que ele se encontra, devolve null caso ele n exista
    if (*raiz == NULL){
    	printf("O elemento %d nao se encontra na arvore", k); //se o elemento n�o se encontrar na �rvore � devolvida uma 
    	return;                                         //mensagem avisando isso
	}
	if( (*raiz)->chave == k ){
		printf("O elemento %d se encontra na arvore", k); //se o elemento se encontrar na �rvore � devolvida uma mensagem avisando isso
		return;
	}
    if ((*raiz)->chave > k)     //essa parte da fun��o indica "aonde" procurar o n�mero, sabendo que os n�meros que s�o
       return busca (&(*raiz)->esq, k); //maiores "v�o" para a direita e os menores pra esquerda
    else
       return busca (&(*raiz)->dir, k);
}

no *doisfilhos(no *raiz){ //essa fun��o foi criada para auxiliar na remo��o de um n� que tem dois filhos
	if(raiz == NULL){     //foi necess�ria a cria��o da fun��o pois os pr�prios filhos daquele n� podem ter 2 filhos
		return NULL;
	}else if(raiz->esq = NULL){
		return raiz;
	}else{
		return doisfilhos(raiz->esq);
	}
}


void remover (no **raiz, int elemento){     //fun��o eu remove o valor desejado
	if(elemento < (*raiz)->chave){          //no caso de estarmos removendo uma fun��o que tem um filho ou nenhum o problema se torna f�cil
		remover(&(*raiz)->esq, elemento);
	}else if(elemento > (*raiz)->chave){
		remover(&(*raiz)->dir, elemento);
	}else if((*raiz)->esq!=NULL && (*raiz)->dir!=NULL){
		no *aux = NULL;
		aux = doisfilhos((*raiz)->dir);   //por�m para remover um n� com dois filhos o problema se torna mais complicado
		(*raiz)->chave = aux->chave;      //para isso foi criada a fun��o doisfilhos
		remover(&(*raiz)->dir, (*raiz)->chave);
	}
	else{
		no *aux = (*raiz);
		if((*raiz)->esq==NULL){
			(*raiz)=(*raiz)->dir;
		}
		else{
			(*raiz)=(*raiz)->esq;
		}
		free(aux);
	}
}



void ordem(no *raiz){ //fun��o que imprime os valores da �rvore em ordem
	if(raiz == NULL){
		return;
	}
	ordem(raiz->esq);
	printf("%d ", raiz->chave);
	ordem(raiz->dir);
	return;
}


void preordem(no *raiz){ //fun��o que imprime os valores da �rvore em "preordem"
	if(raiz == NULL){
		return;
	}
	printf("%d ", raiz->chave);
	preordem(raiz->esq);
	preordem(raiz->dir);
	return;
}


void posordem(no *raiz){ //fun��o que imprime os valores da �rvore em "posordem"
	if(raiz == NULL){
		return;
	}
	posordem(raiz->esq);
	posordem(raiz->dir);
	printf("%d ", raiz->chave);
	return;
}


void lbracketing(no *raiz){ //essa fun��o imprimir� a �rvore no formato de co
	printf("[");
	if(raiz!=NULL){
		printf("%d", raiz->chave);
		lbracketing(raiz->esq);
		lbracketing(raiz->dir);
	}
	printf("]");
	return;
}




/*Todas as fun��es acima ser�o usadas no decorrer do programa, a fun��o que vem agora
� o menu, aonde o usu�rio poder� escolher o que deseja fazer com a �rvore que entrou */




void menu(no *raiz){
	int j = 1;
	int n, i;
	printf("Agora que voce ja selecionou os elementos da arvore,\nselecione o que deseja fazer: ");
	while(j!=0){
		printf("\n\n1 : Imprime a arvore em ordem\n2 : Imprime a arvore em preordem\n3 : Imprime a arvore em posordem\n");
		printf("4 : Imprime em Labelled Bracketing\n5 : Buscar um numero\n6 : Remover um numero\n7 : Inserir um numero\n");
		printf("8 : Sair\n");
		scanf("%d", &i);
		switch(i){  //para cada n�mero que o usu�rio entrar o programa realizar� um comando diferente
			case 1:
				ordem(raiz);
			break;
			case 2:
				preordem(raiz);
			break;
			case 3:
				posordem(raiz);
			break;
			case 4:
				lbracketing(raiz);
			break;
			case 5:
				printf("\nEscreva o elemento que deseja buscar: ");
				scanf("%d", &n);
				busca(&raiz, n);
			break;
			case 6:
				printf("\nEscreva o elemento que deseja remover, escreva um que esta na arvore! :");	
				scanf("%d", &n);
				remover(&raiz, n);
			break;
			case 7:
				printf("Digite o elemento que deseja inserir, digite um que nao esteja na arvore! :");
				scanf("%d", &n);
				inserir(&raiz, n);
			break;
			case 8:
				j=0;
			break;	
			default	:
				printf("Insira um valor v�lido!\n");
			break;		
								
		}
	}
	return;
}






void main(){
	no *raiz = NULL;
	int n, i, elemento;
	printf("Ola, por favor insira quantidade de numeros com que voce ira trabalhar \nnesta arvore:");
	scanf("%d", &n);  //recebo o n�mero de elementos que o usu�rio deseja utilizar
	printf("Agora insira os elementos:\n");
	for(i=1;i<=n;i++){             //usando um la�o de repeti��o eu recolho o valor de todos os elementos da �rvore
		printf("Elemento %d: ", i);
		scanf("%d", &elemento);
		inserir(&raiz, elemento);
	}
	menu(raiz);
	return ;
}
