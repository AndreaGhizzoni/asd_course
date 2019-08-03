using namespace std;

#include <iostream>
#include <fstream>

int binarysearch( int* v, int wanted, int start, int end ){
    if( start > end ){
        return 0;
    }else{
        int middle = (start+end)/2;
        if( v[middle] == wanted ){
            return middle;
        }else if( v[middle] < wanted ){
            return binarysearch(v, wanted, middle+1, end);
        }else{
            return binarysearch(v, wanted, start, middle-1);
        }
    }
}

int main(int argc, char** argv){
    ifstream in("input.txt");
    int n;
    in >> n;
    int v[n];
    int wanted;
    in >> wanted;
    for( int i=0; i<n; i++ ){
        in >> v[i];
    }

    int index_wanted = binarysearch(v, wanted, 0, n-1);
        
    ofstream out("output.txt");
    if( v[index_wanted] == wanted )
        out << "found";
    else
        out << "not found";
    out << endl;
    return 0;
}


