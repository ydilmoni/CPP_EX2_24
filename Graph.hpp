
//Mail : yonidil1997@gmail.com
//ID : 316529445

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector> 
using namespace std;


namespace ariel {
    class Graph {
    private:
        vector<vector<int> > matrix_graph;
        size_t num_of_vertices;
        size_t num_of_edges;
        bool isDirected;
        bool isWeighted;
        bool haveNegative;

    public:
        Graph();  // Constructor declaration
        Graph(const Graph& other); // copy constructor : task 2
        Graph(int num_of_vertex); // empty constructor - for operators: task 2
        ~Graph(); // Destructor declaration
        
        void loadGraph(const vector<vector<int> >& matrix);
 
        void printGraph() const;
 
        size_t getNumOfvertices() const { 
            return num_of_vertices; 
        }
 
        size_t getNumOfEdges() const {
             return num_of_edges; 
        }
 
        const vector<vector<int> >& getMatrixGraph() const { 
            return matrix_graph; 
        }
 
        bool getIsDirected() const { 
            return isDirected; 
        } 
 
        bool getIsWeighted() const { 
            return isWeighted; 
        } 
 
        bool getHaveNegative() const { 
            return haveNegative; 
        } 

        static bool validateSquareMatrix(const vector<vector<int> >& matrix);

        vector<vector<int>> matrix_multification(vector<vector<int>> matrixA,vector<vector<int>> matrixB);
        Graph operator+(const Graph& other) const;
        Graph& operator++(); //prefix ++
        Graph operator++(int);
        // Graph operator-(const Graph& other) const;
        // Graph operator--(int);
        // Graph operator--();
        // Graph operator*(const Graph& other) const;
        // Graph& Graph::operator+=(const Graph& other);
        // Graph& Graph::operator-=(const Graph& other);
        // Graph& Graph::operator*=(const Graph& other);

        void print_matrix();
    };
}

#endif // GRAPH_HPP