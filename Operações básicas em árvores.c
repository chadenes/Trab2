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
	printf("\nAgora escolha um elemento para remover da arvore: ");
	scanf("%d", &elemento);
	remover(&raiz, elemento);
	busca(&raiz, elemento);
	return ;
}
