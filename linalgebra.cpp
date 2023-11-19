#include "linalgebra.h"


mMatrix::mMatrix(int rows, int columns):
    data(rows,QVdouble(columns)),
    _rows(rows),
    _columns(columns)
{
    if (_rows == _columns) {
        _dim = _rows;
        _type = mmtSquare;
    }
    fillZeros();
}

mMatrix::mMatrix(QVVdouble matr):
    data(matr),
    _rows(matr.size()),
    _columns(matr.at(0).size()),
    _dim(0){
    if (_rows == _columns) {
        _dim = _rows;
        _type = mmtSquare;
    }
    for (int i = 0; i < _rows; ++i) {
        if (data.at(i).length()!=_columns){
            _type = mmtNotMatr;
        }
    }
}

mMatrix::mMatrix(std::initializer_list<std::initializer_list<double> > matr)
{
    QVVdouble newData;
    for (auto vec : matr) {
        newData.append(QVdouble(vec));
    }
    data = newData;
    _rows = newData.size();
    _columns = newData.at(0).size();
    if (_rows == _columns) {
        _dim = _rows;
        _type = mmtSquare;
    }
    for (int i = 0; i < _rows; ++i) {
        if (data.at(i).length()!=_columns){
            _type = mmtNotMatr;
        }
    }
}

mMatrix::mMatrix(const mMatrix &matr):
        data(matr.data),
        _rows(matr._rows),
        _columns(matr._columns),
        _type(matr._type),
        _dim(matr._dim)
{}


int mMatrix::rowLen() const
{
    return _rows;
}

int mMatrix::colLen() const
{
    return _columns;
}

int mMatrix::dim() const
{
    return _dim;
}

void mMatrix::resize(int newRow, int newCol, bool isSafeResize)
{
    if (isSafeResize) {
        if (_columns > newCol) {
            for (int row = 0; row < _rows; ++row) {
                for (int i = 0; i < _columns-newCol; ++i) {
                    data[row].removeLast();
                }
            }
            _columns = newCol;
        }
        if (_columns < newCol) {

            for (int row = 0; row < _rows; ++row) {
                for (int i = 0; i < _columns-newCol; ++i) {
                    data[row].append(0.0);
                }
            }
            _columns = newCol;
        }
        if (_rows > newRow) {
            for (int i = 0; i < _rows-newRow; ++i) {
                data.removeLast();
            }
            _rows = newRow;
        }
        if (_rows < newRow) {
            for (int i = 0; i < newRow-_rows; ++i) {
                data.append(QVdouble(_columns));
            }
            _rows = newRow;
        }
    } else {
        data = QVVdouble(newRow,QVdouble(newCol));
    }

}

void mMatrix::copymMatrix(const mMatrix &matr)
{
    if (matr._columns != _columns || matr._rows != _rows){
        assert(matr._columns == _columns || matr._rows == _rows);
        throw std::logic_error("Wrong sizes");
    }

    this->data = matr.data;

    this->_rows     = matr._rows;
    this->_columns  = matr._columns;
    this->_type     = matr._type;
    this->_dim      = matr._dim;
}

void mMatrix::resizeAndCopymMatrix(const mMatrix &matr)
{
    this->_columns = matr._columns;
    this->_rows    = matr._rows;
    this->data     = matr.data;
    if (_rows == _columns) {
        _dim = _rows;
        _type = mmtSquare;
    }
}

void mMatrix::print()
{
    for (int i = 0; i < _rows; i++){
        for (int j = 0; j < _columns; j++){
            std::cout << data[i][j] << " " ;
        }
        std::cout << std::endl;
    }
}

QString mMatrix::toQStr(QString sep,
                        QString format) const
{
    QList<QStringList> dataInStr;
    for (int i = 0; i < _rows; i++){
        QStringList rowStr;
        for (int j = 0; j < _columns; j++){
            rowStr.append(QString::number(data[i][j]));
        }
        dataInStr.append(rowStr);
    }

    QVector<int> max_length = QVector<int>(dataInStr.at(0).length()).fill(0);
    int lev_otst, prav_otst = 0;

    for (int row = 0; row < dataInStr.length(); row++) {
        for (int col = 0; col < max_length.length(); col++) {
            int len = dataInStr.at(row).at(col).length();
            if (len > max_length[col]){
                max_length[col] = len;
            }
        }
    }

    QString export_string = "";

//        exportStream.setLocale(QLocale(QLocale::Russian, QLocale::Russia));
    QString out = "";
    int raznica = 0;
    for (int row = 0; row < dataInStr.length(); row++) {
        for (int col = 0; col < max_length.length(); col++) {
                raznica = (max_length.at(col) -
                           dataInStr.at(row).at(col).length());
                if (raznica > 0){
                    if (dataInStr.at(row).at(col).length()>0) {
                        lev_otst = (dataInStr.at(row).at(col).startsWith("-"))?0:1;
                        prav_otst = raznica - lev_otst;
                    } else {
                        lev_otst = 0;
                        prav_otst = raznica;
                    }
                } else {
                    lev_otst = 0;
                    prav_otst = 0;
                }
                export_string += str_fill(lev_otst) +
                        dataInStr.at(row).at(col)
                        + str_fill(prav_otst) +
                        ((col+1 < max_length.length())?sep:"");
        }
        out += export_string + ((row+1 != dataInStr.length())?"\n":"");
        export_string = "";
    }
    return out;
}



void mMatrix::setItem(int row, int columns, double value)
{
    data[row][columns] = value;
}

void mMatrix::setRow(int rNum, QVdouble row)
{
    assert(row.size() >= 0 && row.size() < _rows);
}

void mMatrix::setCol(int cNum, QVdouble col)
{
    assert(col.size() >= 0 && col.size() < _columns);
}

double mMatrix::it(int row, int columns) const
{
    return data[row][columns];
}

QVdouble mMatrix::row(int indx)
{
    return data[indx];
}

QVdouble mMatrix::col(int indx)
{
    QVdouble outCol(colLen());
    for (int row = 0; row < _rows; ++row) {
        outCol[row] = data.at(row).at(indx);
    }
    return outCol;

}

void mMatrix::fillZeros()
{
    for (int i = 0; i < _rows; i++){
        for (int j = 0; j < _columns; j++){
            data[i][j] = 0.0;
        }
    }
}

mMatrix mMatrix::T()
{
    mMatrix transposedM(_columns, _rows);
    for(int r = 0; r < transposedM.rowLen(); r++){
        for(int c = 0; c < transposedM.colLen(); c++){
            transposedM(r,c) = data[c][r];
        }
    }
    return transposedM;
}

mMatrix mMatrix::M(int rowNum, int colNum)
{
    mMatrix adjugatedM(_dim-1,_dim-1);
    for(int r = 0, rowOfNewM = 0; r < _dim; r++){
        if(rowNum != r){
            for(int c = 0, colOfNewM = 0; c < _dim; c++){
                if(colNum != c){
                    adjugatedM(rowOfNewM,colOfNewM) = data.at(r).at(c);
                    colOfNewM++;
                }
            }
            rowOfNewM++;
        }
    }

    return adjugatedM;
}

double mMatrix::Minor(int row, int col)
{
    return M(row,col).det();
}

mMatrix mMatrix::MMatr()
{
    mMatrix MM(_dim,_dim);
    for (int i = 0; i < _rows; i++){
        for (int j = 0; j < _columns; j++){
            MM(i,j) = Minor(i,j);
        }
    }
    return MM;
}

double mMatrix::det()
{

    double det = 0.0;

    mMatrix m = *this;

    if (_type == mmtSquare) {
        if(_dim==1){
            det = m(0,0);
        }
        if(_dim == 2){
            det = m(0, 0) * m(1, 1) - m(0, 1) * m(1, 0);
        } else if(_dim == 3){
            det = m(0, 0) * m(1, 1) * m(2, 2) +
                  m(0, 1) * m(1, 2) * m(2, 0) +
                  m(0, 2) * m(1, 0) * m(2, 1) -
                  m(0, 2) * m(1, 1) * m(2, 0) -
                  m(2, 1) * m(1, 2) * m(0, 0) -
                  m(2, 2) * m(1, 0) * m(0, 1);
        }else{
            for(int cNum=0;cNum<_dim;++cNum){
                det+=ad(0,cNum);
            }
        }
    }

    return det;
}



mMatrix mMatrix::adMatr()
{
    mMatrix ad_matr(_dim,_dim);
    for (int rNum = 0; rNum < _dim; ++rNum) {
        for (int cNum = 0; cNum < _dim; ++cNum) {
            ad_matr(rNum,cNum) = ad(rNum,cNum);
        }
    }
    return ad_matr;
}

double mMatrix::ad(int rNum, int cNum)
{
    return pow((double)-1,(rNum+cNum))*Minor(rNum,cNum);
}

mMatrix mMatrix::inv()
{
    double det = this->det();
    if(det != 0.0){
        return mMatrix((1.0/det)*this->adMatr().T());
    } else {
        return *this;
    }
}

bool mMatrix::isE()
{
    for(int r = 0; r < rowLen(); r++){
        for(int c = 0; c < colLen(); c++){
            if (r == c) {
                if (data.at(r).at(c) != 1.0) {
                    return false;
                }
            } else {
                if (data.at(r).at(c) != 0.0) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool mMatrix::isSqr()
{
    if (_type == mmtSquare) {
        return true;
    }
    return false;
}




mMatrix mMatrix::operator+(const mMatrix & second)
{
    mMatrix newM(rowLen(), colLen());

    for(int r = 0; r < rowLen(); r++){
        for(int c = 0; c < colLen(); c++){
            newM(r,c) = this->data[r][c] + second(r,c);
        }
    }

    return newM;
}

mMatrix mMatrix::operator-(const mMatrix & second)
{
    mMatrix newM(rowLen(), colLen());

    for(int r = 0; r < rowLen(); r++){
        for(int c = 0; c < colLen(); c++){
            newM(r,c) = this->data[r][c] + second(r,c);
        }
    }

    return newM;
}

mMatrix mMatrix::operator*(const double & num)
{

    mMatrix newM(rowLen(), colLen());

    for(int r = 0; r < rowLen(); r++){
        for(int c = 0; c < colLen(); c++){
            newM(r,c) = this->data[r][c] * num;
        }
    }

    return newM;
}

mMatrix mMatrix::operator/(const double &num)
{
    mMatrix newM(rowLen(), colLen());

    for(int r = 0; r < rowLen(); r++){
        for(int c = 0; c < colLen(); c++){
            newM(r,c) = this->data[r][c] / num;
        }
    }

    return newM;
}

mMatrix operator*(const mMatrix &Matr1,
                  const mMatrix &Matr2)
{
    assert(Matr1.colLen() == Matr2.rowLen());
    if (Matr1.colLen()!= Matr2.rowLen())
    {
        throw std::logic_error("Wrong sizes");
    }
    mMatrix newM(Matr1.rowLen(), Matr2.colLen());

    for(int r = 0; r < Matr1.rowLen(); r++){
        for(int c = 0; c < Matr2.colLen(); c++){
            double elem(0.0);
            for(int i = 0; i < Matr1.colLen(); i++){
                elem += Matr1(r,i) * Matr2(i,c);

            }
            newM(r,c) = elem;
        }
    }

    return newM;
}

mMatrix operator*(const double num, const mMatrix &Matr)
{

    mMatrix newM(Matr.rowLen(), Matr.colLen());

    for(int r = 0; r < Matr.rowLen(); r++){
        for(int c = 0; c < Matr.colLen(); c++){
            newM(r,c) = num*Matr(r,c);
        }
    }

    return newM;
}

std::ostream & operator<<(std::ostream & ostream, const mMatrix &matr)
{
    ostream << matr.toQStr().toStdString();
    return ostream;
}

std::istream & operator>>(std::istream & istream, mMatrix & number)
{
    if(number.rowLen() == 0 || number.colLen() == 0)
    {
        int row, col;
        std::cout << "Rows: ";
        istream >> row;
        number._rows = row;
        std::cout << "Cols: ";
        istream >> col;
        number._columns = col;
    }

    std::cout << "Your mMatrix has " << number.rowLen() <<
                 " rows and " << number.colLen() <<
                 " cols." << std::endl <<
                 "Insert elements now: " << std::endl;

    QVVdouble m = QVVdouble(number.rowLen(),
                            QVdouble(number.colLen()));

    for (int r = 0; r < number.rowLen(); r++)
    {
        for (int c = 0; c < number.colLen(); c++)
        {
            double tempNumber;
            istream >> tempNumber;
            m[r][c] = tempNumber;
        }
    }

    number.data = m;

    return istream;
}

mVector mVector::operator+(const mVector & second)
{
    if (this->_vType == second._vType) {
        if (this->len()!= second.len())
        {
            assert(this->len()==second.len());
            throw std::logic_error("Wrong sizes");
        }
    }
    mVector newV(this->len(),this->_vType);

    for(int i = 0; i < this->len(); i++){
        newV[i] = this->at(i) + second[i];
    }

    return newV;
}

mVector mVector::operator*(const double & num)
{
    mVector newV(this->len(),this->_vType);

    for(int i = 0; i < this->len(); i++){
        newV[i] = this->at(i) * num;
    }

    return newV;
}

mVector mVector::operator-(const mVector & second)
{
    return mVector::operator+(-1.0*second);
}


mVector mVector::operator/(const double &num)
{
    return mVector::operator*(1.0/num);
}

double mVector::dot(const mVector vec) const{
    double out = 0.0;
    if (this->_vType == vec._vType) {
        if (this->len()!= vec.len())
        {
            assert(this->len()==vec.len());
            throw std::logic_error("Wrong sizes");
        }
    }
    for (int ix = 0; ix < len(); ix++) {
        out += this->at(ix)*vec[ix];
    }
    return out;
}

mVector operator*(const double num, const mVector &Vec)
{

    mVector outV(Vec.len(),Vec._vType);

    for(int r = 0; r < Vec.rowLen(); r++){
        for(int c = 0; c < Vec.colLen(); c++){
            outV(r,c) = num*Vec(r,c);
        }
    }

    return outV;
}

mVector operator*(const mVector &Vec, const double num)
{

    mVector outV(Vec.len(),Vec._vType);

    for(int r = 0; r < Vec.rowLen(); r++){
        for(int c = 0; c < Vec.colLen(); c++){
            outV(r,c) = num*Vec(r,c);
        }
    }

    return outV;
}

mMatrix operator*(const mMatrix &Matr, const mVector &Vec)
{
    if (Matr.colLen()!= Vec.rowLen())
    {
        assert(Matr.colLen()== Vec.rowLen());
        throw std::logic_error("Wrong sizes");
    }

    mMatrix newM(Matr.rowLen(), Vec.colLen());

    for(int r = 0; r < Matr.rowLen(); r++){
        for(int c = 0; c < Vec.colLen(); c++){
            double elem(0.0);
            for(int i = 0; i < Matr.colLen(); i++){
                elem += Matr(r,i) * Vec(i,c) ;

            }
            newM(r,c) = elem;
        }
    }

    return newM;
}

mMatrix operator*(const mVector &Vec , const mMatrix &Matr)
{
    if (Matr.rowLen()!= Vec.colLen())
    {
        assert(Vec.colLen()==Matr.rowLen());
        throw std::logic_error("Wrong sizes");
    }

    mMatrix newM(Vec.rowLen(), Matr.colLen());

    for(int r = 0; r < Vec.rowLen(); r++){
        for(int c = 0; c < Matr.colLen(); c++){
            double elem(0.0);
            for(int i = 0; i < Vec.colLen(); i++){
                elem += Vec(r,i) * Matr(i,c) ;

            }
            newM(r,c) = elem;
        }
    }

    return newM;
}

mMatrix operator*(const mVector &Vec1 , const mVector &Vec2)
{

    if (Vec1._vType == Vec2._vType) {
        if (Vec2.len()!= Vec1.len())
        {
            assert(Vec1.len()==Vec2.len());
            throw std::logic_error("Wrong sizes");
        }
        mVector outV(Vec1.len(),Vec1._vType);

        for (int ix = 0; ix < Vec1.len(); ix++) {
            outV[ix] = Vec1[ix]*Vec2[ix];
        }
        return outV.toMatrix();
    } else {
        mMatrix outM(Vec1.rowLen(), Vec2.colLen());
        for(int r = 0; r < Vec1.rowLen(); r++){
            for(int c = 0; c < Vec2.colLen(); c++){
                double elem(0.0);
                for(int i = 0; i < Vec1.colLen(); i++){
                    elem += Vec1(r,i) * Vec2(i,c) ;

                }
                outM(r,c) = elem;
            }
        }
        return outM;
    }




}



