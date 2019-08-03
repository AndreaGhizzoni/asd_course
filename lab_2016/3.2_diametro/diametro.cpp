#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

//#define DEBUG 1

struct nodo{
    vector<int> near;
    bool visited;
    int erdos;
    int index;
};


/**
 * Read the graph form input file and fill the references argument with data.
 */
void get_graph( vector<nodo> &graph, int &n_nodes, int &n_edges, int &start_node ){
    ifstream in("input.txt");
    in >> n_nodes >> n_edges;
    graph.resize( n_nodes );
    for( int i=0; i<graph.size(); i++ ) graph[i].index = i;

    int from, to;
    for( int i=0; i<n_edges; i++ ){
        in >> from >> to;
        graph[from].visited = false;
        graph[from].erdos = -1;
        graph[from].near.push_back(to);
        graph[to].visited = false;
        graph[to].erdos = -1;
        graph[to].near.push_back(from);
    }
}


/**
 * This function calculate the Erdos distance-vector for given graph from given
 * starting node.
 */
void erdos( vector<nodo> &graph, int n_nodes, int start_node, 
        vector<int> &padri){

    padri.resize( n_nodes );

    graph[start_node].erdos = 0;
    padri[start_node] = -1;
    queue<nodo> q;
    q.push( graph[start_node] );

    while( !q.empty() ){
        nodo current = q.front();
        q.pop();

        //current_erdos++;        
        for( int v=0; v<current.near.size(); v++ ){
            int near = current.near[v];
            if( graph[near].erdos == -1 ){
                graph[near].erdos = current.erdos+1;
                padri[near] = current.index;
                q.push( graph[near] );
            }
        }
    }
}


/**
 * Utility method to get max erdos attribute from graph
 */
int extract_max_erdos( vector<nodo> &v ){
    int curr_max = v[0].erdos;
    for( int i=1; i<v.size(); i++ ){
        if( v[i].erdos > curr_max )
            curr_max = v[i].erdos;
    }
    return curr_max;
}


/**
 * Print the given graph
 */
void print_graph( vector<nodo> &graph, int n_nodes ){
    for( int i=0; i<n_nodes; i++ ){
        cout << "Nodo " << i << " ha " << graph[i].near.size() << " vicini \n";
        for(int v=0; v<graph[i].near.size(); v++)
            cout << "  " << graph[i].near[v] << "\n";
    }
}

void print_vector( vector<int> &vec ){
    for( int i=0; i<vec.size(); i++ ){
        cout << vec[i] << " ";
    }
    cout << endl;
}


int main( int argc, char** argv ){
    vector<nodo> graph;
    int n_nodes, n_edges, start_node;
    vector<int> padri;
    get_graph( graph, n_nodes, n_edges, start_node );

    //print_graph( graph, n_nodes );

    erdos( graph, n_nodes, 0, padri );

    //print_vector( padri );

    ofstream out("output.txt");
    out << extract_max_erdos( graph );
    return 0;
}
