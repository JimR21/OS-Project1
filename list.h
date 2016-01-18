
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

#include "myRecordDef.h"
#include "hashfunction.h"


typedef struct komvos* pnode;

/* Komvos tou hashtable. Se periptwsh sygkroushs dhmioyrgeitai lista. */
struct komvos
{
    MyRecord data;
    pnode next;
    pnode previous;
};

typedef struct komvos node;

typedef struct index_komvos* index_pnode;

/* Eswterikos komvos tou inverted index */
struct index_komvos
{
    pnode record;
    index_pnode previous;
    index_pnode next;
};

typedef struct index_town* pnode_town;

/* Arxikos komvos kathe listas record pou vriskontai sthn idia polh. Sundeontai metaksi tous epishs se lista */
struct index_town
{
    char name[20];
    index_pnode start;
    int pop;
    int sum;
    char top_spender[20];
    int ts_invoice;
    pnode_town next;
    pnode_town previous;
};

/* Eisagwgh se hashtable kai inverted index record r */
int InsertL(MyRecord r, pnode *hashtable, int htsize, pnode_town start_town);

/* Ektupwsh periexomenwn tou komvou */
void WriteL(pnode p);

/* Anazhthsh ston hashtable */
int SearchL(char* num, pnode* hashtable, int htsize, MyRecord* rec);

/* Diagrafh tou record me thlefwno num apo ton hashtable */
int DeleteL(char* num, pnode *hashtable, int htsize, pnode_town start_town);


/* Arxikopoihsh tou inverted index me dhmiourgia ths start_town arxh gia thn lista twn polewn */
int InitializeI(pnode_town *start_town);

/* Eisagwgh ston inverted index */
int InsertI(pnode_town start_town, pnode node);

/* Diagrafh apo ton inverted index */
int DeleteI(MyRecord rec, pnode_town start_town);

/* Sunarthsh pou epistrefei ton pluthismo kathe polhs h -1 an apotuxei */
int PopulationI(pnode_town start_town, char* town);

/* Sunarthsh poy epistrefei to sunoliko ofeiloymeno poso kathe polhs h -1 an apotuxei */
int SummaryI(pnode_town start_town, char* town);

/* Sunarthsh poy epistrefei tis k prwtes poleis me to megalutero poso */
int Top(pnode_town start_town, int k);

/* Sunarthsh pou epistrefei tou k prwtous arithmous pou ofeiloun ta perissotera sthn polh town */
int TopKSpenders(pnode_town start_town, char *town, int k);

/* Sunarthsh pou epistrefei ton arithmo pou ofeilei ta perissotera se kathe polh */
int TopTownSpenders(pnode_town start_town);

/* EPistrefei ton megalutero arithmo */
int CompareMax(char *phone1, char *phone2);

/* Epistrefei ton mikrotero arithmo */
int CompareMin(char *phone1, char *phone2);

/* Emfanish tou megaluterou aithmou poy uparxei sth vash */
int Max(pnode_town start_town);

/* Emfanish tou mikroterou arithmou pou yparxei sth vash */
int Min(pnode_town start_town);

/* Apodesmeush mnhmhs */
int FreeIndex(pnode_town start_town);



