import gurobipy as gp
from gurobipy import GRB
import sys
import tsplib95
import networkx as nx
from itertools import combinations
import lib.sec as sc

def subtour(subtour, vals):
    # obtains a arcs list with its solutions values
    arcs = gp.tuplelist((i, j) for i, j in vals.keys() if vals[i, j] > 0.5)
    noVisited = list(range(n))
    while noVisited:  # true if list is non-empty
        cycle = []
        neighbors = noVisited
        while neighbors:
            current = neighbors[0]
            cycle.append(current)
            noVisited.remove(current)
            neighbors = [j for i, j in arcs.select(current, '*') if j in noVisited]
        if len(subtour) > len(cycle):
            subtour[:] = cycle
                       
def CUT_fractional_callback0(m, where): # using graphs (networkx)
    case1 = where == GRB.Callback.MIPSOL # integer solutions
    case2 = (where == GRB.Callback.MIPNODE) and (m.cbGet(GRB.Callback.MIPNODE_STATUS) == GRB.OPTIMAL) # fractional solutions
    
    if not case1 and not case2:
        return
    
    # obtains the LP solution
    if case1:
        xval = m.cbGetSolution(m._x)
    elif case2:
        xval = m.cbGetNodeRel(m._x)
        
    DG = m._DG
    edges_used = [(i,j) for i,j in DG.edges if xval[i,j] > m._epsilon]

    # check if any CUT inequalities are violated (by solving some min cut problems)
    for i,j in DG.edges:
        DG.edges[i,j]['capacity'] = xval[i,j]

    s = 0
    for t in range(1, n):
        (cut_value, node_partition) = nx.minimum_cut(DG, _s = s, _t = t)
        if cut_value < 1 - m._epsilon:
            S = node_partition[0]  # 'left' side of the cut
            T = node_partition[1]  # 'right' side of the cut
            m.cbLazy(gp.quicksum(m._x[i,j] for i in S for j in T) >= 1)
            return

def CUT_fractional_callback1(m, where):
    case1 = where == GRB.Callback.MIPSOL
    case2 = (where == GRB.Callback.MIPNODE) and (m.cbGet(GRB.Callback.MIPNODE_STATUS) == GRB.OPTIMAL)
    
    if not case1 and not case2:
        return
    
    # obtains the LP solution
    if case1:
        xval = m.cbGetSolution(m._x)
    elif case2:
        xval = m.cbGetNodeRel(m._x)
        
    tour = sc.SEC(xval, m._epsilon, n) # using SECpy by C power
    
    if len(tour) == 0:
        return

    tour2 = [i for i in range(n) if i not in tour]    
    m.cbLazy(gp.quicksum(m._x[i,j] for i in tour for j in tour2) >= 1)
    return

def CUT_fractional_callback2(modelo, where):
    if where == GRB.Callback.MIPSOL:
        valoresX = modelo.cbGetSolution(modelo._x)
        # finds smaller cycle
        tour = [i for i in range(n+1)]
        subtour(tour, valoresX)
        
        if len(tour) < n:
            # adds cut DFJ
            tour2 = [i for i in cities if i not in tour]
            #tour2 = list(filter(lambda x: x not in tour, range(n)))
            modelo.cbLazy(gp.quicksum(modelo._x[i, j] for i in tour for j in tour2) >= 1)
                                          
def CUT_fractional_callback3(m, where): # mix between version 1 and 2
    case1 = where == GRB.Callback.MIPSOL
    case2 = (where == GRB.Callback.MIPNODE) and (m.cbGet(GRB.Callback.MIPNODE_STATUS) == GRB.OPTIMAL)
    
    if not case1 and not case2:
        return
    
    # obtains the LP solution
    if case1:
        xval = m.cbGetSolution(m._x)
    elif case2:
        xval = m.cbGetNodeRel(m._x)

    tour = [i for i in range(n+1)]
    subtour(tour, xval)
    if len(tour) < n:
     # adds cut DFJ
        tour2 = [i for i in range(n) if i not in tour]
        m.cbLazy(gp.quicksum(m._x[i, j] for i in tour for j in tour2) >= 1)
    else:
        tour = sc.SEC(xval, m._epsilon, n)
        
        if len(tour) == 0:
            return

        tour2 = [i for i in range(n) if i not in tour]    
        m.cbLazy(gp.quicksum(m._x[i,j] for i in tour for j in tour2) >= 1)
    
# Reads data
instance = sys.argv[1]
callback = int(sys.argv[2])
problem = tsplib95.load(instance)
# TSP info
n = len(list(problem.get_nodes()))
starting = list(problem.get_nodes())[0]
cities = [i for i in range(n)]
cte = [i for i in range(n+1)]
arcs = [(i, j) for i in cities for j in cities if i != j]
# Graph using networkx 
G = nx.complete_graph(n)

info = problem.as_keyword_dict()

starting = list(problem.get_nodes())[0]
if starting == 0:
    dist = {(i, j):problem.get_weight(*(i, j)) for i, j in arcs}
    for i,j in G.edges:
        G.edges[i,j]['length'] = problem.get_weight(*(i, j))
else:
    dist = {(i, j):problem.get_weight(i+1, j+1) for i, j in arcs}
    for i,j in G.edges:
        G.edges[i,j]['length'] = problem.get_weight(i+1, j+1)

# Only for callback 0
# Complete graph on n vertices
G = nx.complete_graph(n)
# DG is directed version of G. Replaces each edge {i,j} by (i,j) and (j,i)
DG = nx.DiGraph(G)

# Create model object
m = gp.Model()

# Create variable for each edge of DG
x = m.addVars(arcs, vtype=GRB.BINARY)

# Objective function
m.setObjective(gp.quicksum(dist[i, j] * x[i,j] for i,j in arcs), GRB.MINIMIZE)

# Constraints 
m.addConstrs(gp.quicksum(x[i,j] for j in cities if i != j) == 1 for i in cities)
m.addConstrs(gp.quicksum(x[i,j] for i in cities if i != j) == 1 for j in cities)

m.update()

# Solve the MILP using a fractional separation callback
m.Params.LazyConstraints = 1
m.Params.Threads = 1

m._epsilon = 0.00001
m._x = x
m._DG = DG
if callback == 0:
    m._callback = CUT_fractional_callback0
elif callback == 1:
    m._callback = CUT_fractional_callback1
elif callback == 2:
    m._callback = CUT_fractional_callback2
elif callback == 3:
    m._callback = CUT_fractional_callback3
else:
    print("No exists")
    exit(0)

m.optimize(m._callback)

print('Upper bound :', m.objVal)
print('Lower bound :', m.ObjBoundC)
print('MILP gap    :', m.MIPGap)
print('Time        :', m.Runtime)
