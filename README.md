## Author Information
- **Name**: Daniel Tsadik
- **ID**: 209307727
- **Email**: tsadik88@gmail.com

---

# Graph Operations Implementation

## Overview
This project extends the functionality of a previously implemented Graph class to support various arithmetic and comparison operations on graphs represented using an adjacency matrix. The Graph class enables the representation and manipulation of graphs in the form of an adjacency matrix.

## Files Included
- `Graph.hpp`: Header file containing the declaration of the Graph class and its member functions.
- `Graph.cpp`: Implementation file containing the definition of the Graph class member functions and operator overloads.
- `Algorithms.cpp`: Implementation file containing various algorithms and functions related to graph operations.
- `README.md`: This file, providing an overview and guide for the project.

## Functionality Added

### Arithmetic Operators
1. **Addition (+) and Addition Assignment (+=)**
   - **Implementation Approach**: The addition operator overloads are implemented to add two graphs element-wise. This is achieved by iterating over each cell in the adjacency matrices of the graphs and adding their corresponding values.
   - **Example**:
     ```cpp
     Graph result = graph1 + graph2;
     ```

2. **Unary Plus Operator (+)**
   - **Implementation Approach**: The unary plus operator returns a copy of the graph. It does not modify the original graph.
   - **Example**:
     ```cpp
     Graph copy = +graph;
     ```

3. **Subtraction (-) and Subtraction Assignment (-=)**
   - **Implementation Approach**: Subtraction operators subtract one graph from another element-wise. Similar to addition, this involves iterating over each cell in the adjacency matrices and performing the subtraction.
   - **Example**:
     ```cpp
     Graph difference = graph1 - graph2;
     ```

4. **Increment (++) and Decrement (--)**
   - **Implementation Approach**: Increment and decrement operators increase or decrease all edge weights by 1. This is achieved by iterating over each cell in the adjacency matrix and incrementing or decrementing its value.
   - **Example**:
     ```cpp
     ++graph;  // Increment all edge weights by 1
     ```

5. **Multiplication (*) and Multiplication Assignment (*=)**
   - **Implementation Approach**: Multiplication operators multiply all edge weights by a scalar value. Similar to addition and subtraction, this involves iterating over each cell in the adjacency matrix and performing the multiplication.
   - **Example**:
     ```cpp
     Graph scaled = graph * 2;
     ```

6. **Division (/) and Division Assignment (/=)**
   - **Implementation Approach**: Division operators divide all edge weights by a scalar value. Proper error handling is implemented to handle cases such as division by zero.
   - **Example**:
     ```cpp
     Graph scaled = graph / 2;
     ```

### Comparison Operators
1. **Greater (>), Greater-than-equal (>=), Less (<), Less-than-equal (<=), Equal (==), and Not-equal (!=)**
   - **Implementation Approach**: Comparison operators compare two graphs based on their number of edges and order. The comparisons are performed by examining the adjacency matrices of the graphs and comparing their values.
   - **Example**:
     ```cpp
     if (graph1 <= graph2) {
         // Do something
     }
     ```

### Output Operator
1. **Output Stream Operator (<<)**
   - **Implementation Approach**: The output stream operator prints the graph in a user-friendly format. This involves iterating over the adjacency matrix and formatting the output accordingly.
   - **Example**:
     ```cpp
     cout << graph << endl;
     ```

## Implementation Details
- The `Graph` class represents graphs using an adjacency matrix, where each cell `(i, j)` represents the weight of the edge from vertex `i` to vertex `j`.
- All arithmetic and comparison operators are defined as member functions of the `Graph` class.
- Operator overloads ensure that the operations are performed efficiently and according to the rules of linear algebra.
- Proper error handling is implemented to handle cases such as incompatible graph sizes or division by zero.

## How to Use
1. Include the `Graph.hpp` header file in your project.
2. Create instances of the `Graph` class and manipulate them using the provided operators.
3. Use the provided algorithms in `Algorithms.cpp` to perform various graph operations efficiently.

---