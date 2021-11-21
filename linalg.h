#ifndef LINALG_H
#define LINALG_H
#include <iostream>
#include <ctime>
#include <cmath>
#include <conio.h>
#include "exception"
#include "iostream"
#include "iomanip"
#include "cstring"
#include "cassert"
#include "vector"
using namespace std;



template <typename T> void FreeMem(T **matr, int n);
template <typename T> void PrintMtx(T **matr, int n);
template <typename T> void SetMtx(T **matr, int n);
template <typename T> void TransponMtx(T **matr, T **tMatr, int n);
void Get_matr(int **matr, int n, int **temp_matr, int indRow, int indCol);
int Det(int **matr, int n);

enum wVecType{
    wvtRow,
    wvtCol
};

class wMatrix
{
protected:
//    double ** data;

    vector<vector<double>> data;
    int _rows;
    int _columns;

public:
    wMatrix(int rows, int columns);
    wMatrix(vector<vector<double>> matr);
    wMatrix(const wMatrix &wMatrix);
    ~wMatrix();

    int    rowLen() const;
    int    colLen() const;
    void   addRow() const;
    void   addCol() const;
    void   appendRow() const;
    void   appendCol() const;

    void   print();
    string toStr(string sep = "\t") const;
    void   copyElementsInRow(const wMatrix &wMatrix, int i);
    void   copywMatrix(const wMatrix &wMatrix);
    void   setIt(int row, int columns, double value);
    void   setRow(int rNum, vector<double> row);
    void   setCol(int cNum, vector<double> col);
    double it(int row, int columns) const;

    vector<double> row(int indx);
    vector<double> col(int indx);
//    vector<vector<double>>& matr(){return data;}
    const vector<vector<double>>& matr() const{return data;} // для константных объектов

    void   fillZeros();

    wMatrix T();

public:

    double& operator()(int row, int col);
    const double& operator()(int row, int col) const; // для константных объектов

    wMatrix &operator=(const wMatrix &wMatrix);

    wMatrix operator+(const wMatrix &);
    wMatrix operator-(const wMatrix &);
//    wMatrix operator*(const wMatrix &);
    wMatrix operator*(const double &);

    friend wMatrix operator*(const wMatrix &Matr1, const wMatrix &Matr2);

    friend istream & operator>>(istream &, wMatrix &);
    friend ostream & operator<<(ostream &, const wMatrix &);
};

inline double &wMatrix::operator()(int row, int col)
{
    assert(col >= 0 && col < _columns);
    assert(row >= 0 && row < _rows);

    return data[row][col];
}
inline const double &wMatrix::operator()(int row, int col) const
{
    assert(col >= 0 && col < _columns);
    assert(row >= 0 && row < _rows);

    return data[row][col];
}


wMatrix operator+(const wMatrix &firstwMatrix, const wMatrix &secondwMatrix);

class wVector : public wMatrix
{
public:

    wVector(int size, wVecType type = wvtRow) :
        wMatrix(((type == wvtRow)?size:1),
                ((type == wvtCol)?size:1)),
        vType(type){}

    wVector(vector<double> vec, wVecType type = wvtRow) :
        wMatrix(((type == wvtCol)?vec.size():1),
                ((type == wvtRow)?vec.size():1)
                ),
        vType(type){
        switch (type) {
        case wvtRow:{
            for (int rIndx = 0; rIndx < vec.size(); ++rIndx) {
                data[0][rIndx] = vec[rIndx];
            }
        }break;
        case wvtCol:{
            for (int cIndx = 0; cIndx < vec.size(); ++cIndx) {
                data[cIndx][0] = vec[cIndx];
            }
        }break;

        }
    }

    friend wMatrix operator*(const wMatrix &Matr, const wVector &Vec);
    friend wMatrix operator*(const wVector &Vec , const wMatrix &Matr);
    friend wMatrix operator*(const wVector &Vec1, const wVector &Vec2);

    wVecType vType;
};





#endif // LINALG_H
