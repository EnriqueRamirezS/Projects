#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <queue>
#include <cctype>

using namespace std;

string toUpper(const string& str){
    string result = str;
    for (char& c : result) {
        c = std::toupper(c);
    }
    return result;
}

class Graph{
public:
    void addVertex(const string& src){
        if(aList.find(src) == aList.end()){
            aList[src] = vector<string>(); // makes a vector
        }
    }
    void addEdge(const string& src, const string& dst){
        addVertex(src);
        addVertex(dst);
        
        vector<string>& destinations = aList[src]; // get the vector of destinations
        auto it = find(destinations.begin(), destinations.end(), dst); // find in vector
        
        if(it == destinations.end()){ // if dst not found
            aList[src].push_back(dst);
        }
    }
    void addEdgeUndirected(unordered_map<string, vector<string>>& graph, const string& src, const string& dst) {
        graph[src].push_back(dst);
        graph[dst].push_back(src); 
    }
   
    void print(const string& src){
        auto it = aList.find(src);
        if(it != aList.end()){
            cout<< src<< ": [";
            for(int i; i<it->second.size(); i++){
                cout<< it->second[i]<<",";
            }
            cout<<"] "<<endl;
        }
        else{
            cout<<"Error no match found"<<endl;  
        }
    }
    
    bool isWeaklyConnected() {
    unordered_map<string, vector<string>> aList_Undirected;

    // Convert to undirected edges
    for (auto it = aList.begin(); it != aList.end(); ++it) {
        const string& src = it->first;
        const vector<string>& destinations = it->second;

        for (auto jt = destinations.begin(); jt != destinations.end(); ++jt) {
            const string& dst = *jt;
            addEdgeUndirected(aList_Undirected, src, dst);
        }
    }

   
    unordered_map<string, bool> visited;
    for (auto it = aList_Undirected.begin(); it != aList_Undirected.end(); ++it) {
        visited[it->first] = false;
    }

    // BFS
    if (!aList_Undirected.empty()) {
        string start = aList_Undirected.begin()->first;
        BFS(aList_Undirected, start, visited);
    }

    
    for (auto it = visited.begin(); it != visited.end(); ++it) {
        if (!it->second) {// found a false
            cout << it->first << ": is not connected" << endl;
            return false; 
            
        }
    }

    return true; // Found no false
}
    
    void ConnectionHelper(const string& src, const string& dst, unordered_map<string, vector<string>>& aList, vector<string>& results, int& count ){
        queue<string> q;
        unordered_map<string, bool> visited;
        unordered_map<string, string> Airports;

        for (auto it = aList.begin(); it != aList.end(); ++it) {
            visited[it->first] = false;
        }
        q.push(src);
        visited[src] = true;


        while (!q.empty()) {
            string current = q.front();
            q.pop();
            
            if (current == dst) {
            for (string at = dst; !at.empty(); at = Airports[at]) {
                count++;
                results.push_back(at);
            }
            reverse(results.begin(), results.end());
            return;
        }
            
            const vector<string>& adj = aList[current];
            
            for (int j = 0; j < adj.size(); ++j) {
                string neighbor = adj[j];
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                    Airports[neighbor] = current;
                }
            }
        }
        results.clear();
        return;
        
    }
    void Connection(const string& src, const string& dst){
    
    vector<string> results;
    int count = 0;
    
    auto it = aList.find(src);
    auto it2 = aList.find(dst);
    
    if(it != aList.end()&&it2 != aList.end()){
        ConnectionHelper(src,dst,aList, results, count);
        
        if(results.size() != 0){
            cout<<count-2<<" ";
            for(int i=0; i< results.size(); i++){
                cout<< results[i]<<", ";
            }
            cout<<endl;
        }
        else{
            cout<<"Path does not exist";
        }
    }
    else{
        cout<<"Airport does not exist"<<endl;
    }
    }
    

    
private:
    unordered_map<string, vector<string>> aList;
    
    void BFS(unordered_map<string, vector<string>>& aList, const string& start, unordered_map<string, bool>& visited) {
        queue<string> q;
        q.push(start);

        for (auto i = aList.begin(); i != aList.end(); ++i) {
            visited[i->first] = false;
        }
        
        visited[start] = true;
        
        while (!q.empty()) {
	    string v = q.front();
    	q.pop();
    	
 	    vector<string> adj_vertices = aList[v]; // Get all its adjacent vertices
 	    
   	    for (int i = 0;i<adj_vertices.size(); i++) {
   	        string current = adj_vertices[i];
   	        
   	        if (!visited[current]){
   	            visited[current] = true; // marked visited
   	            q.push(current);//push visited
             }
	} 
    } 

}


};


int main(){
    Graph Flights;
    /* */
    ifstream data;
    
    data.open("data.txt");
    if(!data.is_open()){
        cout << "Unable to open file" << endl;
        return 0;
    }
    

    string src;
    string dst;
    string directflight;
    
    string dummy;
    string wholeLine;
    
    while(getline(data, wholeLine)){
        stringstream ss(wholeLine);
        
        getline(ss, dummy, ',');
        getline(ss, dummy, ',');
        getline(ss, src, ',');
        getline(ss, dummy, ',');
        getline(ss, dst, ',');
        getline(ss, dummy, ',');
        getline(ss, dummy, ',');
        getline(ss, directflight, ',');
        getline(ss, dummy, ',');
        
        if(directflight == "0"){
            Flights.addEdge(src , dst);
        }
    }
    
    data.close();
   
    Flights.print("CLT");
    //Flights.print("LHR");
    //Flights.print("ABX");
    
    if(Flights.isWeaklyConnected()){
        cout<<"The Graph is Weakly Connected"<<endl;
    }else{
        cout<<"The Graph is NOT Weakly Connected"<<endl;
    }
    
    Flights.Connection("GFF", "ABX");
    
    string userSrc;
    string userDst;

    cout << "Source airport: ";
    cin >> userSrc;
    string userSrcUpper = toUpper(userSrc);

    cout << "Destination airport: ";
    cin >> userDst;
    string userDstUpper = toUpper(userDst);

    
    Flights.Connection(userSrcUpper, userDstUpper);
    
    /*
    Graph g;
    
    // Adding edges for a weakly connected graph
    g.addEdge("A", "B");
    g.addEdge("B", "C");
    g.addEdge("C", "A");
    g.addEdge("C", "D");
    g.addEdge("D", "E");
    
    // Checking if the graph is weakly connected
    if (g.isWeaklyConnected()) {
        cout << "The graph is weakly connected" << endl;
    } else {
        cout << "The graph is not weakly connected" << endl;
    }
    
    
    Graph h;
    
    // Adding edges for a not weakly connected graph
    h.addEdge("A", "B");
    h.addEdge("B", "C");
    h.addEdge("C", "A");
    h.addEdge("D", "E");
    
    // Checking if the graph is weakly connected
    if (h.isWeaklyConnected()) {
        cout << "The graph is weakly connected" << endl;
    } else {
        cout << "The graph is not weakly connected" << endl;
    }
    */
    
    
    
    return 0;
}