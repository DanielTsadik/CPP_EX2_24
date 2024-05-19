// Daniel Tsadik
// ID: 209307727
// Mail: tsadik88@gmail.com

// Algorithms.hpp
#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "Graph.hpp"
#include <vector>
#include <string>
#include <stack>

namespace ariel
{
    class Algorithms
    {
    private:
        /**
         * @brief Performs a depth-first search (DFS) traversal starting from a given vertex.
         *
         * @param g The graph to traverse.
         * @param v The starting vertex for the DFS traversal.
         * @param visited A vector to track visited vertices.
         */
        static void DFS(const Graph &g, size_t v, std::vector<bool> &visited);

        /**
         * @brief Performs a depth-first search (DFS) traversal to detect cycles in a graph.
         *
         * @param g The graph to traverse.
         * @param v The current vertex in the DFS traversal.
         * @param visited A vector to track visited vertices.
         * @param parent A vector to track parent vertices in the traversal.
         * @param cycle A deque to store the cycle if found.
         * @return true if a cycle is detected, false otherwise.
         */
        static bool DFSCycle(const Graph &g, size_t v, std::vector<bool> &visited, std::vector<size_t> &parent, std::deque<int> &cycle);

        /**
         * @brief Checks if a graph is bipartite using DFS traversal.
         *
         * @param g The graph to check for bipartiteness.
         * @param v The current vertex in the DFS traversal.
         * @param color A vector to assign colors to vertices.
         * @return true if the graph is bipartite, false otherwise.
         */
        static bool isBipartiteUtil(const Graph &g, size_t v, std::vector<int> &color);

        /**
         * @brief Finds the negative cycle in a graph using Bellman-Ford algorithm.
         *
         * @param g The graph to find the negative cycle in.
         * @param source The source vertex for the Bellman-Ford algorithm.
         * @return A string representation of the negative cycle if found, otherwise "No negative cycle".
         */
        static std::string negativeCycleUtil(const Graph &g, size_t source);

    public:
        /**
         * @brief Checks if a graph is connected.
         *
         * @param g The graph to check for connectivity.
         * @return true if the graph is connected, false otherwise.
         */
        static bool isConnected(Graph &g);

        /**
         * @brief Finds the shortest path between two vertices in a graph.
         *
         * @param g The graph to find the shortest path in.
         * @param source The source vertex.
         * @param destination The destination vertex.
         * @return A string representing the shortest path between the source and destination vertices.
         */
        static std::string shortestPath(Graph &g, size_t source, size_t destination);

        /**
         * @brief Checks if a graph contains a cycle.
         *
         * @param g The graph to check for cycles.
         * @return true if the graph contains a cycle, false otherwise.
         */
        static bool isContainsCycle(Graph &g);

        /**
         * @brief Checks if a graph is bipartite.
         *
         * @param g The graph to check for bipartiteness.
         * @return A string indicating if the graph is bipartite and the partitions if it is.
         */
        static std::string isBipartite(Graph &g);

        /**
         * @brief Finds the negative cycle in a graph.
         *
         * @param g The graph to find the negative cycle in.
         * @return A string representation of the negative cycle if found, otherwise "No negative cycle".
         */
        static std::string negativeCycle(Graph &g);
    };
}

#endif