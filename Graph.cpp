//Mail : yonidil1997@gmail.com
//ID : 316529445

#include "Graph.hpp"
#include <iostream>
using namespace std;

namespace ariel {

    Graph::Graph(){
        num_of_vertices = 0;
        num_of_edges = 0;
    }

    Graph::Graph(const Graph& other)
    {
        this->loadGraph(other.getMatrixGraph());
    }

    Graph::Graph(int num_of_vertex)
    {
        vector<vector<int>> matrix(num_of_vertex, vector<int>(num_of_vertex, 0));
        this->loadGraph(matrix);
    }

    Graph::~Graph() {}

    void Graph::loadGraph(const vector<vector<int>> &matrix)
    {
        if (!validateSquareMatrix(matrix)){
            throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
        }
        num_of_vertices = 0;
        num_of_edges = 0;
        this->matrix_graph = matrix;
        this->num_of_vertices = this->matrix_graph.size();
        if(num_of_vertices==0){
            throw std::invalid_argument("Invalid graph: There is no vertex.");
        }
        
        this->num_of_edges = 0;
        this->isDirected=false;
        this->isWeighted=false;
        this->haveNegative=false;
        for (size_t i = 0 ; i<this->num_of_vertices; i++) {
            for (size_t j=0; j< this->num_of_vertices; j++) {
                if (this->matrix_graph[i][j]!= 0) {
                    if(i==j){
                        throw std::invalid_argument("Invalid graph: There is a edge from vertex "+to_string(i)+" to himself.");
                    }

                    num_of_edges++;
                    
                    if (this->matrix_graph[i][j]!=1){//אם זה לא אחד ולא 0 אז יש משקל
                        this->isWeighted = true;
                        if (this->matrix_graph[i][j] < 0){
                            //אם יש משקל והוא קטן מ0 אז יש משקל שלילי (ואולי גם מעגל שלילי בהמשך)
                            this->haveNegative=true;
                        }
                    }
                }
                if (this->matrix_graph[i][j] != this->matrix_graph[j][i]){
                    //בדיקה האם המטריצה סימטרית- אם לא סימטרית אז היא מכוונת
                    this->isDirected=true;
                }

            }
        }
        if (!isDirected){
        //אם הגרף לא מכוון אז ספרנו כל צלע פעמיים - גם את צלע (1,3) וגם את צלע (3,1) למרות שזאת אותה צלע
            num_of_edges /= 2;//לכן נחלק ב2
        }
    }

    void Graph::printGraph() const {
        cout << "The graph has " << num_of_vertices << " vertices and " << num_of_edges << " edges" << endl;
    }
    
    bool Graph::validateSquareMatrix(const vector<vector<int>> &matrix)
    {
        for (size_t i=0; i<matrix.size(); i++){
            if (matrix.size() != matrix[i].size()){
                return false;
            }
        }
        return true;
    }

    vector<vector<int>> Graph::matrix_multification(vector<vector<int>> matrixA, vector<vector<int>> matrixB)
    {
        if (matrixA.size() != matrixB.size() || matrixA[0].size() != matrixB.size() || matrixA.size() != matrixA[0].size())
        {
            throw std::invalid_argument("Graphs must have the same number of vertices to be multipule.");
        }
        size_t n = matrixA.size();

        vector<vector<int>> result(n, vector<int>(n, 0));

        for (size_t i = 0; i < n ; i++) {
            for (size_t j = 0; j < n ; j++) {
                for (size_t k = 0; k < n ; k++) {
                    result[i][j] += matrixA[i][k] * matrixB[k][j];
                }
            }
        }
        return result;
    }

    Graph Graph::operator+(const Graph &other) const
    {
        if (num_of_vertices != other.num_of_vertices) {
            throw std::invalid_argument("Graphs must have the same number of vertices to be added.");
        }
        Graph result_graph;
        vector<vector<int>> result_matrix(num_of_vertices, vector<int>(num_of_vertices, 0));
        for (size_t i = 0; i < num_of_vertices; i++) {
            for (size_t j = 0; j < num_of_vertices; j++) {
                result_matrix[i][j] = matrix_graph[i][j] + other.matrix_graph[i][j];
            }
        }
        result_graph.loadGraph(result_matrix);
        return result_graph;
    }


    Graph& Graph::operator++(){ // prefix ++
        vector<vector<int>> result_matrix(num_of_vertices, vector<int>(num_of_vertices, 0));
        for (size_t i = 0; i < num_of_vertices; i++) {
            for (size_t j = 0; j < num_of_vertices; j++) {
                if (matrix_graph[i][j] != 0){
                    result_matrix[i][j] = matrix_graph[i][j] + 1;
                }
            }
        }
        this->loadGraph(result_matrix);
        return *this;
    }

    Graph Graph::operator++(int)
    {
        Graph result_graph = *this;
        ++(*this);
        return result_graph;
    }

    // Graph Graph::operator-(const Graph &other) const{
    //      if (num_of_vertices != other.num_of_vertices) {
    //         throw std::invalid_argument("Graphs must have the same number of vertices to be added.");
    //     }
    //     Graph result_graph;
    //     vector<vector<int>> result_matrix(num_of_vertices, vector<int>(num_of_vertices, 0));
    //     for (size_t i = 0; i < num_of_vertices; i++) {
    //         for (size_t j = 0; j < num_of_vertices; j++) {
    //             result_matrix[i][j] = matrix_graph[i][j] - other.matrix_graph[i][j];
    //         }
    //     }
    //     result_graph.loadGraph(result_matrix);
    //     return result_graph;
    // }

    // Graph Graph::operator*(const Graph &other) const
    // {
    //     return Graph();
    // }

    void Graph::print_matrix()
    {
        for (size_t i = 0; i < this->getNumOfvertices(); i++)
        {
            for (size_t j = 0; j < this->getNumOfvertices(); j++)
            {
                cout<< this->getMatrixGraph()[i][j]<< " ";
            }
            cout<<endl;
        }
        
    }
}