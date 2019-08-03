#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

struct nodo{
    vector<int> near;
    bool visited;
    int id; // used for cc functions

    // filed used to store the index that this node has into the vector
    int vector_index; 
};


/**
 * Print the given graph
 */
void print_graph( vector<nodo> &graph, int n_nodes ){
    for( int i=0; i<n_nodes; i++ ){
        cout << "Nodo " << i << " [id: "<< graph[i].id << "] ha " 
             << graph[i].near.size() << " vicini \n";
        for( int v=0; v<graph[i].near.size(); v++ )
            cout << "  " << graph[i].near[v] << "\n";
    }
}


/**
 * Read the graph form input file and fill the references argument with data.
 */
void get_graph( vector<nodo> &graph, int &n_nodes, int &n_edges, int &start_node ){
    ifstream in("input.txt");
    in >> n_nodes >> n_edges;
    graph.resize( n_nodes );
    int from, to;
    for( int i=0; i<n_edges; i++ ){
        in >> from >> to;
        graph[from].id = 0;
        graph[from].visited = false;
        graph[from].vector_index = from;
        graph[from].near.push_back(to);
    }
}


/**
 * create a new vector of nodo that represents a transposed graph of argument 
 * given.
 */
vector<nodo> get_graph_transposed( vector<nodo> &graph ){
    vector<nodo> graph_transposed;
    graph_transposed.resize( graph.size() );
    for( int i=0; i<graph.size(); i++ ){
        graph_transposed[i].vector_index = i;
        graph_transposed[i].visited = false;
        graph_transposed[i].id = 0;
        for( int j=0; j<graph[i].near.size(); j++ ){
            // get the index of the j-th near of node i-th
            int index_near = graph[i].near[j]; 
            graph_transposed[index_near].near.push_back(i);
        }
    }
    return graph_transposed;
}


/**
 * Auxiliary functions that execute a DFS from 'current' node's index and assign
 * the 'current_component_id' argument.
 * graph                : vector<nodo> the graph of nodo structure with id 
 *                        attribute to set in this procedure
 * current_component_id : int the current id that will be assigned for each node
 *                        in DFS
 * current              : int index of node to start DFS
 */
void cc_dfs( vector<nodo> &graph, int current_component_id, int current ){
    graph[current].id = current_component_id;
    for( int i=0; i<graph[current].near.size(); i++ ){
        int index_near = graph[current].near[i];
        if( graph[index_near].id == 0 ){
            cc_dfs( graph, current_component_id, index_near );
        }
    }
}


/**
 * Connected Component: this procedure take a graph and a vector of his index
 * to fill 'id' attribute of graph with appropriate component number.
 * graph : vector<nodo> the graph of nodo structure with id attribute to set in
 *         this procedure
 * ordine: vector<int> the vector of node's index. This index represents the
 *         order that graph's node is visited.
 */
void cc( vector<nodo> &graph, vector<int> &ordine ){
    int current_component_id = 0;
    for( int i=0; i<graph.size(); i++ ){
        if( graph[ ordine[i] ].id == 0 ){ // no component set
            current_component_id++;
            cc_dfs( graph, current_component_id, ordine[i] );
        }
    }
}


/**
 * Auxiliary function that execute a DFS on graph given and from node indexed of
 * 'start' argument. Every node post-visited are pushed into 'stack_ord'.
 * graph     : vector<nodo> the graph of nodo structure with id attribute to set 
 *             in this procedure
 * stack_ord : stack<int> filled of post-visited node by DFS recursion.
 * start     : int index of node to start DFS
 */
void dfs_stack( vector<nodo> &graph, stack<int> &stack_ord, int start ){
    graph[start].visited = true;
    for( int i=0; i<graph[start].near.size(); i++ ){
        int index_near = graph[start].near[i];
        if( !graph[index_near].visited ){
            dfs_stack( graph, stack_ord, index_near );
        }
    }
    stack_ord.push( start );
}


/**
 * Strong Connected Component: this function get a graph and returns a transposed
 * graph with strong connected component calculated on 'id' attribute.
 * graph : vector<nodo> the graph of nodo structure with id attribute to set in
 *         this procedure
 * return vector<nodo> that represents a transposed graph of graph given with
 *        strong connected components calculated on 'id' attribute.
 */
vector<nodo> scc( vector<nodo> &graph ){
    stack<int> stack_ord; // order of indexed of nodes
    for( int i=0; i<graph.size(); i++ ){
        if( !graph[i].visited ) 
            dfs_stack( graph, stack_ord, i );
    }

    /*
    print_graph( graph, graph.size() );
    cout << "STACK: " << endl;
    for( stack<int> dump = stack_ord; !dump.empty(); dump.pop() )
        cout << dump.top() << " ";
    cout << endl;
    */

    vector<int> ordine; // indexes of nodes
    ordine.resize( graph.size() );
    for( int i=0; i<ordine.size(); i++ ){
        ordine[i] = stack_ord.top();
        stack_ord.pop();
    }

    /*
    cout << "ORDINE:" << endl;
    for( int i=0; i<ordine.size(); i++ ) cout << ordine[i] << " ";
    cout << endl;
    */

    vector<nodo> graph_transposed = get_graph_transposed( graph );

    cc( graph_transposed, ordine );
    return graph_transposed;
}


int main( int argc, char** argv ){
    vector<nodo> graph;
    int n_nodes, n_edges, start_node;
    get_graph( graph, n_nodes, n_edges, start_node );

    vector<nodo> graph_transposed = scc( graph );

    /*
    cout << "TRASPOSED GRAPH:" << endl;
    print_graph( graph_trasposed, graph_trasposed.size() );
    */

    // find the maximum id of scc
    int max_scc = 0;
    for( int i=0; i<graph_transposed.size(); i++ ){
        if( graph_transposed[i].id > max_scc ) max_scc = graph_transposed[i].id;
    }
    //cout << "this graph has " <<  max_scc << " scc"  << endl; 

    vector<int> count_nodes_in_scc;
    count_nodes_in_scc.resize( max_scc );
    for( int i=0; i<graph_transposed.size(); i++ ){
        count_nodes_in_scc[ graph_transposed[i].id-1 ]++;
    }
    /*
    cout << "<id of scc> : <number of nodes in that scc>" << endl;
    for( int i=0; i<count_nodes_in_scc.size(); i++ ){ 
        cout << i+1 << " : " << count_nodes_in_scc[i] << endl; 
    }
    */
    
    // find the biggest scc
    int max_number_of_nodes_in_scc = count_nodes_in_scc[0];
    for( int i=1; i<count_nodes_in_scc.size(); i++ ){
        if( count_nodes_in_scc[i] > max_number_of_nodes_in_scc ){
            max_number_of_nodes_in_scc = count_nodes_in_scc[i];
        }
    }
    //cout << "dimension of maximum scc = " << max_number_of_nodes_in_scc << endl;

    ofstream out("output.txt");
    out  << max_number_of_nodes_in_scc << endl;
    return 0;
}
