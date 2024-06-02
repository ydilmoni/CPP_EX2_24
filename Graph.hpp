


#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector> 
#include <ostream>
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

        Graph operator+(const Graph& other) const;
        Graph operator+(int n) const;
        Graph& operator++(); //prefix ++
        Graph operator++(int);
        Graph& operator+=(const Graph& other);
        Graph& operator+=(int n);

        Graph operator-(const Graph& other) const;
        Graph operator-(int n) const;
        Graph& operator--(); // prefix --
        Graph operator--(int);
        Graph& operator-=(const Graph &other);
        Graph& operator-=(int n);

        vector<vector<int>> matrix_multification(const vector<vector<int>>& matrixA, const vector<vector<int>>& matrixB) const;

        Graph operator*(const Graph& other) const;
        Graph& operator*=(const Graph& other);
        Graph operator*(int n) const;
        Graph& operator*=(int n);

        bool subMatrix(const vector<vector<int>> largeMatrix, const vector<vector<int>> smalMatrix) const;
        bool operator==(const Graph& other)const;
        bool operator>(const Graph& other)const;
        bool operator>=(const Graph& other)const;
        bool operator<(const Graph& other)const;
        bool operator<=(const Graph& other)const;
        bool operator!=(const Graph& other)const;

        friend ostream& operator<<(ostream &os, Graph graph);


        string print_matrix();
    };
}

#endif // GRAPH_HPP