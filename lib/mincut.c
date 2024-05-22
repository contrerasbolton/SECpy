/*124:*/
#line 7 "mincut.w"


#include "common.h"

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
#line 11 "mincut.w"
)
{

/*24:*/
#line 260 "header.w"

int status= MCC_ok;











#line 1 "auxiliary.w"
/*:24*/
#line 14 "mincut.w"

/*28:*/
#line 17 "graph.w"
MCC_graph g;
MCC_graph*G= &g;

/*:28*/
#line 15 "mincut.w"

/*51:*/
#line 228 "graph.w"

int*tmp_h= 0;
int*tmp_t= 0;
MCC_cap*tmp_c= 0;
int*pnt= 0;
int*index= 0;
int*out_degree= 0;

/*:51*/
#line 16 "mincut.w"

/*95:*/
#line 21 "hash.w"

Hash hash_area= {0,0,0,{0},0,0,0,0};
Hash*H= &hash_area;

/*:95*/
#line 17 "mincut.w"

/*50:*/
#line 198 "graph.w"

{int j,e,t,h,c_actual_edges;
MCC_cap xe;

/*30:*/
#line 27 "graph.w"

int s_nodes,s_edges,*c_nodes,*c_edges,*first,*prev,*next,*tip;
int*orig_name,*active_pos,*active_node;
MCC_cap*capacity;

/*:30*/
#line 202 "graph.w"


Graphalloc(nnod,nedg);
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
#line 205 "graph.w"


if(do_sort)/*52:*/
#line 236 "graph.w"

Alloc(tmp_h,nedg,int);
Alloc(tmp_t,nedg,int);
Alloc(tmp_c,nedg,MCC_cap);
Alloc(pnt,nedg,int);
Alloc(index,nnod,int);
Calloc(out_degree,nnod,int);

/*:52*/
#line 207 "graph.w"

*c_edges= c_actual_edges= 0;
if(canonical_names){
/*54:*/
#line 248 "graph.w"

{
*c_nodes= nnod;
For_nodes(j)/*55:*/
#line 254 "graph.w"

{
orig_name[j]= active_pos[j]= active_node[j]= j;
first[j]= End_list;
}

/*:55*/
#line 251 "graph.w"

}

/*:54*/
#line 210 "graph.w"

/*56:*/
#line 260 "graph.w"

{
for(e= 0;e<nedg;e++){
xe= ecap[e];
t= tail[e];
h= head[e];
if((t<0)||(t>=*c_nodes)||(h<0)||(h>=*c_nodes)||
(xe<-Epsilon))Error(MCC_invalid_data);
if(xe>Epsilon){
if(do_sort)/*57:*/
#line 275 "graph.w"

{
tmp_t[c_actual_edges]= t;
tmp_h[c_actual_edges]= h;
tmp_c[c_actual_edges]= xe;
pnt[c_actual_edges]= c_actual_edges;
out_degree[t]++;
c_actual_edges++;
}

/*:57*/
#line 269 "graph.w"

else Insert_edge(t,h,xe);
}
}
}

/*:56*/
#line 211 "graph.w"

}
else{
/*58:*/
#line 285 "graph.w"

{
*c_nodes= (ncno<=0)?nnod:ncno;
H->size= *c_nodes;
H->key_len= sizeof(int);
/*98:*/
#line 72 "hash.w"

{long i;

Alloc(H->keys,H->size*H->key_len,char);
Alloc(H->head,H->size,long);
Alloc(H->link,H->size,long);
Alloc(H->key.C,H->key_len,char);
for(i= 0;i<H->size;i++)H->head[i]= End_list;
H->last_index= 0;
}

/*:98*/
#line 290 "graph.w"


if(ncno>0)
For_nodes(j){
H->key.I[0]= node[j];
/*101:*/
#line 97 "hash.w"

{long p;
long missing;
/*100:*/
#line 86 "hash.w"

{unsigned char*t;
long i;

for(i= 0,t= (unsigned char*)H->key.C,H->index= 0;i<H->key_len;i++,t++){
H->index+= (H->index^(H->index>>1))+HASH_MULT*(*t);
while(H->index>=HASH_PRIME)H->index-= HASH_PRIME;
}
H->index= H->index%H->size;
}

/*:100*/
#line 100 "hash.w"

p= H->head[H->index];
if(At_end(p)){
/*102:*/
#line 120 "hash.w"

if(H->last_index<H->size){
H->link[H->last_index]= H->head[H->index];
H->head[H->index]= H->last_index;
(void)memcpy(H->keys+H->last_index*H->key_len,H->key.C,
(size_t)H->key_len);
H->index= H->last_index++;
}
else{
H->index= End_list;
}

/*:102*/
#line 103 "hash.w"

}
else{
while((missing= (memcmp(H->keys+p*H->key_len,
H->key.C,(size_t)H->key_len)!=0))
&&Not_at_end(H->link[p])){
p= H->link[p];
}
if(missing){
/*102:*/
#line 120 "hash.w"

if(H->last_index<H->size){
H->link[H->last_index]= H->head[H->index];
H->head[H->index]= H->last_index;
(void)memcpy(H->keys+H->last_index*H->key_len,H->key.C,
(size_t)H->key_len);
H->index= H->last_index++;
}
else{
H->index= End_list;
}

/*:102*/
#line 112 "hash.w"

}
else{
H->index= End_list;
}
}
}

/*:101*/
#line 295 "graph.w"

if(Not_at_end(H->index))/*60:*/
#line 329 "graph.w"

{
orig_name[H->index]= H->key.I[0];
active_node[H->index]= active_pos[H->index]= H->index;
first[H->index]= End_list;
}

/*:60*/
#line 296 "graph.w"

}
}

/*:58*/
#line 214 "graph.w"

/*59:*/
#line 300 "graph.w"

{
for(e= 0;e<nedg;e++){
xe= ecap[e];
H->key.I[0]= tail[e];
/*103:*/
#line 132 "hash.w"

{long p;

/*100:*/
#line 86 "hash.w"

{unsigned char*t;
long i;

for(i= 0,t= (unsigned char*)H->key.C,H->index= 0;i<H->key_len;i++,t++){
H->index+= (H->index^(H->index>>1))+HASH_MULT*(*t);
while(H->index>=HASH_PRIME)H->index-= HASH_PRIME;
}
H->index= H->index%H->size;
}

/*:100*/
#line 135 "hash.w"

p= H->head[H->index];
while(Not_at_end(p)&&
(memcmp(H->keys+p*H->key_len,H->key.C,(size_t)H->key_len)!=0))
p= H->link[p];
H->index= p;
}
#line 1 "heaps.w"
/*:103*/
#line 305 "graph.w"

if((ncno<=0)&&At_end(H->index)){
/*101:*/
#line 97 "hash.w"

{long p;
long missing;
/*100:*/
#line 86 "hash.w"

{unsigned char*t;
long i;

for(i= 0,t= (unsigned char*)H->key.C,H->index= 0;i<H->key_len;i++,t++){
H->index+= (H->index^(H->index>>1))+HASH_MULT*(*t);
while(H->index>=HASH_PRIME)H->index-= HASH_PRIME;
}
H->index= H->index%H->size;
}

/*:100*/
#line 100 "hash.w"

p= H->head[H->index];
if(At_end(p)){
/*102:*/
#line 120 "hash.w"

if(H->last_index<H->size){
H->link[H->last_index]= H->head[H->index];
H->head[H->index]= H->last_index;
(void)memcpy(H->keys+H->last_index*H->key_len,H->key.C,
(size_t)H->key_len);
H->index= H->last_index++;
}
else{
H->index= End_list;
}

/*:102*/
#line 103 "hash.w"

}
else{
while((missing= (memcmp(H->keys+p*H->key_len,
H->key.C,(size_t)H->key_len)!=0))
&&Not_at_end(H->link[p])){
p= H->link[p];
}
if(missing){
/*102:*/
#line 120 "hash.w"

if(H->last_index<H->size){
H->link[H->last_index]= H->head[H->index];
H->head[H->index]= H->last_index;
(void)memcpy(H->keys+H->last_index*H->key_len,H->key.C,
(size_t)H->key_len);
H->index= H->last_index++;
}
else{
H->index= End_list;
}

/*:102*/
#line 112 "hash.w"

}
else{
H->index= End_list;
}
}
}

/*:101*/
#line 307 "graph.w"

/*60:*/
#line 329 "graph.w"

{
orig_name[H->index]= H->key.I[0];
active_node[H->index]= active_pos[H->index]= H->index;
first[H->index]= End_list;
}

/*:60*/
#line 308 "graph.w"

}
t= H->index;
if(At_end(t)&&ncno>0)continue;
if(At_end(t)||(xe<-Epsilon))Error(MCC_invalid_data);
H->key.I[0]= head[e];
/*103:*/
#line 132 "hash.w"

{long p;

/*100:*/
#line 86 "hash.w"

{unsigned char*t;
long i;

for(i= 0,t= (unsigned char*)H->key.C,H->index= 0;i<H->key_len;i++,t++){
H->index+= (H->index^(H->index>>1))+HASH_MULT*(*t);
while(H->index>=HASH_PRIME)H->index-= HASH_PRIME;
}
H->index= H->index%H->size;
}

/*:100*/
#line 135 "hash.w"

p= H->head[H->index];
while(Not_at_end(p)&&
(memcmp(H->keys+p*H->key_len,H->key.C,(size_t)H->key_len)!=0))
p= H->link[p];
H->index= p;
}
#line 1 "heaps.w"
/*:103*/
#line 314 "graph.w"

if((ncno<=0)&&At_end(H->index)){
/*101:*/
#line 97 "hash.w"

{long p;
long missing;
/*100:*/
#line 86 "hash.w"

{unsigned char*t;
long i;

for(i= 0,t= (unsigned char*)H->key.C,H->index= 0;i<H->key_len;i++,t++){
H->index+= (H->index^(H->index>>1))+HASH_MULT*(*t);
while(H->index>=HASH_PRIME)H->index-= HASH_PRIME;
}
H->index= H->index%H->size;
}

/*:100*/
#line 100 "hash.w"

p= H->head[H->index];
if(At_end(p)){
/*102:*/
#line 120 "hash.w"

if(H->last_index<H->size){
H->link[H->last_index]= H->head[H->index];
H->head[H->index]= H->last_index;
(void)memcpy(H->keys+H->last_index*H->key_len,H->key.C,
(size_t)H->key_len);
H->index= H->last_index++;
}
else{
H->index= End_list;
}

/*:102*/
#line 103 "hash.w"

}
else{
while((missing= (memcmp(H->keys+p*H->key_len,
H->key.C,(size_t)H->key_len)!=0))
&&Not_at_end(H->link[p])){
p= H->link[p];
}
if(missing){
/*102:*/
#line 120 "hash.w"

if(H->last_index<H->size){
H->link[H->last_index]= H->head[H->index];
H->head[H->index]= H->last_index;
(void)memcpy(H->keys+H->last_index*H->key_len,H->key.C,
(size_t)H->key_len);
H->index= H->last_index++;
}
else{
H->index= End_list;
}

/*:102*/
#line 112 "hash.w"

}
else{
H->index= End_list;
}
}
}

/*:101*/
#line 316 "graph.w"

/*60:*/
#line 329 "graph.w"

{
orig_name[H->index]= H->key.I[0];
active_node[H->index]= active_pos[H->index]= H->index;
first[H->index]= End_list;
}

/*:60*/
#line 317 "graph.w"

}
h= H->index;
if(At_end(h)&&ncno>0)continue;
if(At_end(h))Error(MCC_invalid_data);
if(xe>Epsilon){
if(do_sort)/*57:*/
#line 275 "graph.w"

{
tmp_t[c_actual_edges]= t;
tmp_h[c_actual_edges]= h;
tmp_c[c_actual_edges]= xe;
pnt[c_actual_edges]= c_actual_edges;
out_degree[t]++;
c_actual_edges++;
}

/*:57*/
#line 323 "graph.w"

else Insert_edge(t,h,xe);
}
}
}

/*:59*/
#line 215 "graph.w"

/*99:*/
#line 83 "hash.w"

Free(H->keys);Free(H->head);Free(H->link);Free(H->key.C);

/*:99*/
#line 216 "graph.w"

}
if(do_sort){
/*68:*/
#line 406 "graph.w"

/*69:*/
#line 411 "graph.w"

{int v;
index[0]= 0;
for(v= 0;v<*c_nodes-1;v++)index[v+1]= index[v]+out_degree[v];
}

/*:69*/
#line 407 "graph.w"
;
/*70:*/
#line 417 "graph.w"

{int e;
for(e= 0;e<c_actual_edges;e++)pnt[e]= index[tmp_t[e]]++;
}

/*:70*/
#line 408 "graph.w"
;


/*:68*/
#line 219 "graph.w"

for(j= 0;j<c_actual_edges;j++){
e= pnt[j];
Insert_edge(tmp_t[e],tmp_h[e],tmp_c[e]);
}
}
/*53:*/
#line 244 "graph.w"

Free(out_degree);Free(index);Free(pnt);
Free(tmp_c);Free(tmp_t);Free(tmp_h);

/*:53*/
#line 225 "graph.w"

}

/*:50*/
#line 18 "mincut.w"


status= (*mcc_fun)(G,option,pril,ncutarray,cutarray,mincutvalue);

freeall:
/*49:*/
#line 190 "graph.w"

Free(g.active_pos);Free(g.active_node);
Free(g.capacity);Free(g.orig_name);Free(g.tip);
Free(g.next);Free(g.prev);Free(g.first);

/*:49*/
#line 23 "mincut.w"

/*99:*/
#line 83 "hash.w"

Free(H->keys);Free(H->head);Free(H->link);Free(H->key.C);

/*:99*/
#line 24 "mincut.w"

/*53:*/
#line 244 "graph.w"

Free(out_degree);Free(index);Free(pnt);
Free(tmp_c);Free(tmp_t);Free(tmp_h);

/*:53*/
#line 25 "mincut.w"

return status;
}


/*:124*/
