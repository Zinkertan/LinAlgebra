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
#include "QList"
#include "QStringList"

typedef QVector<double> QVdouble;
typedef QVector<QVdouble> QVVdouble;

inline QString str_fill (int length, char fillChar = ' ') {
    QString String_p = "";
    for (int i = 0; i < length; ++i) {
        String_p += fillChar;
    }
    return String_p;
}

inline QString str_fill (int length, QString fillStr) {
    QString String_p = "";
    for (int i = 0; i < length; ++i) {
        String_p += fillStr;
    }
    return String_p;
}

enum mMatrType{
    mmtNotMatr,
    mmtDefault,
    mmtSquare
};

class mMatrix {
    // Матрица организована как вектор строк(row),
    // т.е. сначала идет строка, потом обращение к колонке

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
    mMatrix(std::initializer_list<std::initializer_list<double>> matr);
    mMatrix(const mMatrix &mMatrix);
    ~mMatrix(){};

    int    rowLen() const;
    int    colLen() const;
    int    dim() const;
    void   resize(int newRow, int newCol, bool isSafeResize = true);
//    void   addRow() const;
//    void   addCol() const;
//    void   appendRow() const;
//    void   appendCol() const;

    void   copymMatrix(const mMatrix &matr);
    void   resizeAndCopymMatrix(const mMatrix &matr);

    void   print();
    QString toQStr(QString sep = "|",
                   QString format = "6 f") const;

    void   setItem(int row, int columns, double value);
    void   setRow (int rNum, QVdouble row);
    void   setCol (int cNum, QVdouble col);
    double it(int row, int columns) const;

    QVdouble row(int indx);
    QVdouble col(int indx);

    const QVVdouble& matr() const{return data;} // для константных объектов

    void   fillZeros();

    mMatrix T(); //возвращает транспонированную матрицу
    mMatrix M(int row, int col); // Возвращает матрицу минора для элемента
    double  Minor(int row, int col); // Возвращает определитель М. минора для элемента
    mMatrix MMatr(); // Возвращает матрицу минора для элемента
    double  det();
    mMatrix adMatr();             // Матрица алгебраических дополнений
    double  ad(int row, int col); // Алгебраическое дополнение
    mMatrix inv();

    bool isE();     // Единичная ли матрица?
    bool isSqr();   // Квадратная ли матрица?

    static mMatrix solve(mMatrix A, mMatrix B); // Решение матричного уровнения A*X=B


public:

    double& operator()(int row, int col);
    const double& operator()(int row, int col) const; // для константных объектов

    mMatrix& operator=(const mMatrix &mMatrix) {
        copymMatrix(mMatrix);
        return *this;
    }

    mMatrix operator+(const mMatrix &);
    mMatrix operator-(const mMatrix &);
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
    assert(row >= 0 && row < _rows);
    assert(col >= 0 && col < _columns);

    return data[row][col];
}
inline const double &mMatrix::operator()(int row, int col) const
{
    assert(row >= 0 && row < _rows);
    assert(col >= 0 && col < _columns);

    return data[row][col];
}


mMatrix operator+(const mMatrix &firstmMatrix, const mMatrix &secondmMatrix);

enum mVecType{
    mvtRow_, // horizontal vector Вектор линия
    mvtColI  // vertical   vector Вектор столбец
};

class mVector : public mMatrix
{
public:
    mVecType vType;

    mVector(int size, mVecType type = mvtColI) :
        mMatrix(((type == mvtColI)?size:1),
                ((type == mvtRow_)?size:1)),
        vType(type){}

    mVector(QVdouble vec, mVecType type = mvtColI) :
        mMatrix(((type == mvtColI)?vec.size():1),
                ((type == mvtRow_)?vec.size():1)
                ),
        vType(type){
        switch (type) {
        case mvtRow_:{
            data[0] = vec;
        }break;
        case mvtColI:{
            for (int cIndx = 0; cIndx < vec.size(); ++cIndx) {
                data[cIndx][0] = vec[cIndx];
            }
        }break;

        }
    }

    mVector(mMatrix M) : mMatrix(0,0){
        assert(M.colLen() == 1 || M.rowLen() == 1);
        if (M.colLen() == 1) {
            vType = mvtRow_;
            this->resizeAndCopymMatrix(M);
        } else if (M.rowLen() == 1){
            vType = mvtRow_;
            this->resizeAndCopymMatrix(M);
        }
    }

    mVector(std::initializer_list<double> args):
        mVector(args,mvtColI){}

    mVector& operator=(const mVector &V){
        // Проверка на самоприсваивание
        if (this == &V)
            return *this;


        assert(V.colLen() == 1 || V.rowLen() == 1);
        if (V.colLen() == 1 || V.rowLen() == 1) {
            mMatrix::operator = (V);
            this->vType = V.vType;
        }
        return *this;
    }

    mVector& operator*=(const double num){
        return mVector::operator=(mVector::operator*(num));
    }

    mVector& operator=(const mMatrix &M){
        if (M.colLen() == 1 || M.rowLen() == 1) {
            this->copymMatrix(M);
        }
        return *this;
    }

    mVector operator+(const mVector &);
    mVector operator-(const mVector &);
    mVector operator*(const double &);
    mVector operator/(const double &);



    int len()const{return (vType == mvtRow_)?colLen():rowLen();}

    mMatrix toMatrix(){
        return mMatrix(data);
    }

    QVdouble toQVd()const {
        switch (vType) {
        case mvtRow_:{
            return data.at(0);
        }break;
        case mvtColI:{
            QVdouble out(len());
            for (int cIndx = 0; cIndx < len(); ++cIndx) {
                out[cIndx] = data.at(cIndx).at(0);
            } return out;
        }break;
        }
    }

    double at(int i) const {
        return (vType == mvtRow_)?data[0][i]:data[i][0];
    }

    double & operator[](int i) {
        return (vType == mvtRow_)?data[0][i]:data[i][0];
    }
    double operator[](int i) const {
        return (vType == mvtRow_)?data[0][i]:data[i][0];
    }


    friend mVector operator*(const double num, const mVector &Vec);
    friend mVector operator*(const mVector &Vec, const double num);
    friend mMatrix operator*(const mMatrix &Matr, const mVector &Vec);
    friend mMatrix operator*(const mVector &Vec , const mMatrix &Matr);
    friend mMatrix operator*(const mVector &Vec1, const mVector &Vec2);



};

inline mMatrix mMatrix::solve(mMatrix A, mMatrix B)
{
    return A.inv() * B;
}


#endif // LINALGEBRA_H
