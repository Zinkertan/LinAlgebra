#include "linalg.h"





//void main()
//{
//    srand((unsigned)time(NULL));
//    setlocale(0, "");
//    int n, det;
//    cout << "Введите размер матрицы: ";
//    cin >> n;
//    int **matr = new int * [n];
//    double **obr_matr = new double * [n];
//    double **tobr_matr = new double * [n];
//    for(int i = 0; i < n; i++){
//        matr[i] = new int[n];
//        obr_matr[i] = new double[n];
//        tobr_matr[i] = new double[n];
//    }
//    SetMtx(matr, n);
//    PrintMtx(matr, n);
//    det = Det(matr, n);
//    cout << "Определитель матрицы = " << det << endl;
//    if(det){
//        for(int i = 0; i < n; i++){
//            for(int j = 0; j < n; j++){
//                int m = n - 1;
//                int **temp_matr = new int * [m];
//                for(int k = 0; k < m; k++)
//                    temp_matr[k] = new int[m];
//                Get_matr(matr, n, temp_matr, i, j);
//                obr_matr[i][j] = pow(-1.0, i + j + 2) * Det(temp_matr, m) / det;
//                FreeMem(temp_matr, m);
//            }
//        }
//    }
//    else
//        cout << "Т.к. определитель матрицы = 0,\nто матрица вырожденная и обратной не имеет!!!" << endl;
//    //Транспонирование матрицы
//    TransponMtx(obr_matr, tobr_matr, n);
//    //Печать обратной матрицы после транспонирования
//    PrintMtx(tobr_matr, n);
//    FreeMem(tobr_matr, n);
//    FreeMem(matr, n);
//    FreeMem(obr_matr, n);
//}
//Функция транспонирования матрицы
template <typename T> void TransponMtx(T **matr, T **tMatr, int n){//
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            tMatr[j][i] = matr[i][j];
}
//Функция освобождения памяти
template <typename T> void FreeMem(T **matr, int n)
{
    for(int i = 0; i < n; i++)
        delete [] matr[i];
    delete [] matr;
}

//функция заполнения матрицы
template <typename T> void SetMtx(T **matr, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matr[i][j] = rand()%9 + 1;
}

//функция печати матрицы
template <typename T> void PrintMtx(T **matr, int n)
{
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++)
            cout << matr[i][j] << " ";
        cout << endl;
    }
}
//функция вычеркивания строки и столбца
void Get_matr(int **matr, int n, int **temp_matr, int indRow, int indCol)
{
    int ki = 0;
    for (int i = 0; i < n; i++){
        if(i != indRow){
            for (int j = 0, kj = 0; j < n; j++){
                if (j != indCol){
                    temp_matr[ki][kj] = matr[i][j];
                    kj++;
                }
            }
            ki++;
        }
    }
}

//==============================================================================================================
//                              вычисление определителя
//==============================================================================================================
//функция вычисления определителя матрицы
int Det(int **matr, int n)
{
    int temp = 0;   //временная переменная для хранения определителя
    int k = 1;      //степень
    if(n < 1){
        cout<<"Не верный размер матрицы!!!" << endl;
        return 0;
    }
    else if (n == 1)
        temp = matr[0][0];
    else if (n == 2)
        temp = matr[0][0] * matr[1][1] - matr[1][0] * matr[0][1];
    else{
        for(int i = 0; i < n; i++){
            int m = n - 1;
            int **temp_matr = new int * [m];
            for(int j = 0; j < m; j++)
                temp_matr[j] = new int [m];
            Get_matr(matr, n, temp_matr, 0, i);
            temp = temp + k * matr[0][i] * Det(temp_matr, m);
            k = -k;
            FreeMem(temp_matr, m);
        }
    }
    return temp;
}



wMatrix::wMatrix(int rows, int columns):
    data(rows,vector<double>(columns)),
    _rows(rows),
    _columns(columns)
{
    fillZeros();
}

wMatrix::wMatrix(vector<vector<double>> matr):
    data(matr),
    _rows(matr.size()),
    _columns(matr.at(0).size()){}

wMatrix::wMatrix(const wMatrix &matr):
        data(matr.data),
        _rows(matr._rows),
        _columns(matr._columns){}

wMatrix::~wMatrix()
{}
int wMatrix::rowLen() const
{
    return _rows;
}

int wMatrix::colLen() const
{
    return _columns;
}

void wMatrix::copyElementsInRow(const wMatrix &m, int i){
    for (int j = 0; j < _columns; ++j)
        data[i][j] = m.data[i][j];
}

void wMatrix::print()
{
    for (int i = 0; i < _rows; i++){
        for (int j = 0; j < _columns; j++){
            std::cout << data[i][j] << " " ;
        }
        std::cout << std::endl;
    }
}

string wMatrix::toStr(string sep) const
{
    string out;
    for (int i = 0; i < _rows; i++){
        for (int j = 0; j < _columns; j++){
            out += to_string(data[i][j]) + sep;
        }
        out += "\n";
    }
    return out;
}

void wMatrix::copywMatrix(const wMatrix &wMatrix)
{
    if (wMatrix._columns != _columns || wMatrix._rows != _rows)
        throw std::logic_error("Wrong sizes");

    for (int i = 0; i < _rows; ++i)
        copyElementsInRow(wMatrix, i);
}

void wMatrix::setIt(int row, int columns, double value)
{
    data[row][columns] = value;
}

void wMatrix::setRow(int rNum, vector<double> row)
{
    assert(row.size() >= 0 && row.size() < _rows);
}

void wMatrix::setCol(int cNum, vector<double> col)
{
    assert(col.size() >= 0 && col.size() < _columns);
}

double wMatrix::it(int row, int columns) const
{
    return data[row][columns];
}

void wMatrix::fillZeros()
{
    for (int i = 0; i < _rows; i++){
        for (int j = 0; j < _columns; j++){
            data[i][j] = 0.0;
        }
    }
}

wMatrix wMatrix::T()
{
    wMatrix transposedM(_columns, _rows);
    for(int r = 0; r < transposedM.rowLen(); r++){
        for(int c = 0; c < transposedM.colLen(); c++){
            transposedM(r,c) = data[c][r];
        }
    }
    return transposedM;
}


wMatrix &wMatrix::operator=(const wMatrix &wMatrix)
{
    copywMatrix(wMatrix);
    return * this;
}

wMatrix wMatrix::operator+(const wMatrix & second)
{
    wMatrix newM(rowLen(), colLen());

    for(int r = 0; r < rowLen(); r++){
        for(int c = 0; c < colLen(); c++){
            newM(r,c) = this->data[r][c] + second(r,c);
        }
    }

    return newM;
}

wMatrix wMatrix::operator-(const wMatrix & second)
{
    wMatrix newM(rowLen(), colLen());

    for(int r = 0; r < rowLen(); r++){
        for(int c = 0; c < colLen(); c++){
            newM(r,c) = this->data[r][c] + second(r,c);
        }
    }

    return newM;
}

wMatrix wMatrix::operator*(const double & num)
{

    wMatrix newM(rowLen(), colLen());

    for(int r = 0; r < rowLen(); r++){
        for(int c = 0; c < colLen(); c++){
            newM(r,c) = this->data[r][c] * num;
        }
    }

    return newM;
}

wMatrix operator*(const wMatrix &Matr1,
                  const wMatrix &Matr2)
{
    assert(Matr1.colLen() == Matr2.rowLen());
    if (Matr1.colLen()!= Matr2.rowLen())
    {
        throw std::logic_error("Wrong sizes");
    }
    wMatrix newM(Matr1.rowLen(), Matr2.colLen());

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
std::ostream & operator<<(std::ostream & ostream, const wMatrix &matr)
{
    ostream << matr.toStr();
    return ostream;
}

std::istream & operator>>(std::istream & istream, wMatrix & number)
{
    if(number.rowLen() == 0 || number.colLen() == 0)
    {
        int row, col;
        cout << "Rows: ";
        istream >> row;
        number._rows = row;
        cout << "Cols: ";
        istream >> col;
        number._columns = col;
    }

    cout << "Your wMatrix has " << number.rowLen() << " rows and " << number.colLen() << " cols." << endl << "Insert elements now: " << endl;

    vector<vector<double>> m =
            vector<vector<double>>
                           (number.rowLen(),
                            vector<double>(number.colLen()));//new double*[number.rowLen()];

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



wMatrix operator*(const wMatrix &Matr, const wVector &Vec)
{
    if (Matr.colLen()!= Vec.rowLen())
    {
        assert(Matr.colLen()== Vec.rowLen());
        throw std::logic_error("Wrong sizes");
    }

    wMatrix newM(Matr.rowLen(), Vec.colLen());

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

wMatrix operator*(const wVector &Vec , const wMatrix &Matr)
{
    if (Matr.rowLen()!= Vec.colLen())
    {
        assert(Vec.colLen()==Matr.rowLen());
        throw std::logic_error("Wrong sizes");
    }

    wMatrix newM(Vec.rowLen(), Matr.colLen());

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

wMatrix operator*(const wVector &Vec1 , const wVector &Vec2)
{
    if (Vec2.rowLen()!= Vec1.colLen())
    {
        assert(Vec1.colLen()==Vec2.rowLen());
        throw std::logic_error("Wrong sizes");
    }

    wMatrix newM(Vec1.rowLen(), Vec2.colLen());

    for(int r = 0; r < Vec1.rowLen(); r++){
        for(int c = 0; c < Vec2.colLen(); c++){
            double elem(0.0);
            for(int i = 0; i < Vec1.colLen(); i++){
                elem += Vec1(r,i) * Vec2(i,c) ;

            }
            newM(r,c) = elem;
        }
    }

    return newM;
}


