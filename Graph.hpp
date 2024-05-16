#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <iostream>

namespace ariel {

class Graph {
public:
    // Constructors
    Graph() : vertices(0), isDirected(false), isWeighted(false) {}

    // Member functions
    void loadGraph(const std::vector<std::vector<int>> &matrix);
    void printGraph() const;

    bool getIsDirected() const;
    size_t getnumVertices() const;
    const std::vector<std::vector<int>> &getAdjacencyMatrix() const;
    bool isAdjacent(size_t vertex1, size_t vertex2) const;

    // Operator overloads
    Graph operator+() const;  // Unary plus
    Graph operator+(const Graph &other) const;
    Graph &operator+=(const Graph &other);

    Graph operator-() const;  // Unary minus
    Graph operator-(const Graph &other) const;
    Graph &operator-=(const Graph &other);

    Graph &operator++();     // Pre-increment
    Graph operator++(int);   // Post-increment

    Graph &operator--();     // Pre-decrement
    Graph operator--(int);   // Post-decrement

    Graph operator*(int scalar) const;
    Graph &operator*=(int scalar);
    Graph operator*(const Graph &other) const;
    Graph &operator*=(const Graph &other);

    bool operator==(const Graph &other) const;
    bool operator!=(const Graph &other) const;
    bool operator<(const Graph &other) const;
    bool operator<=(const Graph &other) const;
    bool operator>(const Graph &other) const;
    bool operator>=(const Graph &other) const;

    // Friend functions
    friend std::ostream &operator<<(std::ostream &os, const Graph &graph);

private:
    size_t vertices;
    bool isDirected;
    bool isWeighted;
    std::vector<std::vector<int>> adjacencyMatrix;

    bool isSimetric(const std::vector<std::vector<int>> &matrix) const;
    size_t countEdges() const;
};

} // namespace ariel

#endif // GRAPH_HPP
