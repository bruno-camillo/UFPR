#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))


typedef struct no {
    int chave;
    int fb; // fator de balanceamento
    struct no *pai;
    struct no *esq;
    struct no *dir;
} no;


typedef struct {
    no *raiz;
} arvore;


no* tree_insert(arvore *t, no *z) {
    no *x, *y;

    x = t->raiz;
    y = NULL;
    while(x != NULL) {
        y = x;
        if(z->chave < x->chave)
            x = x->esq;
        else
            x = x->dir;
    }
    z->pai = y;
    if(y == NULL)
        t->raiz = z;
    else if(z->chave < y->chave)
        y->esq = z;
    else
        y->dir = z;
    return y;
}


void transplant(arvore *t, no *u, no *v) {
    if(u->pai == NULL)
        t->raiz = v;
    else if(u == u->pai->esq)
        u->pai->esq = v;
    else
        u->pai->dir = v;
    if(v != NULL)
        v->pai = u->pai;
}


no* tree_minimum(no *x) {
    while(x->esq != NULL)
        x = x->esq;
    return x;
}


no* tree_delete(arvore *t, no *z) {
    no *x, *y;

    x = z->pai;
    if(z->esq == NULL)
        transplant(t, z, z->dir);
    else if(z->dir == NULL)
        transplant(t, z, z->esq);
    else {
        y = tree_minimum(z->dir);
        x = y->pai;
        if(y != z->dir) {
            transplant(t, y, y->dir);
            y->dir = z->dir;
            y->dir->pai = y;
        }
        transplant(t, z, y);
        y->esq = z->esq;
        y->esq->pai = y;
    }
    return x;
}


no* rot_esq(no *p) {
    no *q;

    q = p->dir;
    p->dir = q->esq;
    if(p->dir)
        p->dir->pai = p;
    q->esq = p;
    q->pai = p->pai;
    p->pai = q;    
    p->fb = p->fb - 1 - MAX(q->fb, 0);
    q->fb = q->fb - 1 + MIN(p->fb, 0);
    return q;
}


no* rot_dir(no *p) {
    no *q;

    q = p->esq;
    p->esq = q->dir;
    if(p->esq)
        p->esq->pai = p;
    q->dir = p;
    q->pai = p->pai;
    p->pai = q;    
    p->fb = p->fb + 1 - MIN(q->fb, 0);
    q->fb = q->fb + 1 + MAX(p->fb, 0);
    return q;
}


no* rot_esqdir(no *p) {
    p->esq = rot_esq(p->esq);
    p->esq->pai = p;
    return rot_dir(p);
}


no* rot_diresq(no *p) {
    p->dir = rot_dir(p->dir);
    p->dir->pai = p;
    return rot_esq(p);
}

no* avl_balance(no *x) {
    int fb;
    no *y;

    y = x;
    // Se o fator de balanceamento de x for menor que -1, 
    // significa que a subárvore esquerda de x ficou mais alta do que a subárvore direita, 
    // e é necessário fazer uma rotação para equilibrar a árvore.
    if(x->fb < -1) { 
        // Se o filho da esquerda de x tem fator de balanceamento positivo, é necessário fazer uma rotação dupla esquerda-direita
        if(x->esq->fb > 0) 
            y = rot_esqdir(x);
        else
            // Caso contrário, é necessário fazer apenas uma rotação simples à direita
            y = rot_dir(x);
    } 
    // Se o fator de balanceamento de x for maior que 1, 
    // significa que a subárvore direita de x ficou mais alta do que a subárvore esquerda, 
    // e é necessário fazer uma rotação para equilibrar a árvore.
    else if(x->fb > 1) { 
        // Se o filho da direita de x tem fator de balanceamento negativo, é necessário fazer uma rotação dupla direita-esquerda
        if(x->dir->fb < 0)
            y = rot_diresq(x);
        else
            y = rot_esq(x); 
    }
    return y;
}


void troca_filho(arvore *t, no *u, no *v) {
    if(v->pai == NULL)
        t->raiz = v;
    else if(u == v->pai->esq)
        v->pai->esq = v;
    else
        v->pai->dir = v;
}


void avl_insert(arvore *t, no *z) {
    int a;
    no *x, *y;

    z->fb = 0;

    x = tree_insert(t, z);
    while(x != NULL) {
        // Verifica de qual lado a inserção ocorreu comparando as chaves
        if(z->chave < x->chave) {
            // O nó desceu pela esquerda, o peso vai pro negativo
            x->fb -= 1; 
        } else {
            // O nó desceu pela direita, o peso vai pro positivo
            x->fb += 1; 
        }

        // Analisa a situação do pai após a atualização
        if(x->fb == 0) {
            // A altura não mudou
            break; 
        } else if(x->fb == 1 || x->fb == -1) {
            // A altura aumentou, continua subindo para atualizar o pai de x
            x = x->pai;
        }
        else if(x->fb == 2 || x->fb == -2) {
            // Se a arvore ficou desbalanceada, faz o balanceamento e para.
            y = avl_balance(x);
            troca_filho(t, x, y); 

            break; 
        }
    }
}        


void avl_delete(arvore *t, no *z) {
    int chave_alvo, fb_original;
    no *x, *y, *sucessor;

    sucessor = NULL;
    // Define se o no z possui um ou dois filhos
    // Se tiver um ou nenhum filho, a chave alvo é a do próprio z, porque é o nó que
    // vai ocupar eh o proprio filho de z (ou NULL)
    // Se tiver dois filhos, a chave alvo é a do sucessor
    // porque é ele que vai ocupar o lugar de z
    if(z->esq == NULL || z->dir == NULL) {
        chave_alvo = z->chave; // Chave do próprio z
    } else {
        sucessor = tree_minimum(z->dir);
        chave_alvo = sucessor->chave; // Chave do sucessor
    }

    // Guarda o fator de balanceamento do nó que vai ser deletado
    // para o sucessor herdar depois (se existir)
    fb_original = z->fb;

    x = tree_delete(t, z);

    // Se o sucessor existir, ele vai ocupar o lugar de z
    // então herda o fator de balanceamento original de z
    if (sucessor != NULL) 
        sucessor->fb = fb_original;

    // Se o sucessor era filho da direita de z, 
    // o x retorna apontando para o próprio z apagado.
    if (x == z) {
        x = sucessor;
    }

    while(x != NULL) {
        // Verifica de qual lado a remoção ocorreu comparando as chaves
        if(chave_alvo < x->chave) {
            x->fb += 1; 
        } else {
            x->fb -= 1; 
        }

        // Analisa a situação do pai após a atualização
        // Se o no ficou com peso 1 ou -1, significa que a altura se manteve
        if(x->fb == 1 || x->fb == -1) {
            break; 
        } 
        else if(x->fb == 0) {
            x = x->pai; // A altura diminuiu, continua subindo para atualizar o pai de x
        } 
        else if(x->fb == 2 || x->fb == -2) {
            // a arvore ficou desbalanceada, faz o balanceamento e continua subindo para atualizar o pai de x
            y = avl_balance(x);
            troca_filho(t, x, y); 

            // Se o fator de balanceamento do nó que ficou no lugar do x for diferente de 0
            // significa que a altura da subárvore se manteve, então para.
            if(y->fb != 0) {
                break;
            } else {
                // Se o fator de balanceamento do nó que ficou no lugar do x for 0
                // significa que a altura da subárvore diminuiu, então continua subindo para atualizar o pai de x
                x = y->pai; 
            }
        }
    }        
}