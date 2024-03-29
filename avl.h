typedef struct avl Avl;
typedef char String[50];

Avl* arv_criavazia();
Avl* arv_libera (Avl *a);
int abb_pertence (Avl* a, String);
void avl_imprime_pre(Avl* a);
void avl_imprime_in(Avl* a);
void avl_imprime_pos(Avl* a);
Avl* abb_busca(Avl* r, String v);
Avl* abb_insere(Avl* a, String v);
Avl* abb_retira (Avl* r, String v);
int avl_altura(Avl *a);
int avl_fator_balanceamento(Avl *a);
Avl* rot_dir(Avl *p);
Avl* rot_esq(Avl *p);
Avl* rot_esq_dir(Avl *p);
Avl* rot_dir_esq (Avl *p);
Avl *avl_balancear(Avl *a);
Avl* avl_insere(Avl* a, String v);
Avl* avl_retira (Avl* r, String v);
void avl_gravar_arquivo(FILE *arquivo, Avl* a);
void avl_notacaoTextual(Avl* a);
void avl_desenharArquivo(Avl* a, int ordem);
