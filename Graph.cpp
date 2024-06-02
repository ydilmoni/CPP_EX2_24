
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

// + operators
 
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

    Graph Graph::operator+(int n) const
    {
        Graph result_graph;
        vector<vector<int>> result_matrix(num_of_vertices, vector<int>(num_of_vertices, 0));
        for (size_t i = 0; i < num_of_vertices; i++) {
            for (size_t j = 0; j < num_of_vertices; j++) {
                if (i != j && matrix_graph[i][j] != 0)
                {
                    result_matrix[i][j] = matrix_graph[i][j] + n;
                }
            }
        }
        result_graph.loadGraph(result_matrix);
        return result_graph;
    }

    Graph& Graph::operator++(){ // prefix ++
        
        for (size_t i = 0; i < num_of_vertices; i++) {
            for (size_t j = 0; j < num_of_vertices; j++) {
                if (matrix_graph[i][j] != 0){
                    matrix_graph[i][j]++;
                }
            }
        }
        this->loadGraph(matrix_graph);
        return *this;
    }

    Graph Graph::operator++(int)
    {
        Graph result_graph = *this;
        ++(*this);
        return result_graph;
    }

    Graph& Graph::operator+=(const Graph &other)
        {
            if (num_of_vertices != other.num_of_vertices) {
                throw std::invalid_argument("Graphs must have the same number of vertices to be added.");
            }
            for (size_t i = 0; i < num_of_vertices; i++) {
                for (size_t j = 0; j < num_of_vertices; j++) {
                    matrix_graph[i][j] += other.matrix_graph[i][j];
                }
            }
            this->loadGraph(matrix_graph);
            return *this;
        }

    Graph &Graph::operator+=(int n)
    {
     for (size_t i = 0; i < num_of_vertices; i++) {
                for (size_t j = 0; j < num_of_vertices; j++) {
                    if(i != j && matrix_graph[i][j] !=0 ){
                        matrix_graph[i][j] += n;
                    }
                }
            }
            this->loadGraph(matrix_graph);
            return *this;       
    }

// - operators

    Graph Graph::operator-(const Graph &other) const
    {
        if (num_of_vertices != other.num_of_vertices) {
            throw std::invalid_argument("Graphs must have the same number of vertices to be added.");
        }
        Graph result_graph;
        vector<vector<int>> result_matrix(num_of_vertices, vector<int>(num_of_vertices, 0));
        for (size_t i = 0; i < num_of_vertices; i++) {
            for (size_t j = 0; j < num_of_vertices; j++) {
                result_matrix[i][j] = matrix_graph[i][j] - other.matrix_graph[i][j];
            }
        }
        result_graph.loadGraph(result_matrix);
        return result_graph;
    }

    Graph Graph::operator-(int n) const
    {
        Graph result_graph;
        vector<vector<int>> result_matrix(num_of_vertices, vector<int>(num_of_vertices, 0));
        for (size_t i = 0; i < num_of_vertices; i++) {
            for (size_t j = 0; j < num_of_vertices; j++) {
                if (i != j && matrix_graph[i][j] != 0)
                {
                    result_matrix[i][j] = matrix_graph[i][j] - n;
                }
            }
        }
        result_graph.loadGraph(result_matrix);
        return result_graph;
    }

    Graph& Graph::operator--()
    {
        for (size_t i = 0; i < num_of_vertices; i++) {
            for (size_t j = 0; j < num_of_vertices; j++) {
                if (matrix_graph[i][j] != 0){
                    matrix_graph[i][j]--;
                }
            }
        }
        this->loadGraph(matrix_graph);
        return *this;
    }

    Graph Graph::operator--(int)
    {
        Graph result_graph = *this;
        --(*this);
        return result_graph;
    }

    Graph& Graph::operator-=(const Graph &other)
        {
            if (num_of_vertices != other.num_of_vertices) {
                throw std::invalid_argument("Graphs must have the same number of vertices to be added.");
            }
            for (size_t i = 0; i < num_of_vertices; i++) {
                for (size_t j = 0; j < num_of_vertices; j++) {
                    matrix_graph[i][j] -= other.matrix_graph[i][j];
                }
            }
            this->loadGraph(matrix_graph);
            return *this;
        }

        Graph &Graph::operator-=(int n)
        {
            for (size_t i = 0; i < num_of_vertices; i++) {
                for (size_t j = 0; j < num_of_vertices; j++) {
                    if(i != j){
                        matrix_graph[i][j] -= n;
                    }
                }
            }
            this->loadGraph(matrix_graph);
            return *this;
        }

// * operators

    vector<vector<int>> Graph::matrix_multification(const vector<vector<int>>& matrixA, const vector<vector<int>>& matrixB) const
    {
        if (matrixA.size() != matrixB.size() || matrixA[0].size() != matrixB.size() || matrixA.size() != matrixA[0].size())
        {
            throw std::invalid_argument("Graphs must have the same number of vertices to be multipule.");
        }
        size_t n = matrixA.size();

        vector<vector<int>> result(n, vector<int>(n, 0));

        for (size_t i = 0; i < n ; i++) {
            for (size_t j = 0; j < n ; j++) {
                if (i != j){
                    for (size_t k = 0; k < n ; k++) {
                        result[i][j] += matrixA[i][k] * matrixB[k][j];
                    }
                }
            }
        }
        return result;
    }

    Graph Graph::operator*(const Graph &other) const
    {
        if (num_of_vertices != other.num_of_vertices) {
            throw std::invalid_argument("Graphs must have the same number of vertices to be added.");
        }
        Graph result_graph;
        vector<vector<int>> result_matrix = matrix_multification(this->getMatrixGraph(), other.getMatrixGraph());
        result_graph.loadGraph(result_matrix);
        return result_graph;
    }

    Graph &Graph::operator*=(const Graph &other)
    {
        if (num_of_vertices != other.num_of_vertices) {
            throw std::invalid_argument("Graphs must have the same number of vertices to be added.");
        }
        
        matrix_graph = matrix_multification(matrix_graph, other.getMatrixGraph());
        this->loadGraph(matrix_graph);
        return *this;
    }

    Graph Graph::operator*(int n) const
    {
        Graph result_graph;
        vector<vector<int>> result_matrix(num_of_vertices, vector<int>(num_of_vertices, 0));
        for (size_t i = 0; i < num_of_vertices; i++){
            for (size_t j = 0; j < num_of_vertices; j++){
                result_matrix[i][j] = matrix_graph[i][j] * n;
            }
        }
        result_graph.loadGraph(result_matrix);
        return result_graph;
    }

    Graph &Graph::operator*=(int n)
    {
        *this = *this * n;
        return *this;
    }

// ><= operators

    bool Graph::subMatrix(const vector<vector<int>> largeMatrix, const vector<vector<int>> smallMatrix) const
    {
        size_t largeSize = largeMatrix.size();
        size_t smallSize = smallMatrix.size();

        if (smallSize > largeSize){
            return false;
        }
        for (size_t i = 0; i < largeSize; i++){
            for (size_t j = 0; j < largeSize; j++){
                bool isSubMatrix = true;

                for (size_t x = 0; x < smallSize && isSubMatrix; x++){
                    for (size_t y = 0; y < smallSize && isSubMatrix; y++){
                        if (largeMatrix[i + x][j + y] != smallMatrix[x][y]) {
                            isSubMatrix = false; // מצאנו חוסר התאמה ולכן נעבור לעמודה הבאה במטריצה הגדולה (J)
                        }
                
                    }
                }
                if (isSubMatrix){ // סיימנו לעבור על כל המטריצה הקטנה והכל התאים
                    return true;
                }
                
            }
        }
        return false; // לא החזרנו אמת עד עכשיו לכן זה בטוח שקר
        
    }

    bool Graph::operator==(const Graph &other) const
    {
        if (this->getNumOfEdges() != other.getNumOfEdges()){
            return false;
        }

        if (this->getNumOfvertices() != other.getNumOfvertices()){
            return false;
        }

        size_t n = this->getNumOfvertices();

        for (size_t i = 0; i < n; i++){
            for (size_t j = 0; j < n; j++){
                if (this->getMatrixGraph()[i][j] != other.getMatrixGraph()[i][j])
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool Graph::operator>(const Graph &other) const
    {
        if (other.getMatrixGraph() == this->getMatrixGraph()){
            return false;
        }

        if (subMatrix(this->getMatrixGraph(), other.getMatrixGraph())){
            return true;
        }

        if (subMatrix(other.getMatrixGraph(), this->getMatrixGraph())){
            return false;
        }

        if (this->getNumOfEdges() > other.getNumOfEdges()){
            return true;
        }
        
        if (this->getNumOfvertices() > other.getNumOfvertices()){
            return true;
        }

        return false;

    }

    bool Graph::operator>=(const Graph &other) const
    {
        if (*this == other || *this > other){
            return true;
        }
        return false;
    }

    bool Graph::operator<(const Graph &other) const
    {
         if (other.getMatrixGraph() == this->getMatrixGraph()){
            return false;
        }

        if (subMatrix(other.getMatrixGraph(), this->getMatrixGraph())){
            return true;
        }

        if (subMatrix(this->getMatrixGraph(), other.getMatrixGraph())){
            return false;
        }

        if (this->getNumOfEdges() < other.getNumOfEdges()){
            return true;
        }
        
        if (this->getNumOfvertices() < other.getNumOfvertices()){
            return true;
        }

        return false;
    }

    bool Graph::operator<=(const Graph &other) const
    {
        if (*this == other || *this < other){
            return true;
        }
        return false;
    }

    bool Graph::operator!=(const Graph &other) const
    {
        if(!(*this == other)){
            return true;
        }
        return false;
    }


    string Graph::print_matrix()
    {
        string result;
        for (size_t i = 0; i < this->getNumOfvertices(); i++)
        {
            for (size_t j = 0; j < this->getNumOfvertices(); j++)
            {
                result += to_string(this->getMatrixGraph()[i][j]) + " ";
            }
            result += "\n";
        }
        return result;
        
    }

    ostream &operator<<(ostream &os, Graph graph)
    {
        os << graph.print_matrix();
        os << endl;
        return os;
    }

}