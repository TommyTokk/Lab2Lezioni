#include "utils.h"

int contaPari(bTree *t){
    if(!t) return 0;
    if(t -> val % 2 == 0){
        return (1 + contaPari(t -> sx) + contaPari(t -> dx));
    }
    return (0 + contaPari(t -> sx) + contaPari(t -> dx));
    
}

void nodoDistruggi(bTree *t){
    free(t);
}

void alberoDistruggi(bTree *t){
    if(t != NULL){
        alberoDistruggi(t -> sx);
        alberoDistruggi(t -> dx);
        nodoDistruggi(t);
    }
}

bTree *pota(bTree *t){
    if(!t) return t;
    if(t -> val < 0){
        alberoDistruggi(t);
        return NULL;
    }

    t -> sx = pota(t -> sx);
    t -> dx = pota(t -> dx);

    return t;
}


void visitaAlbero(bTree *t){
    if(t != NULL){
        printf("%d\n", t -> val);
        visitaAlbero(t -> sx);
        visitaAlbero(t -> dx);
    }
}

int contaFoglie(bTree *t){
    if(!t) return 0;
    if(t -> sx == NULL && t -> dx == NULL) return 1;
    return contaFoglie(t -> sx) + contaFoglie(t -> dx);
}

int valoreAlbero(bTree *t){
    if(!t) return 0;
    return (t -> val + valoreAlbero(t -> sx) + valoreAlbero(t -> dx));
}

bTree *posAlbero(bTree *t){
    if(!t) return t;
    if(t -> val < 0){
        t -> val = valoreAlbero(t -> sx);
    }
    t -> sx = posAlbero(t -> sx);
    t -> dx = posAlbero(t -> dx);

    return t;
}