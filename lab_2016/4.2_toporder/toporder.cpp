#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct nodo{
    vector<int> near;
    bool visited;
};


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


/**
 * Read the graph form input file and fill the references argument with data.
 */
void get_graph( vector<nodo> &graph, int &n_nodes, int &n_edges, int &start_node ){
    ifstream in("input.txt");
    //in >> n_nodes >> n_edges >> start_node;
    in >> n_nodes >> n_edges;
    graph.resize( n_nodes );
    int from, to;
    for( int i=0; i<n_edges; i++ ){
        in >> from >> to;
        graph[from].visited = false;
        graph[from].near.push_back(to);
    }
}


/**
 * Auxiliary function that execute a DFS from node index 'start' on 'graph'
 * given. Argument given 'i' counts how many nodes goes through the DFS and
 * place the index node 'start' in the correct position into 'ts_order' vector.
 * graph   : vector<int> a directed acyclic graph
 * start   : int the index of node to start DFS.
 * i       : int current node encountered through DFS recursion.
 * ts_order: vector<int> reference to vector that will be filled up with node's
 *           id, that will represents the topological order.
 */
int ts_dfs( vector<nodo> &graph, int start, int i, vector<int> &ts_order ){
    graph[start].visited = true;
    for( int u=0; u<graph[start].near.size(); u++ ){
        int index_near = graph[start].near[u];
        if( !graph[index_near].visited ){
            i = ts_dfs( graph, index_near, i, ts_order);
        }
    }
    ts_order[ graph.size()-i ] = start;
    return i+1; 
}


/**
 * Top Sort procedure: take a graph reference and an empty vector of int that
 * will fill up with indexes, that are in topological order.
 * graph: vector<int> a directed acyclic graph
 * ts_order: vector<int> reference that will be filled up with node's id, that
 *           will represents the topological order. This reference WILL BE
 *           RESIZED to graph.size().
 */
void top_sort( vector<nodo> &graph, vector<int> &ts_order ){
    ts_order.resize( graph.size() );
    int i = 1;
    for( int u=0; u<graph.size(); u++ ){
        if( !graph[u].visited ){
            i = ts_dfs( graph, u, i, ts_order );
        }
    }
}


int main( int argc, char** argv ){
    vector<nodo> graph;
    int n_nodes, n_edges, start_node;
    get_graph( graph, n_nodes, n_edges, start_node );

    vector<int> topological_order;
    top_sort( graph, topological_order );

    ofstream out("output.txt");
    for( int i=0; i<topological_order.size(); i++ ){
        out  << topological_order[i] << " ";
    }
    return 0;
}
