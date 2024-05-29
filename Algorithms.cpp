//Mail : yonidil1997@gmail.com
//ID : 316529445

#include "Algorithms.hpp"
#include <vector>
#include <queue>
#include <string>
#include <unordered_set>
#include <limits>
#include <stack>
#include <iostream>
#include <climits>
#include <thread>
#include <chrono>
#include <algorithm>
using namespace std;

namespace ariel
{


    bool Algorithms::isConnected(const Graph &g)
    {
        vector< vector<int>> matrix = g.getMatrixGraph();
        size_t vertex = matrix.size();

        vector<bool> visited(vertex, false);
        queue<size_t> q;
        int count = 1;
        //אם הגרף לא מכוון אפשר פשוט לבדוק אם ניתן להגיע מקודקוד 0 לכל שאר הגרף, אחרת צריך לבדוק עבור כל קודקוד
        int iteration = g.getIsDirected()? vertex : 1;
        for (size_t i=0; i<iteration; i++){
            for (size_t j=0; j<vertex; j++){
                fill(visited.begin(), visited.end(), false);
                q.push(i);
                visited[i] = true;
                count = 1;

                while (!q.empty()) {
                    size_t u = q.front();
                    q.pop();

                    for (size_t v = 0; v < vertex; v++) {
                        if (matrix[u][v] != 0 && !visited[v]) {
                            visited[v] = true;
                            q.push(v);
                            count++;
                        }
                    }
                }

                if (count != vertex) {
                    cout<<"Unconnected graph!"<<endl;
                    return false;
                }
                               
            }
        }

        cout<<"The graph is connected"<<endl;
        return true;
    }

    string Algorithms::shortestPath(const Graph &g, int start, int end) 
    {
        if (start < 0 || end < 0 || start > g.getNumOfvertices() - 1 || end > g.getNumOfvertices() - 1)
        {
            // כלומר אם ביקשת את הפעולה עבור קודקודים שלא נמצאים בכלל
            cout<< "Out of range!\n you must ask for values between 0 and " +to_string(g.getNumOfvertices() - 1)<<endl;
            return "-1";
        }

        if (start == end)
        {
            cout<<"Start and end vertices are the same."<<endl;
            return  "-1";
        }

        vector<vector<int>> matrix = g.getMatrixGraph();
        vector<int> parents;

        if (!g.getIsWeighted())//אם אין משקלים
        {
            parents= bfs(matrix, start, end);
            //הלולאה שפה רק למקרה שרוצים לבדוק שהאלגוריתם החזיר את רשימת ההורים שציפינו
            // for(int i =0; i<matrix.size();i++){
            //     cout<<"father of "<< to_string(i)<<" is "<<to_string(parents[i])<<endl;
            // }
            return printPath(parents, start, end);
        }

        if (!g.getHaveNegative())//אם גרף ממושקל ללא משקלים שליליים נשתמש בדייקסטרה
        {
            cout << "using Dijkstra's algorithm to find the shortest path from: \n \
            vertex "<< to_string(start) << " to vertex "<< to_string(end) << endl;
            parents = dijkstra(matrix, start, end);

            return printPath(parents, start, end);
        }

        cout << "There is a negative value in the graph.\
        \nUsing Bellman-Ford algorithm to find the shortest path from\
         \nvertex " +to_string(start) + " to vertex " +to_string(end)<<endl;

        parents  = belmanFordAlgorithm(matrix, start);
        return printPath(parents, start, end);
    }

    bool Algorithms::isContainsCycle(const Graph &g)
    {
        if(g.getNumOfEdges()<2){
            cout<<"No cycle found."<<endl;//אין מעגל אם אין מספיק צלעות
            return false;
        }
        size_t vertex = g.getNumOfvertices();
        vector<vector<int>> matrix = g.getMatrixGraph();
        string result;
        vector<int> parentsIJ(vertex,-1);
        int ij;

        for (size_t i=0; i<vertex; i++){
            for (size_t j=0; j<vertex; j++){
                if(i!=j){
                    ij = matrix[i][j];
                    if (!g.getIsDirected()){
                        matrix[i][j] = 0;
                    }

                    parentsIJ = bfs(matrix,i,j); //בודק אם יש מסלול בשני הכיוונים- אם יש אז יש מעגל

                    matrix[i][j] = ij;

                    if(parentsIJ[j]!=-1){//קיים מסלול מההתחלה לסוף
                        {
                            if (!g.getIsDirected() && matrix[j][i]!=0){//אם הוא לא מכוון וגם יש צלע מב' לא' אז יש מעגל
                                vector<int> cycleVec;
                                int k=j;
                                while (k >= 0){
                                    cycleVec.push_back(k);
                                    k=parentsIJ[k];
                                }
                                cycleVec.push_back(j);
                                size_t vecSize = cycleVec.size();

                                cout<<"There is a cycle in the graph: \n"<<endl;
                                for(size_t t=0; t< vecSize-1; t++){
                                    result = result+to_string(cycleVec[t])+"->";
                                }
                                result = result+to_string(cycleVec[vecSize-1]);
                                cout<< result<<endl;
                                return true;

                            }
                            else if (g.getIsDirected() && matrix[j][i]!=0)//'או אם הוא לא מכוון ויש צלע בין ב' לא
                            {
                                vector<int> cycleVec;
                                int k=j;
                                while (k != -1){
                                    cycleVec.push_back(k);
                                    k=parentsIJ[k];
                                }
                                cycleVec.push_back(j);
                                size_t vecSize = cycleVec.size();

                                cout<<"There is a cycle in the graph: \n"<<endl;
                                for(size_t t=0; t< vecSize-1; t++){
                                    result = result+to_string(cycleVec[t])+"->";
                                }
                                result = result+to_string(cycleVec[vecSize-1]);
                                cout<< result<<endl;
                                return true;
                            }
                            
                        }
                    }
                    

                }                
            }
        }
        cout<<"No cycle found."<<endl;//לא מצאנו מעגל אמיתי עד עכשיו לכן אין מעגל
        return false;
    }

    bool Algorithms::isBipartite(const Graph &g)
    {
        vector<vector<int>> matrix = g.getMatrixGraph();
        size_t numVertices = g.getNumOfvertices();

        vector<int> colors(numVertices, -1); // מעקב אחרי צבעים
        vector<vector<int>> groups(2);//קבוצות החלוקה       
        queue<int> q;                        

        for (size_t i = 0; i < numVertices; i++)//מעבר על כל הקודקודים
        {
            if (colors[i] == -1)//אם אתה עדיין לא צבוע
            {
                colors[i] = 0;//נצבע אותך בצבע 0          
                groups[0].push_back(i); //ונוסיף אותך לקבוצה 0
                q.push(i);

                while (!q.empty())
                {
                    int current = q.front();
                    q.pop();

                    
                    for (size_t neighbor = 0; neighbor < matrix[current].size(); neighbor++)//מעבר על כל השכנים
                    {
                        if (matrix[current][neighbor])//אם קיימת צלע ביניהם
                        {
                           
                            if (colors[neighbor] == -1) //אם השכן לא צבוע 
                            {
                                colors[neighbor] = 1 - colors[current];//נצבע אותו בצבע ההפוך מהקודקוד הנוכחי
                                groups[colors[neighbor]].push_back(neighbor);//נוסיף את השכן לקבוצה שלו
                                q.push(neighbor);
                            }
                            //אם לשכן יש אותו צבע כמו לנוכחי אז הם לא ניתנים לחלוקה ל2
                            else if (colors[neighbor] == colors[current])
                            {
                                cout<<"The graph is not bipartite."<<endl;
                                return false;
                            }
                        }
                    }
                }
            }
        }

        //הדפסה של הקבוצות
        string result = "Bipartite groups:\nGroup A: ";
        for (int vertex : groups[0])
        {
            result += to_string(vertex) + " ";
        }
        result += "\nGroup B: ";
        for (int vertex : groups[1])
        {
            result += to_string(vertex) + " ";
        }
        cout<<result<<endl;
        return true;;
    }

    bool Algorithms::negativeCycle(const Graph &g)
    {
        if (!g.getHaveNegative() || !g.getIsWeighted() || g.getNumOfEdges()<2 || g.getNumOfvertices()<2)
        {
            cout<<"There is no negative values in this graph --> There is no negative cycle\
            \n Or there is no enough edges or vertices --> There is no negative cycle "<<endl;
            return false;
        }

        
        vector<vector<int>> matrix = g.getMatrixGraph();
        size_t n = g.getNumOfvertices();
        vector<int> distances (n,INT_MAX);
        vector<int> parents(n,-1);
        distances[0]=0;
        
        string result;

        for (size_t i = 0; i < n-1; i++)
        {
            for(size_t u = 0; u < n ; u++ ){
                for(size_t v = 0; v < n; v++) {
                    if(u!=v && matrix[u][v]!=0 && distances[u]!=INT_MAX && distances[v] > distances[u] + matrix[u][v] ){
                        distances[v] = distances[u] + matrix[u][v];
                        parents[v] = u;
                    }
                }
            }
        }
        
        for(size_t u = 0; u < n ; u++ ){
            for(size_t v = 0; v < n; v++) {
                if(matrix[u][v]!=0 &&distances[u]!=INT_MAX&& (distances[v] > distances[u] + matrix[u][v])){

                    
                    if (!g.getIsDirected()){
                        for(size_t i=0; i<parents.size(); i++){
                            if(parents[i]>=0 && parents[parents[i]]==i){
                                cout<<"There is no negative cycle"<<endl;
                                return false;
                            }
                        }
                        
                    }
                    result= printNegativePath(parents, matrix, 0);
                    cout<<result<<endl;
                    return true;
                    

                }
            }
        }
        
        cout<<"There is no negative cycle"<<endl;
        
        return false;
    }

    vector<int> Algorithms::bfs(const vector<vector<int>> &matrix, int start, int end)//סיימתי
    {
        queue<int> Q; // ככה קראו לתור באלגו 1. זרמתי
        size_t vertex = matrix.size();
        vector<string> colors(vertex, "white");
        vector<int> distans(vertex, INT_MAX);
        vector<int> parents(vertex, -1); // יסמן אין הורים כרגע, אולי יהיו הורים אחר כך
        colors[start] = "gray";
        distans[start] = 0;
        parents[start] = -1;
        Q.push(start);
        while (!Q.empty())
        {
            int u = Q.front();
            Q.pop();
            for (size_t v = 0; v < vertex; v++)
            {
                if (matrix[u][v] != 0 && v != u)
                {
                    if (colors[v] == "white")
                    {
                        colors[v] = "gray";
                        distans[v] = distans[u] + 1;
                        parents[v] = u;
                        Q.push(v);
                    }
                }
            }
            colors[u] = "black";
        }
        return parents;
    }

    vector<int> Algorithms::dijkstra(const vector<vector<int>> &matrix, int start, int end)//סיימתח
    {

        vector<int> distances(matrix.size(), INT_MAX);
        vector<int> parents(matrix.size(), -1);

        auto compare = [&distances](size_t a, size_t b) {
            return distances[a] > distances[b];
        };

        priority_queue<int, vector<int>, decltype(compare)> pq(compare);

        distances[start] = 0;
        pq.push(start); 

        while (!pq.empty())
        {
            int u = pq.top();
            pq.pop();
            for (size_t v = 0; v < matrix.size(); v++)
            {
                if (matrix[u][v] != 0 && distances[v] > distances[u] + matrix[u][v])
                {
                    distances[v] = distances[u] + matrix[u][v];
                    parents[v] = u;
                    pq.push(v); 
                }
            }
        }


        return parents;
    }

    vector<int> Algorithms::belmanFordAlgorithm(const vector<vector<int>>& matrix, int start)//סיימתי
    {
        size_t n = matrix.size();
        vector<int> distances(n, INT_MAX);
        vector<int> parents(n,-1);
        distances[start] = 0;
        for (size_t i = 0; i < n-1; i++)
        {
            for (size_t u = 0; u < n; u++)
            {
                for (size_t v = 0; v < n; v++)//עבור כל צלע
                {
                    if (u!=v && matrix[u][v]!=0 && distances[u]!=INT_MAX && distances[v] > distances[u] + matrix[u][v] ){
                        distances[v] = distances[u] + matrix[u][v];
                        parents[v] = u;
                    }
                }
            }
        }
        
        for (size_t u = 0; u < n; u++)
        {
            for (size_t v = 0; v < n; v++)
            {
                if (matrix[u][v]!=0 &&distances[u]!=INT_MAX&& (distances[v] > distances[u] + matrix[u][v]) )
                {   
                    parents.push_back(-3);
                    return parents;
                }
            }
        }
        return parents;
    }

    string Algorithms::printPath(vector<int> &parents, int start, int end)//סיימתי
    {
        
        if (parents[parents.size()-1]==-3){
            cout<< "Error: there is a negative cycle."<<endl;//קיבלתי את הסימון של בלמן פורד לכך שיש מעגל שלילי
            return "-1";
        }
        
        if(parents[end] == start){
            return to_string(start) + "->" + to_string(end);
        }
        
        string result;
        size_t current = end;
        while (parents[current]!= -1)
        {
            result = "->" + to_string(current) + result;
            current = parents[current];
        }

        if (result == "" || current != start){
            cout<<"There is no path from vertex "+ to_string(start) +" to vertex " +to_string(end)<<endl;
            return "-1";
        }
        result =to_string(start)+ result;
        
        return result;
    }

    string Algorithms::printNegativePath(vector<int> &parents,const vector<vector<int>>& matrix, int start)
    {
        string result;
        size_t n = parents.size();
        vector<bool> visited(n,false);
        size_t u = start;

        while (!visited[u])
        {
            visited[u] = true;
            u = parents[u];
        }

        size_t v = parents[u];
        cout << "Negative cycle found: "<<endl;
        result += "{{ "+ to_string(u)+" }} ";
        
        while (v != u) {
        
        // result += "--( W: "+to_string(matrix[v][parents[v]])+ " ) -->> {{ "+ to_string(v)+" }} "; // אם רוצים לראות גם משקלים
        result += "---->> {{ "+ to_string(v)+" }} ";
        v = parents[v];
        }
        // result += "--( W: "+to_string(matrix[v][parents[v]])+ " )-->> {{ "+ to_string(u)+" }} ";//אם רוצים עם משלקים
        result += "---->> {{ "+ to_string(u)+" }} ";

        return result;
    }
}