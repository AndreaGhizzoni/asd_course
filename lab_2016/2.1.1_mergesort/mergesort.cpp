using namespace std;

#include <iostream>
#include <fstream>

void merge(int* v, int first, int last, int mid){
    int i, j, k;
    int ord[last+1];

    i = first;
    j = mid+1;
    k = first;

    while( i<=mid && j<=last ){
        if( v[i]<=v[j] )
            ord[k++] = v[i++];
        else
            ord[k++] = v[j++];
    }
    
    j = last;
    for(int h=mid; h>=i; h--)
        v[j--] = v[h];
    
    for(j=first; j<=k-1; j++)
        v[j] = ord[j];
}

void merge_sort(int* v, int first, int last){
    if(first < last){
        int mid = (first+last)/2;
        merge_sort(v, first, mid);
        merge_sort(v, mid+1, last);
        merge(v, first, last, mid);
    }
}

int main(int argc, char** argv){
    ifstream in("input.txt");
    int n;

    in >> n;
    int v[n];
    for(int i=0; i<n; i++)
        in >> v[i];

    merge_sort(v, 0, n-1);
   
    ofstream out("output.txt");
    for(int i=0; i<n; i++)
        out << v[i] << " ";

    return 0;
}

