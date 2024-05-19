// Daniel Tsadik
// ID: 209307727
// Mail: tsadik88@gmail.com

#include "Graph.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <sstream>

using namespace std;

namespace ariel
{

    // Checks if a given matrix is symmetric
    bool Graph::isSimetric(const std::vector<std::vector<int>> &matrix) const
    {
        for (size_t i = 0; i < matrix.size(); i++)
        {
            for (size_t j = 0; j < matrix[i].size(); j++)
            {
                if (matrix[i][j] != matrix[j][i])
                {
                    return false;
                }
            }
        }
        return true;
    }

    // Loads the graph from a given adjacency matrix
    void Graph::loadGraph(const std::vector<std::vector<int>> &matrix)
    {
        if (matrix.empty())
        {
            throw invalid_argument("Invalid graph: The graph is empty.");
        }
        for (size_t i = 0; i < matrix.size(); i++)
        {
            if (matrix.size() != matrix[i].size())
            {
                throw invalid_argument("Invalid graph: The graph is not a square matrix.");
            }
        }
        this->adjacencyMatrix = matrix;
        this->vertices = matrix.size();
        this->isDirected = !isSimetric(matrix);
    }

    // Returns a string representation of the graph
    std::string Graph::printGraph() const
    {
        std::ostringstream os;
        for (size_t i = 0; i < adjacencyMatrix.size(); ++i)
        {
            os << "[";
            for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j)
            {
                os << adjacencyMatrix[i][j];
                if (j < adjacencyMatrix[i].size() - 1)
                {
                    os << ", ";
                }
            }
            os << "]";
            if (i < adjacencyMatrix.size() - 1)
            {
                os << "\n";
            }
        }
        return os.str();
    }

    // Returns whether the graph is directed
    bool Graph::getIsDirected() const
    {
        return this->isDirected;
    }

    // Returns the number of vertices in the graph
    size_t Graph::getnumVertices() const
    {
        return this->vertices;
    }

    // Returns a constant reference to the adjacency matrix of the graph
    const std::vector<std::vector<int>> &Graph::getAdjacencyMatrix() const
    {
        return this->adjacencyMatrix;
    }

    // Checks if two vertices are adjacent
    bool Graph::isAdjacent(size_t vertex1, size_t vertex2) const
    {
        if (vertex1 >= this->vertices || vertex2 >= this->vertices)
        {
            throw invalid_argument("Invalid vertex: The vertex is out of range.");
        }
        return this->adjacencyMatrix[vertex1][vertex2] != 0;
    }

    // Operator overloading implementations

    // Unary + operator: returns a copy of the graph
    Graph Graph::operator+() const
    {
        return *this;
    }

    // Addition operator: adds two graphs element-wise
    Graph Graph::operator+(const Graph &other) const
    {
        if (this->vertices != other.vertices)
        {
            throw invalid_argument("Graphs must be of the same size to add.");
        }
        std::vector<std::vector<int>> result(this->vertices, std::vector<int>(this->vertices));
        for (size_t i = 0; i < this->vertices; ++i)
        {
            for (size_t j = 0; j < this->vertices; ++j)
            {
                result[i][j] = this->adjacencyMatrix[i][j] + other.adjacencyMatrix[i][j];
            }
        }
        Graph sum;
        sum.loadGraph(result);
        return sum;
    }

    // Addition assignment operator: adds another graph to this graph element-wise
    Graph &Graph::operator+=(const Graph &other)
    {
        if (this->vertices != other.vertices)
        {
            throw invalid_argument("Graphs must be of the same size to add.");
        }
        for (size_t i = 0; i < this->vertices; ++i)
        {
            for (size_t j = 0; j < this->vertices; ++j)
            {
                this->adjacencyMatrix[i][j] += other.adjacencyMatrix[i][j];
            }
        }
        return *this;
    }

    // Unary minus operator: negates the adjacency matrix of the graph
    Graph Graph::operator-() const
    {
        std::vector<std::vector<int>> result(this->vertices, std::vector<int>(this->vertices));
        for (size_t i = 0; i < this->vertices; ++i)
        {
            for (size_t j = 0; j < this->vertices; ++j)
            {
                result[i][j] = -this->adjacencyMatrix[i][j];
            }
        }
        Graph negation;
        negation.loadGraph(result);
        return negation;
    }

    // Subtraction operator: subtracts another graph from this graph element-wise
    Graph Graph::operator-(const Graph &other) const
    {
        if (this->vertices != other.vertices)
        {
            throw invalid_argument("Graphs must be of the same size to subtract.");
        }
        std::vector<std::vector<int>> result(this->vertices, std::vector<int>(this->vertices));
        for (size_t i = 0; i < this->vertices; ++i)
        {
            for (size_t j = 0; j < this->vertices; ++j)
            {
                result[i][j] = this->adjacencyMatrix[i][j] - other.adjacencyMatrix[i][j];
            }
        }
        Graph difference;
        difference.loadGraph(result);
        return difference;
    }

    // Subtraction assignment operator: subtracts another graph from this graph element-wise
    Graph &Graph::operator-=(const Graph &other)
    {
        if (this->vertices != other.vertices)
        {
            throw invalid_argument("Graphs must be of the same size to subtract.");
        }
        for (size_t i = 0; i < this->vertices; ++i)
        {
            for (size_t j = 0; j < this->vertices; ++j)
            {
                this->adjacencyMatrix[i][j] -= other.adjacencyMatrix[i][j];
            }
        }
        return *this;
    }

    // Pre-increment operator: increments all elements of the adjacency matrix
    Graph &Graph::operator++()
    {
        for (size_t i = 0; i < this->vertices; ++i)
        {
            for (size_t j = 0; j < this->vertices; ++j)
            {
                ++this->adjacencyMatrix[i][j];
            }
        }
        // Set diagonal elements to 0
        for (size_t i = 0; i < this->vertices; ++i)
        {
            this->adjacencyMatrix[i][i] = 0;
        }
        return *this;
    }

    // Post-increment operator: increments all elements of the adjacency matrix and returns the old value
    Graph Graph::operator++(int)
    {
        Graph temp = *this;
        ++(*this);
        return temp;
    }

    // Pre-decrement operator: decrements all elements of the adjacency matrix
    Graph &Graph::operator--()
    {
        for (size_t i = 0; i < this->vertices; ++i)
        {
            for (size_t j = 0; j < this->vertices; ++j)
            {
                --this->adjacencyMatrix[i][j];
            }
        }
        // Set diagonal elements to 0
        for (size_t i = 0; i < this->vertices; ++i)
        {
            this->adjacencyMatrix[i][i] = 0;
        }
        return *this;
    }

    // Post-decrement operator: decrements all elements of the adjacency matrix and returns the old value
    Graph Graph::operator--(int)
    {
        Graph temp = *this;
        --(*this);
        return temp;
    }

    // Scalar multiplication operator: multiplies all elements of the adjacency matrix by a scalar
    Graph Graph::operator*(int scalar) const
    {
        std::vector<std::vector<int>> result(this->vertices, std::vector<int>(this->vertices));
        for (size_t i = 0; i < this->vertices; ++i)
        {
            for (size_t j = 0; j < this->vertices; ++j)
            {
                result[i][j] = this->adjacencyMatrix[i][j] * scalar;
            }
        }
        Graph product;
        product.loadGraph(result);
        return product;
    }

    // Scalar multiplication operator (scalar * graph): multiplies all elements of the adjacency matrix by a scalar
    Graph operator*(int scalar, const Graph &graph)
    {
        return graph * scalar; // Utilize the existing Graph::operator*(int scalar) const
    }

    // Scalar multiplication assignment operator: multiplies all elements of the adjacency matrix by a scalar
    Graph &Graph::operator*=(int scalar)
    {
        for (size_t i = 0; i < this->vertices; ++i)
        {
            for (size_t j = 0; j < this->vertices; ++j)
            {
                this->adjacencyMatrix[i][j] *= scalar;
            }
        }
        return *this;
    }

    // Scalar division operator: divides all elements of the adjacency matrix by a scalar
    Graph &Graph::operator/(int scalar)
    {
        if (scalar == 0)
        {
            throw invalid_argument("Division by zero is not allowed.");
        }
        for (size_t i = 0; i < this->vertices; ++i)
        {
            for (size_t j = 0; j < this->vertices; ++j)
            {
                this->adjacencyMatrix[i][j] /= scalar;
            }
        }
        return *this;
    }

    // Scalar division assignment operator: divides all elements of the adjacency matrix by a scalar
    Graph &Graph::operator/=(int scalar)
    {
        if (scalar == 0)
        {
            throw invalid_argument("Division by zero is not allowed.");
        }
        for (size_t i = 0; i < this->vertices; ++i)
        {
            for (size_t j = 0; j < this->vertices; ++j)
            {
                this->adjacencyMatrix[i][j] /= scalar;
            }
        }
        return *this;
    }

    // Scalar division operator (scalar / graph): divides the scalar by each non-zero element of the adjacency matrix
    Graph operator/(int scalar, const Graph &graph)
    {
        std::vector<std::vector<int>> result(graph.vertices, std::vector<int>(graph.vertices, 0));
        for (size_t i = 0; i < graph.vertices; ++i)
        {
            for (size_t j = 0; j < graph.vertices; ++j)
            {
                if (i != j && graph.adjacencyMatrix[i][j] != 0)
                {
                    result[i][j] = scalar / graph.adjacencyMatrix[i][j];
                }
            }
        }
        Graph quotient;
        quotient.loadGraph(result);
        return quotient;
    }

    // Graph multiplication operator: multiplies two graphs element-wise
    Graph Graph::operator*(const Graph &other) const
    {
        if (this->vertices != other.vertices)
        {
            throw invalid_argument("The number of columns in the first matrix must be equal to the number of rows in the second matrix.");
        }
        std::vector<std::vector<int>> result(this->vertices, std::vector<int>(this->vertices, 0));
        for (size_t i = 0; i < this->vertices; ++i)
        {
            for (size_t j = 0; j < this->vertices; ++j)
            {
                for (size_t k = 0; k < this->vertices; ++k)
                {
                    result[i][j] += this->adjacencyMatrix[i][k] * other.adjacencyMatrix[k][j];
                }
                // Ensure the diagonal elements are set to 0
                if (i == j)
                {
                    result[i][j] = 0;
                }
            }
        }
        Graph product;
        product.loadGraph(result);
        return product;
    }

    // Graph multiplication assignment operator: multiplies this graph by another graph element-wise
    Graph &Graph::operator*=(const Graph &other)
    {
        if (this->vertices != other.vertices)
        {
            throw invalid_argument("Graphs must be of the same size to multiply.");
        }

        std::vector<std::vector<int>> result(this->vertices, std::vector<int>(this->vertices, 0));

        for (size_t i = 0; i < this->vertices; ++i)
        {
            for (size_t j = 0; j < this->vertices; ++j)
            {
                for (size_t k = 0; k < this->vertices; ++k)
                {
                    result[i][j] += this->adjacencyMatrix[i][k] * other.adjacencyMatrix[k][j];
                }
                if (i == j)
                {
                    result[i][j] = 0; // Ensure diagonal is zero
                }
            }
        }

        this->loadGraph(result);
        return *this;
    }

    // Comparison operators: compare two graphs
    bool Graph::operator<(const Graph &other) const
    {
        // Compare number of edges
        size_t thisEdges = this->countEdges();
        size_t otherEdges = other.countEdges();
        if (thisEdges != otherEdges)
        {
            return thisEdges < otherEdges;
        }

        // If number of edges is the same, compare number of vertices
        if (this->vertices != other.vertices)
        {
            return this->vertices < other.vertices;
        }

        // If number of edges and vertices are the same, perform element-wise comparison
        for (size_t i = 0; i < this->vertices; ++i)
        {
            for (size_t j = 0; j < this->vertices; ++j)
            {
                if (this->adjacencyMatrix[i][j] != other.adjacencyMatrix[i][j])
                {
                    return this->adjacencyMatrix[i][j] < other.adjacencyMatrix[i][j];
                }
            }
        }

        // If all else is equal, the graphs are not less than each other
        return false;
    }

    size_t Graph::countEdges() const
    {
        size_t count = 0;
        for (const auto &row : this->adjacencyMatrix)
        {
            for (int val : row)
            {
                if (val != 0)
                {
                    count++;
                }
            }
        }
        return count / 2; // Assuming undirected graph, each edge is counted twice
    }

    bool Graph::operator>(const Graph &other) const
    {
        return other < *this;
    }

    bool Graph::operator==(const Graph &other) const
    {
        return this->adjacencyMatrix == other.adjacencyMatrix || (!(*this < other) && !(other < *this));
    }

    bool Graph::operator<=(const Graph &other) const
    {
        return !(*this > other);
    }

    bool Graph::operator>=(const Graph &other) const
    {
        return !(*this < other);
    }

    bool Graph::operator!=(const Graph &other) const
    {
        return !(*this == other);
    }

    // Output stream operator: prints the graph
    std::ostream &operator<<(std::ostream &os, const Graph &graph)
    {
        os << graph.printGraph() << "\n"; // Append newline after printing each graph
        return os;
    }

} // namespace ariel
