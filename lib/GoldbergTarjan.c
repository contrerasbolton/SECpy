/*148:*/
#line 98 "GoldbergTarjan.w"


#include "mincut.h"
#include "common.h"

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
#line 103 "GoldbergTarjan.w"
)
{
/*24:*/
#line 260 "header.w"

int status= MCC_ok;











#line 1 "auxiliary.w"
/*:24*/
#line 105 "GoldbergTarjan.w"

/*149:*/
#line 124 "GoldbergTarjan.w"

/*150:*/
#line 139 "GoldbergTarjan.w"

int*firstact= 0;
int*succact= 0;
int hd;


/*:150*/
#line 125 "GoldbergTarjan.w"

/*153:*/
#line 160 "GoldbergTarjan.w"

int wfirst;
int*wsucc= 0;
int*wpred= 0;
int*awake= 0;

/*:153*/
#line 126 "GoldbergTarjan.w"

/*156:*/
#line 184 "GoldbergTarjan.w"

MCC_cap*rcap= 0;
MCC_cap*excess= 0;
int*dist= 0;
int*ndist= 0;
int*currentarc= 0;

/*:156*/
#line 127 "GoldbergTarjan.w"

/*159:*/
#line 202 "GoldbergTarjan.w"

int bound;
int nrelabel;
int minrelabel;

/*:159*/
#line 128 "GoldbergTarjan.w"

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
#line 129 "GoldbergTarjan.w"


/*:149*/
#line 106 "GoldbergTarjan.w"

/*151:*/
#line 145 "GoldbergTarjan.w"

{
Alloc(succact,s_nodes,int);Alloc(firstact,2*(*c_nodes)+1,int);
}

/*:151*//*154:*/
#line 166 "GoldbergTarjan.w"

{
Alloc(wsucc,s_nodes,int);Alloc(wpred,s_nodes,int);Alloc(awake,s_nodes,int);
}

/*:154*//*157:*/
#line 191 "GoldbergTarjan.w"

{
Alloc(rcap,2*s_edges,MCC_cap);Alloc(excess,s_nodes,MCC_cap);
Alloc(dist,s_nodes,int);Calloc(ndist,2*(*c_nodes),int);
Alloc(currentarc,s_nodes,int);
}

/*:157*/
#line 107 "GoldbergTarjan.w"

/*160:*/
#line 207 "GoldbergTarjan.w"

if(*c_nodes<2)
Error(MCC_invalid_data);

/*:160*/
#line 108 "GoldbergTarjan.w"

/*161:*/
#line 219 "GoldbergTarjan.w"

{int v,i;

memcpy(currentarc,first,s_nodes*sizeof(int));
memcpy(rcap,capacity,2*s_edges*sizeof(MCC_cap));
hd= 0;
bound= *c_nodes-1;
nrelabel= 0;
minrelabel= *c_nodes;

wfirst= End_list;
For_active_nodes(v,i)if(v!=source){
wsucc[v]= wfirst;
if(Not_at_end(wfirst))wpred[wfirst]= v;
wfirst= v;
}
if(At_end(wfirst))Error(MCC_invalid_data);
wpred[wfirst]= End_list;
For_active_nodes(v,i)excess[v]= Zero;

for(i= 0;i<2*(*c_nodes)+1;i++)firstact[i]= End_list;
}

/*:161*/
#line 109 "GoldbergTarjan.w"

/*162:*/
#line 250 "GoldbergTarjan.w"

{int disconnected;

status= initdistlabels(source,sink,c_nodes,active_node,
tip,first,
next,capacity,dist,ndist,&disconnected);

if(status)
goto freeall;

if(disconnected){
/*185:*/
#line 624 "GoldbergTarjan.w"

{int v,i;

*mincutvalue= excess[sink];
*ncutarray= 0;
For_active_nodes(v,i)
if(dist[v]>=*c_nodes)cutarray[(*ncutarray)++]= v;
}

/*:185*/
#line 261 "GoldbergTarjan.w"

/*152:*/
#line 150 "GoldbergTarjan.w"

Free(succact);Free(firstact);


/*:152*//*155:*/
#line 171 "GoldbergTarjan.w"

Free(wsucc);Free(wpred);Free(awake);

/*:155*//*158:*/
#line 198 "GoldbergTarjan.w"

Free(rcap);Free(excess);Free(dist);Free(ndist);
Free(currentarc);

/*:158*/
#line 262 "GoldbergTarjan.w"

goto freeall;
}
}

/*:162*/
#line 110 "GoldbergTarjan.w"

/*163:*/
#line 277 "GoldbergTarjan.w"

{int a,w;
MCC_cap delta;

For_neighbors(source,w,a){
if(dist[w]<*c_nodes){
delta= rcap[a];
if(delta>Epsilon){
rcap[a]= Zero;
rcap[Mate_of(a)]+= delta;
if(excess[w]<=Epsilon){
/*164:*/
#line 303 "GoldbergTarjan.w"

{int dw;

dw= dist[w];
if((w!=sink)&&(w!=source)){
succact[w]= firstact[dw];
firstact[dw]= w;
if(dw>hd)hd= dw;
}
}

/*:164*/
#line 288 "GoldbergTarjan.w"

}
excess[w]+= delta;
excess[source]-= delta;
}
}
}
}

/*:163*/
#line 111 "GoldbergTarjan.w"

/*165:*/
#line 320 "GoldbergTarjan.w"

{
ndist[dist[source]]--;
dist[source]= *c_nodes;
}

/*:165*/
#line 112 "GoldbergTarjan.w"

/*166:*/
#line 334 "GoldbergTarjan.w"

{int v,dv,a;
while(/*168:*/
#line 377 "GoldbergTarjan.w"

hd>0

/*:168*/
#line 336 "GoldbergTarjan.w"
){
/*169:*/
#line 385 "GoldbergTarjan.w"

{
v= firstact[hd];
if(Not_at_end(v))firstact[hd]= succact[v];
}

/*:169*/
#line 337 "GoldbergTarjan.w"

while(Not_at_end(v)){
/*170:*/
#line 396 "GoldbergTarjan.w"

{
for(a= currentarc[v];Not_at_end(a);a= next[a])
if((dist[v]==dist[tip[a]]+1)&&(rcap[a]>Epsilon))break;
currentarc[v]= a;
}

/*:170*/
#line 339 "GoldbergTarjan.w"

if(Not_at_end(a)){
/*171:*/
#line 410 "GoldbergTarjan.w"

{int w;
MCC_cap delta;

if(excess[v]<=rcap[a]+Epsilon){
/*172:*/
#line 431 "GoldbergTarjan.w"

{
delta= excess[v];
rcap[a]-= delta;
excess[v]= Zero;
v= End_list;
}

/*:172*/
#line 415 "GoldbergTarjan.w"

}
else{
/*173:*/
#line 439 "GoldbergTarjan.w"

{
delta= rcap[a];
rcap[a]= Zero;
excess[v]-= delta;
}

/*:173*/
#line 418 "GoldbergTarjan.w"

}
rcap[Mate_of(a)]+= delta;
w= tip[a];
if(excess[w]<=Epsilon){
/*164:*/
#line 303 "GoldbergTarjan.w"

{int dw;

dw= dist[w];
if((w!=sink)&&(w!=source)){
succact[w]= firstact[dw];
firstact[dw]= w;
if(dw>hd)hd= dw;
}
}

/*:164*/
#line 423 "GoldbergTarjan.w"

}
excess[w]+= delta;
}

/*:171*/
#line 341 "GoldbergTarjan.w"

}
else{
/*175:*/
#line 464 "GoldbergTarjan.w"

{int newdis,firsta;

dv= dist[v];
/*176:*/
#line 490 "GoldbergTarjan.w"

{int w;

newdis= bound;
For_neighbors(v,w,a)
if((rcap[a]>Epsilon)&&(dist[w]<newdis)){
newdis= dist[w];
firsta= a;
break;
}
for(;Not_at_end(a);a= next[a]){
w= tip[a];
if((rcap[a]>Epsilon)&&(dist[w]<newdis))newdis= dist[w];
}
}

/*:176*/
#line 468 "GoldbergTarjan.w"


if(newdis==bound){
/*177:*/
#line 513 "GoldbergTarjan.w"

{
if(v==wfirst){
wfirst= wsucc[v];
if(Not_at_end(wfirst))wpred[wfirst]= End_list;
}
else{
if(Not_at_end(wsucc[v]))wpred[wsucc[v]]= wpred[v];
if(Not_at_end(wpred[v]))wsucc[wpred[v]]= wsucc[v];
}
ndist[dist[v]]--;
dist[v]= *c_nodes;
bound--;
v= End_list;
}

/*:177*/
#line 471 "GoldbergTarjan.w"

}
else if(ndist[dv]){
/*178:*/
#line 529 "GoldbergTarjan.w"

{
newdis++;
ndist[dist[v]]--;
dist[v]= newdis;
ndist[newdis]++;
currentarc[v]= firsta;
hd= newdis;
}

/*:178*/
#line 474 "GoldbergTarjan.w"

}
if(!ndist[dv]){
/*180:*/
#line 558 "GoldbergTarjan.w"

{int g;

firstact[dv]= End_list;
for(g= wfirst;Not_at_end(g);g= wsucc[g])
if((dv<=dist[g])&&(dist[g]<*c_nodes)){
ndist[dist[g]]--;
dist[g]= *c_nodes;
/*181:*/
#line 572 "GoldbergTarjan.w"

{
if(g==wfirst){
wfirst= wsucc[wfirst];
if(Not_at_end(wfirst))wpred[wfirst]= End_list;
}
else{
if(Not_at_end(wsucc[g]))wpred[wsucc[g]]= wpred[g];
if(Not_at_end(wpred[g]))wsucc[wpred[g]]= wsucc[g];
}
}

/*:181*/
#line 566 "GoldbergTarjan.w"

bound--;
}
v= End_list;
}

/*:180*/
#line 477 "GoldbergTarjan.w"

}
++nrelabel;
}

/*:175*/
#line 344 "GoldbergTarjan.w"

}
}
if(nrelabel>=minrelabel){
/*182:*/
#line 587 "GoldbergTarjan.w"

{int v,i;
nrelabel= 0;
For_active_nodes(v,i)awake[v]= (dist[v]<*c_nodes)?True:False;

status= reinitdistlabels(source,sink,c_nodes,active_node,tip,
first,next,rcap,currentarc,
awake,wfirst,wsucc,dist,ndist);

if(status)goto freeall;

/*183:*/
#line 604 "GoldbergTarjan.w"

for(i= 0;i<=*c_nodes;i++)firstact[i]= End_list;

hd= 0;
for(v= wfirst;Not_at_end(v);v= wsucc[v])if(excess[v]>Epsilon){
dv= dist[v];
succact[v]= firstact[dv];
firstact[dv]= v;
if(dv>hd)hd= dv;
}

/*:183*/
#line 598 "GoldbergTarjan.w"

}

/*:182*/
#line 348 "GoldbergTarjan.w"

}
else{
/*184:*/
#line 618 "GoldbergTarjan.w"

while(hd&&(At_end(firstact[hd])))--hd;

/*:184*/
#line 351 "GoldbergTarjan.w"

}
}
}

/*:166*/
#line 113 "GoldbergTarjan.w"

/*185:*/
#line 624 "GoldbergTarjan.w"

{int v,i;

*mincutvalue= excess[sink];
*ncutarray= 0;
For_active_nodes(v,i)
if(dist[v]>=*c_nodes)cutarray[(*ncutarray)++]= v;
}

/*:185*/
#line 114 "GoldbergTarjan.w"

#ifdef TTT
/*186:*/
#line 634 "GoldbergTarjan.w"

{
int a;
int v,dv;

Err0("time for phase 1:");
printtime(stderr,cputime()-cpuphase1);
Err0("\n");
cpuphase2= cputime();
status= initdistlabels_phase2(source,sink,*c_nodes,active_node,
tip,first,next,rcap,dist);
if(status)goto freeall;

/*187:*/
#line 661 "GoldbergTarjan.w"

{int v,i;

For_active_nodes(v,i){
currentarc[v]= first[v];
if(excess[v]>Epsilon){
dv= dist[v];
if((v!=source)&&(v!=sink)){
succact[v]= firstact[dv];
firstact[dv]= v;
if(dv>hd)hd= dv;
}
}
}
bound= 2*(*c_nodes);

}

/*:187*/
#line 647 "GoldbergTarjan.w"

/*188:*/
#line 679 "GoldbergTarjan.w"

while(/*168:*/
#line 377 "GoldbergTarjan.w"

hd>0

/*:168*/
#line 680 "GoldbergTarjan.w"
){
/*169:*/
#line 385 "GoldbergTarjan.w"

{
v= firstact[hd];
if(Not_at_end(v))firstact[hd]= succact[v];
}

/*:169*/
#line 681 "GoldbergTarjan.w"

while(Not_at_end(v)){
/*170:*/
#line 396 "GoldbergTarjan.w"

{
for(a= currentarc[v];Not_at_end(a);a= next[a])
if((dist[v]==dist[tip[a]]+1)&&(rcap[a]>Epsilon))break;
currentarc[v]= a;
}

/*:170*/
#line 683 "GoldbergTarjan.w"

if(Not_at_end(a)){
/*171:*/
#line 410 "GoldbergTarjan.w"

{int w;
MCC_cap delta;

if(excess[v]<=rcap[a]+Epsilon){
/*172:*/
#line 431 "GoldbergTarjan.w"

{
delta= excess[v];
rcap[a]-= delta;
excess[v]= Zero;
v= End_list;
}

/*:172*/
#line 415 "GoldbergTarjan.w"

}
else{
/*173:*/
#line 439 "GoldbergTarjan.w"

{
delta= rcap[a];
rcap[a]= Zero;
excess[v]-= delta;
}

/*:173*/
#line 418 "GoldbergTarjan.w"

}
rcap[Mate_of(a)]+= delta;
w= tip[a];
if(excess[w]<=Epsilon){
/*164:*/
#line 303 "GoldbergTarjan.w"

{int dw;

dw= dist[w];
if((w!=sink)&&(w!=source)){
succact[w]= firstact[dw];
firstact[dw]= w;
if(dw>hd)hd= dw;
}
}

/*:164*/
#line 423 "GoldbergTarjan.w"

}
excess[w]+= delta;
}

/*:171*/
#line 685 "GoldbergTarjan.w"

}
else{
/*189:*/
#line 694 "GoldbergTarjan.w"

{
int newdis,firsta;

dv= dist[v];
/*176:*/
#line 490 "GoldbergTarjan.w"

{int w;

newdis= bound;
For_neighbors(v,w,a)
if((rcap[a]>Epsilon)&&(dist[w]<newdis)){
newdis= dist[w];
firsta= a;
break;
}
for(;Not_at_end(a);a= next[a]){
w= tip[a];
if((rcap[a]>Epsilon)&&(dist[w]<newdis))newdis= dist[w];
}
}

/*:176*/
#line 699 "GoldbergTarjan.w"


if(newdis==bound){
Err0("GT phase 2: relabeling failed\n");
exit(1);
}
else{
/*190:*/
#line 714 "GoldbergTarjan.w"

newdis++;
ndist[dist[v]]--;
dist[v]= newdis;
ndist[newdist]++;
currentarc[v]= firsta;
hd= newdis;

/*:190*/
#line 706 "GoldbergTarjan.w"

}
}

/*:189*/
#line 688 "GoldbergTarjan.w"

}
}
/*184:*/
#line 618 "GoldbergTarjan.w"

while(hd&&(At_end(firstact[hd])))--hd;

/*:184*/
#line 691 "GoldbergTarjan.w"

}

/*:188*/
#line 648 "GoldbergTarjan.w"

Err0("time for phase 2:");
printtime(stderr,cputime()-cpuphase2);
Err0("\n");
/*191:*/
#line 722 "GoldbergTarjan.w"

/*192:*/
#line 726 "GoldbergTarjan.w"

if(fabs(excess[source]+excess[sink])<Epsilon)
Err0("maxflow == mincut\n");
else{
Err1("excess[source] = %lf\n",excess[source]);
Err1("excess[sink]   = %lf\n",excess[sink]);
}

/*:192*/
#line 723 "GoldbergTarjan.w"

/*193:*/
#line 734 "GoldbergTarjan.w"

{int v,i;
For_active_nodes(v,i)
if((excess[v]>Epsilon)&&(v!=source)&&(v!=sink))
Err("excess[%d] = %lf\n",v,excess[v]);
}

/*:193*/
#line 724 "GoldbergTarjan.w"


/*:191*/
#line 652 "GoldbergTarjan.w"

/*194:*/
#line 741 "GoldbergTarjan.w"

{int a,v,i;
if(flow)
For_active_nodes(v,i)
For_star(v,a)
flow[a]= cap[a]-rcap[a];


#line 1 "initdistlabels.w"

/*:194*/
#line 653 "GoldbergTarjan.w"
;
}

/*:186*/
#line 116 "GoldbergTarjan.w"

#endif
freeall:
/*152:*/
#line 150 "GoldbergTarjan.w"

Free(succact);Free(firstact);


/*:152*//*155:*/
#line 171 "GoldbergTarjan.w"

Free(wsucc);Free(wpred);Free(awake);

/*:155*//*158:*/
#line 198 "GoldbergTarjan.w"

Free(rcap);Free(excess);Free(dist);Free(ndist);
Free(currentarc);

/*:158*/
#line 119 "GoldbergTarjan.w"

return status;

}

/*:148*/
