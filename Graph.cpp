#include "Graph.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

namespace ariel {

// Checks if a given matrix is symmetric
bool Graph::isSimetric(const std::vector<std::vector<int>> &matrix) const {
    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < matrix[i].size(); j++) {
            if (matrix[i][j] != matrix[j][i]) {
                return false;
            }
        }
    }
    return true;
}

// Loads the graph from a given adjacency matrix
void Graph::loadGraph(const std::vector<std::vector<int>> &matrix) {
    if (matrix.empty()) {
        throw invalid_argument("Invalid graph: The graph is empty.");
    }
    for (size_t i = 0; i < matrix.size(); i++) {
        if (matrix.size() != matrix[i].size()) {
            throw invalid_argument("Invalid graph: The graph is not a square matrix.");
        }
    }
    this->adjacencyMatrix = matrix;
    this->vertices = matrix.size();
    this->isDirected = !isSimetric(matrix);
}

// Prints information about the graph
void Graph::printGraph() const {
    for (const auto &row : adjacencyMatrix) {
        for (const auto &val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

// Returns whether the graph is directed
bool Graph::getIsDirected() const {
    return this->isDirected;
}

// Returns the number of vertices in the graph
size_t Graph::getnumVertices() const {
    return this->vertices;
}

// Returns a constant reference to the adjacency matrix of the graph
const std::vector<std::vector<int>> &Graph::getAdjacencyMatrix() const {
    return this->adjacencyMatrix;
}

// Checks if two vertices are adjacent
bool Graph::isAdjacent(size_t vertex1, size_t vertex2) const {
    if (vertex1 >= this->vertices || vertex2 >= this->vertices) {
        throw invalid_argument("Invalid vertex: The vertex is out of range.");
    }
    return this->adjacencyMatrix[vertex1][vertex2] != 0;
}

// Operator overloading implementations

// Unary + operator
Graph Graph::operator+() const {
    return *this;
}

// Addition operator
Graph Graph::operator+(const Graph &other) const {
    if (this->vertices != other.vertices) {
        throw invalid_argument("Graphs must be of the same size to add.");
    }
    std::vector<std::vector<int>> result(this->vertices, std::vector<int>(this->vertices));
    for (size_t i = 0; i < this->vertices; ++i) {
        for (size_t j = 0; j < this->vertices; ++j) {
            result[i][j] = this->adjacencyMatrix[i][j] + other.adjacencyMatrix[i][j];
        }
    }
    Graph sum;
    sum.loadGraph(result);
    return sum;
}

// Addition assignment operator
Graph &Graph::operator+=(const Graph &other) {
    if (this->vertices != other.vertices) {
        throw invalid_argument("Graphs must be of the same size to add.");
    }
    for (size_t i = 0; i < this->vertices; ++i) {
        for (size_t j = 0; j < this->vertices; ++j) {
            this->adjacencyMatrix[i][j] += other.adjacencyMatrix[i][j];
        }
    }
    return *this;
}

// Unary minus operator
Graph Graph::operator-() const {
    std::vector<std::vector<int>> result(this->vertices, std::vector<int>(this->vertices));
    for (size_t i = 0; i < this->vertices; ++i) {
        for (size_t j = 0; j < this->vertices; ++j) {
            result[i][j] = -this->adjacencyMatrix[i][j];
        }
    }
    Graph negation;
    negation.loadGraph(result);
    return negation;
}

// Subtraction operator
Graph Graph::operator-(const Graph &other) const {
    if (this->vertices != other.vertices) {
        throw invalid_argument("Graphs must be of the same size to subtract.");
    }
    std::vector<std::vector<int>> result(this->vertices, std::vector<int>(this->vertices));
    for (size_t i = 0; i < this->vertices; ++i) {
        for (size_t j = 0; j < this->vertices; ++j) {
            result[i][j] = this->adjacencyMatrix[i][j] - other.adjacencyMatrix[i][j];
        }
    }
    Graph difference;
    difference.loadGraph(result);
    return difference;
}

// Subtraction assignment operator
Graph &Graph::operator-=(const Graph &other) {
    if (this->vertices != other.vertices) {
        throw invalid_argument("Graphs must be of the same size to subtract.");
    }
    for (size_t i = 0; i < this->vertices; ++i) {
        for (size_t j = 0; j < this->vertices; ++j) {
            this->adjacencyMatrix[i][j] -= other.adjacencyMatrix[i][j];
        }
    }
    return *this;
}

// Pre-increment operator
Graph &Graph::operator++() {
    for (size_t i = 0; i < this->vertices; ++i) {
        for (size_t j = 0; j < this->vertices; ++j) {
            ++this->adjacencyMatrix[i][j];
        }
    }
    return *this;
}

// Post-increment operator
Graph Graph::operator++(int) {
    Graph temp = *this;
    ++(*this);
    return temp;
}

// Pre-decrement operator
Graph &Graph::operator--() {
    for (size_t i = 0; i < this->vertices; ++i) {
        for (size_t j = 0; j < this->vertices; ++j) {
            --this->adjacencyMatrix[i][j];
        }
    }
    return *this;
}

// Post-decrement operator
Graph Graph::operator--(int) {
    Graph temp = *this;
    --(*this);
    return temp;
}

// Scalar multiplication operator
Graph Graph::operator*(int scalar) const {
    std::vector<std::vector<int>> result(this->vertices, std::vector<int>(this->vertices));
    for (size_t i = 0; i < this->vertices; ++i) {
        for (size_t j = 0; j < this->vertices; ++j) {
            result[i][j] = this->adjacencyMatrix[i][j] * scalar;
        }
    }
    Graph product;
    product.loadGraph(result);
    return product;
}

// Scalar multiplication assignment operator
Graph &Graph::operator*=(int scalar) {
    for (size_t i = 0; i < this->vertices; ++i) {
        for (size_t j = 0; j < this->vertices; ++j) {
            this->adjacencyMatrix[i][j] *= scalar;
        }
    }
    return *this;
}

// Graph multiplication operator
Graph Graph::operator*(const Graph &other) const {
    try {
        loadGraph(other.adjacencyMatrix);
        loadGraph(this->adjacencyMatrix); // Check if the matrices are valids
    }
    catch (const std::invalid_argument &e) {
        throw invalid_argument("The number of columns in the first matrix must be equal to the number of rows in the second matrix.");
    }
    
    if (this->vertices != other.vertices ) {
        throw invalid_argument("Graphs must be of the same size to multiply.");
    }
    std::vector<std::vector<int>> result(this->vertices, std::vector<int>(this->vertices, 0));
    for (size_t i = 0; i < this->vertices; ++i) {
        for (size_t j = 0; j < this->vertices; ++j) {
            for (size_t k = 0; k < this->vertices; ++k) {
                result[i][j] += this->adjacencyMatrix[i][k] * other.adjacencyMatrix[k][j];
            }
        }
    }
    Graph product;
    product.loadGraph(result);
    return product;
}

// Graph multiplication assignment operator
Graph &Graph::operator*=(const Graph &other) {
    if (this->vertices != other.vertices) {
        throw invalid_argument("Graphs must be of the same size to multiply.");
    }
    std::vector<std::vector<int>> result(this->vertices, std::vector<int>(this->vertices, 0));
    for (size_t i = 0; i < this->vertices; ++i) {
        for (size_t j = 0; j < this->vertices; ++j) {
            for (size_t k = 0; k < this->vertices; ++k) {
                result[i][j] += this->adjacencyMatrix[i][k] * other.adjacencyMatrix[k][j];
            }
        }
    }
    this->loadGraph(result);
    return *this;
}

// Equality operator
bool Graph::operator==(const Graph &other) const {
    return this->adjacencyMatrix == other.adjacencyMatrix;
}

// Inequality operator
bool Graph::operator!=(const Graph &other) const {
    return !(*this == other);
}

// Less than operator
bool Graph::operator<(const Graph &other) const {
    return this->countEdges() < other.countEdges();
}

// Less than or equal operator
bool Graph::operator<=(const Graph &other) const {
    return this->countEdges() <= other.countEdges();
}

// Greater than operator
bool Graph::operator>(const Graph &other) const {
    return this->countEdges() > other.countEdges();
}

// Greater than or equal operator
bool Graph::operator>=(const Graph &other) const {
    return this->countEdges() >= other.countEdges();
}

// Counts the number of edges in the graph
size_t Graph::countEdges() const {
    size_t count = 0;
    for (size_t i = 0; i < this->vertices; ++i) {
        for (size_t j = 0; j < this->vertices; ++j) {
            if (this->adjacencyMatrix[i][j] != 0) {
                ++count;
            }
        }
    }
    return count;
}

// Output stream operator
std::ostream &operator<<(std::ostream &os, const Graph &graph) {
    for (const auto &row : graph.adjacencyMatrix) {
        os << "[ ";
        for (const auto &val : row) {
            os << val << " ";
        }
        os << "]" << std::endl;
    }
    return os;
}

} // namespace ariel
