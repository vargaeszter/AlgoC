#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

enum{
    /*ASCII 48-57:  0-9 
            65-90:  A-Z*/
    startSZAM = 48,
    startABC = 65,
    /*szobaszamok*/
    szobaSZAM = 16,     //4
    emeletSZAM = 18,     //2
    lakoSZAM = 4,       
    marad = 0,
    atkolt = 1,
    kikolt = 2,
    bekolt = 3,
    /*idosavokra*/
    numIDOSAV = 8,      //4
    num_max_fo = 20,    //5 
    LEFT = 1,
    MIDDLE = 2,
    RIGHT = 3 ,
    NOTCHILD = 0,
    ISGROOT = 1,
    cases = 500,
};

typedef struct{
    int e;
    int sz;
} cim;

typedef struct {
    char neptun[6];
    cim honnan;
    cim hova;
} data, *pdata;

typedef struct tree{
    data d;
    int which;
    struct tree* left;
    struct tree* middle;
    struct tree* right;
    struct tree* parent;
} treeelem, *ptree;

typedef struct lista{
    data d;
    struct lista* p;
} listelem, *list;

typedef struct {
    int nap;
    int idosav;
    int count;
} type_ido, *pido;

void gen_nept(char* location){
    int rnd;
    for(int i = 0; i < 6; i++) {
        rnd = rand() % 36;
        if(rnd < 10) {
            location[i] = rnd + startSZAM;
        } else {
            rnd -= 10;
            location[i] = rnd + startABC;
        }
    }
}

int gen_szoba(){
    return rand() % szobaSZAM*emeletSZAM;
}

void gen_koltozo_lista_A(){
    int countFELSZAB = 0, countMARAD = 0, countATKOLTOZOK = 0;
    char NEPTUN[7] = { 0 };
    int bekoltozok[szobaSZAM*emeletSZAM] = { 0 };
    FILE *f;
    f = fopen("koltozok.txt", "w");
    if(f == NULL){
        fprintf(stderr, "file hiba\n");
        return;
    }
    for(int i = 0; i < emeletSZAM; i++) {
        for(int j = 0; j < szobaSZAM; j++)
            for(int k = 0; k<lakoSZAM; k++){
                gen_nept(NEPTUN);
                
                int decision = rand() % 3;
                if(decision == marad && bekoltozok[szobaSZAM*i + j] == lakoSZAM){
                    decision = atkolt;
                }
                switch (decision)
                {
                case marad:  {
                        bekoltozok[szobaSZAM*i + j]++;
                        fprintf(f, "%s\t%d/%d\t%d/%d\n", NEPTUN, i+1, j+1, i+1, j+1);
                        countMARAD++;
                    }
                    break;
                case atkolt: {
                        int szoba  = gen_szoba();
                        while(bekoltozok[szoba] >= lakoSZAM) {
                            szoba ++;
                            if(szoba == emeletSZAM*szobaSZAM) szoba = 0;
                        }
                        bekoltozok[szoba]++;
                        int emelet = (int)(szoba / szobaSZAM + 1);
                        int szobaszam = szoba % szobaSZAM + 1;
                        fprintf(f, "%s\t%d/%d\t%d/%d\n", NEPTUN, i+1, j+1, emelet, szobaszam);
                        countATKOLTOZOK++;
                    }
                    break;
                default: {
                        countFELSZAB++;
                        fprintf(f, "%s\t%d/%d\t%d/%d\n", NEPTUN, i+1, j+1, 0, 0);
                    }
                    
                    break;
                }
            }
    }

    for(int i = 0; i < emeletSZAM*szobaSZAM; i++) {
        while(bekoltozok[i] < lakoSZAM) {
            gen_nept(NEPTUN);
            bekoltozok[i]++;
            int emelet = (int)(i / szobaSZAM + 1);
            int szobaszam = i % szobaSZAM + 1;
            fprintf(f, "%s\t%d/%d\t%d/%d\n", NEPTUN, 0, 0, emelet, szobaszam);
        }
    }
    fclose(f);
}

void gen_koltozo_lista_B(){
    int countFELSZAB = 0, countMARAD = 0, countATKOLTOZOK = 0;
    char NEPTUN[7] = { 0 };
    int bekoltozok[szobaSZAM*emeletSZAM] = { 0 };
    FILE *f;
    f = fopen("koltozok.txt", "w");
    if(f == NULL){
        fprintf(stderr, "file hiba\n");
        return;
    }
    for(int i = 0; i < emeletSZAM; i++) {
        for(int j = 0; j < szobaSZAM; j++)
            for(int k = 0; k<lakoSZAM; k++){
                gen_nept(NEPTUN);
                
                int decision = rand() % 3;
                if(decision == marad && bekoltozok[szobaSZAM*i + j] == lakoSZAM){
                    decision = atkolt;
                }
                switch (decision)
                {
                case marad:  {
                        bekoltozok[szobaSZAM*i + j]++;
                        fprintf(f, "%s\t%d/%d\t%d/%d\n", NEPTUN, i+1, j+1, i+1, j+1);
                        countMARAD++;
                    }
                    break;
                case atkolt: {
                        int szoba  = gen_szoba();
                        while(bekoltozok[szoba] >= lakoSZAM) {
                            szoba ++;
                            if(szoba == emeletSZAM*szobaSZAM) szoba = 0;
                        }
                        bekoltozok[szoba]++;
                        int emelet = (int)(szoba / szobaSZAM + 1);
                        int szobaszam = szoba % szobaSZAM + 1;
                        fprintf(f, "%s\t%d/%d\t%d/%d\n", NEPTUN, emelet, szobaszam, i+1, j+1);
                        countATKOLTOZOK++;
                    }
                    break;
                default: {
                        countFELSZAB++;
                        fprintf(f, "%s\t%d/%d\t%d/%d\n", NEPTUN, 0, 0, i+1, j+1);
                    }
                    break;
                }
            }
    }
    for(int i = 0; i < emeletSZAM*szobaSZAM; i++) {
        while(bekoltozok[i] < lakoSZAM) {
            gen_nept(NEPTUN);
            bekoltozok[i]++;
            int emelet = (int)(i / szobaSZAM + 1);
            int szobaszam = i % szobaSZAM + 1;
            fprintf(f, "%s\t%d/%d\t%d/%d\n", NEPTUN, emelet, szobaszam, 0, 0);
        }
    }
    fclose(f);
}

void gen_koltozo_lista_C(){
    int countFELSZAB = 0, countMARAD = 0, countATKOLTOZOK = 0;
    char NEPTUN[7] = { 0 };
    int bekoltozok[szobaSZAM*emeletSZAM] = { 0 };
    FILE *f;
    f = fopen("koltozok.txt", "w");
    if(f == NULL){
        fprintf(stderr, "file hiba\n");
        return;
    }
    for(int i = 0; i < emeletSZAM; i++) {
        for(int j = 0; j < szobaSZAM; j++)
            for(int k = 0; k<lakoSZAM; k++){
                gen_nept(NEPTUN);
                
                int decision = rand() % 2;
                if(decision == marad && bekoltozok[szobaSZAM*i + j] == lakoSZAM){
                    decision = atkolt;
                }
                switch (decision)
                {
                case marad:  {
                        bekoltozok[szobaSZAM*i + j]++;
                        fprintf(f, "%s\t%d/%d\t%d/%d\n", NEPTUN, i+1, j+1, i+1, j+1);
                        countMARAD++;
                    }
                    break;
                case atkolt: {
                        int szoba  = gen_szoba();
                        while(bekoltozok[szoba] >= lakoSZAM) {
                            szoba ++;
                            if(szoba == emeletSZAM*szobaSZAM) szoba = 0;
                        }
                        bekoltozok[szoba]++;
                        int emelet = (int)(szoba / szobaSZAM + 1);
                        int szobaszam = szoba % szobaSZAM + 1;
                        fprintf(f, "%s\t%d/%d\t%d/%d\n", NEPTUN, emelet, szobaszam, i+1, j+1);
                        countATKOLTOZOK++;
                    }
                    break;
                default: {
                        countFELSZAB++;
                        fprintf(f, "BAJ VAN %s\t%d/%d\t%d/%d\n", NEPTUN, 0, 0, i+1, j+1);
                    }
                    break;
                }
            }
    }
    fclose(f);
}

int cim_lq(cim nagyobb, cim kisebb){
    if((kisebb.e < nagyobb.e) || (kisebb.e == nagyobb.e && kisebb.sz < nagyobb.sz)) {
        return 1;
    } else
        return 0;
}

int cim_eq(cim szoba, cim ujszoba){
    if(ujszoba.e == szoba.e && ujszoba.sz == szoba.sz) {
        return 1;
    } else
        return 0;
}

void data_cpy(pdata from, pdata to){
    to->honnan.e = from->honnan.e;
    to->honnan.sz = from->honnan.sz;
    to->hova.e = from->hova.e;
    to->hova.sz = from->hova.sz;
    strcpy(to->neptun, from->neptun);
}

void zero_ptr(ptree t) {
    t->left = NULL;
    t->middle = NULL;
    t->right = NULL;
    t->parent = NULL;
}

int _index(cim szoba){
    return (szoba.e - 1)*szobaSZAM + (szoba.sz - 1);
} 

void insert(ptree* head, pdata tmp){
    if (head == NULL) return;
    ptree ptr, new;
    ptr = *head;
    new = (ptree)malloc(sizeof(treeelem));
    data_cpy(tmp, &(new->d));
    zero_ptr(new);
    if(ptr == NULL){
        new->which = NOTCHILD;
        *head = new;
    } else {
        while((new != ptr->left) && (new != ptr->middle) && (new != ptr->right)) {
            if(cim_lq(ptr->d.honnan, new->d.honnan)) {
                if(ptr->left == NULL) {
                    ptr->left = new;
                    new->parent = ptr;
                    new->which = LEFT;
                }
                else ptr = ptr->left;
            } else if (cim_eq(ptr->d.honnan, new->d.honnan)) {
                if(ptr->middle == NULL) {
                    ptr->middle = new;
                    new->parent = ptr;
                    new->which = MIDDLE;
                }
                else ptr = ptr->middle;
            } else {
                if(ptr->right == NULL) {
                    ptr->right = new;
                    new->parent = ptr;
                    new->which = RIGHT;
                }
                else ptr = ptr->right;
            }
        }
    }
}

ptree maxi(ptree p) {
    if(!p) return NULL;
    while(p->right) p = p->right;
    while(p->middle) p = p->middle;
    return p;
}

ptree mini(ptree p) {
    if(!p) return NULL;
    while(p->left) p = p->left;
    while(p->middle) p = p->middle;
    return p;
}

ptree find_value(cim h0, ptree p){
    while(1) {
        if(!p) return NULL;
        if(cim_eq(h0,p->d.honnan)){ 
            while(p->middle != NULL) {
                p = p->middle;
            }
            return p;
        }
        if(cim_lq(p->d.honnan, h0)) {
            p = p->left;
        }
        else p = p->right;
    }
}

void set_ido(pido ido, int i, FILE *f){
    ido->nap = i;
    ido->idosav = 1;
    ido->count = 0;
    fprintf(f, "%d. NAP\n%d. IDOSAV\n", ido->nap, ido->idosav);
}

void increment_ido(pido ido, FILE * f){
    if(ido->count == num_max_fo){
        ido->count = 1;
        if(ido->idosav == numIDOSAV){
            ido->idosav = 1;
            ido->nap++;
            fprintf(f, "%d. NAP\n%d. IDOSAV\n", ido->nap, ido->idosav);
        } else {
            ido->idosav++;
            fprintf(f, "%d. IDOSAV\n", ido->idosav);
        }
    } else {
        ido->count++;
    }
}

int not_enough_time(pido ido, int count){
    if((numIDOSAV-ido->idosav)*num_max_fo+(num_max_fo-ido->count) >= count)
        return 0;
    else if(ido->idosav == 1 && ido->count == 0) return 0;
    else return 1;
}

void koltozes_print(pido ido, data tmp, FILE *f, int type) {
    increment_ido(ido, f);
    if(type == kikolt){
        fprintf(f, "\t%d.\t%s\t%d/%d\tKI\n", ido->count, tmp.neptun, tmp.honnan.e, tmp.honnan.sz);}
    else if(type == bekolt) { 
        fprintf(f, "\t%d.\t%s\tBE\t%d/%d\n", ido->count, tmp.neptun, tmp.hova.e, tmp.hova.sz); }
    else if(type == atkolt){
        fprintf(f, "\t%d.\t%s\t%d/%d\t%d/%d\n", ido->count, tmp.neptun, tmp.honnan.e, tmp.honnan.sz, tmp.hova.e, tmp.hova.sz);}
}

ptree withdraw (ptree *head, ptree *treegroot){
    if(head == NULL || *head == NULL) return NULL;
    ptree tmp = *head;
    int flag = 0;
    if(*head == *treegroot){
        flag = ISGROOT;
    }
    if(tmp->middle){
        *head = tmp->middle;
        (*head)->which = tmp->which;
        (*head)->right = tmp->right;
        if((*head)->right) (*head)->right->parent = *head;
        (*head)->left = tmp->left;
        if((*head)->left) (*head)->left->parent = *head;
        (*head)->parent = tmp->parent;
        if ((*head)->parent) {
            switch(tmp->which){
                case LEFT: tmp->parent->left = *head; break;
                case MIDDLE: tmp->parent->middle = *head; break;
                case RIGHT: tmp->parent->right = *head; break;
            }
        }
    }
    else if(tmp->left == NULL && tmp->right == NULL) {
        
            switch((*head)->which){
                case LEFT: (*head)->parent->left = NULL; break;
                case MIDDLE: (*head)->parent->middle = NULL; break;
                case RIGHT: (*head)->parent->right = NULL; break;
                default: *head = NULL; break;
            }
    }
    else if (tmp->left == NULL || tmp->right == NULL) {
        if (tmp->left == NULL) *head = (*head)->right;
        else *head = (*head)->left;
        (*head)->parent = tmp->parent;
        (*head)->which = tmp->which;
        switch((*head)->which){
            case LEFT: {
                (*head)->parent->left = *head;
                break;}
            case MIDDLE: {
                (*head)->parent->middle = *head;
                break;}
            case RIGHT: {
                (*head)->parent->right = *head;
                break;}
        }    
    }
    else {
        ptree move = maxi(tmp->left);
                switch(move->which){
                    case LEFT: {
                        move->parent->left = move->left;
                        if(move->left) move->left->which = LEFT;
                        break;}
                    case MIDDLE: {
                        move->parent->middle = move->left;
                        if(move->left) move->left->which = MIDDLE;
                        break;}
                    case RIGHT: {
                        move->parent->right = move->left; 
                        if(move->left) move->left->which = RIGHT;
                        break;}
                    default: move->left->which = NOTCHILD; break;
                    }
                if(move->left) move->left->parent = move->parent;
                {
                    move->left = tmp->left;
                    if(move->left) move->left->parent = move;
                    move->right = tmp->right;
                    if(move->right) move->right->parent = move;
                    move->which = tmp->which;
                    move->parent = tmp->parent;
                    switch(move->which){
                        case LEFT:move->parent->left = move; break;
                        case MIDDLE: move->parent->middle = move; break;
                        case RIGHT: move->parent->right = move; break;
                        }
                }
        *head = move;
    }
    if(flag) {
        *treegroot = *head;
    }
    zero_ptr(tmp);
    return tmp;
}

int traversal(ptree* head, int* lakok, pido ido, FILE *f){
    int flag = 0, count = 0;
    if(head == NULL) return -1;
    ptree ptr, mark_parent;
    ptr = *head;
    while(ptr != NULL) {
        if(ptr->left && flag < LEFT) {
            flag = 0;
            ptr = ptr->left;
        }
        else if(ptr->middle && flag < MIDDLE){
            flag = 0;
            ptr = ptr->middle;
        }
        else if (ptr->right && flag < RIGHT) {
            flag = 0;
            ptr = ptr->right;
        }
        else {
            flag = ptr->which;

            if(lakok[_index(ptr->d.hova)] < lakoSZAM) {
                koltozes_print(ido, ptr->d, f, atkolt);
                lakok[_index(ptr->d.honnan)]--;
                lakok[_index(ptr->d.hova)]++;
                mark_parent = ptr->parent;
                switch(ptr->which){
                    case LEFT: mark_parent->left = NULL; break;
                    case MIDDLE: mark_parent->middle = NULL; break;
                    case RIGHT: mark_parent->right = NULL; break;
                }
                ptr = withdraw(&ptr, head);
                free(ptr);
                ptr = mark_parent;
                count ++;
            }
            else {
                ptr = ptr->parent;
            }
        }
    }
    return count;
}

void koltozteto(int * napszam) {
    int lakok[szobaSZAM*emeletSZAM] = {0};

    FILE *source, *target;
    source = fopen("koltozok.txt", "r");
    target = fopen("idobeosztas.txt", "w");
    if(source == NULL || target == NULL){
        fprintf(stderr, "file hiba\n");
        return;
    }
    type_ido ido;
    set_ido(&ido, 1, target);

    data tmp;
    ptree temp, be_varok = NULL;
    ptree *atkoltozok = (ptree*)malloc(sizeof(ptree));
    *atkoltozok = NULL;

    while((fscanf(source, "%s\t%d/%d\t%d/%d\n", tmp.neptun, &tmp.honnan.e, &tmp.honnan.sz, &tmp.hova.e, &tmp.hova.sz)) != EOF){
        if(tmp.hova.e == 0 && tmp.hova.sz == 0){
            koltozes_print(&ido, tmp, target, kikolt);

        } else if(tmp.honnan.e == tmp.hova.e && tmp.honnan.sz == tmp.hova.sz){
            lakok[_index(tmp.honnan)] ++;

        } else if(tmp.honnan.e != 0 && tmp.honnan.sz != 0){
            insert(atkoltozok, &tmp);
            lakok[_index(tmp.honnan)] ++;

        } else if(tmp.honnan.e == 0 && tmp.honnan.sz == 0){
            temp =  (ptree)malloc(sizeof(treeelem));
            data_cpy(&tmp, &(temp->d));
            zero_ptr(temp);
            temp->middle = be_varok;
            be_varok = temp;
        }
    }
    
    fclose(source);

    while(traversal(atkoltozok, lakok, &ido, target) > 0){}

    ptree waiting;
    int count;
    while ((*atkoltozok)) {
        ptree  puffer = NULL;
        ptree waiting = maxi(*atkoltozok);
        waiting = withdraw(&waiting, atkoltozok);
        puffer = waiting;
        count = 1;
        while(! cim_eq(puffer->d.honnan,waiting->d.hova)){
            temp = find_value(waiting->d.hova, *atkoltozok);
            temp = withdraw(&temp, atkoltozok);
            waiting->parent = temp;
            temp->middle = waiting;
            waiting = temp;
            count ++;
        }

        if(not_enough_time(&ido, count + 1)){
            set_ido(&ido, ido.nap+1, target);
        }

        koltozes_print(&ido, puffer->d, target, kikolt);
        lakok[_index(puffer->d.honnan)] --;

        while(waiting && (lakok[_index(waiting->d.hova)] < lakoSZAM)  && waiting != puffer){
            koltozes_print(&ido, waiting->d, target, atkolt);
            lakok[_index(waiting->d.honnan)] --;
            lakok[_index(waiting->d.hova)] ++;
            temp = waiting;
            waiting = waiting->middle;
            free(temp);
        }

        koltozes_print(&ido, puffer->d, target, bekolt);
        lakok[_index(puffer->d.hova)]++;
        free(puffer);
    }
    free(atkoltozok);

    while(be_varok){
        koltozes_print(&ido, be_varok->d, target, bekolt);
        lakok[(be_varok->d.hova.e -1 )*szobaSZAM + (be_varok->d.hova.sz - 1)] ++;
        temp = be_varok;
        be_varok = be_varok->middle;
        free(temp);
    }
    fclose(target);
    *napszam = ido.nap;
}

int main() {
    time_t t;
    srand(time(&t));
    double avg = 0;
    int temp = 0;
    int  max = 0;
    int min = INT_MAX;

    for(int i = 0; i < cases; i++){
        gen_koltozo_lista_B();
        koltozteto(&temp);
        avg += (double)temp;
        if(temp > max) max = temp;
        if(temp < min) min = temp;
    }
    avg /= cases;

    printf("\tMinimum time:\t%d\t\tdays\n", min);
    printf("\tAverage time:\t%lf\tdays\n", avg);
    printf("\tMaximum time:\t%d\t\tdays\n", max);

    return 0; 
}