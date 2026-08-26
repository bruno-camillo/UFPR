#ifndef ARVBINBUSCA
#define AVRBINBUSCA

// estrutura de dados para a árvore binária de busca
typedef struct arvore {
    nodo *raiz;
    int tam; // numero de nodos da arvore
} arvore;

// definição do nodo da árvore binária de busca
typedef struct nodo {
    nodo *pai;
    nodo *esq;
    nodo *dir;
    int chave;
    void *conteudo;
    int altura;
} nodo;

// funções para manipular a árvore binária de busca

// inicializa a árvore A, alocando memória para ela e setando a raiz como NULL
int tree_build (arvore **A);

// inicializa o nodo n, alocando memória para ele e setando os ponteiros para NULL
int nodo_build (nodo **n, int chave, void *conteudo);

// desaloca a memória alocada para a árvore A e seus nodos
int tree_free (arvore *A);

// libera a memória alocada para o nodo n e seus filhos
int nodo_free (nodo *n);

// imprime a arvore seguindo as chaves da menor para a maior
void inorder_tree_walk (nodo * n);

// imprime a arvore seguindo a notação polonesa
void preorder_tree_walk (nodo * n);

// imprime a arvore seguindo a notação polonesa reversa
void posorder_tree_walk (nodo * n);

// realiza a busca de uma chave na arvore, a partir da raiz ou de outra subarvore
// funciona de maneira recursiva
// retorna um ponteiro para o nodo com essa chave
nodo * tree_search (nodo * n, int chave);

// mesma função do tree_search porém é executado de maneira iterativa
nodo * it_tree_search (nodo *n, int chave);

//min e max
// retorna um ponteiro para a menor chave da árvore
nodo * tree_minimum (nodo *n);

// retorna um ponteiro para a maior chave da árvore
nodo * tree_maximum (nodo *n);

//sucessor
// retorna um ponteiro para o sucessor do nodo n
nodo * tree_successor (nodo *n);

// inserção
// insere o novo nodo n na árvore A
nodo * tree_insert (arvore *A, nodo *n);

//transplante
// substitui a subárvore enraizada em u pela subárvore enraizada em v
// o pai de u passa a ser pai de v, e o pai de v passa a ser pai de u
int transplant (arvore *A, nodo *u, nodo *v);

// delete
// remove o nodo n da árvore A
int tree_delete (arvore *A, nodo *n);

#endif 