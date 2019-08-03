using namespace std;

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

struct nodo{
  vector<int> near;
  bool visited;
};

/**
 * This function take a graph and a start node and count the nodes that it can
 * visits form the start node.
 */
int n_node( vector<nodo> graph, int start_node ){
    int count_visited_nodes = 1;
    queue<nodo> q;
    
    q.push( graph[start_node] );
    graph[start_node].visited = true;

    while( !q.empty() ){
        nodo current = q.front();
        q.pop();
        
        for( int v=0; v<current.near.size(); v++ ){
            int near = current.near[v];
            if( !graph[near].visited ){
                graph[near].visited = true;
                q.push( graph[near] );
                count_visited_nodes++;
            }
        }
    }

    return count_visited_nodes;
}


/**
 * Read the graph form input file and fill the references argument with data.
 */
void get_graph( vector<nodo> &graph, int &n_nodes, int &n_edges, int &start_node ){
    ifstream in("input.txt");
    in >> n_nodes >> n_edges >> start_node;
    graph.resize( n_nodes );
    int from, to;
    for( int i=0; i<n_edges; i++ ){
        in >> from >> to;
        graph[from].near.push_back(to);
    }
}


int main( int argc, char** argv ){
    vector<nodo> graph;
    int n_nodes, n_edges, start_node;
    get_graph( graph, n_nodes, n_edges, start_node );
    
    ofstream out("output.txt");
    out << n_node(graph, start_node);
    return 0;
}
