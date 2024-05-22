#include <iostream>
#include <vector>
#include <stdio.h>

#include "SEC.hpp"
#include "common.h"

using namespace std;
extern MCC_fun PadbergRinaldi;
// g++ -DSYSV -DMCC_DOUBLE -DLINUX -O3 -Wall -fPIC -fno-strict-aliasing -DIL_STD -std=c++14 -Wno-reorder -Wno-ignored-attributes -I/opt/ibm/ILOG/CPLEX_Studio128/cplex/include -I/opt/ibm/ILOG/CPLEX_Studio128/concert/include -c test.c -o test.o
// g++ auxiliary.o reinitdistlabels.o heaps.o GoldbergTarjan.o PadbergRinaldi.o mincut.o initdistlabels.o PadbergRinaldiPrep.o -shared -o test.so -fPIC test.o

void free_memory(double *ptr) {
    free(ptr);
}


int* separation_procedure(double *x, int nnod, int *nSet) {
 
  int e;

  int canonical_names= 0;
  int pril= 0;
  int do_sort= 0;
  int option= 0;
  MCC_fun*algo = &PadbergRinaldi;

  int nedg = 0;
  int ncno;
  int*tail= 0;
  int*head= 0;
  MCC_cap*ecap= 0;
  int*node= 0;

  int ncutarray;
  MCC_cap mincutvalue;
  int*cutarray= 0;
  int status= MCC_ok;

  vector<vector<double> > edge(nnod, vector<double>(nnod, 0.0));

  for(auto i = 0; i < nnod; ++i)
    {
      for(auto j = 0; j < nnod; ++j)
        {
          double y = x[i * nnod + j] + x[i * nnod + j];
          if(y > 0.0)
            {
              int jj = j;
              int ii = i;

              if(edge[ii][jj] == 0.0 && ii != jj)
                {
                  nedg++;
                  edge[ii][jj] = edge[jj][ii] = y;
                }
            }
        }
    }

  //nedg = m;
  //nnod = n;
  Alloc(tail,nedg,int);
  Alloc(head,nedg,int);
  Alloc(ecap,nedg,MCC_cap);
  Alloc(node,nnod,int);
  Alloc(cutarray,nnod,int);

  // cout << "edges " << m << endl;
  e = 0;
  for(auto i = 0; i < nnod; ++i)
    {
      for(auto j = 0; j < nnod; ++j)
        {
          if(edge[i][j] > 0.0 && i != j)
            {
              //cout << i << " " << j << " " << edge[i][j] << endl;
              int aux[2];
              aux[0] = i;
              aux[1] = j;
              if(aux[0] > aux[1])
                {
                  int aux2 = aux[0];
                  aux[0] = aux[1];
                  aux[1] = aux2;
                }
              tail[e] = aux[0];
              head[e] = aux[1];
              ecap[e] = (MCC_cap) edge[i][j];
              e++;
              // if(i != j)
              edge[i][j] = edge[j][i] = 0.0;

            }
        }
    }
  ncno = nnod;
  for(auto j= 0;j<ncno;j++)
    node[j] = j;
  
  //type of output
  pril = 3;
  //printf("%d %d %d %d %d %d %d\n",nnod,nedg, ncno, canonical_names, option, do_sort, pril);
  do_sort = 1;

  status = mincut(nnod, nedg, ncno, canonical_names, node, tail, head, ecap,
                  algo, option, do_sort, pril,
                  &ncutarray, cutarray, &mincutvalue);

  if(status!=MCC_ok)
    {
      cout << "error" << endl;
      exit(0);
    }

  //Out1(0,"%10.4lf",((double)mincutvalue));
  //printf("\n");
  //printf("min is %10.20lf\n",((double)mincutvalue));

  {
  freeall:
    Free(tail);
    Free(head);
    Free(ecap);
    Free(node);
  }

  
  if(mincutvalue > 1.99999999)
    {
      *nSet = -1;
      //Free(cutarray);
      return cutarray;
    }
  *nSet = ncutarray;

  //Free(cutarray);
  return cutarray;
}
