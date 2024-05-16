// Daniel Tsadik	
// ID: 209307727	
// Mail: tsadik88@gmail.com

// Algorithms.cpp
#include "Algorithms.hpp"
#include <vector>
#include <algorithm>
#include <iostream>
#include <climits>
#include <deque>
#include <queue>

using namespace std;

namespace ariel
{
    void Algorithms::DFS(const Graph &g, size_t v, std::vector<bool> &visited)
    {
        // Mark the current vertex as visited
        visited[static_cast<std::vector<bool>::size_type>(v)] = true;
        const std::vector<std::vector<int>> &matrix = g.getAdjacencyMatrix();

        // Recursively visit all adjacent vertices that have not been visited yet
        for (size_t i = 0; i < g.getnumVertices(); i++)
        {
            if (matrix[v][i] != 0 && !visited[i])
            {
                DFS(g, i, visited);
            }
        }
    }

    bool Algorithms::isConnected(Graph &g)
    {
        // If the graph has no vertices, it is considered connected
        if (g.getnumVertices() == 0)
        {
            return true;
        }
        size_t vertices = g.getnumVertices();
        std::vector<bool> visited(vertices, false);

        // Perform DFS traversal starting from vertex 0
        DFS(g, 0, visited);

        // Check if all vertices were visited
        for (size_t i = 0; i < vertices; i++)
        {
            if (!visited[i])
            {
                return false;
            }
        }

        // If the graph is directed, perform DFS from each vertex and check if all vertices are reachable
        if (g.getIsDirected())
        {
            for (size_t i = 1; i < vertices; i++)
            {
                visited = std::vector<bool>(vertices, false);
                DFS(g, i, visited);
                for (size_t j = 0; j < vertices; j++)
                {
                    if (!visited[j])
                    {
                        return false;
                    }
                }
            }
        }

        return true;
    }

    std::string ariel::Algorithms::shortestPath(Graph &g, size_t source, size_t destination)
    {
        // If the graph has no vertices, or if source/destination is out of range, return "-1"
        if (g.getnumVertices() == 0 || source >= g.getnumVertices() || destination >= g.getnumVertices())
        {
            return "-1";
        }
        size_t V = g.getnumVertices();
        vector<size_t> distances(V, INT_MAX);
        vector<size_t> parent(V, (size_t)-1);
        distances[source] = 0;

        // Relax edges repeatedly to find shortest paths
        for (size_t i = 1; i <= V - 1; i++)
        {
            for (size_t u = 0; u < V; u++)
            {
                for (size_t v = 0; v < V; v++)
                {
                    if (g.getAdjacencyMatrix()[u][v] != 0 && distances[u] != INT_MAX && distances[u] + (size_t)g.getAdjacencyMatrix()[u][v] < distances[v])
                    {
                        distances[v] = distances[u] + (size_t)g.getAdjacencyMatrix()[u][v];
                        parent[v] = u;
                    }
                }
            }
        }

        // Check for negative-weight cycles
        for (size_t u = 0; u < V; u++)
        {
            for (size_t v = 0; v < V; v++)
            {
                if (g.getAdjacencyMatrix()[u][v] != 0 && distances[u] != INT_MAX && distances[u] + (size_t)g.getAdjacencyMatrix()[u][v] < distances[v])
                {
                    return "-1"; // Negative cycle found
                }
            }
        }

        // If destination is unreachable, return "-1"
        if (distances[destination] == INT_MAX)
        {
            return "-1";
        }

        // Construct the shortest path string
        string path;
        for (size_t v = destination; v != -1; v = parent[v])
        {
            path = to_string(v) + (path.empty() ? "" : "->" + path);
        }

        return path;
    }

    bool Algorithms::DFSCycle(const Graph &g, size_t v, vector<bool> &visited, vector<size_t> &parent, deque<int> &cycle)
{
    // Mark the current vertex as visited and add it to the cycle
    visited[v] = true;
    cycle.push_back(v);

    // Get the adjacency matrix of the graph
    const vector<vector<int>> &matrix = g.getAdjacencyMatrix();

    // Iterate over all vertices adjacent to the current vertex
    for (size_t u = 0; u < g.getnumVertices(); u++)
    {
        // If there is an edge between v and u
        if (matrix[v][u] != 0)
        {
            // If u has not been visited yet, recursively explore it
            if (!visited[u])
            {
                parent[u] = v;
                if (DFSCycle(g, u, visited, parent, cycle))
                {
                    return true;
                }
            }
            // If u has been visited and is not the parent of v, a cycle is found
            else if (parent[v] != u)
            {
                // Construct the cycle path
                vector<int> cyclePath;
                cyclePath.push_back(u);
                for (size_t pv = v; pv != u; pv = parent[pv])
                {
                    cyclePath.push_back(pv);
                }
                cyclePath.push_back(u);

                // Print the cycle path
                cout << "The cycle is: ";
                for (auto it = cyclePath.rbegin(); it != cyclePath.rend(); ++it)
                {
                    cout << *it;
                    if (it != cyclePath.rend() - 1)
                    {
                        cout << "->";
                    }
                }
                cout << endl;

                return true;
            }
        }
    }

    // If no cycle is found, backtrack
    cycle.pop_back();
    return false;
}

bool Algorithms::isContainsCycle(Graph &g)
{
    // If the graph is empty, it cannot contain cycles
    if (g.getnumVertices() == 0)
    {
        return false;
    }

    // Initialize vectors to track visited vertices and their parents
    size_t V = g.getnumVertices();
    vector<bool> visited(V, false);
    vector<size_t> parent(V, (size_t)-1);
    deque<int> cycle;

    // Iterate over each vertex to start the DFS from all unvisited vertices
    for (size_t v = 0; v < V; v++)
    {
        if (!visited[v] && DFSCycle(g, v, visited, parent, cycle))
        {
            return true;
        }
    }

    // If no cycle is found in any DFS traversal, return false
    return false;
}


    bool Algorithms::isBipartiteUtil(const Graph &g, size_t v, std::vector<int> &color)
    {
        // Color the current vertex as 1
        color[v] = 1;
        std::queue<size_t> q;
        q.push(v);

        while (!q.empty())
        {
            size_t u = q.front();
            q.pop();

            // Self loop, graph is not bipartite
            if (g.getAdjacencyMatrix()[u][u] != 0)
            {
                return false;
            }

            // Traverse all adjacent vertices of u
            for (size_t v = 0; v < g.getnumVertices(); v++)
            {
                // An edge from u to v exists and destination v is not colored
                if (g.getAdjacencyMatrix()[u][v] && color[v] == -1)
                {
                    // Assign alternate color to this adjacent v of u
                    color[v] = 1 - color[u];
                    q.push(v);
                }
                // An edge from u to v exists and destination v is colored with the same color as u
                else if (g.getAdjacencyMatrix()[u][v] && color[v] == color[u])
                {
                    return false; // Not bipartite
                }
            }
        }

        return true; // Bipartite
    }

    std::string Algorithms::isBipartite(Graph &g)
    {
        std::vector<int> color(g.getnumVertices(), -1); // Initialize all vertices as not colored (-1)

        // Check if the graph is bipartite using BFS traversal
        for (size_t i = 0; i < g.getnumVertices(); i++)
        {
            if (color[i] == -1)
            {
                if (!isBipartiteUtil(g, i, color))
                {
                    return "0"; // Not bipartite
                }
            }
        }

        // Construct partitions A and B based on vertex colors
        std::vector<size_t> setA, setB;
        for (size_t i = 0; i < color.size(); i++)
        {
            if (color[i] == 1)
            {
                setA.push_back(i);
            }
            else
            {
                setB.push_back(i);
            }
        }

        // Construct the bipartite graph information string
        std::string result = "The graph is bipartite: A={";
        for (size_t i = 0; i < setA.size(); i++)
        {
            result += std::to_string(setA[i]);
            if (i != setA.size() - 1)
            {
                result += ", ";
            }
        }
        result += "}, B={";
        for (size_t i = 0; i < setB.size(); i++)
        {
            result += std::to_string(setB[i]);
            if (i != setB.size() - 1)
            {
                result += ", ";
            }
        }
        result += "}";

        return result;
    }

    std::string Algorithms::negativeCycleUtil(const Graph &g, size_t source)
{
    size_t numVertices = g.getnumVertices();
    std::vector<int> distance(numVertices, std::numeric_limits<int>::max());
    std::vector<size_t> predecessor(numVertices, (size_t)-1);
    distance[source] = 0;

    // Relax all edges numVertices - 1 times
    for (size_t i = 1; i <= numVertices - 1; i++)
    {
        for (size_t u = 0; u < numVertices; u++)
        {
            for (size_t v = 0; v < numVertices; v++)
            {
                if (g.getAdjacencyMatrix()[u][v] != 0 && distance[u] != std::numeric_limits<int>::max() && distance[u] + g.getAdjacencyMatrix()[u][v] < distance[v])
                {
                    distance[v] = distance[u] + g.getAdjacencyMatrix()[u][v];
                    predecessor[v] = u;
                }
            }
        }
    }

    // Check for negative-weight cycles
    for (size_t u = 0; u < numVertices; u++)
    {
        for (size_t v = 0; v < numVertices; v++)
        {
            if (g.getAdjacencyMatrix()[u][v] != 0 && distance[u] != std::numeric_limits<int>::max() && distance[u] + g.getAdjacencyMatrix()[u][v] < distance[v])
            {
                // Negative cycle found, construct cycle
                std::vector<int> cycle;
                for (size_t v = u;; v = predecessor[v])
                {
                    cycle.push_back(v);
                    if (v == u && cycle.size() > 1)
                    {
                        break;
                    }
                }
                std::reverse(cycle.begin(), cycle.end());

                // Construct the cycle string with "->" between vertices
                std::string cycleStr = "Negative cycle: ";
                for (size_t i = 0; i < cycle.size(); ++i)
                {
                    cycleStr += std::to_string(cycle[i]);
                    if (i < cycle.size() - 1)
                    {
                        cycleStr += "->";
                    }
                }
                return cycleStr;
            }
        }
    }

    return "No negative cycle";
}



    std::string Algorithms::negativeCycle(Graph &g)
    {
        if (g.getnumVertices() == 0)
        {
            return "No negative cycle";
        }
        for (size_t i = 0; i < g.getnumVertices(); i++)
        {
            std::string result = negativeCycleUtil(g, i);
            if (result != "No negative cycle")
            {
                return result;
            }
        }
        return "No negative cycle";
    }
}