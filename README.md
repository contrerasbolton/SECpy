# SECpy

SECpy is a Python wrapper that utilizes the subtour elimination constraints (SECs) separation procedure proposed by Padberg and Rinaldi (1990), implemented in C. This library integrates with general-purpose solvers such as Gurobi and Cplex.

## Instructions to run

These instructions guide you on how to run SECpy.

1. Navigate to the `lib` directory:

```
cd lib
```

2. Build the project using the `make` command:


```
make
```

3. Return to the parent directory:


```
cd ..
```

## Running example

Here's an example of how to run SECpy:

```
python main.py instances/berlin52.tsp 0
```

**Explanation of arguments:**

- `instances/berlin52.tsp`: This specifies the file containing the TSP instance data.
- `0`: This is the second argument and indicates the type of SEC calculation to perform:
    - 0: SEC min-cut by networkx (fractional)
    - 1: SEC min-cut by C power (fractional)
    - 2: SEC gurobi example (integer)
    - 3: SEC mix between 1 and 2
