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

    Graph::~Graph() {}
    void Graph::loadGraph(const vector<vector<int>> &matrix)
    {
        if (!validateSquareMatrix(matrix)){
            throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
        }

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
}