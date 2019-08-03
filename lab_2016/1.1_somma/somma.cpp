using namespace std;

#include <fstream>

int main(int argc, char** argv){
    int a, b;
    ifstream in("input.txt");
    in >> a >> b;
    ofstream out("output.txt");
    out << a+b << endl;
    return 0;
}


