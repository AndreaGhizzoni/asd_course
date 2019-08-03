#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <utility>

using namespace std;

struct nodo{
    vector<int> near;
    bool visited;
};


struct T{
    list<int> childs;
    bool visited;
    int level;
};


struct arco_pokemon{
    pair<int, int> arco;
    int pokemon;
};


list<int> loop_lengths;
list<arco_pokemon> disposizioni_pokemon;



void print_disposizioni_pokemon(){
    list<arco_pokemon>::iterator it = disposizioni_pokemon.begin();
    for( ; it!=disposizioni_pokemon.end(); ++it ){
        cout << "( " << (*it).arco.first << ", " << (*it).arco.second << " ) : "
             << (*it).pokemon << endl;
    }
}



void add_to_loop( list<int> &l ){
    if( !l.empty() ){
        list<int>::iterator it;
        for( it=l.begin(); it!=l.end(); ++it ){
            loop_lengths.push_back( *it );
        }
    }
}


/**
 * Print the given graph
 */
void print_graph( vector<nodo> &graph ){
    for( int u=0; u<graph.size(); u++ ){
        cout << "Nodo " << u  << " ["
             << "v = " << graph[u].visited
             << "] ha " << graph[u].near.size() << " vicini\n";
        for(int v=0; v<graph[u].near.size(); v++)
            cout << "  " << graph[u].near[v] << "\n";
    }
}


void print_dfs_tree( vector<T> &dfs_tree ){
    for( int u=0; u<dfs_tree.size(); u++ ){
        cout << "Nodo " << u  << " ["
             << "l = "<< dfs_tree[u].level << " " 
             << "] ha " << dfs_tree[u].childs.size() << " vicini\n";
        list<int> childs = dfs_tree[u].childs;
        for( list<int>::iterator it=childs.begin(); it!=childs.end(); ++it ){
            cout << "  " << (*it) << "\n";
        }
    }
}


/**
 * Read the graph form input file and fill the references argument with data.
 */
void get_graph( vector<nodo> &graph, 
                 int &n_nodes, 
                 int &n_edges, 
                 int &start_node ){

    ifstream in("input.txt");
    in >> n_nodes >> n_edges;
    graph.resize( n_nodes );
    int from, to;
    for( int i=0; i<n_edges; i++ ){
        in >> from >> to;
        graph[from].visited = false;
        graph[from].near.push_back(to);
        graph[to].visited = false;
        graph[to].near.push_back(from);
    }
}


void init_dfs_tree( vector<nodo> &graph, vector<T> &dfs_tree ){
    dfs_tree.resize( graph.size() );
}


int get_k( vector<int> &v ){
    int k=-1;
    bool div=1;
    //trovo valore minimo
    int min =v[0];
    for (int i=1;i<v.size();i++){
        if (min>v[i]) min=v[i];
    }
    
    for (int i=1;i<=min;i++){ //scorro i divisori del min
        bool div=1;
        if((min%i) == 0 ){
            k=min/i;
            int j=0;
            while(div && j<v.size()){
                if(v[j]%k !=0) div = 0;
                j++;
            } 
            if(div){
                break;
                return k;
            }
        }
        
    }
    return k;
}


bool find( list<int> &list, int to_search ){
    if( list.empty() ) return false;
    for( std::list<int>::iterator it=list.begin(); it!=list.end(); ++it ){
        if( (*it) == to_search ) return true;
    }
    return false;
}


void populate_dfs_tree( vector<nodo> &graph, vector<T> &dfs_tree, 
                  int current_node,
                  int previous_node,
                  list<int> &possible_node_start_cicle){

    graph[current_node].visited = true;

    for( int i=0; i<graph[current_node].near.size(); i++ ){
        int index_near = graph[current_node].near[i];

        if( index_near == previous_node ) continue;
        //if( graph[index_near].near.size() < 2 ) continue;

        if( !graph[index_near].visited ){

            if( graph[index_near].near.size() >= 3 )
                possible_node_start_cicle.push_back( index_near );

            dfs_tree[current_node].childs.push_back( index_near );
            populate_dfs_tree( graph, 
                               dfs_tree, 
                               index_near, 
                               current_node, 
                               possible_node_start_cicle );

        }else if( find( possible_node_start_cicle, index_near ) ){
            dfs_tree[current_node].childs.push_back( index_near );
        }
    }

    if( find( possible_node_start_cicle, current_node ) ){
        possible_node_start_cicle.remove( current_node );
    }
}


void count_cicle_in_dfs_tree( vector<T> &dfs_tree,
                             int current_tree_node,
                             int current_level){

    dfs_tree[current_tree_node].visited = true;
    dfs_tree[current_tree_node].level = current_level;

    list<int> childs = dfs_tree[current_tree_node].childs;
    for( list<int>::iterator it=childs.begin(); it!=childs.end(); ++it ){
        int k = current_level;
        int index_child = (*it);

        if( !dfs_tree[index_child].visited ){
            count_cicle_in_dfs_tree( dfs_tree, 
                                     index_child,
                                     ++k );
        }else{
            int level_child = dfs_tree[index_child].level;
            loop_lengths.push_back( (current_level - level_child)+1 );
        }
    }
}


/**
 * questa funzione utilizza i false come true e i true come false.
 */
void qualcosa( vector<T> &dfs_tree, 
               int current_tree_node, 
               int k){

    dfs_tree[current_tree_node].visited = false;

    list<int> childs = dfs_tree[current_tree_node].childs;
    for( list<int>::iterator it=childs.begin(); it!=childs.end(); ++it ){
        int index_child = (*it);
        arco_pokemon tmp;

        if( dfs_tree[current_tree_node].level > k-1 ){
            tmp.arco = make_pair( index_child, current_tree_node );
            tmp.pokemon = dfs_tree[current_tree_node].level - k;
        }else{
            if( dfs_tree[current_tree_node].level == k-1 ){
                tmp.arco = make_pair( index_child, current_tree_node );
            }else
                tmp.arco = make_pair( current_tree_node, index_child );

            tmp.pokemon = dfs_tree[current_tree_node].level;
        }

        disposizioni_pokemon.push_back( tmp );

        if( dfs_tree[index_child].visited ){
            qualcosa( dfs_tree, index_child, k );
        }
    }
}


bool compare( const arco_pokemon &f, const arco_pokemon &s ){
    return f.arco.first < s.arco.first || ( f.arco.first == s.arco.first
           &&  f.arco.second < s.arco.second );
}


int main( int argc, char** argv ){
    vector<nodo> graph;
    int n_nodes, n_edges, start_node;
    get_graph( graph, n_nodes, n_edges, start_node );
    vector<T> dfs_tree;
    init_dfs_tree( graph, dfs_tree );
    
    //cout << "GRAPH:" << endl;
    //print_graph( graph );
    
    for( int i=0; i<graph.size(); i++ ){
        if( !graph[i].visited ){
            list<int> possible_node_start_cicle;
            possible_node_start_cicle.push_back( i );
            populate_dfs_tree( graph, dfs_tree, i, i, possible_node_start_cicle );
        }
    }

    for( int i=0; i<dfs_tree.size(); i++ ){
        if( !dfs_tree[i].visited ){
            count_cicle_in_dfs_tree( dfs_tree, i, 0 );
        }
    }

    //cout << "DFS TREE:" << endl;
    //print_dfs_tree( dfs_tree );

    vector<int> v;
    v.resize( loop_lengths.size() );
    list<int>::iterator it; int i=0;
    cout << "loop: ";
    for (it=loop_lengths.begin(); it!=loop_lengths.end(); ++it){
        cout << *it << " ";
        v[i++] = *it;
    }
    cout << endl;

    int K = get_k( v );

    for( int i=0; i<dfs_tree.size(); i++ ){
        if( dfs_tree[i].visited ){ // questo e' giusto cosi
            qualcosa( dfs_tree, i, K );
        }
    }

    disposizioni_pokemon.sort(compare);
    print_disposizioni_pokemon();

    ofstream out("output.txt");
    out << K << endl;
    /*
    list<arco_pokemon>::iterator e = disposizioni_pokemon.begin();
    for( ; e!=disposizioni_pokemon.end(); ++e ){
        out << (*e).pokemon << endl;
    }
    */

    return 0;
}
