using namespace std;

#include <fstream>

int main(int argc, char** argv){
    int n;
    ifstream in("input.txt");
    in >> n;

    int array[n];
    for( int i=0; i<n; i++ ){
        in >> array[i];
    }

    int maxx = 0; // massimo trovato
    int here = 0; // massimo valore che terminano nella posizione attuale
    for( int i=0; i<n; i++ ){
       here = max(here+array[i], 0);
       maxx = max(here, maxx);
    }

    ofstream out("output.txt");
    out << maxx << endl;

    return 0;
}


