#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;

TEST_CASE("Test graph addition")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g3 = g1 + g2;
    vector<vector<int>> expectedGraph = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};
    CHECK(g3.printGraph() == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]");

    ariel::Graph g4 = g1 + g1;
    vector<vector<int>> expectedGraph2 = {
        {0, 2, 0},
        {2, 0, 2},
        {0, 2, 0}};
    CHECK(g4.printGraph() == "[0, 2, 0]\n[2, 0, 2]\n[0, 2, 0]");

    ariel::Graph g5;
    vector<vector<int>> graph2 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g5.loadGraph(graph2);
    CHECK_THROWS(g1 + g5);
}

TEST_CASE("Test graph multiplication")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g4 = g1 * g2;
    vector<vector<int>> expectedGraph = {
        {0, 0, 2},
        {1, 0, 1},
        {1, 0, 0}};
    CHECK(g4.printGraph() == "[0, 0, 2]\n[1, 0, 1]\n[1, 0, 0]");

    ariel::Graph g5;
    vector<vector<int>> graph2 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g5.loadGraph(graph2);
    CHECK_THROWS(g1 * g5);

    ariel::Graph g6 = g1 * 2;
    vector<vector<int>> expectedGraph2 = {
        {0, 2, 0},
        {2, 0, 2},
        {0, 2, 0}};
    CHECK(g6.printGraph() == "[0, 2, 0]\n[2, 0, 2]\n[0, 2, 0]");    
}

TEST_CASE("Invalid operations")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1, 1},
        {1, 0, 2, 1},
        {1, 2, 0, 1}};
    // g2.loadGraph(weightedGraph);
    ariel::Graph g5;
    vector<vector<int>> graph2 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g5.loadGraph(graph2);
    CHECK_THROWS(g5 * g1);
    // CHECK_THROWS(g1 * g2);

    // Addition of two graphs with different dimensions
    ariel::Graph g6;
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g6.loadGraph(graph3);
    CHECK_THROWS(g1 + g6);
}

TEST_CASE("Test unary plus operator")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2 = +g1;
    CHECK(g2.printGraph() == "[0, 1, 0]\n[1, 0, 1]\n[0, 1, 0]");
}

TEST_CASE("Test += operator")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    g1 += g2;
    CHECK(g1.printGraph() == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]");

    ariel::Graph g3;
    vector<vector<int>> grpah1 = {
        {0, 12, 17, -2},
        {24, 0, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}};

    g3.loadGraph(grpah1);
    ariel::Graph g4;    
    vector<vector<int>> grpah2 = {
        {0, 1, 0, 0},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {0, 0, 1, 0}};
    g4.loadGraph(grpah2);
    g3 += g4;
    CHECK(g3.printGraph() == "[0, 13, 17, -2]\n[25, 0, 2, 0]\n[0, 1, 0, 1]\n[0, 0, 1, 0]");

    // Addition of two graphs with different dimensions
    ariel::Graph g6;
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g6.loadGraph(graph3);   
    CHECK_THROWS(g1 += g6);
}

TEST_CASE("Test unary minus operator")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2 = -g1;
    CHECK(g2.printGraph() == "[0, -1, 0]\n[-1, 0, -1]\n[0, -1, 0]");

    ariel::Graph g3;
    vector<vector<int>> grpah1 = {
        {0, 12, 17, -2},
        {24, 0, 1, 0},
        {0, 44, 0, 0},
        {-115, 0, 0-5, 0}};
    g3.loadGraph(grpah1);
    ariel::Graph g4 = -g3;
    CHECK(g4.printGraph() == "[0, -12, -17, 2]\n[-24, 0, -1, 0]\n[0, -44, 0, 0]\n[115, 0, 5, 0]");
}

TEST_CASE("Test - operator")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g3 = g1 - g2;
    vector<vector<int>> expectedGraph = {
        {0, 0, -1},
        {0, 0, -1},
        {-1, -1, 0}};
    CHECK(g3.printGraph() == "[0, 0, -1]\n[0, 0, -1]\n[-1, -1, 0]");

    ariel::Graph g4 = g1 - g1;
    vector<vector<int>> expectedGraph2 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    CHECK(g4.printGraph() == "[0, 0, 0]\n[0, 0, 0]\n[0, 0, 0]");

    //try to subtract two graphs with different dimensions
    ariel::Graph g5;
    vector<vector<int>> graph2 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g5.loadGraph(graph2);
    CHECK_THROWS(g1 - g5);
}

TEST_CASE("Test -= operator")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    g1 -= g2;
    CHECK(g1.printGraph() == "[0, 0, -1]\n[0, 0, -1]\n[-1, -1, 0]");

    ariel::Graph g3;
    vector<vector<int>> grpah1 = {
        {0, 12, 17, -2},
        {24, 0, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}};
    g3.loadGraph(grpah1);
    ariel::Graph g4;
    vector<vector<int>> grpah2 = {
        {0, 1, 0, 0},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {0, 0, 1, 0}};
    g4.loadGraph(grpah2);
    g3 -= g4;
    CHECK(g3.printGraph() == "[0, 11, 17, -2]\n[23, 0, 0, 0]\n[0, -1, 0, -1]\n[0, 0, -1, 0]");

    //try to subtract two graphs with different dimensions
    ariel::Graph g5;
    vector<vector<int>> graph2 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g5.loadGraph(graph2);
    CHECK_THROWS(g1 -= g5);
}

TEST_CASE("Test pre-increment operator")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ++g1;
    CHECK(g1.printGraph() == "[0, 2, 1]\n[2, 0, 2]\n[1, 2, 0]");

    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}}; 

    g2.loadGraph(weightedGraph);    
    ++g2;
    CHECK(g2.printGraph() == "[0, 2, 2]\n[2, 0, 3]\n[2, 3, 0]");

    //try to increment a graph with negative values
    ariel::Graph g3;
    vector<vector<int>> grpah1 = {
        {0, 12, 17, -2},
        {24, 0, 1, 0},
        {0, -8, 0, 0},
        {230, -10, 0, 0}};
    g3.loadGraph(grpah1);
    ++g3;
    CHECK(g3.printGraph() == "[0, 13, 18, -1]\n[25, 0, 2, 1]\n[1, -7, 0, 1]\n[231, -9, 1, 0]");
}

TEST_CASE("Test post-increment operator")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2 = g1++;
    CHECK(g2.printGraph() == "[0, 1, 0]\n[1, 0, 1]\n[0, 1, 0]");
    CHECK(g1.printGraph() == "[0, 2, 1]\n[2, 0, 2]\n[1, 2, 0]");

    ariel::Graph g3;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g3.loadGraph(weightedGraph);
    ariel::Graph g4 = g3++;
    CHECK(g4.printGraph() == "[0, 1, 1]\n[1, 0, 2]\n[1, 2, 0]");
    CHECK(g3.printGraph() == "[0, 2, 2]\n[2, 0, 3]\n[2, 3, 0]");

    //try to increment a graph with negative values
    ariel::Graph g5;
    vector<vector<int>> grpah1 = {
        {0, 12, 17, -2},
        {24, 0, 1, 0},
        {0, -8, 0, 0},
        {230, -10, 0, 0}};
    g5.loadGraph(grpah1);
    ariel::Graph g6 = g5++;
    CHECK(g6.printGraph() == "[0, 12, 17, -2]\n[24, 0, 1, 0]\n[0, -8, 0, 0]\n[230, -10, 0, 0]");
    CHECK(g5.printGraph() == "[0, 13, 18, -1]\n[25, 0, 2, 1]\n[1, -7, 0, 1]\n[231, -9, 1, 0]");
}

TEST_CASE("Test pre-decrement operator")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 2, 1},
        {2, 0, 2},
        {1, 2, 0}};
    g1.loadGraph(graph);
    --g1;
    CHECK(g1.printGraph() == "[0, 1, 0]\n[1, 0, 1]\n[0, 1, 0]");

    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 2, 2},
        {2, 0, 3},
        {2, 3, 0}};
    g2.loadGraph(weightedGraph);
    --g2;
    CHECK(g2.printGraph() == "[0, 1, 1]\n[1, 0, 2]\n[1, 2, 0]");

    //try to decrement a graph with negative values
    ariel::Graph g3;
    vector<vector<int>> grpah1 = {
        {0, 13, 18, -1},
        {25, 0, 2, 1},
        {1, -7, 0, 1},
        {231, -9, 1, 0}};
    g3.loadGraph(grpah1);
    --g3;
    CHECK(g3.printGraph() == "[0, 12, 17, -2]\n[24, 0, 1, 0]\n[0, -8, 0, 0]\n[230, -10, 0, 0]");
}

TEST_CASE("Test post-decrement operator")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 2, 1},
        {2, 0, 2},
        {1, 2, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2 = g1--;
    CHECK(g2.printGraph() == "[0, 2, 1]\n[2, 0, 2]\n[1, 2, 0]");
    CHECK(g1.printGraph() == "[0, 1, 0]\n[1, 0, 1]\n[0, 1, 0]");

    ariel::Graph g3;
    vector<vector<int>> weightedGraph = {
        {0, 2, 2},
        {2, 0, 3},
        {2, 3, 0}};
    g3.loadGraph(weightedGraph);
    ariel::Graph g4 = g3--;
    CHECK(g4.printGraph() == "[0, 2, 2]\n[2, 0, 3]\n[2, 3, 0]");
    CHECK(g3.printGraph() == "[0, 1, 1]\n[1, 0, 2]\n[1, 2, 0]");

    //try to decrement a graph with negative values
    ariel::Graph g5;
    vector<vector<int>> grpah1 = {
        {0, 13, 18, -1},
        {25, 0, 2, 1},
        {1, -7, 0, 1},
        {231, -9, 1, 0}};
    g5.loadGraph(grpah1);
    ariel::Graph g6 = g5--;
    CHECK(g6.printGraph() == "[0, 13, 18, -1]\n[25, 0, 2, 1]\n[1, -7, 0, 1]\n[231, -9, 1, 0]");
    CHECK(g5.printGraph() == "[0, 12, 17, -2]\n[24, 0, 1, 0]\n[0, -8, 0, 0]\n[230, -10, 0, 0]");
}

// test for multiplication of a graph by a scalar
TEST_CASE("Test * operator")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 2, 1},
        {2, 0, 2},
        {1, 2, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2 = g1 * 2;
    CHECK(g2.printGraph() == "[0, 4, 2]\n[4, 0, 4]\n[2, 4, 0]");

    ariel::Graph g3;
    vector<vector<int>> weightedGraph = {
        {0, 2, 2},
        {2, 0, 3},
        {2, 3, 0}};
    g3.loadGraph(weightedGraph);
    ariel::Graph g4 = g3 * 3;
    CHECK(g4.printGraph() == "[0, 6, 6]\n[6, 0, 9]\n[6, 9, 0]");

    // Multiply a graph with negative values
    ariel::Graph g5;
    vector<vector<int>> grpah1 = {
        {0, 13, 18, -1},
        {25, 0, 2, 1},
        {1, -7, 0, 1},
        {231, -9, 1, 0}};
    g5.loadGraph(grpah1);
    ariel::Graph g6 = g5 * -2;
    CHECK(g6.printGraph() == "[0, -26, -36, 2]\n[-50, 0, -4, -2]\n[-2, 14, 0, -2]\n[-462, 18, -2, 0]");

    //try to multiply a graph with 0
    ariel::Graph g7;
    vector<vector<int>> grpah2 = {
        {0, 13, 18, -1},
        {25, 0, 2, 1},
        {1, -7, 0, 1},
        {231, -9, 1, 0}};
    g7.loadGraph(grpah2);
    ariel::Graph g8 = g7 * 0;
    CHECK(g8.printGraph() == "[0, 0, 0, 0]\n[0, 0, 0, 0]\n[0, 0, 0, 0]\n[0, 0, 0, 0]");
}

TEST_CASE("Test *= operator")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 2, 1},
        {2, 0, 2},
        {1, 2, 0}};
    g1.loadGraph(graph);    
    g1 *= 2;
    CHECK(g1.printGraph() == "[0, 4, 2]\n[4, 0, 4]\n[2, 4, 0]");

    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 2, 2},
        {2, 0, 3},
        {2, 3, 0}};
    g2.loadGraph(weightedGraph);    
    g2 *= 3;
    CHECK(g2.printGraph() == "[0, 6, 6]\n[6, 0, 9]\n[6, 9, 0]");
    // Multiply a graph with negative values
    ariel::Graph g3;
    vector<vector<int>> grpah1 = {
        {0, 13, 18, -1},
        {25, 0, 2, 1},
        {1, -7, 0, 1},
        {231, -9, 1, 0}};
    g3.loadGraph(grpah1);   
    g3 *= -2;
    CHECK(g3.printGraph() == "[0, -26, -36, 2]\n[-50, 0, -4, -2]\n[-2, 14, 0, -2]\n[-462, 18, -2, 0]");

    //try to multiply a graph with 0
    ariel::Graph g4;
    vector<vector<int>> grpah2 = {
        {0, 13, 18, -1},
        {25, 0, 2, 1},
        {1, -7, 0, 1},
        {231, -9, 1, 0}};
    g4.loadGraph(grpah2);
    g4 *= 0;
    CHECK(g4.printGraph() == "[0, 0, 0, 0]\n[0, 0, 0, 0]\n[0, 0, 0, 0]\n[0, 0, 0, 0]");
}

TEST_CASE("== operator")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    CHECK(g1 == g1);
    CHECK(g1 != g2);

    ariel::Graph g3;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g3.loadGraph(graph);
    CHECK(g1 == g3); 
}