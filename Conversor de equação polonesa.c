#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Operacao{
	char* oper;
	struct Operacao* dir;
	struct Operacao* esq;
};

int para_int(char* string){
	int i = 0;
	while(*string != '\0'){
		i *= 10;
		i += *string - '0';
		++string;
	}
	return i;
}

/*
  Retorna parte de uma string.

 */
char* extrair(char* str, int pos, int tam){
	char* resultado = (char*)calloc(tam, sizeof(char));
	int i = 0;
	for(;i < tam-1 && str[i+pos] != '\0'; ++i){
		resultado[i] = str[i+pos];
	}
	resultado[tam-1] = '\0';
	return resultado;
}	

/*
 Gera a árvore de operações.
 */
struct Operacao* gerar(char* string, int tamanho){
	struct Operacao* no = (struct Operacao*)calloc(1, sizeof(struct Operacao));
	if(string[0] >= '0' && string[0] <= '9'){
		no->oper = string;
		return no;
	}
	no->oper = (char*)malloc(2*sizeof(char));
	no->oper[0] = string[0];
	no->oper[1] = '\0';
	int pos = tamanho-1;
	int fase = 0;
	while( fase != 2){
		if(fase == 0){
			if((string[pos] >= '0' && string[pos] <= '9') || string[pos] == ' '){
				--pos;
			} else {
				++fase;
			}
		} else if(fase == 1){
			if((!(string[pos] >= '0' && string[pos] <= '9') || string[pos] == ' ') && pos > 0){
				--pos;
			} else {
				++fase;
			}
		}
	}
	if(pos == 0){
		int tam_dir = 0;
		while(string[tamanho - tam_dir] != ' '){
			++tam_dir;
		}
		no->dir = gerar(extrair(string, tamanho-tam_dir+1, tam_dir), tam_dir-1);
		no->esq = gerar(extrair(string, 2, tamanho-tam_dir-1), tamanho-tam_dir-2);
	} else {
		no->dir = gerar(extrair(string, pos+2, tamanho-pos-1), tamanho-pos-2);
		no->esq = gerar(extrair(string, 2, pos), pos-1);
	}
	return no;
}

/*
  Imprime em notação polonesa 
*/
void not_polonesa(struct Operacao* raiz){
	if(raiz != NULL){
		printf("%s ", raiz->oper);
		not_polonesa(raiz->esq);
		not_polonesa(raiz->dir);
	}
}
void not_pol_reversa(struct Operacao* raiz){
	if(raiz != NULL){
		not_pol_reversa(raiz->esq);
		not_pol_reversa(raiz->dir);
		printf("%s ", raiz->oper);
	}
}
/*
 Imprime em notação infixa (em ordem).
 */
void infixa(struct Operacao* raiz){
	if(raiz != NULL){
		if(raiz->esq != NULL)
			printf("( ");
		infixa(raiz->esq);
		printf("%s ", raiz->oper);
		infixa(raiz->dir);
		if(raiz->esq != NULL)
			printf(")");
	}
}
/*
Resolve
 */
double resolver(struct Operacao* raiz){
	double res = 0;
	if(raiz->esq != NULL && raiz->dir != NULL){
		res = resolver(raiz->esq);
		switch(raiz->oper[0]){
			case '+':
				res += resolver(raiz->dir);
				break;
			case '-':
				res -= resolver(raiz->dir);
				break;
			case '*':
				res *= resolver(raiz->dir);
				break;
			case '/':
				res /= resolver(raiz->dir);
				break;
			case '^':
				res = pow(res, resolver(raiz->dir));
				break;
			default:
				printf("\nERRO: operacao desconhecida.\n");
				return 0.0;
		}
	} else if(raiz->esq == NULL && raiz->dir == NULL){
		res = para_int(raiz->oper);
	} else {
		printf("\nERRO: expressao mal formulada.\n");
		return 0.0;
	}
	return res;
}

/*
 Dá o tamanho da string
 */
int tamanho(char* string){
	int tam = 0;
	while(*(string+tam) != '\0'){
		++tam;
	}
	return tam;
}
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
char* obter_linha(){
	int tam = 0;
	char buffer[128];
	char c;
	while(tam == 0){
		while((c = getchar()) != '\n' && c != EOF){
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

int main(){
	struct Operacao* raiz = NULL;
	char* expr = (char*)calloc(256, sizeof(char));
	printf("Insira a expressao.\n");
	expr = obter_linha();
	raiz = gerar(expr, tamanho(expr));
	printf("Escolha a operacao de acordo com o numero.\n");
	printf("1 - notacao polonesa.\n");
	printf("2 - RPN.\n");
	printf("3 - infixa.\n");
	printf("4 - Solucionar.\n");
	printf("9 - Out.\n");
	printf("0 - Main.\n\n");
	char* opcao = obter_palavra();
	while(opcao[0] != '9'){
		switch(opcao[0]){
			case '1':
				printf("Em notacao polonesa:\n");
				not_polonesa(raiz);
				printf("\n");
				break;
			case '2':
				printf("Em RPN:\n");
				not_pol_reversa(raiz);
				printf("\n");
				break;
			case '3':
				printf("Em infixa:\n");
				infixa(raiz);
				printf("\n");
				break;
			case '4':
				printf("Solucionar: %f", resolver(raiz));
				printf("\n");
				break;
			case '0':
				printf("1 -notacao polonesa.\n");
				printf("2 -RPN.\n");
				printf("3 -infixa.\n");
				printf("4 -Solucionar.\n");
				printf("9 -Out.\n");
				printf("0 -Main.\n");
				break;
		}
		printf("\n");
		free(opcao);
		opcao = obter_palavra();
	}
	return 0;
}
