/*16:*/
#line 136 "header.w"


#ifndef COMMON_H
#define COMMON_H
#include "mincut.h"
/*18:*/
#line 158 "header.w"

/*19:*/
#line 163 "header.w"

#define Error(a)  \
do  {             \
  status =  a;       \
  error_prt (a);    \
  goto freeall;     \
}  while (0)

#define Out0(p,a)         if (p < pril) fprintf (stdout, a),          \
                          fflush (stdout)
#define Out1(p,a,b)       if (p < pril) fprintf (stdout, a, b),       \
                          fflush (stdout)
#define Out2(p,a,b,c)     if (p < pril) fprintf (stdout, a, b, c),    \
                          fflush (stdout)
#define Out3(p,a,b,c,d)   if (p < pril) fprintf (stdout, a, b, c, d), \
                          fflush (stdout)
#define Out4(p,a,b,c,d,e) if (p < pril) fprintf (stdout, a, b, c, d, e), \
                          fflush (stdout)

#define chkmem(p) if (!(p)) Error(MCC_not_enough_memory)

#define Alloc(p,a,t)  \
chkmem ( p =  (t *) malloc ((size_t) ((a) * sizeof (t))) )

#define Calloc(p,a,t) \
chkmem ( p =  (t *) calloc ((size_t) (a), (size_t) sizeof (t)) )

#define Free(p) do {if (p) {free (p); p =  0;} } while (0)

/*:19*/
#line 159 "header.w"

/*33:*/
#line 58 "graph.w"

#define End_list -1
#define At_end(a) ((a) < 0)
#define Not_at_end(a) ((a) >= 0)

/*:33*//*34:*/
#line 64 "graph.w"

#define Find_end_vertices(e,t,h)  \
{ int m_a;                        \
   m_a =  e << 1;                    \
   t =  tip[m_a];                    \
   h =  tip[++m_a];                  \
}

/*:34*//*35:*/
#line 77 "graph.w"

#define Find_edge(t,h,e,tarc,harc,cape)                       \
{ int u_fe, v_fe;                                             \
   e =  End_list;                                                \
   cape =  Zero;                                                 \
   for (u_fe =  first[t]; Not_at_end (u_fe); u_fe =  next[u_fe]) {\
     v_fe =  tip[u_fe];                                          \
     if (v_fe == h) {                                           \
       harc =  u_fe;                                             \
       cape =  capacity[harc];                                   \
       tarc =  Mate_of (harc);                                   \
       e =  Edge_of (harc);                                      \
       break;                                                   \
     }                                                          \
   }                                                            \
}

/*:35*//*36:*/
#line 95 "graph.w"

#define Unlink_arc(a,v)               \
{ int m_this_arc =  a;                 \
    int m_prev_arc =  prev[m_this_arc];  \
    int m_next_arc =  next[m_this_arc];  \
   if (At_end (m_prev_arc))             \
     first[v] =  m_next_arc;             \
   else                                 \
     next[m_prev_arc] =  m_next_arc;     \
   if (Not_at_end (m_next_arc))         \
     prev[m_next_arc] =  m_prev_arc;     \
}

/*:36*//*37:*/
#line 109 "graph.w"

#define Link_arc(a,v)                                             \
 { int m_next_arc, m_this_arc =  a;                              \
   prev[m_this_arc] =  End_list;                                     \
   m_next_arc =  first[v];                                           \
   next[m_this_arc] =  m_next_arc;                                   \
   if (Not_at_end (m_next_arc)) prev[m_next_arc] =  m_this_arc;      \
   first[v] =  m_this_arc;                                           \
}

/*:37*//*38:*/
#line 120 "graph.w"

#define Relink_arc(a)                          \
{ int m_this_arc =  a;                          \
    int m_prev_arc =  prev[m_this_arc];           \
    int m_next_arc =  next[m_this_arc];           \
   if (At_end (m_prev_arc))                      \
     first[tip[Mate_of (m_this_arc)]] =  m_this_arc; \
   else                                          \
     next[m_prev_arc] =  m_this_arc;              \
   if (Not_at_end (m_next_arc))                  \
     prev[m_next_arc] =  m_this_arc;              \
}

/*:38*//*39:*/
#line 133 "graph.w"

#define Insert_edge(t,h,c)           \
{ int h_ie, t_ie;                    \
   t_ie =  *c_edges << 1;                \
   h_ie =  t_ie + 1;                    \
   ++(*c_edges);                          \
   capacity[h_ie] =  capacity[t_ie] =  c;\
   tip[h_ie] =  h;                      \
   Link_arc(h_ie,t);                   \
   tip[t_ie] =  t;                      \
   Link_arc(t_ie,h);                   \
}

/*:39*//*40:*/
#line 146 "graph.w"

#define For_neighbors(u,v,a)                                       \
  for (a =  first[u]; Not_at_end (a); a =  next[a]) if (v =  tip[a], 1)

/*:40*//*41:*/
#line 150 "graph.w"

#define For_neighbors_save_next(u,v,a,n)                                 \
  for (a =  first[u]; Not_at_end (a); a =  n) if (n =  next[a], v =  tip[a], 1)

/*:41*//*42:*/
#line 154 "graph.w"

#define For_star(u,a)                           \
  for (a =  first[u]; Not_at_end (a); a =  next[a])

/*:42*//*43:*/
#line 158 "graph.w"

#define For_active_nodes(u,i)                                       \
  for (i =  0; i < *c_nodes; i++) if (u =  active_node[i], 1)

/*:43*//*44:*/
#line 162 "graph.w"

#define For_nodes(i)          \
  for (i =  0; i < *c_nodes; i++)

/*:44*//*45:*/
#line 166 "graph.w"

#define Edge_of(a) ((a) >> 1)

/*:45*//*46:*/
#line 169 "graph.w"

#define Arc_of(e) ((e) << 1)

/*:46*//*47:*/
#line 172 "graph.w"

#define Mate_of(a) ((a) % 2 ? (a) - 1 : (a) + 1)

/*:47*//*48:*/
#line 175 "graph.w"

#define Graphalloc(nnod,nedg)           \
   g.s_nodes =  nnod;                      \
   g.s_edges =  nedg;                      \
   g.c_nodes =  0;                         \
   g.c_edges =  0;                         \
   Alloc (g.first, nnod, int);            \
   Alloc (g.prev, 2 * nedg, int);         \
   Alloc (g.next, 2 * nedg, int);         \
   Alloc (g.tip, 2 * nedg, int);          \
   Alloc (g.orig_name, nnod, int);        \
   Alloc (g.capacity, 2 * nedg, MCC_cap); \
   Alloc (g.active_node, nnod, int);      \
   Alloc (g.active_pos, nnod, int)

/*:48*/
#line 160 "header.w"

/*5:*/
#line 19 "marks.w"

#define Mark(v,m)           \
{                             \
    marked_node[c_marks++] =  v; \
    mark[v] =  m;            \
}

/*:5*//*6:*/
#line 26 "marks.w"

#define Remove_marks                                    \
  while (c_marks) mark[marked_node[--c_marks]] =  End_list

/*:6*/
#line 161 "header.w"


/*:18*/
#line 141 "header.w"

/*21:*/
#line 210 "header.w"

#ifdef MCC_INT

#define Infinity INT_MAX
#define Epsilon 0
#define Zero 0
#define Two 2
#define Wformat "%d"

#elif MCC_FLOAT

#define Infinity 1.0e30
#define Epsilon 1.0e-6
#define Zero 0.0
#define Two 2.0
#define Wformat "%f"

#elif MCC_DOUBLE

#define Infinity 1.0e30
#define Epsilon 1.0e-8
#define Zero 0.0
#define Two 2.0
#define Wformat "%f"

#endif


/*:21*/
#line 142 "header.w"

/*22:*/
#line 240 "header.w"


#define False 0
#define True  1

/*:22*//*23:*/
#line 247 "header.w"

#define MAX_FNAME_LEN  255
#ifndef DATA_PATH
#define DATA_PATH ""
#endif
#ifndef INPUT_EXT
#define INPUT_EXT ""
#endif
#ifndef OUTPUT_EXT
#define OUTPUT_EXT ".out"
#endif


/*:23*//*94:*/
#line 17 "hash.w"

#define HASH_MULT  314159
#define HASH_PRIME 516595003

/*:94*/
#line 143 "header.w"

#endif

/*:16*/
