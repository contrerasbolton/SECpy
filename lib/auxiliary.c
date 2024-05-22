/*26:*/
#line 15 "auxiliary.w"


#include "common.h"

#ifdef LINUX
#include <time.h>
int cputime()
{
  return(int)clock();
}

void printtime(int t)

{
  int pril= 1;
  int secs= t/CLOCKS_PER_SEC;
  int mins= secs/60;
  double dsecs= (double)(t/((double)CLOCKS_PER_SEC)-60.0*mins);
  Out2(0,"%7d:%05.2f",mins,dsecs);
}

#else

#include <sys/types.h>
#include <sys/times.h>

int cputime()
{
  struct tms now;
  times(&now);
  return(int)now.tms_utime;
}

void printtime(int t)

{
  int pril= 1;
  int secs= t/CLOCKS_PER_SEC;
  int mins= secs/60;
  double dsecs= (double)(t/((double)CLOCKS_PER_SEC)-60.0*mins);
  Out2(0,"%7d:%05.2f",mins,dsecs);
}


#endif

void error_prt(int t)
{
  char*s;
  switch(t){
  case MCC_not_enough_memory:s= "MCC -- Not enough memory !\n";
    break;
  case MCC_error_in_input_file:s= "MCC -- Error in input file !\n";
    break;
  case MCC_invalid_data:s= "MCC -- Invalid data !\n";
    break;
  default:s= "MCC -- Error not classified !\n";
    break;
  }
}

/*:26*/
