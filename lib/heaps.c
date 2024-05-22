/*105:*/
#line 23 "heaps.w"


#include "common.h"


int Bheap(
int y,
MCC_cap*weight,
int op)

{
static int*p;
static int*pinv;
static int nelements;
/*24:*/
#line 260 "header.w"

int status= MCC_ok;











#line 1 "auxiliary.w"
/*:24*/
#line 37 "heaps.w"


switch(op){
case allocate_heap:/*106:*/
#line 57 "heaps.w"

{
Alloc(p,(y+2),int);Alloc(pinv,(y+2),int);
}

/*:106*/
#line 40 "heaps.w"

break;
case init:/*107:*/
#line 62 "heaps.w"

nelements= 0;

/*:107*/
#line 42 "heaps.w"

break;
case enq:/*108:*/
#line 65 "heaps.w"

{
p[++nelements]= y;
pinv[y]= nelements;
/*109:*/
#line 72 "heaps.w"

{int pos,compos,ppos,pcompos,finished;
MCC_cap wppos,wpcompos;

pos= pinv[y];
finished= False;
while((!finished)&&(pos>1)){
compos= pos/2;
ppos= p[pos];
wppos= weight[ppos];
pcompos= p[compos];
wpcompos= weight[pcompos];
if(wpcompos<wppos){
p[pos]= pcompos;
pinv[pcompos]= pos;
p[compos]= ppos;
pinv[ppos]= compos;
}
else finished= True;
pos= compos;
}
}


/*:109*/
#line 69 "heaps.w"

}

/*:108*/
#line 44 "heaps.w"

break;
case req:/*109:*/
#line 72 "heaps.w"

{int pos,compos,ppos,pcompos,finished;
MCC_cap wppos,wpcompos;

pos= pinv[y];
finished= False;
while((!finished)&&(pos>1)){
compos= pos/2;
ppos= p[pos];
wppos= weight[ppos];
pcompos= p[compos];
wpcompos= weight[pcompos];
if(wpcompos<wppos){
p[pos]= pcompos;
pinv[pcompos]= pos;
p[compos]= ppos;
pinv[ppos]= compos;
}
else finished= True;
pos= compos;
}
}


/*:109*/
#line 46 "heaps.w"

break;
case del:/*110:*/
#line 96 "heaps.w"

{int from,to,k,m,pm,pto,pfrom,pk,maxnode;
MCC_cap max,wpm,wpto,wpfrom;

if(!nelements)return(End_list);
from= 1;
maxnode= p[1];
p[1]= p[nelements];
pinv[p[1]]= 1;
nelements--;
to= nelements;
if(to>1){
k= 1;
while(k){
k= 0;
pto= p[to];wpto= weight[pto];
pfrom= p[from];wpfrom= weight[pfrom];
if((2*from==to)&&(wpto>wpfrom)){
p[from]= pto;pinv[pto]= from;
p[to]= pfrom;pinv[pfrom]= to;
}
else if((2*from+1)<=to){
max= wpfrom;
m= 2*from;
pm= p[m];wpm= weight[pm];
if(wpm>max){
k= m;
max= wpm;
}
m= 2*from+1;
pm= p[m];wpm= weight[pm];
if(wpm>max)k= m;
if(k){
pk= p[k];
p[from]= pk;pinv[pk]= from;
p[k]= pfrom;pinv[pfrom]= k;
}
}
from= k;
}
}
return(maxnode);
}

/*:110*/
#line 48 "heaps.w"

case free_heap:/*111:*/
#line 140 "heaps.w"

Free(p);Free(pinv);

/*:111*/
#line 49 "heaps.w"

break;
default:;
}
freeall:
return(0);
}

/*:105*//*112:*/
#line 146 "heaps.w"



int Fheap(
int y,
MCC_cap*weight,
int op)

{
static int*parent;
static int*child;
static int*lsib;
static int*rsib;
static int*rank_tag;
static int*new_roots;
static int F_heap;
/*24:*/
#line 260 "header.w"

int status= MCC_ok;











#line 1 "auxiliary.w"
/*:24*/
#line 162 "heaps.w"


switch(op){
case allocate_heap:/*113:*/
#line 182 "heaps.w"

{
Alloc(parent,y,int);Alloc(child,y,int);Alloc(lsib,y,int);
Alloc(rsib,y,int);Alloc(rank_tag,y,int);Alloc(new_roots,49,int);
}

/*:113*/
#line 165 "heaps.w"

break;
case init:/*114:*/
#line 188 "heaps.w"

F_heap= End_list;

/*:114*/
#line 167 "heaps.w"

break;
case enq:/*115:*/
#line 191 "heaps.w"

{int u;
MCC_cap d;

d= weight[y];
parent[y]= End_list;
rank_tag[y]= 0;
if(At_end(F_heap)){
F_heap= lsib[y]= rsib[y]= y;
}
else{
u= lsib[F_heap];
lsib[y]= u;
rsib[y]= F_heap;
lsib[F_heap]= rsib[u]= y;
if(weight[F_heap]<d)F_heap= y;
}
}

/*:115*/
#line 169 "heaps.w"

break;
case req:/*116:*/
#line 210 "heaps.w"

{int p,pp;
int u,w;
int r;
MCC_cap d;

d= weight[y];
p= parent[y];
if(At_end(p)){
if(weight[F_heap]<d)F_heap= y;
}
else
if(weight[p]<d)
while(1){
r= rank_tag[p];
if(r>=4){
u= lsib[y];
w= rsib[y];
rsib[u]= w;
lsib[w]= u;
if(child[p]==y)child[p]= w;
}
parent[y]= End_list;
u= lsib[F_heap];
lsib[y]= u;
rsib[y]= F_heap;
lsib[F_heap]= rsib[u]= y;
if(weight[F_heap]<d)F_heap= y;
pp= parent[p];
if(At_end(pp)){
rank_tag[p]= r-2;break;
}
if((r&1)==0){
rank_tag[p]= r-1;break;
}
else
rank_tag[p]= r-2;
y= p;p= pp;
}
}

/*:116*/
#line 171 "heaps.w"

break;
case del:/*117:*/
#line 251 "heaps.w"

{int final_v= F_heap;
int t,u,v,w;
int h= -1;
int r;

if(Not_at_end(F_heap)){
if(rank_tag[F_heap]<2)v= rsib[F_heap];
else{
w= child[F_heap];
v= rsib[w];
rsib[w]= rsib[F_heap];

for(w= v;w!=rsib[F_heap];w= rsib[w])parent[w]= End_list;
}
while(v!=F_heap){
w= rsib[v];
/*118:*/
#line 276 "heaps.w"

{
r= rank_tag[v]>>1;
while(1){
if(h<r){
do{
h++;
new_roots[h]= (h==r?v:End_list);
}while(h<r);
break;
}
if(At_end(new_roots[r])){
new_roots[r]= v;
break;
}
u= new_roots[r];
new_roots[r]= End_list;
if(weight[u]>weight[v]){
rank_tag[v]= r<<1;
t= u;u= v;v= t;
}
/*119:*/
#line 303 "heaps.w"

{
if(r==0){
child[v]= u;
lsib[u]= rsib[u]= u;
}
else{
t= child[v];
rsib[u]= rsib[t];
lsib[u]= t;
lsib[rsib[u]]= rsib[t]= u;
}
parent[u]= v;
}

/*:119*/
#line 297 "heaps.w"

r++;
}
rank_tag[v]= r<<1;
}

/*:118*/
#line 268 "heaps.w"

v= w;
}
/*120:*/
#line 318 "heaps.w"

if(h<0)
F_heap= End_list;
else{MCC_cap d;
u= v= new_roots[h];

d= weight[u];
F_heap= u;
for(h--;h>=0;h--)
if(Not_at_end(new_roots[h])){
w= new_roots[h];
lsib[w]= v;
rsib[v]= w;
if(weight[w]>d){
F_heap= w;
d= weight[w];
}
v= w;
}
rsib[v]= u;
lsib[u]= v;
}

/*:120*/
#line 271 "heaps.w"

}
return(final_v);
}

/*:117*/
#line 173 "heaps.w"

case free_heap:/*121:*/
#line 341 "heaps.w"

Free(parent);Free(child);Free(lsib);
Free(rsib);Free(rank_tag);Free(new_roots);

#line 33 "book.w"

#line 1 "mincut.w"
/*:121*/
#line 174 "heaps.w"

break;
default:;
}
freeall:
return(0);
}

/*:112*/
