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
void get_graph( vector<nodo> &graph, int &n_nodes, int &n_edges, 
        int &start_node, int &end_node ){

    ifstream in("input.txt");
    in >> n_nodes >> n_edges >> start_node >> end_node;
    graph.resize( n_nodes );
    int from, to;
    for( int i=0; i<n_edges; i++ ){
        in >> from >> to;
        graph[from].near.push_back(to);
    }
}

int main( int argc, char** argv ){
    vector<nodo> graph;
    int n_nodes, n_edges, start_node, end_node;
    get_graph( graph, n_nodes, n_edges, start_node, end_node );

    print_graph( graph, n_nodes );

    return 0;
}
