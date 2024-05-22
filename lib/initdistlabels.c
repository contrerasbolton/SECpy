/*200:*/
#line 46 "initdistlabels.w"


#include "mincut.h"
#include "common.h"

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
#line 51 "initdistlabels.w"
)
{
/*201:*/
#line 73 "initdistlabels.w"

/*24:*/
#line 260 "header.w"

int status= MCC_ok;











#line 1 "auxiliary.w"
/*:24*/
#line 74 "initdistlabels.w"

int*queue= 0;

/*:201*/
#line 53 "initdistlabels.w"

/*202:*/
#line 77 "initdistlabels.w"

Alloc(queue,*c_nodes,int);

/*:202*/
#line 54 "initdistlabels.w"

/*204:*/
#line 89 "initdistlabels.w"

{int v,i;

For_active_nodes(v,i)dist[v]= *c_nodes;
}

/*:204*/
#line 55 "initdistlabels.w"

/*205:*/
#line 108 "initdistlabels.w"

{int tail_queue,head_queue;
/*206:*/
#line 117 "initdistlabels.w"

{
queue[0]= sink;
tail_queue= head_queue= 0;
dist[sink]= 0;
ndist[0]= 1;
ndist[*c_nodes]= *c_nodes-1;
}

/*:206*/
#line 110 "initdistlabels.w"

while(/*207:*/
#line 126 "initdistlabels.w"

tail_queue<=head_queue

/*:207*/
#line 111 "initdistlabels.w"
){int v;
/*208:*/
#line 132 "initdistlabels.w"

v= queue[tail_queue++];

/*:208*/
#line 112 "initdistlabels.w"

/*209:*/
#line 145 "initdistlabels.w"

{int w,a;
int newdis;

newdis= dist[v]+1;
For_neighbors(v,w,a)
if((dist[w]==*c_nodes)&&(cap[a]>Epsilon)){
/*210:*/
#line 182 "initdistlabels.w"

{
dist[w]= newdis;
ndist[newdis]++;
queue[++head_queue]= w;
if(--ndist[*c_nodes]==0)break;
}

/*:210*/
#line 152 "initdistlabels.w"

}
}

/*:209*/
#line 113 "initdistlabels.w"

}
}

/*:205*/
#line 56 "initdistlabels.w"

freeall:
/*203:*/
#line 80 "initdistlabels.w"

Free(queue);

/*:203*/
#line 58 "initdistlabels.w"

/*212:*/
#line 193 "initdistlabels.w"

*disconnected= dist[source]==*c_nodes?1:0;

/*:212*/
#line 59 "initdistlabels.w"

return status;
}

/*:200*//*216:*/
#line 212 "initdistlabels.w"

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
#line 213 "initdistlabels.w"
)
{
/*201:*/
#line 73 "initdistlabels.w"

/*24:*/
#line 260 "header.w"

int status= MCC_ok;











#line 1 "auxiliary.w"
/*:24*/
#line 74 "initdistlabels.w"

int*queue= 0;

/*:201*/
#line 215 "initdistlabels.w"

/*202:*/
#line 77 "initdistlabels.w"

Alloc(queue,*c_nodes,int);

/*:202*/
#line 216 "initdistlabels.w"

/*217:*/
#line 224 "initdistlabels.w"

{int v,i;

For_active_nodes(v,i)dist[v]= 2*(*c_nodes);
}

/*:217*/
#line 217 "initdistlabels.w"

/*218:*/
#line 230 "initdistlabels.w"

{int tail_queue,head_queue;

/*219:*/
#line 240 "initdistlabels.w"

{
queue[0]= source;
tail_queue= head_queue= 0;
dist[source]= *c_nodes;
}

/*:219*/
#line 233 "initdistlabels.w"

while(/*207:*/
#line 126 "initdistlabels.w"

tail_queue<=head_queue

/*:207*/
#line 234 "initdistlabels.w"
){int v;
/*208:*/
#line 132 "initdistlabels.w"

v= queue[tail_queue++];

/*:208*/
#line 235 "initdistlabels.w"

/*220:*/
#line 247 "initdistlabels.w"

{int w,a;
int newdis;

newdis= dist[v]+1;
For_neighbors(v,w,a)
if((dist[w]==2*(*c_nodes))&&(cap[Mate_of(a)]>Epsilon)){
/*221:*/
#line 258 "initdistlabels.w"

{
dist[w]= newdis;
if(w!=sink)queue[++head_queue]= w;
}
#line 1 "reinitdistlabels.w"

/*:221*/
#line 254 "initdistlabels.w"

}
}

/*:220*/
#line 236 "initdistlabels.w"

}
}

/*:218*/
#line 218 "initdistlabels.w"

freeall:
/*203:*/
#line 80 "initdistlabels.w"

Free(queue);

/*:203*/
#line 220 "initdistlabels.w"

return status;
}

/*:216*/
