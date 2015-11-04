#include<stdio.h>
#include<stdlib.h>

struct arvore{           //criado o tipo de struct que irá compor nossa árvore de busca
	int chave;
	struct arvore *esq;
	struct arvore *dir;
};
typedef struct arvore no; //definindo essa struct como nó, para ficar mais rápido de escrever


void inserir (no **raiz, int k){//função que insere novos nós na árvore
	if(*raiz == NULL){
		no *aux = (no *)malloc(sizeof(no)); //cria uma variável auxiliar com alocação dinÂmica de memória
		aux->chave = k;
		aux->dir=aux->esq=NULL;
		*raiz = aux;
		return;
	}
	if((*raiz)->chave > k){        //usando recursão fazemos com que o nó, se maior que o elemento analisado á para a direita 
		inserir(&(*raiz)->esq, k);//e se for menor para a esquerda
	}else{
		inserir(&(*raiz)->dir, k);
	}
}





no  busca (no **raiz, int k) {//função que busca determinado elemento e devolve o nó em que ele se encontra, devolve null caso ele n exista
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
	scanf("%d", &n);  //recebo o número de elementos que o usuário deseja utilizar
	printf("Agora insira os elementos:\n");
	for(i=1;i<=n;i++){             //usando um laço de repetição eu recolho o valor de todos os elementos da árvore
		printf("Elemento %d: ", i);
		scanf("%d", &elemento);
		inserir(&raiz, elemento);
	}
	printf("Escolha um elemento para verificar se ele esta na arvore: ");
	scanf("%d", &elemento);
	busca(&raiz, elemento);
	return ;
}
