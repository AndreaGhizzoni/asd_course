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


/**
 * TODO add description
 */
int max_from( vector<int> &vector ){
    if( vector.size() == 0 ) return 0;
    int l_max = vector[0];
    for( int i=0; i<vector.size(); i++ ){
        if( vector[i] > l_max ) l_max = vector[i];
    }
    return l_max;
}


/**
 * TODO add description
 */
int my_dfs( vector<nodo> &graph, int start ){
    vector<int> deep_from_neer;
    deep_from_neer.resize( graph[start].near.size() );

    for( int u=0; u<graph[start].near.size(); u++ ){
        int index_near = graph[start].near[u];
        deep_from_neer[u] = 1 + my_dfs( graph, index_near );
    }

    return max_from( deep_from_neer );
}


int main( int argc, char** argv ){
    vector<nodo> graph;
    int n_nodes, n_edges, start_node;
    get_graph( graph, n_nodes, n_edges, start_node );

    print_graph( graph );

    vector<int> max_distance_from;
    max_distance_from.resize( graph.size() );
    for( int i=0; i<graph.size(); i++ ){
        max_distance_from[i] = my_dfs( graph, i );
    }

    cout << endl << 
        "Vector of distance v[i] = n: length's path form i is n"
        << endl;
    for( int i=0; i<max_distance_from.size(); i++ )
        cout << "v[" << i << "] = " << max_distance_from[i] << " " << endl;

    cout << endl << max_from( max_distance_from ) << endl;
    ofstream of("output.txt");
    of << max_from( max_distance_from );
    return 0;
}
