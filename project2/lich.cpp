#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

struct nodo{
    vector<int> vicini;
    vector<int> pesi;
    // i cavaglieri che risiedono in questo nodo attaccheranno la citta'
    // indicizzata da: attacking_edge.first in attacking_edge.second giorni
    pair<int, int> attacking_edge;
};

vector<int> L;
vector<nodo> algoritmia;
//vector<int> periferia_algoritmia;


pair<int,int> dfs_max_path( int previous_node, int current ){
    // previuos_node == -1 means that this function is called for the first time
    if( algoritmia[current].vicini.size() == 1 &&
            previous_node != -1 ){
        return make_pair(current, 0);
    }

    vector< pair<int,int> > max_depth;
    for( int i=0; i<algoritmia[current].vicini.size(); i++){
        if( algoritmia[current].vicini[i] != previous_node ){
            pair<int,int> attacking_from_i = dfs_max_path( 
                    current,
                    algoritmia[current].vicini[i]
            );
            attacking_from_i.second += algoritmia[current].pesi[i];
            max_depth.push_back( attacking_from_i );
        }
    }
    
    int index_of_max = 0;
    for( int i=1; i<max_depth.size(); i++ ){
        if( max_depth[i].second > max_depth[index_of_max].second ){
            index_of_max = i;
        }
    }
    return max_depth[index_of_max];
}


int max_distance_in_algoritmia = -1;

void parse_input(){
    ifstream in("input.txt");

    int number_of_cities;
    in >> number_of_cities;
    algoritmia.resize( number_of_cities );
    int from, to, weight;
    for( int i=0; i<number_of_cities-1; i++){
        in >> from >> to >> weight;
        algoritmia[from].vicini.push_back(to);
        algoritmia[from].pesi.push_back(weight);
        algoritmia[to].vicini.push_back(from);
        algoritmia[to].pesi.push_back(weight);
    }
    for( int i=0; i<algoritmia.size(); i++){
        pair<int,int> attack = dfs_max_path(-1, i);
        algoritmia[i].attacking_edge = attack;
        if( attack.second > max_distance_in_algoritmia )
            max_distance_in_algoritmia = attack.second;

    }

    /*
    for( int i=0; i<algoritmia.size(); i++){
        if( algoritmia[i].vicini.size() == 1){
            periferia_algoritmia.push_back( i );
        }
    }
    */

    int number_of_L;
    in >> number_of_L;
    L.resize( number_of_L );
    for( int i=0; i<L.size(); i++ ){
        in >> L[i];
    }
}


void print_data(){
    cout << "=== Input data:" << endl;
    cout << "Algoritmia:" << endl;
    for( int i=0; i<algoritmia.size(); i++ ){
        cout << "> Nodo " << i 
             << " ha "  << algoritmia[i].vicini.size()
             << " vicini" << endl;
        for( int j=0; j<algoritmia[i].vicini.size(); j++ ){
            cout << " " << algoritmia[i].vicini[j]
                 << " " << algoritmia[i].pesi[j] << endl;

        }
        cout << "Le Truppe attaccheranno la citta' "
             << algoritmia[i].attacking_edge.first << " in "
             << algoritmia[i].attacking_edge.second << " giorni" 
             << endl << endl;
    }
    /*
    cout << "Nodi Periferici: ";
    for( int i=0; i<periferia_algoritmia.size(); i++){
        cout << periferia_algoritmia[i] << " ";
    }
    cout << endl;
    */

    cout << endl << "L :";
    for( int i=0; i<L.size(); i++)
        cout << L[i] << " ";
    cout << endl << "===" << endl;
}


int m;
int M;
int diff_max;
vector<int> v;

void compute( int prev_n, int cur_n, int &l ){

    for( int i=0; i<algoritmia[cur_n].vicini.size(); i++ ){
        int index_near = algoritmia[cur_n].vicini[i];
        if( index_near != prev_n ){
            int local_min = m;
            int local_max = M;
            int local_diff_max = diff_max;

            int near_distance = algoritmia[index_near].attacking_edge.second;
            if( near_distance < local_min )
                local_min = near_distance;
            else if( near_distance > local_max )
                local_max = near_distance;
            else{
                //cout << "near_d "<< near_distance << endl;
                v.push_back( near_distance );
                compute( cur_n, index_near, l);
                continue;
            }
            
            local_diff_max = local_max - local_min;

            if( local_diff_max <= l ){
                m = local_min;
                M = local_max;
                diff_max = local_diff_max;
                v.push_back( near_distance );
                compute( cur_n, index_near, l);
            }
        }
    }
}


int main( int argc, char** argv ){
    parse_input();
    print_data();

    vector<int> s;
    s.resize( L.size() );
    for( int l=L.size()-1; l>=0; l--){
    
    //int l=1; int i=4;
        if( L[l] >= max_distance_in_algoritmia )
            s[l] = algoritmia.size();
        else {
            int max_from_v = -1;
            for( int i=0; i<algoritmia.size(); i++ ){
                int curr_days = algoritmia[i].attacking_edge.second;
                v.push_back( curr_days );
                m = curr_days;
                M = curr_days;
                diff_max = curr_days-curr_days;
                compute( -1, i, L[l] );

                int v_size = v.size();
                /*
                if( i == 4 && L[l] == 3 ){
                    cout << "m " << m << endl;
                    cout << "M " << M << endl;
                    cout << "d " << diff_max << endl;
                    for( int i=0; i<v_size; i++ ) 
                        cout << v[i] << " ";
                    cout << endl;
                }
                */

                if( v_size > max_from_v )
                    max_from_v = v_size;

                v.clear();
            }

            s[l] = max_from_v;
        }
    }

    ofstream out("output.txt");
    for( int i=0; i<s.size(); i++ ) out << s[i] << endl;

    return 0;
}
