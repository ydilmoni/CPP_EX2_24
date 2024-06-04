
//Mail : yonidil1997@gmail.com
//ID : 316529445


#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Graph.hpp"
using namespace std;

TEST_CASE("Add")
{
    ariel::Graph graph1, graph2, graph3, graph4;
    vector<vector<int>> matrix1 = {
        {0, -3},
        {7, 0}};
    vector<vector<int>> matrix2 = {
        {0, 3},
        {3, 0}};
    graph1.loadGraph(matrix1);
    graph2.loadGraph(matrix2);
    graph3 = graph1 + graph2;
    vector<vector<int>> expectedMatrix = {{0, 0},{10,0}};
    ariel::Graph expected;
    expected.loadGraph(expectedMatrix);
    CHECK(graph3 == expected);
    graph4.loadGraph(matrix1);
    graph4+= graph2;
    CHECK(graph3 == graph4);

    graph4++;
    CHECK(++graph3 == graph4);
    graph3 += 1;
    CHECK(graph3 == ++graph4);


}

TEST_CASE("Subtract") {
    ariel::Graph graph1, graph2, graph3;
    vector<vector<int>> matrix1 = {{0, 1}, {2, 0}};
    vector<vector<int>> matrix2 = {{0}};
    graph1.loadGraph(matrix1);
    graph2.loadGraph(matrix2);
    CHECK_THROWS(graph3 = graph1 - graph2);


    matrix1 = {{0, 5, -2}, {5, 0, 1}, {-2, 1, 0}};
    matrix2 = {{0, 2, 0}, {2, 0, -3}, {0, -3, 0}};
    graph1.loadGraph(matrix1);
    graph2.loadGraph(matrix2);
    graph3 = graph1 - graph2;
    vector<vector<int>> expectedMatrix = {{0, 3, -2}, {3, 0, 4}, {-2, 4, 0}};
    ariel::Graph expectedGraph;
    expectedGraph.loadGraph(expectedMatrix);
    CHECK(graph3 == expectedGraph);

    graph3 -= graph2;
    expectedMatrix = {{0,1,-2}, {1,0,7}, {-2, 7, 0}};
    expectedGraph.loadGraph(expectedMatrix);
    CHECK(graph3 == expectedGraph);

    graph3 -= 3;
    expectedMatrix = {{0,-2,-5}, {-2,0,4}, {-5, 4, 0}};
    expectedGraph.loadGraph(expectedMatrix);
    CHECK(graph3 == expectedGraph);

    expectedGraph -= 1;
    CHECK(--graph3 == expectedGraph);

    CHECK(graph3-- == expectedGraph); // decreade happend after the line

    expectedGraph -= 1;
    CHECK(graph3 == expectedGraph);

    
}

TEST_CASE("Multiple"){
    ariel::Graph graph1, graph2, graph3, graph4, expectedGraph;
    vector<vector<int>> matrix1 = {{0, 1}, {2, 0}};
    vector<vector<int>> matrix2 = {{0}};
    vector<vector<int>> matrix3 = {{0,2}, {5,0}};
    vector<vector<int>> expectedMatrix = {{0, 0}, {0, 0}};
    graph1.loadGraph(matrix1);
    graph2.loadGraph(matrix2);
    CHECK_THROWS(graph3 = graph1 * graph2);
    graph3.loadGraph(matrix3);
    graph4 = graph1 * graph3;
    expectedGraph.loadGraph(expectedMatrix);
    CHECK(graph4 == expectedGraph);


    matrix1 = {{0, 1,0}, {2, 0,5},{4,2,0}};
    matrix2 = {{0,2,5}, {5,0,5},{0,0,0}};
    graph1.loadGraph(matrix1);
    graph2.loadGraph(matrix2);
    graph3 = graph1 * graph2;
    expectedMatrix = {{0,0,5}, {0,0,10}, {10,8,0}};
    expectedGraph.loadGraph(expectedMatrix);
    CHECK(graph3 == expectedGraph);

    graph2 *= 2; 
    expectedMatrix = {{0,4,10}, {10,0,10},{0,0,0}};
    expectedGraph.loadGraph(expectedMatrix);
    CHECK(graph2 == expectedGraph);
    
    graph4  = graph1 * 5;
    expectedMatrix = {{0, 5,0}, {10, 0,25},{20,10,0}};
    expectedGraph.loadGraph(expectedMatrix);
    CHECK(graph4 == expectedGraph);

}

TEST_CASE("Bompare Between Graphs"){
    ariel::Graph graph1, graph2, graph3, graph4, expectedGraph;
    vector<vector<int>> matrix1 = {{0, 1}, {2, 0}};
    vector<vector<int>> matrix2 = {{0}};
    vector<vector<int>> matrix3 = {{0,4,8,9},{1,0,3,5},{1,8,0,6},{8,4,7,0}};
    vector<vector<int>> matrix4 = {{0,4}, {1,0}};
    vector<vector<int>> expectedMatrix = {{0, 0}, {0, 0}};
    graph1.loadGraph(matrix1);
    graph2.loadGraph(matrix2);
    graph3.loadGraph(matrix3);
    graph4.loadGraph(matrix4);
    CHECK(graph2 < graph1);
    CHECK(graph2 != graph1);
    CHECK(graph3 > graph4);
    CHECK_FALSE(graph1 > graph4);
    CHECK_FALSE(graph1 < graph4);
    graph3.loadGraph(matrix4);
    CHECK(graph3 >= graph4);
    CHECK(graph3 <= graph4);
    
}


