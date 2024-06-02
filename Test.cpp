
//Mail : yonidil1997@gmail.com
//ID : 316529445


#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Graph.hpp"
using namespace std;

TEST_CASE("Add graphs with different sizes") {
  ariel::Graph g1, g2, g3;
  vector<vector<int>> graph1 = {{0, 1}, {2, 0}};
  vector<vector<int>> graph2 = {{0}};
  g1.loadGraph(graph1);
  g2.loadGraph(graph2);

  // Expect an exception for graphs with different sizes
  CHECK_THROWS(g3 = g1 + g2);
}

TEST_CASE("Add weighted graphs with overlapping edges") {
  ariel::Graph g1, g2;
  vector<vector<int>> graph1 = {{0, 5, -2}, {5, 0, 1}, {-2, 1, 0}};
  vector<vector<int>> graph2 = {{0, 2, 0}, {2, 0, -3}, {0, -3, 0}};
  g1.loadGraph(graph1);
  g2.loadGraph(graph2);
  ariel::Graph g3 = g1 + g2;

  // Expected result: Sum of corresponding edge weights
  vector<vector<int>> expectedGraph = {{0, 7, -2}, {7, 0, -2}, {-2, -2, 0}};
  ariel::Graph expected;
  expected.loadGraph(expectedGraph);
  CHECK(g3 == expected);
}




TEST_CASE("Add")
{
    ariel::Graph g1, g2, g3, g4;
    vector<vector<int>> graph1 = {
        {0, -3},
        {7, 0}};
    vector<vector<int>> graph2 = {
        {0, 3},
        {3, 0}};
    g1.loadGraph(graph1);
    g2.loadGraph(graph2);
    g3 = g1 + g2;
    vector<vector<int>> expectedGraph = {{0, 0},{10,0}};
    ariel::Graph expected;
    expected.loadGraph(expectedGraph);
    CHECK(g3 == expected);
    g4.loadGraph(graph1);
    g4+= g2;
    CHECK(g3 == g4);

    g4++;
    CHECK(++g3 == g4);
    g3 += 1;
    CHECK(g3 == ++g4);


}

TEST_CASE("Subtract") {
    ariel::Graph g1, g2, g3;
    vector<vector<int>> graph1 = {{0, 1}, {2, 0}};
    vector<vector<int>> graph2 = {{0}};
    g1.loadGraph(graph1);
    g2.loadGraph(graph2);
    CHECK_THROWS(g3 = g1 - g2);


    graph1 = {{0, 5, -2}, {5, 0, 1}, {-2, 1, 0}};
    graph2 = {{0, 2, 0}, {2, 0, -3}, {0, -3, 0}};
    g1.loadGraph(graph1);
    g2.loadGraph(graph2);
    g3 = g1 - g2;
    vector<vector<int>> expectedGraph = {{0, 3, -2}, {3, 0, 4}, {-2, 4, 0}};
    ariel::Graph expected;
    expected.loadGraph(expectedGraph);
    CHECK(g3 == expected);

    g3 -= g2;
    expectedGraph = {{0,1,-2}, {1,0,7}, {-2, 7, 0}};
    expected.loadGraph(expectedGraph);
    CHECK(g3 == expected);

    g3 -= 3;
    expectedGraph = {{0,-2,-5}, {-2,0,4}, {-5, 4, 0}};
    expected.loadGraph(expectedGraph);
    CHECK(g3 == expected);

    expected -= 1;
    CHECK(--g3 == expected);

    CHECK(g3-- == expected); // decreade happend after the line

    expected -= 1;
    CHECK(g3 == expected);

    
}

TEST_CASE("Multiple"){
    ariel::Graph g1, g2, g3, g4;
    vector<vector<int>> graph1 = {{0, 1}, {2, 0}};
    vector<vector<int>> graph2 = {{0}};
    g1.loadGraph(graph1);
    g2.loadGraph(graph2);
    CHECK_THROWS(g3 = g1 * g2);


}