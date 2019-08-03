using namespace std;

#include <iostream>
#include <fstream>

void swap(int* v, int i, int j){
    int tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}

int perno(int* v, int first, int last){
    int x = v[first];
    int j = first;
    for( int i=first; i<=last; i++ ){
        if( v[i]<x ){
            j++;
            swap(v, i, j);
        }
    }
    v[first] = v[j];
    v[j] = x;
    return j;
}

void quicksort(int* v, int first, int last){
    if( first < last ){
        int j = perno(v, first, last);
        quicksort(v, first, j-1);
        quicksort(v, j+1, last);
    }
}

int main(int argc, char** argv){
    ifstream in("input.txt");

    int n;
    in >> n;
    int v[n];
    for( int i=0; i<n; i++ )
        in >> v[i];

    quicksort(v, 0, n-1);

    ofstream out("output.txt");
    for( int i=0; i<n; i++ )
        out << v[i] << " ";

    return 0;
}


