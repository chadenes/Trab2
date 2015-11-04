#include<stdio.h>
#include<stdlib.h>

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
	}else{
		inserir(&(*raiz)->dir, k);
	}
}





no  busca (no **raiz, int k) {//fun��o que busca determinado elemento e devolve o n� em que ele se encontra, devolve null caso ele n exista
    if (*raiz == NULL){
    	printf("O elemento nao se encontra na arvore");
    	return;
	}
	if( (*raiz)->chave == k ){
		printf("O elemento se encontra na arvore");
		return;
	}
    if ((*raiz)->chave > k)
       return busca (&(*raiz)->esq, k);
    else
       return busca (&(*raiz)->dir, k);
}






void main(){
	no *raiz = NULL;
	int n, i, elemento;
	printf("Ola, por favor insira quantidade de numeros com que voce ira trabalhar \n nesta arvore:");
	scanf("%d", &n);  //recebo o n�mero de elementos que o usu�rio deseja utilizar
	printf("Agora insira os elementos:\n");
	for(i=1;i<=n;i++){             //usando um la�o de repeti��o eu recolho o valor de todos os elementos da �rvore
		printf("Elemento %d: ", i);
		scanf("%d", &elemento);
		inserir(&raiz, elemento);
	}
	printf("Escolha um elemento para verificar se ele esta na arvore: ");
	scanf("%d", &elemento);
	busca(&raiz, elemento);
	return ;
}
