#include <stdio.h>
#include <stdlib.h>

struct pessoa{
	char* Id;
	struct pessoa* pai;
	struct pessoa* mae;
};

struct Lista{
	struct pessoa* valor;
	struct Lista* prox;
};

struct pessoa* criar(char Id[]){
	struct pessoa* novo = (struct pessoa*)malloc(sizeof(struct pessoa));
	novo->Id = Id;
	novo->pai = NULL;
	novo->mae = NULL;
	return novo;
}

//função que compara se duas strings são iguais
int igual(char str1[], char str2[]){
	while(*str1 != '\0' && str2 != '\0' && *str1 == *str2){
		++str1;
		++str2;
	}
	return (*str1 == *str2);
}

/**
 * Retorna uma palavra inserida via entrada padrão.
 */
char* obter_palavra(){
	int tam = 0;
	char buffer[128];
	char c;
	while(tam == 0){
		while((c = getchar()) != ' ' && c != '\n' && c != EOF){
			buffer[tam] = c;
			++tam;
		}
	}
	buffer[tam] = '\0';
	char* end = (char*)malloc((tam+1)*sizeof(char));
	int i;
	for(i = 0; i < tam+1; i++){
		end[i] = buffer[i];
	}
	return end;
}

/**
 * Efetua uma busca de varredura em uma árvore.
 *
 * chave - Chave a ser procurada.
 * raiz  - Raiz da árvore.
 */
struct pessoa* busca(char chave[], struct pessoa* raiz){
	struct Lista* inicio = (struct Lista*)malloc(sizeof(struct Lista));
	struct Lista* fim = inicio;
	inicio->valor = raiz;
	while(inicio != NULL && !igual(chave, inicio->valor->Id)){	
		if(inicio->valor->mae != NULL){
			struct Lista* no = (struct Lista*)malloc(sizeof(struct Lista));
			no->valor = inicio->valor->mae;
			no->prox = NULL;
			fim->prox = no;
			fim = fim->prox;
		}
		if(inicio->valor->pai != NULL){
			struct Lista* no = (struct Lista*)malloc(sizeof(struct Lista));
			no->valor = inicio->valor->pai;
			no->prox = NULL;
			fim->prox = no;
			fim = fim->prox;
		}
		struct Lista* l = inicio;
		inicio = inicio->prox;
		free(l);
	}
	return (inicio == NULL)?NULL:inicio->valor;
}
	
//função que insere o nó na árvore
void inserir(char filho[], char pai[], char mae[], struct pessoa* raiz){
	struct pessoa* no = busca(filho, raiz);
	if(no != NULL){
		no->pai = criar(pai);
		no->mae = criar(mae);
	}
}

//função que imprime a pessoa e seus antepassados

void imprimir(char filho[], struct pessoa* raiz){
	struct Lista* inicio = (struct Lista*)malloc(sizeof(struct Lista));
	inicio->valor = busca(filho, raiz);
	inicio->prox = NULL;
	struct Lista* fim = inicio;
	int geracao_atual = 1;
	int geracao_seg = 0;
	while(inicio != NULL){
		printf("%s ", inicio->valor->Id);	
		if(inicio->valor->pai != NULL){
			++geracao_seg;
			struct Lista* no = (struct Lista*)malloc(sizeof(struct Lista));
			no->valor = inicio->valor->pai;
			no->prox = NULL;
			fim->prox = no;
			fim = fim->prox;
		}
		if(inicio->valor->mae != NULL){
			++geracao_seg;
			struct Lista* no = (struct Lista*)malloc(sizeof(struct Lista));
			no->valor = inicio->valor->mae;
			no->prox = NULL;
			fim->prox = no;
			fim = fim->prox;
		}
		--geracao_atual;
		if(geracao_atual == 0){
			printf("\n");
			geracao_atual = geracao_seg;
			geracao_seg = 0;
		}
		struct Lista* l = inicio;
		inicio = inicio->prox;
		free(l);
	}
}
//função que imprime o grau de parentesco entre duas pessoas, recebendo as duas pessoas e a raiz da arvore como parâmetro

void grau(char par1[], char par2[], struct pessoa* raiz){
	struct Lista* inicio = (struct Lista*)malloc(sizeof(struct Lista));
	inicio->valor = raiz;
	inicio->prox = NULL;
	struct Lista* fim = inicio;
	int geracao_atual = 1;
	int geracao_seg = 0;
	int ger1 = 0;
	int ger2 = 0;
	int enc1 = 0;
	int enc2 = 0;
	while(inicio != NULL && (enc1 == 0 || enc2 == 0)){
		if(igual(inicio->valor->Id, par1)){
			enc1 = 1;
		}
		if(igual(inicio->valor->Id, par2)){
			enc2 = 1;
		}
		if(inicio->valor->pai != NULL){
			++geracao_seg;
			struct Lista* no = (struct Lista*)malloc(sizeof(struct Lista));
			no->valor = inicio->valor->pai;
			no->prox = NULL;
			fim->prox = no;
			fim = fim->prox;
		}
		if(inicio->valor->mae != NULL){
			++geracao_seg;
			struct Lista* no = (struct Lista*)malloc(sizeof(struct Lista));
			no->valor = inicio->valor->mae;
			no->prox = NULL;
			fim->prox = no;
			fim = fim->prox;
		}
		--geracao_atual;
		if(geracao_atual == 0){
			if(enc1 == 0){
				++ger1;
			}
			if(enc2 == 0){
				++ger2;
			}
			geracao_atual = geracao_seg;
			geracao_seg = 0;
		}
		struct Lista* l = inicio;
		inicio = inicio->prox;
		free(l);
	}
	int res = abs(ger1 - ger2);
	struct pessoa* p1 = busca(par1, raiz);
	struct pessoa* p2 = busca(par2, raiz);
	if(p1 == NULL || p2 == NULL){
		res = 0;
	} else if(busca(par2, p1) == NULL && busca(par1, p2) == NULL){
		res = 0;
	}
	printf("O grau de pessoasco entre %s e %s eh %i\n", par1, par2, res);
}

//função que irá imprimir a árvore em labelled bracketing, o que possibilita fazer o gráfico da árvore em alguns sites
void imprimir_lb(struct pessoa* raiz){
	printf("[");
	if(raiz != NULL){
		printf("%s", raiz->Id);
		if(raiz->pai != NULL){
			imprimir_lb(raiz->pai);
			printf(" ");
		}
		if(raiz->mae != NULL){
			imprimir_lb(raiz->mae);
		}
	}
	printf("]");
}

int main(){
	struct pessoa* raiz = (struct pessoa*)malloc(sizeof(struct pessoa));
	printf("Digite a quantidade inicial de tuplas que ira inserir,\n");
	printf("lembre-se de que cada tupla deve ser inserida em uma linha \ne no formado explicado no pdf : ");
	int tam;
	scanf("%i", &tam);
	int i;
	char* Id = obter_palavra();
	raiz->Id = Id;
	char* pai = obter_palavra();
	char* mae = obter_palavra();
	inserir(Id, pai, mae, raiz);
	for(i = 1; i < tam; ++i){
		Id = obter_palavra();
		pai = obter_palavra();
		mae = obter_palavra();
		inserir(Id, pai, mae, raiz);
	}
	free(pai);
	free(Id);
	free(mae);
	printf("Escolha o numero da operacao que deseja utilizar, \nseguido pela informacao que eh necessaria em cada caso\n");
	printf("1 - Inserir.\n");
	printf("2 - Imprimir árvore.\n");
	printf("3 - Antepassados.\n");
	printf("4 - Labelled bracketing.\n");
	printf("9 - Sair.\n");
	printf("0 - Menu.\n");
	char* opcao = obter_palavra();
	while(opcao[0] != '9'){
		switch(opcao[0]){
			case '1':
				Id = obter_palavra();
				pai = obter_palavra();
				mae = obter_palavra();
				inserir(Id, pai, mae, raiz);
				free(pai);
				free(Id);
				free(mae);
				break;
			case '2':
				imprimir(raiz->Id, raiz);
				break;
			case '3':
				imprimir(obter_palavra(), raiz);
				break;
			case '4':
				imprimir_lb(raiz);
				printf("\n");
				break;
			case '0':		
				printf("1 - Inserir.\n");
				printf("2 - Imprimir árvore.\n");
				printf("3 - Antepassados.\n");
				printf("4 - Labelled bracketing.\n");
				printf("9 - Sair.\n");
				printf("0 - Menu.\n");
				break;
			default:
				break;
		}
		opcao = obter_palavra();
	}
	return 0;
}





	
	
