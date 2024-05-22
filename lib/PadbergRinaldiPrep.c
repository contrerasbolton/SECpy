/*275:*/
#line 10 "PadbergRinaldiPrep.w"


#include "common.h"

#define heap Bheap
extern Heap_function Bheap;

#define DEAD_LIST

int PadbergRinaldiPrep(
/*12:*/
#line 93 "header.w"

MCC_graph*G,
int option,
int pril,
int*ncutarray,
int*cutarray,
MCC_cap*mincutvalue

/*:12*/
#line 20 "PadbergRinaldiPrep.w"
,
int*last,
int*succ,
MCC_cap*star_capacity
)
{
int c_fail= 0,c_maxf= 0,why;
/*276:*/
#line 39 "PadbergRinaldiPrep.w"

int reason[5]= {0,0,0,0,0};
/*258:*/
#line 78 "PadbergRinaldi.w"

MCC_cap*edge_cap;
int*edge_flag;

/*:258*/
#line 41 "PadbergRinaldiPrep.w"

/*24:*/
#line 260 "header.w"

int status= MCC_ok;











#line 1 "auxiliary.w"
/*:24*/
#line 42 "PadbergRinaldiPrep.w"

/*2:*/
#line 7 "marks.w"

int c_marks;
int*marked_node;
int*mark;

/*:2*/
#line 43 "PadbergRinaldiPrep.w"

/*72:*/
#line 424 "graph.w"

/*73:*/
#line 438 "graph.w"

int n_neigh;
int a_neigh;
int a_next;

/*:73*/
#line 425 "graph.w"

#ifdef DEAD_LIST
int*dead_list;
int*base_dead_list;
#endif
#ifdef UNSHRINK
int*stack_pointer;
int*base_stack_pointer;
int c_pushed;
#endif

/*:72*/
#line 44 "PadbergRinaldiPrep.w"

/*29:*/
#line 20 "graph.w"

/*30:*/
#line 27 "graph.w"

int s_nodes,s_edges,*c_nodes,*c_edges,*first,*prev,*next,*tip;
int*orig_name,*active_pos,*active_node;
MCC_cap*capacity;

/*:30*/
#line 21 "graph.w"


/*31:*/
#line 32 "graph.w"

s_nodes= G->s_nodes;
s_edges= G->s_edges;
c_nodes= &G->c_nodes;
c_edges= &G->c_edges;
first= G->first;

prev= G->prev;

next= G->next;

tip= G->tip;
orig_name= G->orig_name;

capacity= G->capacity;
active_pos= G->active_pos;


active_node= G->active_node;



/*:31*/
#line 23 "graph.w"


/*:29*/
#line 45 "PadbergRinaldiPrep.w"


/*:276*/
#line 27 "PadbergRinaldiPrep.w"


/*277:*/
#line 47 "PadbergRinaldiPrep.w"

/*259:*/
#line 82 "PadbergRinaldi.w"

Alloc(edge_cap,s_edges,MCC_cap);
Alloc(edge_flag,s_edges,int);
heap(s_edges,edge_cap,allocate_heap);

/*:259*/
#line 48 "PadbergRinaldiPrep.w"

/*3:*/
#line 12 "marks.w"

Alloc(mark,s_nodes,int);Alloc(marked_node,s_nodes,int);


/*:3*/
#line 49 "PadbergRinaldiPrep.w"

/*74:*/
#line 443 "graph.w"

#ifdef DEAD_LIST
Alloc(dead_list,2*(*c_nodes),int);
#endif
#ifdef UNSHRINK
Alloc(stack_pointer,4*(*c_nodes)+2*(*c_edges),int);
#endif

/*:74*/
#line 50 "PadbergRinaldiPrep.w"


/*:277*/
#line 29 "PadbergRinaldiPrep.w"

/*278:*/
#line 52 "PadbergRinaldiPrep.w"

/*7:*/
#line 30 "marks.w"

{
for(c_marks= 0;c_marks<s_nodes;c_marks++)
mark[c_marks]= End_list;
c_marks= 0;
}
#line 1 "header.w"

/*:7*/
#line 53 "PadbergRinaldiPrep.w"

/*75:*/
#line 451 "graph.w"

{
#ifdef DEAD_LIST
base_dead_list= dead_list;
#endif
#ifdef UNSHRINK
base_stack_pointer= stack_pointer;
#endif
}

/*:75*/
#line 54 "PadbergRinaldiPrep.w"

/*261:*/
#line 94 "PadbergRinaldi.w"

{int e,v,w;
heap(0,edge_cap,init);
for(e= 0;e<*c_edges;e++){
edge_cap[e]= capacity[Arc_of(e)];
heap(e,edge_cap,enq);
edge_flag[e]= 1;
}
}

/*:261*/
#line 55 "PadbergRinaldiPrep.w"


/*:278*/
#line 30 "PadbergRinaldiPrep.w"


/*280:*/
#line 67 "PadbergRinaldiPrep.w"

{/*240:*/
#line 104 "naive.w"

int e_shrink;
int n_left;
int n_right;
MCC_cap e_shrink_cap;

/*:240*/
#line 68 "PadbergRinaldiPrep.w"


/*267:*/
#line 169 "PadbergRinaldi.w"

{int v,i;
MCC_cap c;

For_active_nodes(v,i){
c= star_capacity[v];
if(c<(*mincutvalue)){
*mincutvalue= c;
*ncutarray= 1;
cutarray[0]= orig_name[v];
if(c<=Epsilon)goto freeall;
}
}
}

/*:267*/
#line 70 "PadbergRinaldiPrep.w"

while(*c_nodes>3){int i;
for(i= 0;i<*c_nodes;i++){
e_shrink= heap(0,edge_cap,del);
if(At_end(e_shrink))break;
if(!edge_flag[e_shrink])continue;
edge_flag[e_shrink]= 0;
Find_end_vertices(e_shrink,n_left,n_right);
e_shrink_cap= capacity[Arc_of(e_shrink)];
/*268:*/
#line 201 "PadbergRinaldi.w"

{MCC_cap n_left_cap,n_right_cap,e_left_cap,e_right_cap;
MCC_cap mincap,totcap;

if(e_shrink_cap>=(*mincutvalue)-Epsilon){why= 1;reason[why]++;goto shrink;}
n_left_cap= star_capacity[n_left];
if(n_left_cap<=Two*e_shrink_cap+Epsilon){why= 2;reason[why]++;goto shrink;}
n_right_cap= star_capacity[n_right];
if(n_right_cap<=Two*e_shrink_cap+Epsilon){why= 2;reason[why]++;goto shrink;}
/*269:*/
#line 227 "PadbergRinaldi.w"

{
Remove_marks;
For_neighbors(n_left,n_neigh,a_neigh)Mark(n_neigh,a_neigh);
}

/*:269*/
#line 210 "PadbergRinaldi.w"

totcap= e_shrink_cap;
For_neighbors(n_right,n_neigh,a_neigh)
if(Not_at_end(mark[n_neigh])){
e_left_cap= capacity[mark[n_neigh]];
e_right_cap= capacity[a_neigh];
mincap= (e_left_cap<e_right_cap)?e_left_cap:e_right_cap;
totcap+= mincap;
if(totcap>=(*mincutvalue)-Epsilon){why= 3;reason[why]++;goto shrink;}

if((n_left_cap<=Two*(e_left_cap+e_shrink_cap)+Epsilon)&&
(n_right_cap<=Two*(e_right_cap+e_shrink_cap)+Epsilon))
{why= 4;reason[why]++;goto shrink;}
}
/* Out0(2,"-"); */
}

/*:268*/
#line 79 "PadbergRinaldiPrep.w"

c_fail++;
}
break;
shrink:
/* Out1(2,"%d",why); */
/*77:*/
#line 479 "graph.w"

{int a_last= End_list,a_lr= End_list;
Out3(3,"Shrink: (%d,%d) ---> %d\n",n_left,n_right,n_left);
e_shrink_cap= Zero;
Remove_marks;
/*78:*/
#line 490 "graph.w"

{
For_neighbors_save_next(n_left,n_neigh,a_neigh,a_next){
if(n_neigh==n_right){
Unlink_arc(a_neigh,n_left);
Unlink_arc(Mate_of(a_neigh),n_neigh);
a_lr= a_neigh;
e_shrink_cap= capacity[a_neigh];
}
else{
Mark(n_neigh,a_neigh);
a_last= a_neigh;
}
}
/*81:*/
#line 532 "graph.w"

{
#ifdef DEAD_LIST
if(Not_at_end(a_lr))*(dead_list++)= Edge_of(a_lr);
else*(dead_list++)= End_list;
#endif
}

/*:81*/
#line 504 "graph.w"

/*82:*/
#line 540 "graph.w"

#ifdef UNSHRINK
*(stack_pointer++)= a_lr;
#endif

/*:82*/
#line 505 "graph.w"

}

/*:78*/
#line 484 "graph.w"

/*79:*/
#line 508 "graph.w"

{
/*80:*/
#line 527 "graph.w"

#ifdef UNSHRINK
c_pushed= 0;
#endif

/*:80*/
#line 510 "graph.w"

For_neighbors_save_next(n_right,n_neigh,a_neigh,a_next){
int a_link= mark[n_neigh];
if(Not_at_end(a_link)){
Unlink_arc(a_neigh,n_right);
Unlink_arc(Mate_of(a_neigh),n_neigh);
/*83:*/
#line 545 "graph.w"

{
#ifdef DEAD_LIST
*(dead_list++)= Edge_of(a_neigh);
*(dead_list++)= Edge_of(a_link);
#endif
}

/*:83*/
#line 516 "graph.w"

capacity[a_link]+= capacity[a_neigh];
capacity[Mate_of(a_link)]= capacity[a_link];
/*84:*/
#line 553 "graph.w"

#ifdef UNSHRINK
*(stack_pointer++)= a_neigh;
*(stack_pointer++)= a_link;
c_pushed++;
#endif

/*:84*/
#line 519 "graph.w"

}
else
tip[Mate_of(a_neigh)]= n_left;
}
/*85:*/
#line 560 "graph.w"

#ifdef UNSHRINK
*(stack_pointer++)= c_pushed;
#endif

/*:85*/
#line 524 "graph.w"

}

/*:79*/
#line 485 "graph.w"

/*86:*/
#line 565 "graph.w"

{int a_first;
a_first= first[n_right];
if(Not_at_end(a_first)){
if(Not_at_end(a_last)){
next[a_last]= a_first;
prev[a_first]= a_last;
}
else
first[n_left]= a_first;
}
}

/*:86*/
#line 486 "graph.w"

/*87:*/
#line 578 "graph.w"

{int j,u;
/*88:*/
#line 588 "graph.w"

#ifdef UNSHRINK
{
*(stack_pointer++)= n_left;
*(stack_pointer++)= n_right;
}
#endif

/*:88*/
#line 580 "graph.w"

j= active_pos[n_right];
u= active_node[*c_nodes-1];
active_node[j]= u;
active_pos[u]= j;
(*c_nodes)--;
}

/*:87*/
#line 487 "graph.w"

}

/*:77*/
#line 85 "PadbergRinaldiPrep.w"

/*271:*/
#line 280 "PadbergRinaldi.w"

{
while(dead_list>base_dead_list+2){int e= *(--dead_list),v,w;
edge_cap[e]= capacity[Arc_of(e)];
if(edge_flag[e]){
heap(e,edge_cap,req);
}else{
heap(e,edge_cap,enq);
edge_flag[e]= 1;
}
e= *(--dead_list);
edge_flag[e]= 0;
}
dead_list= base_dead_list;
}

/*:271*/
#line 86 "PadbergRinaldiPrep.w"

/*272:*/
#line 296 "PadbergRinaldi.w"

{int e;
MCC_cap c;

star_capacity[n_left]+= (star_capacity[n_right]-Two*e_shrink_cap);
#ifdef EXPERIMENTAL
For_neighbors(n_left,n_neigh,a_neigh){
e= Edge_of(a_neigh);
if(!edge_flag[e]){
heap(e,edge_cap,enq);
edge_flag[e]= 1;
}
}
#endif
}

/*:272*/
#line 87 "PadbergRinaldiPrep.w"

/*65:*/
#line 376 "graph.w"

{
#ifdef UNSHRINK
pred[n_right]= last[n_left];
#endif
succ[last[n_left]]= n_right;
last[n_left]= last[n_right];
}

/*:65*/
#line 88 "PadbergRinaldiPrep.w"

/*273:*/
#line 314 "PadbergRinaldi.w"

{int v;
MCC_cap c;

c= star_capacity[n_left];
if(c<(*mincutvalue)){
*mincutvalue= c;
*ncutarray= 0;
v= n_left;
for(v= n_left;Not_at_end(v);v= succ[v])
cutarray[(*ncutarray)++]= orig_name[v];
if(c<=Epsilon)goto freeall;
}
}
#line 1 "PadbergRinaldiPrep.w"
/*:273*/
#line 89 "PadbergRinaldiPrep.w"

}
Out1(2,"\nFailures: %d \n",c_fail);
Out2(2,"\nPR problem size reduction from %d to %d nodes.\n",s_nodes,*c_nodes);
if(pril==0)printf(" %5d",*c_nodes);
}
#line 1 "HaoOrlin.w"
/*:280*/
#line 32 "PadbergRinaldiPrep.w"


/*279:*/
#line 57 "PadbergRinaldiPrep.w"

freeall:
/*76:*/
#line 461 "graph.w"

#ifdef DEAD_LIST
Free(base_dead_list);
#endif
#ifdef UNSHRINK
Free(base_stack_pointer);
#endif

/*:76*/
#line 59 "PadbergRinaldiPrep.w"

/*4:*/
#line 16 "marks.w"

Free(marked_node);Free(mark);

/*:4*/
#line 60 "PadbergRinaldiPrep.w"

/*260:*/
#line 87 "PadbergRinaldi.w"

heap(0,edge_cap,free_heap);
Free(edge_flag);
Free(edge_cap);

/*:260*/
#line 61 "PadbergRinaldiPrep.w"


/*:279*/
#line 34 "PadbergRinaldiPrep.w"

return status;
}
#undef DEAD_LIST

/*:275*/
