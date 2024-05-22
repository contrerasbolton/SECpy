/*224:*/
#line 30 "reinitdistlabels.w"


#include "mincut.h"
#include "common.h"

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
#line 35 "reinitdistlabels.w"
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
#line 37 "reinitdistlabels.w"

/*202:*/
#line 77 "initdistlabels.w"

Alloc(queue,*c_nodes,int);

/*:202*/
#line 38 "reinitdistlabels.w"

/*225:*/
#line 51 "reinitdistlabels.w"

{int v;

for(v= wfirst;Not_at_end(v);v= wsucc[v]){
dist[v]= *c_nodes;
curarc[v]= first[v];
}
for(v= 0;v<*c_nodes;v++)ndist[v]= 0;
}

/*:225*/
#line 39 "reinitdistlabels.w"

/*226:*/
#line 63 "reinitdistlabels.w"

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
#line 65 "reinitdistlabels.w"

while(/*207:*/
#line 126 "initdistlabels.w"

tail_queue<=head_queue

/*:207*/
#line 66 "reinitdistlabels.w"
){int v;
/*208:*/
#line 132 "initdistlabels.w"

v= queue[tail_queue++];

/*:208*/
#line 67 "reinitdistlabels.w"

/*227:*/
#line 77 "reinitdistlabels.w"

{int w,a;
int newdis;

newdis= dist[v]+1;
For_neighbors(v,w,a)
if((dist[w]==*c_nodes)&&awake[w]&&(cap[Mate_of(a)]>Epsilon)){
/*210:*/
#line 182 "initdistlabels.w"

{
dist[w]= newdis;
ndist[newdis]++;
queue[++head_queue]= w;
if(--ndist[*c_nodes]==0)break;
}

/*:210*/
#line 84 "reinitdistlabels.w"

}
}
#line 1 "naive.w"
/*:227*/
#line 68 "reinitdistlabels.w"

}
}

/*:226*/
#line 40 "reinitdistlabels.w"

freeall:
/*203:*/
#line 80 "initdistlabels.w"

Free(queue);

/*:203*/
#line 42 "reinitdistlabels.w"

return status;
}


/*:224*/
