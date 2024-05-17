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

    // Unary + operator
    Graph Graph::operator+() const
    {
        return *this;
    }

    // Addition operator
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

    // Addition assignment operator
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

    // Unary minus operator
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

    // Subtraction operator
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

    // Subtraction assignment operator
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

    // Pre-increment operator
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

// Post-increment operator
Graph Graph::operator++(int)
{
    Graph temp = *this;
    ++(*this);
    return temp;
}

// Pre-decrement operator
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

// Post-decrement operator
Graph Graph::operator--(int)
{
    Graph temp = *this;
    --(*this);
    return temp;
}


    // Scalar multiplication operator
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

    // Scalar multiplication operator (scalar * graph)
    Graph operator*(int scalar, const Graph &graph)
    {
        return graph * scalar; // Utilize the existing Graph::operator*(int scalar) const
    }

    // Scalar multiplication assignment operator
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

    Graph &Graph::operator/(int scalar){
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

    // Scalar division assignment operator
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

    Graph operator/(int scalar, const Graph &graph)
    {
        std::vector<std::vector<int>> result(graph.vertices, std::vector<int>(graph.vertices));
        for (size_t i = 0; i < graph.vertices; ++i)
        {
            for (size_t j = 0; j < graph.vertices; ++j)
            {
                if (graph.adjacencyMatrix[i][j] == 0)
                {
                    result[i][j] = 0; // Avoid division by zero
                }
                else
                {
                    result[i][j] = scalar / graph.adjacencyMatrix[i][j];
                }
            }
        }
        Graph quotient;
        quotient.loadGraph(result);
        return quotient;
    }

    // Graph multiplication operator
    Graph Graph::operator*(const Graph &other) const
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

    // Graph multiplication assignment operator
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
            }
        }
        this->loadGraph(result);
        return *this;
    }

    bool Graph::operator<(const Graph &other) const
{
    // Check if this graph is contained in the other graph
    if (this->vertices <= other.vertices)
    {
        bool isContained = true;
        for (size_t i = 0; i < this->vertices; ++i)
        {
            for (size_t j = 0; j < this->vertices; ++j)
            {
                if (this->adjacencyMatrix[i][j] != 0 && other.adjacencyMatrix[i][j] == 0)
                {
                    isContained = false;
                    break;
                }
            }
            if (!isContained) break;
        }
        if (isContained) return true;
    }

    // If not contained, compare number of edges
    size_t thisEdges = this->countEdges();
    size_t otherEdges = other.countEdges();
    if (thisEdges != otherEdges)
    {
        return thisEdges < otherEdges;
    }

    // If number of edges is the same, compare number of vertices
    return this->vertices < other.vertices;
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


    // Counts the number of edges in the graph
    size_t Graph::countEdges() const
    {
        size_t count = 0;
        for (size_t i = 0; i < this->vertices; ++i)
        {
            for (size_t j = 0; j < this->vertices; ++j)
            {
                if (this->adjacencyMatrix[i][j] != 0)
                {
                    ++count;
                }
            }
        }
        return count;
    }

    // Output stream operator
    std::ostream &operator<<(std::ostream &os, const Graph &graph)
    {
        os << graph.printGraph() << "\n"; // Append newline after printing each graph
        return os;
    }

} // namespace ariel
