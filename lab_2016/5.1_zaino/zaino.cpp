using namespace std;

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

struct item{
    int peso;
    int valore;
    item(int p, int v){ 
        peso=p;
        valore=v; 
    }
};

const int NOT_SET = -1;


int zaino( vector<item> &items, int c, int n, vector<vector<int>> &table ){
    if( n < 0 ){
        return 0;
    }
    if( c < 0 ){
        return -10000;
    }
    if( table[c][n] == NOT_SET ){
        int peso_item_cor = items[n].peso;
        int valore_item_cor  = items[n].valore;
        table[c][n] = max( zaino(items, c, n-1, table), 
                           zaino(items, c-peso_item_cor, n-1, table)
                           + valore_item_cor );
    }

    return table[c][n];
}



void printM( vector<vector<int>> &v ){
    cout << "n:   ";
    for( int j=0; j<v[0].size(); j++ ){ 
        cout << setw(3) << j;
    }
    cout << endl;

    for( int i=0; i<v.size(); i++ ){
        cout << "c[" << setw(2) << i << "] ";
        for( int j=0; j<v[i].size(); j++ ){ cout << setw(2) << v[i][j] << " "; }
        cout << endl;
    }
}



int main( int argc, char** argv ){
    ifstream in("input.txt");
    int c, N; //c backpack capacity, N # objects
    in >> c >> N;
    cout << "[c] capacity: " << c << ", [N] objects: " << N << endl;
    vector<item> items;
    vector<vector<int>> table = vector<vector<int>>( c+1, vector<int>(N+1, NOT_SET));

    for(int i=0; i<N; i++){
        int peso, valore;
        in >> peso >> valore;
        items.push_back( item(peso,valore) );
    }

    for( int i=0; i<table.size(); i++ ){ table[i][0] = 0; }
    for( int i=0; i<table[0].size(); i++ ){ table[0][i] = 0; }

    zaino( items, c, N, table );
    printM( table );

    ofstream out("output.txt");
    out << table[c][N] << endl;

    return 0;
}

