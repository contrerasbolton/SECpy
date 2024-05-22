/*253:*/
#line 15 "PadbergRinaldi.w"


#include "common.h"

#define heap Bheap
extern Heap_function Bheap;

#define DEAD_LIST

int PadbergRinaldi(/*12:*/
#line 93 "header.w"

MCC_graph*G,
int option,
int pril,
int*ncutarray,
int*cutarray,
MCC_cap*mincutvalue

/*:12*/
#line 24 "PadbergRinaldi.w"
)
{
int c_fail= 0,c_maxf= 0,why;
/*254:*/
#line 42 "PadbergRinaldi.w"

int reason[5]= {0,0,0,0,0};
/*258:*/
#line 78 "PadbergRinaldi.w"

MCC_cap*edge_cap;
int*edge_flag;

/*:258*/
#line 44 "PadbergRinaldi.w"

/*262:*/
#line 104 "PadbergRinaldi.w"

MCC_cap*star_capacity;

/*:262*/
#line 45 "PadbergRinaldi.w"

/*24:*/
#line 260 "header.w"

int status= MCC_ok;










#line 1 "auxiliary.w"
/*:24*/
#line 46 "PadbergRinaldi.w"

/*2:*/
#line 7 "marks.w"

int c_marks;
int*marked_node;
int*mark;

/*:2*/
#line 47 "PadbergRinaldi.w"

/*230:*/
#line 39 "naive.w"

int cutcar;
MCC_cap flow;
int*cutlist= 0;


/*:230*/
#line 48 "PadbergRinaldi.w"

/*61:*/
#line 342 "graph.w"

int*last= 0;
int*succ= 0;
#ifdef UNSHRINK
int*pred= 0;
#endif

/*:61*/
#line 49 "PadbergRinaldi.w"

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
#line 50 "PadbergRinaldi.w"

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
#line 51 "PadbergRinaldi.w"


/*:254*/
#line 27 "PadbergRinaldi.w"


/*255:*/
#line 53 "PadbergRinaldi.w"

/*259:*/
#line 82 "PadbergRinaldi.w"

Alloc(edge_cap,s_edges,MCC_cap);
Alloc(edge_flag,s_edges,int);
heap(s_edges,edge_cap,allocate_heap);

/*:259*/
#line 54 "PadbergRinaldi.w"

/*263:*/
#line 107 "PadbergRinaldi.w"

Alloc(star_capacity,s_nodes,MCC_cap);

/*:263*/
#line 55 "PadbergRinaldi.w"

/*3:*/
#line 12 "marks.w"

Alloc(mark,s_nodes,int);Alloc(marked_node,s_nodes,int);


/*:3*/
#line 56 "PadbergRinaldi.w"

/*233:*/
#line 54 "naive.w"

Alloc(cutlist,s_nodes,int);

/*:233*/
#line 57 "PadbergRinaldi.w"

/*62:*/
#line 349 "graph.w"

Alloc(last,s_nodes,int);Alloc(succ,s_nodes,int);
#ifdef UNSHRINK
Alloc(pred,s_nodes,int);
#endif

/*:62*/
#line 58 "PadbergRinaldi.w"

/*74:*/
#line 443 "graph.w"

#ifdef DEAD_LIST
Alloc(dead_list,2*(*c_nodes),int);
#endif
#ifdef UNSHRINK
Alloc(stack_pointer,4*(*c_nodes)+2*(*c_edges),int);
#endif

/*:74*/
#line 59 "PadbergRinaldi.w"


/*:255*/
#line 29 "PadbergRinaldi.w"

/*256:*/
#line 61 "PadbergRinaldi.w"

/*7:*/
#line 30 "marks.w"

{
for(c_marks= 0;c_marks<s_nodes;c_marks++)
mark[c_marks]= End_list;
c_marks= 0;
}
#line 1 "header.w"

/*:7*/
#line 62 "PadbergRinaldi.w"

/*64:*/
#line 361 "graph.w"

{int v;
For_nodes(v){
last[v]= v;
succ[v]= End_list;
#ifdef UNSHRINK
pred[v]= End_list;
#endif
}
}

/*:64*/
#line 63 "PadbergRinaldi.w"

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
#line 64 "PadbergRinaldi.w"

/*265:*/
#line 113 "PadbergRinaldi.w"

{int i,a;
For_nodes(i){
star_capacity[i]= Zero;
For_star(i,a)star_capacity[i]+= capacity[a];
}
}

/*:265*/
#line 65 "PadbergRinaldi.w"

/*67:*/
#line 393 "graph.w"

{
int a_neigh;
*mincutvalue= Zero;
For_star(0,a_neigh)*mincutvalue+= capacity[a_neigh];
*ncutarray= 1;
cutarray[0]= orig_name[0];
if(*mincutvalue<=Epsilon)goto freeall;
}


/*:67*/
#line 66 "PadbergRinaldi.w"

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
#line 67 "PadbergRinaldi.w"


/*:256*/
#line 30 "PadbergRinaldi.w"


/*266:*/
#line 131 "PadbergRinaldi.w"

{/*240:*/
#line 104 "naive.w"

int e_shrink;
int n_left;
int n_right;
MCC_cap e_shrink_cap;

/*:240*/
#line 132 "PadbergRinaldi.w"


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
#line 134 "PadbergRinaldi.w"

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
#line 143 "PadbergRinaldi.w"

c_fail++;
}
/*270:*/
#line 242 "PadbergRinaldi.w"

{int i,v,s;
MCC_cap bigcap,maxcap,c;

Remove_marks;
maxcap= -Infinity;
For_active_nodes(v,i){
c= star_capacity[v];
if(c>maxcap){
maxcap= c;
s= v;
}
}
Mark(s,True);
maxcap= -Infinity;
For_neighbors(s,n_neigh,a_neigh){
Mark(n_neigh,True);
bigcap= star_capacity[n_neigh]-Two*capacity[a_neigh];
if(bigcap>maxcap){
maxcap= bigcap;
e_shrink= Edge_of(a_neigh);
edge_flag[e_shrink]= 0;
}
}
Find_end_vertices(e_shrink,n_left,n_right);
e_shrink_cap= capacity[Arc_of(e_shrink)];
For_active_nodes(v,i)if(At_end(mark[v])){
bigcap= star_capacity[v];
if(bigcap>maxcap){
maxcap= bigcap;
n_left= s;
n_right= v;
e_shrink= End_list;
e_shrink_cap= Zero;
}
}
}

/*:270*/
#line 146 "PadbergRinaldi.w"

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
#line 147 "PadbergRinaldi.w"

c_fail++;
/*241:*/
#line 110 "naive.w"

{
/* Out0(2,"*"); */
GoldbergTarjan(G,option,pril,&cutcar,cutlist,&flow,
n_left,n_right,NULL);
}

/*:241*/
#line 149 "PadbergRinaldi.w"

c_maxf++;
why= 0;
reason[why]++;
/*242:*/
#line 117 "naive.w"

if(flow<(*mincutvalue)){int i,v;
*mincutvalue= flow;
*ncutarray= 0;
for(i= 0;i<cutcar;i++)
for(v= cutlist[i];Not_at_end(v);v= succ[v])
cutarray[(*ncutarray)++]= orig_name[v];
if(flow<=Epsilon)goto freeall;
}


#line 1 "GomoryHu.w"
/*:242*/
#line 153 "PadbergRinaldi.w"

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
#line 156 "PadbergRinaldi.w"

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
#line 157 "PadbergRinaldi.w"

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
#line 158 "PadbergRinaldi.w"

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
#line 159 "PadbergRinaldi.w"

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
#line 160 "PadbergRinaldi.w"

}
/* Out2(2,"\n  Failures: %d  Max flows: %d\n",c_fail,c_maxf); */
}

/*:266*/
#line 32 "PadbergRinaldi.w"


if(pril==0)printf("    -1 %5d %5d %5d %5d %5d %5d %6d    -1    -1 ",
reason[0],reason[1],reason[2],reason[3],reason[4],
c_maxf,c_fail);
/*257:*/
#line 69 "PadbergRinaldi.w"

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
#line 71 "PadbergRinaldi.w"

/*63:*/
#line 355 "graph.w"

Free(succ);Free(last);
#ifdef UNSHRINK
Free(pred);
#endif

/*:63*/
#line 72 "PadbergRinaldi.w"

/*237:*/
#line 74 "naive.w"

Free(cutlist);

/*:237*/
#line 73 "PadbergRinaldi.w"

/*4:*/
#line 16 "marks.w"

Free(marked_node);Free(mark);

/*:4*/
#line 74 "PadbergRinaldi.w"

/*264:*/
#line 110 "PadbergRinaldi.w"

Free(star_capacity);

/*:264*/
#line 75 "PadbergRinaldi.w"

/*260:*/
#line 87 "PadbergRinaldi.w"

heap(0,edge_cap,free_heap);
Free(edge_flag);
Free(edge_cap);

/*:260*/
#line 76 "PadbergRinaldi.w"


/*:257*/
#line 37 "PadbergRinaldi.w"

return status;
}
#undef DEAD_LIST

/*:253*/
