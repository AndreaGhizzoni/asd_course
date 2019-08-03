#include <fstream>
#include <iostream>

using namespace std;

const int max_size = 2000;

typedef struct {
    int matrix[max_size][max_size];
    int rows;
    int cols;
} obj_matrix;

int max_partial_sum(obj_matrix* m, int first_col, int last_col){
    int msum = 0, curr = 0;
    for(int i=0; i< m->rows; i++){
        for(int j=first_col; j<=last_col; j++){
            curr += m->matrix[i][j];
        }
        curr = max(curr, 0);
        msum = max(msum, curr);
    }
    return msum;
}

int max_sum(obj_matrix* m){
	int msum = 0;
 	for(int i=0; i< m->cols; i++){
    	for(int j=i; j< m->cols; j++){
        	msum = max(msum, max_partial_sum(m, i, j));
	    }
	}
	return msum;
}

obj_matrix* read_matrix(){
    ifstream in("input.txt");
    obj_matrix* m = new obj_matrix();
    in >> m->rows;
    in >> m->cols;

    for(int i=0; i< m->rows; i++){
		for(int j=0; j< m->cols; j++ ){
			in >> m->matrix[i][j];
		}
	}

    return m;
}

int main(int argc, char** argv){
	obj_matrix* m = read_matrix();

    ofstream out("output.txt");
	out << max_sum(m) << endl;
	return 0;
}

