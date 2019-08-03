using namespace std;

#include <iostream>
#include <fstream>
#include <algorithm>
#include <utility>
#include <vector>

void print_pair( pair< int, int > p ){
    cout << "(" << p.first << ", " << p.second << ") ";
}

void print_array(vector< pair< int,int > > v){
    for(int i=0; i<v.size(); i++)
        print_pair(v[i]);
    cout << endl;
}

pair< int,int > max( pair< int,int > p1, pair< int, int > p2 ){
    int d1 = p1.second - p1.first;
    int d2 = p2.second - p2.first;
    if(d1>d2)
        return p1;
    else if(d2>d1)
        return p2;

    if(p1.first < p2.first)
        return p1;
    else
        return p2;
}

/**
 * Precondition: v must be ordered by finish time.
 * This method find the maximum gap between each pari in the vector
 */
pair< int, int > find_range(vector< pair< int, int > > v){
    pair< int, int > m = make_pair(0,0);
    int k;

    // this for compares the i-th interval with the k-th next to it.
    for(int i=0; i<v.size()-1;){ // i : index of first interval
        k=i+1; // k : index next to i

        // this wile skip all the interval that ends before the interval i-th.
        while(k<v.size() && v[i].second >= v[k++].second);
        k--; // because k++ is executed one time more than necessary
        

        // at this point i points to an interval that v[i].second < v[k].second
        // than check if there is a gap between the i-th interval and the k-th:
        // if is true, calculate the interval and compare with the current max
        // gap found.
        if(v[i].second < v[k].first ){
             pair< int,int > tmp;
             tmp.first = v[i].second;
             tmp.second = v[k].first;
             m = max( m, tmp );            
        }
        // skip all interval between i and k because the while has already
        // skipped it
        i=k;
    }
    return m;
}

int main(int argc, char** argv){
    ifstream in("input.txt");
    int n;
    vector< pair<int,int> > arr;

    in >> n;
    int f,s;
    for(int i=0; i<n; i++){
        in >> f;
        in >> s;
        arr.push_back( make_pair(f,s) );
    }
        
    //print_array(arr);
    sort(arr.begin(), arr.end());
    //print_array(arr);        

    pair<int, int> r = find_range(arr);
    //print_pair(r); 
    
    ofstream out("output.txt");
    if(r.first==0&&r.second==0)
        out << 0;
    else
        out << r.first << " " << r.second << endl;
    return 0;
}

