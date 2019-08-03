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
void print_graph( vector<nodo> &graph ){
    for( int u=0; u<graph.size(); u++ ){
        cout << "Nodo " << u << " ha " << graph[u].near.size() << " vicini\n";
        for(int v=0; v<graph[u].near.size(); v++)
            cout << "  " << graph[u].near[v] << "\n";
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


int main( int argc, char** argv ){
    vector<nodo> graph;
    int n_nodes, n_edges, start_node;
    get_graph( graph, n_nodes, n_edges, start_node );

    print_graph( graph );

    return 0;
}
