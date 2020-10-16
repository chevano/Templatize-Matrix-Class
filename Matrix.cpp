// Chevano Gordon

#include <iostream>
#include <cstdlib>
#include <cassert>

using namespace std;

template <typename T> class SA;
template <typename T> ostream& operator<< (ostream& os, const SA<T>& s);

template <typename T>
class SA {
  private:
    int low, high, size;
    T* p;

  public:

 // default constructor
 // allows for writing things like SA a;

    SA() {
        low = 0; 
        high = -1;
        size = 0;
        p = NULL;
    }

 // 2 parameter constructor lets us write
 // SA x(10,20);

    SA(int l, int h){
        
        if((h-l+1) <= 0){
            cout<< "constructor error in bounds definition" << endl;
            exit(1);
        }
        
        low = l;
        high = h;
        size = h-l+1;
        p = new T[size];
    }

 // single parameter constructor lets us
 // create a SA almost like a "standard" one by writing
 // SA x(10); and getting an array x indexed from 0 to 9

    SA(int i) {
        low = 0;
        high = i-1;
        size = i;
        p = new T[size];
    }
 
 // copy constructor for pass by value and
 // initialization

    SA(const SA& s){
        size = s.high - s.low + 1;
        p = new T[size];

        for(int i = 0; i < size; i++)
            p[i] = s.p[i];
        low = s.low;
        high = s.high;
    }
 // destructor

    ~SA() {
        delete [] p;
    }
 //overloaded [] lets us write
 //SA x(10,20); x[15]= 100;

    T& operator[](int i) {
        if(i < low || i > high) {
            cout << "index "<< i <<" out of range" << endl;
            exit(1);
        }

        size = i - low;
        return p[size];
    }

 // overloaded assignment lets us assign
 // one SA to another

    SA & operator=(const SA & s){
        if(this == &s)
            return *this;

        delete [] p;
        size = s.high - s.low + 1;
        p = new T[size];

        for(int i = 0; i < size; i++)
            p[i] = s.p[i];

        low = s.low;
        high = s.high;

        return *this;
    }

    int length() {
        return size;
    }

    operator T*() { // conversion function
        return p;
    }

    friend ostream& operator<< <T>(ostream& os, const SA<T>& s);
};

// template <class T>
template <typename T>
ostream& operator<<(ostream& os, const SA<T>& s) {
    int size = s.high - s.low + 1;

    for(int i = 0; i < size; i++)
        os << s.p[i] << endl;

    return os;
};

template <typename T>
class Matrix {
  private:
    SA< SA<T> > matrix;

  public:

    Matrix(int row, int col) {
        matrix = SA< SA<T> >(0, row-1);

        for(int i = 0; i < row; i++) {
            matrix[i] = SA<T>(0, col-1);
        }
    }

    Matrix(int r1, int r2, int c1, int c2) {
        matrix = SA< SA<T> >(r1, r2-1);

        for(int i = r1; i < r2; i++)
            matrix[i] = SA<T>(c1, c2-1);
    }

    SA<T>& operator[](int r) {
        return matrix[r];
    }

    operator SA<T>*() { // conversion function
        return matrix;
    }
};

int main(){

    Matrix <int> arr(6,9);      // creates a 2D array of 6 rows from 0-5 and 9 columns from 0-8
    Matrix <int> arr1(9,2);     // creates a 2D array of 9 rows from 0-8 and 2 columns from 0-2
    Matrix <int> product(9,2);  // creates a 2D array of 9 rows from 0-8 and 

    Matrix <int> matrix1(2,2);  // creates a 2D array of 2 rows from 0-1 and 2 columns from 0-1
    Matrix <int> matrix2(2,2);
    Matrix <int> prodMatrix(2,2);

    Matrix <int> mat1(1,5,2,4); // creates a 2D array of 4 rows from 1-4 and 2 cols from 2-3
    Matrix <int> mat2(2,4,2,5); // creates a 2D array of 2 rows from 2-3 and 3 cols from 2-4
    Matrix <int> prodMat(1,5,2,5); // creates a 2D array of 4 rows from 1-4 and 3 cols from 2-4

    /********************** matrix1 x matrix2 ****************************/

    matrix1[0][0] = 1;
    matrix1[0][1] = 2;
    matrix1[1][0] = 3;
    matrix1[1][1] = 4;

    matrix2[0][0] = 1;
    matrix2[0][1] = 1;
    matrix2[1][0] = 1;
    matrix2[1][1] = 1;

    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            prodMatrix[i][j] = 0;
            for(int k = 0; k < 2; k++) {
                prodMatrix[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            cout << prodMatrix[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl << endl;

/********************** arr x arr2 ****************************/

    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 9; j++) {
            arr[i][j] = i + j;
        } 
    }

    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 2; j++) {
            arr1[i][j] = i + j;
        } 
    }

    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 2; j++) {
            product[i][j] = 0;
            for(int k = 0; k < 9; k++) {
                product[i][j] += arr[i][k] * arr1[k][j];
            }
        }
    }

    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 2; j++) {
            cout << product[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl << endl;

    /********************** mat1 x mat2 ****************************/

    for(int i = 1; i < 5; i++) {
        for(int j = 2; j < 4; j++) {
            mat1[i][j] = i + j;
        } 
    }

    for(int i = 2; i < 4; i++) {
        for(int j = 2; j < 5; j++) {
            mat2[i][j] = i + j;
        } 
    }

    for(int i = 1; i < 5; i++) {
        for(int j = 2; j < 5; j++) {
            prodMat[i][j] = 0;
            for(int k = 2; k < 4; k++) {
                prodMat[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }

    for(int i = 1; i < 5; i++) {
        for(int j = 2; j < 5; j++) {
            cout << prodMat[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
} 