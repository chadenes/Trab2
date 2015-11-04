#include<stdio.h>
#include<stdlib.h>

/* No início do programa estão escritas todas as funções que serão utilizadas 
ao decorrer do mesmo */




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
	}
	if((*raiz)->chave<k){
		inserir(&(*raiz)->dir, k);
	}
}





no  busca (no **raiz, int k) {//função que busca determinado elemento e devolve o nó em que ele se encontra, devolve null caso ele n exista
    if (*raiz == NULL){
    	printf("O elemento %d nao se encontra na arvore", k); //se o elemento não se encontrar na árvore é devolvida uma 
    	return;                                         //mensagem avisando isso
	}
	if( (*raiz)->chave == k ){
		printf("O elemento %d se encontra na arvore", k); //se o elemento se encontrar na árvore é devolvida uma mensagem avisando isso
		return;
	}
    if ((*raiz)->chave > k)     //essa parte da função indica "aonde" procurar o número, sabendo que os números que são
       return busca (&(*raiz)->esq, k); //maiores "vão" para a direita e os menores pra esquerda
    else
       return busca (&(*raiz)->dir, k);
}

no *doisfilhos(no *raiz){ //essa função foi criada para auxiliar na remoção de um nó que tem dois filhos
	if(raiz == NULL){     //foi necessária a criação da função pois os próprios filhos daquele nó podem ter 2 filhos
		return NULL;
	}else if(raiz->esq = NULL){
		return raiz;
	}else{
		return doisfilhos(raiz->esq);
	}
}


void remover (no **raiz, int elemento){     //função eu remove o valor desejado
	if(elemento < (*raiz)->chave){          //no caso de estarmos removendo uma função que tem um filho ou nenhum o problema se torna fácil
		remover(&(*raiz)->esq, elemento);
	}else if(elemento > (*raiz)->chave){
		remover(&(*raiz)->dir, elemento);
	}else if((*raiz)->esq!=NULL && (*raiz)->dir!=NULL){
		no *aux = NULL;
		aux = doisfilhos((*raiz)->dir);   //porém para remover um nó com dois filhos o problema se torna mais complicado
		(*raiz)->chave = aux->chave;      //para isso foi criada a função doisfilhos
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
	printf("\nAgora escolha um elemento para remover da arvore: ");
	scanf("%d", &elemento);
	remover(&raiz, elemento);
	busca(&raiz, elemento);
	return ;
}
