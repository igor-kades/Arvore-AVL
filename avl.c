#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

struct avl{
    String info;
    struct avl* esq;
    struct avl* dir;
};

Avl* arv_criavazia(){
    return NULL;
}

Avl* arv_libera (Avl *a){
    if(a == NULL)
        return NULL;

    a->esq = arv_libera(a->esq);
    a->dir = arv_libera(a->dir);
    free(a);
    return NULL;
}

int abb_pertence (Avl* a, String v){
    if(a == NULL)
        return 0;
    else{
        return (strcmp(a->info, v) == 0) || abb_pertence(a->esq, v) || abb_pertence(a->dir, v);
    }
}

void avl_imprime_pre(Avl* a){
    if(a != NULL){
        printf("%s\n", a->info);
        avl_imprime_pre(a->esq);
        avl_imprime_pre(a->dir);
    }
}

void avl_imprime_in(Avl* a){
    if(a != NULL){
        avl_imprime_in(a->esq);
        printf("%s\n", a->info);
        avl_imprime_in(a->dir);
    }
}

void avl_imprime_pos(Avl* a){
    if(a != NULL){
        avl_imprime_pos(a->esq);
        avl_imprime_pos(a->dir);
        printf("%s\n", a->info);
    }
}

Avl* abb_busca(Avl* r, String v){
    if(r == NULL)
        return NULL;
    if(strcmp(r->info, v) > 0)
        return abb_busca(r->esq, v);
    if(strcmp(r->info, v) < 0)
        return abb_busca(r->dir, v);
    return r;
}

Avl* abb_insere(Avl* a, String v){
    if(a == NULL){
        a = (Avl*)malloc(sizeof(Avl));
        strcpy(a->info, v);
        a->esq = a->dir = NULL;
    }else{
        if(strcmp(a->info, v) > 0)
            a->esq = abb_insere(a->esq, v);
        else
            a->dir = abb_insere(a->dir, v);
    }
    return a;
}

Avl* abb_retira (Avl* r, String v){
    if (r == NULL)
        return NULL;
    else if (r->info > v)
            r->esq = abb_retira(r->esq, v);
    else if (r->info < v)
            r->dir = abb_retira(r->dir, v);
    else {      /* achou o nó a remover */
     /* nó sem filhos */
        if (r->esq == NULL && r->dir == NULL) {
            free (r);
            r = NULL;
        }
        /* nó só tem filho à direita */
        else if (r->esq == NULL) {
            Avl* t = r;
            r = r->dir;
            free (t);
        }
        /* só tem filho à esquerda */
        else if (r->dir == NULL) {
        Avl* t = r;
        r = r->esq;
        free (t);
        }
        /* nó tem os dois filhos */
        else {
            Avl* f = r->esq;
            while (f->dir != NULL) {
                f = f->dir;
            }
            strcpy(r->info, f->info); /* troca as informações */
            strcpy(f->info, v);
            r->esq = abb_retira(r->esq, v);
        }
    }
    return r;
}

int avl_altura(Avl *a){
	int altura_esq = 0;
	int altura_dir = 0;

	if(a->esq)  altura_esq = avl_altura(a->esq);
	if(a->dir)  altura_dir = avl_altura(a->dir);

	return altura_dir > altura_esq ? ++altura_dir : ++altura_esq;
}

int avl_fator_balanceamento(Avl *a){
	int fb = 0;

	if(a->esq)
        fb += avl_altura(a->esq);
	if(a->dir)
	fb -= avl_altura(a->dir);

	return fb;
}

Avl* rot_dir(Avl *p){
    Avl* q, *temp;
    q = p->esq;
    temp = q->dir;
    q->dir = p;
    p->esq = temp;
    return q;
}

Avl* rot_esq(Avl *p){
    Avl* q, *temp;
    q = p->dir;
    temp = q->esq;
    q->esq = p;
    p->dir = temp;
    return q;
}

Avl* rot_esq_dir(Avl *p){
    p->esq = rot_esq(p->esq);
    p = rot_dir(p);
    return p;
}

Avl* rot_dir_esq (Avl *p){
    p->dir = rot_dir(p->dir);
    p = rot_esq(p);
    return p;
}

Avl *avl_balancear(Avl *a){
	Avl *novaraiz = NULL;

	/* Balanceia as sub-arvores se existirem */
	if(a->esq)
		a->esq  = avl_balancear(a->esq);
	if(a->dir)
		a->dir = avl_balancear(a->dir);

	int fb = avl_fator_balanceamento(a);

	if(fb >= 2){
		if(avl_fator_balanceamento(a->esq ) <= -1)
			novaraiz = rot_esq_dir(a);
		else
			novaraiz = rot_dir(a);
	}else
        if(fb <= -2){
            if(avl_fator_balanceamento(a->dir) >= 1)
                novaraiz = rot_dir_esq(a);
            else
                novaraiz = rot_esq(a);
        }else{
            novaraiz = a;
        }

	return(novaraiz);
}

Avl* avl_insere(Avl* a, String v){
    a = abb_insere(a, v);
    int fb = avl_fator_balanceamento(a);
    if(fb >= 2 || fb <= -2)     //Verifica se a árvore precisa ser balanceada após a inserção
        a = avl_balancear(a);       //Balanceia a árvore
    return a;
}

Avl* avl_retira (Avl* a, String v){
    a = abb_retira(a, v);
    int fb = avl_fator_balanceamento(a);
    if(fb >= 2 || fb <= -2)     //Verifica se a árvore precisa ser balanceada após a inserção
        a = avl_balancear(a);       //Balanceia a árvore
    return a;
}

void gravar_arquivo(FILE *arquivo, Avl* a){
    if(arquivo != 0){
        if(a){
            fputc(' ', arquivo);                //Adiciona um espaço antes da palavra
            fprintf(arquivo, a->info);          //Escreve a string no arquivo
            gravar_arquivo(arquivo, a->esq);    //Faz a mesma operação na sub árvore esquerda
            gravar_arquivo(arquivo, a->dir);    //Faz a mesma operação na sub árvore direita
        }
    }
}

void avl_gravar_arquivo(FILE *arquivo, Avl* a){
    if(arquivo != 0){
        if(a){
            fprintf(arquivo, a->info);          //Escreve a string no arquivo sem um espaço antes
            gravar_arquivo(arquivo, a->esq);    //Chama a função de gravar com espaço para a sub árvore esquerda
            gravar_arquivo(arquivo, a->dir);    //Chama a função de gravar com espaço para a sub árvore direita
        }
    }
}

void avl_notacaoTextual(Avl* a){
    if(a){
        printf("<%s ", a->info);
        avl_notacaoTextual(a->esq);
        printf(" ");
        avl_notacaoTextual(a->dir);
        printf(" >");
    }else{
        printf("<>");
    }
}

void avl_desenharArquivo(Avl* a, int ordem){
    if(a){
        int i;
        for(i=0; i<ordem; i++){     //Calcula a indentação
            printf("\t");          //Imprime o "|" para representar a estrutura de arquivo
        }
        printf("%s\n", a->info);   //Imprime a info
        avl_desenharArquivo(a->esq, ordem + 1);     //Chamada recursiva para a sub árvore esquerda, incrementando a indentação
        avl_desenharArquivo(a->dir, ordem + 1);     //Chamada recursiva para a sub árvore direita, incrementando a indentação
    }
}
