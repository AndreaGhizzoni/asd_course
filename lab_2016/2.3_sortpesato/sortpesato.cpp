using namespace std;

#include <iostream>
#include <fstream>
#include <utility>

#define DEBUG 0

int index_of(int* v, int n, int el){
    int index = 0;
    bool found = false;

    while( !found && index<n ){
        if(v[index++]==el)
            found = true;
    }
    
    // index-1 because (index++) is executed when the element is found too.
    return( found? index-1 : -1 );
} 

void swap(int* v, int n, int i, int j ){
    int tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}

void print_array( int* v, int n ){
    for(int i=0; i<n; i++)
        cout << v[i] << " ";
    cout << endl;
}

/**
 * Precondition: each elements of v must be in range 1<= x < n
 * 
 * This algorithm returns a pair of integer <S, P> where S is the minimum swaps
 * to get the vector ordered and P is the minimum cost to order v; where cost 
 * is the sum of elements to swap each time.
 */
pair<int, int> sort(int*v, int n){
    int tot_op=0;
    int tot_cost=0;
    int n_op=0;
    int l_cost=0;

    int k = 1; // k is the value that goes from 1 to n
    int p = index_of(v,n,k);    
    while(k<n){
        // check if p is in place, because the ordered vector mus be:
        // v[0]=1, v[1]=2 ecc..
        if(v[p]-1 == p){ 
            tot_cost += l_cost + min(n_op*(p+1), n_op+2*(p+2));
            tot_op += n_op;

            l_cost = 0;
            n_op=0;
            p = index_of(v, n, ++k);
        }else{
            // search the element next to p to swap with.
            int to_swap = index_of(v, n, p+1 );
            swap( v, n, p, to_swap );

            n_op++;
            l_cost += v[p];
            p = to_swap;
            
            if(DEBUG){
                print_array(v,n);
                cout << l_cost << endl;
            }
        }
     }  

     return make_pair(tot_op, tot_cost);
}

int main(int argc, char** argv){
    ifstream in("input.txt");
    int n;
    in >> n;
    
    int* arr = new int[n];
    for(int i=0; i<n; i++)
        in >> arr[i];
    if(DEBUG) print_array(arr,n);
    
    pair<int, int> p = sort(arr,n);

    ofstream out("output.txt");
    out << p.first << " " << p.second;
    
    return 0;
}
