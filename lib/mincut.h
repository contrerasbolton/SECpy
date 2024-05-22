/*8:*/
#line 4 "header.w"


#ifndef MCC_MINCUT_H
#define MCC_MINCUT_H
/*17:*/
#line 146 "header.w"

#include <stdio.h>
#include <stdlib.h>
#ifdef SYSV
#include <string.h>
#else
#include <strings.h>
#endif
#include <ctype.h>
#include <math.h>
#include <limits.h>

/*:17*/
#line 8 "header.w"

/*9:*/
#line 15 "header.w"

#ifdef MCC_INT
typedef int MCC_cap;
#elif MCC_FLOAT
typedef float MCC_cap;
#elif MCC_DOUBLE
typedef double MCC_cap;
#else
#error "Capacity type not defined. Compile with -DMCC_INT, -DMCC_FLOT, or -DMCC_DOUBLE."
#endif

/*:9*/
#line 9 "header.w"

/*20:*/
#line 195 "header.w"

#define  MCC_ok                      0 
#define  MCC_not_enough_memory       1 
#define  MCC_cannot_open_input_file  2 
#define  MCC_cannot_open_output_file 3 
#define  MCC_error_in_input_file     4 
#define  MCC_graph_is_empty          5 
#define  MCC_results_inconsistency   6 
#define  MCC_invalid_data            7 

/*:20*/
#line 10 "header.w"

/*10:*/
#line 26 "header.w"

typedef struct{
int s_nodes;
int s_edges;
int c_nodes;
int c_edges;
int*first;
int*prev;
int*next;
int*tip;
int*orig_name;
MCC_cap*capacity;
int*active_node;
int*active_pos;
}MCC_graph;

/*:10*/
#line 11 "header.w"

/*14:*/
#line 119 "header.w"


typedef int(MCC_fun)(/*12:*/
#line 93 "header.w"

MCC_graph*G,
int option,
int pril,
int*ncutarray,
int*cutarray,
MCC_cap*mincutvalue

/*:12*/
#line 121 "header.w"
);

MCC_fun/*15:*/
#line 125 "header.w"

naive,HaoOrlin,PadbergRinaldi,KargerStein,
NagamochiOnoIbaraki,NagamochiOnoIbarakiFH,NagamochiOnoIbarakiHybrid,
StoerWagner,StoerWagnerFH,GomoryHu;



/*:15*/
#line 123 "header.w"


/*:14*//*25:*/
#line 6 "auxiliary.w"


int cputime();
void printtime(int);
void error_prt(int);

/*:25*//*93:*/
#line 4 "hash.w"


/*97:*/
#line 53 "hash.w"

typedef union{
char*C;
int*I;
long*L;
float*F;
double*D;
}Key;
typedef struct{
char*keys;
long*head;
long*link;
Key key;
long size;
long key_len;
long last_index;
long index;
}Hash;

/*:97*/
#line 6 "hash.w"


#define setup_hash    1
#define insert_key    2
#define lookup_key    3
#define free_hash     4

int hash(Hash*,int);

/*:93*//*104:*/
#line 8 "heaps.w"


#define allocate_heap 1
#define init          2
#define enq           3
#define req           4
#define del           5
#define free_heap     6


typedef int(Heap_function)(int,MCC_cap*,int);

/*:104*//*123:*/
#line 3 "mincut.w"


int mincut(/*13:*/
#line 101 "header.w"

int nnod,
int nedg,
int ncno,
int canonical_names,
int*node,
int*tail,
int*head,
MCC_cap*ecap,
MCC_fun*mcc_fun,
int option,
int do_sort,
int pril,
int*ncutarray,
int*cutarray,
MCC_cap*mincutvalue


/*:13*/
#line 5 "mincut.w"
);

/*:123*//*147:*/
#line 91 "GoldbergTarjan.w"


int GoldbergTarjan(/*146:*/
#line 81 "GoldbergTarjan.w"

/*12:*/
#line 93 "header.w"

MCC_graph*G,
int option,
int pril,
int*ncutarray,
int*cutarray,
MCC_cap*mincutvalue

/*:12*/
#line 82 "GoldbergTarjan.w"
,
int source,
int sink,
MCC_cap*flow


/*:146*/
#line 93 "GoldbergTarjan.w"
);

/*:147*//*199:*/
#line 39 "initdistlabels.w"


int initdistlabels(/*196:*/
#line 17 "initdistlabels.w"

/*197:*/
#line 21 "initdistlabels.w"

int source,
int sink,
int*c_nodes,
int*active_node,
int*tip,
int*first,
int*next,
MCC_cap*cap,

/*:197*/
#line 18 "initdistlabels.w"

/*198:*/
#line 31 "initdistlabels.w"

int*dist,
int*ndist,
int*disconnected

/*:198*/
#line 19 "initdistlabels.w"


/*:196*/
#line 41 "initdistlabels.w"
);

/*:199*//*215:*/
#line 209 "initdistlabels.w"

int initdistlabels_phase2(/*213:*/
#line 198 "initdistlabels.w"

int source,
int sink,
int*c_nodes,
int*active_node,
int*tip,
int*first,
int*next,
MCC_cap*cap,
int*dist

/*:213*/
#line 210 "initdistlabels.w"
);

/*:215*//*223:*/
#line 23 "reinitdistlabels.w"


int reinitdistlabels(/*222:*/
#line 7 "reinitdistlabels.w"

int source,
int sink,
int*c_nodes,
int*activenode,
int*tip,
int*first,
int*next,
MCC_cap*cap,
int*curarc,
int*awake,
int wfirst,
int*wsucc,
int*dist,
int*ndist

/*:222*/
#line 25 "reinitdistlabels.w"
);

/*:223*/
#line 12 "header.w"

#endif

/*:8*/
