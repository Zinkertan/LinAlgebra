#ifndef LINALGEBRA_H
#define LINALGEBRA_H

#include <iostream>
#include <ctime>
#include <cmath>
#include <conio.h>
#include "exception"
#include "iostream"
#include "iomanip"
#include "QString"
#include "cassert"
#include "QVector"
#include "additional_func.h"

enum mMatrType{
    mmtNotMatr,
    mmtDefault,
    mmtSquare
};

class mMatrix
{
protected:
//    double ** data;

    QVVdouble data;
    int _rows;
    int _columns;
    mMatrType _type = mmtDefault;
    int _dim;

public:
    mMatrix(int rows, int columns);
    mMatrix(QVVdouble matr);
    mMatrix(const mMatrix &mMatrix);
    ~mMatrix();

    int    rowLen() const;
    int    colLen() const;
    int    dim() const;
    void   addRow() const;
    void   addCol() const;
    void   appendRow() const;
    void   appendCol() const;

    void   print();
    void   copymMatrix(const mMatrix &Matr);
    void   copyElementsInRow(const mMatrix &Matr, int i);
    QString toQStr(QString sep = "|",
                   QString format = "6 f") const;
    void   setItem(int row, int columns, double value);
    void   setRow (int rNum, QVdouble row);
    void   setCol (int cNum, QVdouble col);
    double it(int row, int columns) const;

    QVdouble row(int indx);
    QVdouble col(int indx);
//    vector<vector<double>>& matr(){return data;}
    const QVVdouble& matr() const{return data;} // для константных объектов

    void   fillZeros();

    mMatrix T(); //возвращает транспонированную матрицу
    mMatrix M(int row, int col); // Возвращает матрицу минора для элемента
    double  Minor(int row, int col); // Возвращает определитель М. минора для элемента
    mMatrix MMatr(); // Возвращает матрицу минора для элемента
    double  det();
    mMatrix adMatr();
    double  ad(int row, int col); // Алгебраическое дополнение
    mMatrix inv();

    bool isE();
    bool isSqr();

    static mMatrix solve(mMatrix A, mMatrix B);


public:

    double& operator()(int row, int col);
    const double& operator()(int row, int col) const; // для константных объектов

    mMatrix &operator=(const mMatrix &mMatrix);

    mMatrix operator+(const mMatrix &);
    mMatrix operator-(const mMatrix &);
//    mMatrix operator*(const mMatrix &);
    mMatrix operator*(const double &);
    mMatrix operator/(const double &);

    friend mMatrix operator*(const mMatrix &Matr1, const mMatrix &Matr2);
    friend mMatrix operator*(const double num, const mMatrix &Matr);

    friend bool operator== (const mMatrix &m1,
                            const mMatrix &m2){
        if(m1._type == m2._type){
            if (m1.rowLen()==m2.rowLen()&&
                    m1.colLen()==m2.colLen()) {
                for(int r = 0; r < m1.rowLen(); r++){
                    for(int c = 0; c < m1.colLen(); c++){
                        if(m1(r,c) != m2(r,c)) return false;;
                    }
                }
                return true;
            }
        }
        return false;
    }
    friend bool operator!= (const mMatrix &m1,
                            const mMatrix &m2){
        if(m1._type == m2._type){
            if (m1.rowLen()==m2.rowLen()&&
                    m1.colLen()==m2.colLen()) {
                for(int r = 0; r < m1.rowLen(); r++){
                    for(int c = 0; c < m1.colLen(); c++){
                        if(m1(r,c) != m2(r,c)) return true;;
                    }
                }
                return false;
            }
        }
        return true;
    }

    friend std::istream & operator>>(std::istream &, mMatrix &);
    friend std::ostream & operator<<(std::ostream &, const mMatrix &);
};

inline double &mMatrix::operator()(int row, int col)
{
    assert(col >= 0 && col < _columns);
    assert(row >= 0 && row < _rows);

    return data[row][col];
}
inline const double &mMatrix::operator()(int row, int col) const
{
    assert(col >= 0 && col < _columns);
    assert(row >= 0 && row < _rows);

    return data[row][col];
}


mMatrix operator+(const mMatrix &firstmMatrix, const mMatrix &secondmMatrix);

enum mVecType{
    mvtRow,
    mvtCol
};

class mVector : public mMatrix
{
public:

    mVector(int size, mVecType type = mvtRow) :
        mMatrix(((type == mvtCol)?size:1),
                ((type == mvtRow)?size:1)),
        vType(type){}

    mVector(QVdouble vec, mVecType type = mvtRow) :
        mMatrix(((type == mvtCol)?vec.size():1),
                ((type == mvtRow)?vec.size():1)
                ),
        vType(type){
        switch (type) {
        case mvtRow:{
            data[0] = vec;
        }break;
        case mvtCol:{
            for (int cIndx = 0; cIndx < vec.size(); ++cIndx) {
                data[cIndx][0] = vec[cIndx];
            }
        }break;

        }
    }

    mVector(std::initializer_list<double> args):
        mVector(args,mvtRow){}

    int len()const{return (vType == mvtRow)?colLen():rowLen();}

    QVdouble toQVd()const {
        switch (vType) {
        case mvtRow:{
            return data.at(0);
        }break;
        case mvtCol:{
            QVdouble out(len());
            for (int cIndx = 0; cIndx < len(); ++cIndx) {
                out[cIndx] = data.at(cIndx).at(0);
            } return out;
        }break;
        }
    }

    double & operator[](int i) {
        return (vType == mvtRow)?data[0][i]:data[i][0];
    }
    double operator[](int i) const {
        return (vType == mvtRow)?data[0][i]:data[i][0];
    }


    friend mVector operator*(const double num, const mVector &Vec);
    friend mVector operator*(const mVector &Vec, const double num);
    friend mMatrix operator*(const mMatrix &Matr, const mVector &Vec);
    friend mMatrix operator*(const mVector &Vec , const mMatrix &Matr);
    friend mMatrix operator*(const mVector &Vec1, const mVector &Vec2);

    mVecType vType;
};

inline mMatrix mMatrix::solve(mMatrix A, mMatrix B)
{
    return A.inv() * B;
}

#endif // LINALGEBRA_H
