#ifndef LINEAR_OBJ_H
#define LINEAR_OBJ_H

#include "math.h"
#include "exception"
#include "cassert"
#include "QVector"
#include "linalgebra.h"

typedef double array_xy[2];
typedef double* ptrarray_xy[2];
typedef double array_xyz[3];
typedef double* ptrarray_xyz[3];

const double glTol = 1e-16;
// Базовый класс
class lObj
{
public:
    enum Axes{
        x_ax = 0,
        y_ax,
        z_ax,
        LAST_ax,
    };

    enum dimensionType{
        dim1 = 1,
        dim2 = 2,
        dim3 = 3
    };

    lObj(dimensionType dT):dim(dT) {}

    dimensionType dim;


//    virtual void move_on(double on_x, double on_y, double on_z){};
//    virtual void move_to(double nx, double ny, double nz){};

    virtual ~lObj(){}
};

// Точка 2D
class lP2D : public lObj{
public:
    double x = 0.0;
    double y = 0.0;
    lP2D(double _x, double _y): lObj(dim2),x(_x),y(_y){}
    lP2D(mVector mVec): lObj(dim2),x(mVec[x_ax]),y(mVec[y_ax]){}
    lP2D(): lP2D(0.0,0.0){}
    lP2D(const lP2D & P):lP2D(){
        // Выполняем копирование значений
        this->x = P.x;
        this->y = P.y;
    }
    virtual ~lP2D() override{}

    lP2D& operator= (const lP2D &P)
    {
        // Проверка на самоприсваивание
        if (this == &P)
            return *this;

        // Выполняем копирование значений
        lObj::operator = (P);
        this->x = P.x;
        this->y = P.y;
        // Возвращаем текущий объект
        return *this;
    }

    friend lP2D operator-(const lP2D &P1, const lP2D &P2){
        return lP2D (P1.x-P2.x,P1.y-P2.y);
    }

    friend lP2D operator+(const lP2D &P1, const lP2D &P2){
        return lP2D (P1.x+P2.x,P1.y+P2.y);
    }

    friend lP2D operator*(const lP2D &P1, const double &num){
        return lP2D (P1.x*num,P1.y*num);
    }

    friend lP2D operator*=(const lP2D &P1, const double &num){
        return lP2D (P1.x*num,P1.y*num);
    }

    double * data() { return *mData;}
    const double * data() const { return *mData; }
    double & operator[](int i) { return *mData[i]; }
    double operator[](int i) const { return *mData[i]; }


    QString toQStr() const{
        QString tmp = "(%1,%2)";
        return tmp.arg(x).arg(y);
    }
private:

    ptrarray_xy mData = {&this->x,&this->y};

};

// Точка 3D
class lP3D : public lObj{
public:
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    lP3D(double _x, double _y, double _z): lObj(dim3),x(_x),y(_y),z(_z){}
    lP3D(mVector mVec): lObj(dim3),x(mVec[x_ax]),y(mVec[y_ax]),z(mVec[z_ax]){}
    lP3D(): lP3D(0.0,0.0,0.0){}
    lP3D(const lP3D & P):lP3D(){
        // Выполняем копирование значений
        this->x = P.x;
        this->y = P.y;
        this->z = P.z;
    }
    virtual ~lP3D() override{}

    lP3D& operator= (const lP3D &P)
    {
        // Проверка на самоприсваивание
        if (this == &P)
            return *this;

        // Выполняем копирование значений (обязательно переменных, нельзя массив с сылками =( )
        lObj::operator = (P);
        this->x = P.x;
        this->y = P.y;
        this->z = P.z;
        // Возвращаем текущий объект
        return *this;
    }

    friend lP3D operator-(const lP3D &P1, const lP3D &P2){
        return lP3D (P1.x-P2.x,P1.y-P2.y,P1.z-P2.z);
    }

    friend lP3D operator+(const lP3D &P1, const lP3D &P2){
        return lP3D (P1.x+P2.x,P1.y+P2.y,P1.z+P2.z);
    }

    friend lP3D operator*(const lP3D &P1, const double &num){
        return lP3D (P1.x*num,P1.y*num,P1.z*num);
    }

    friend lP3D operator*=(const lP3D &P1, const double &num){
        return lP3D (P1.x*num,P1.y*num,P1.z*num);
    }

    double * data() { return *mData;}
    const double * data() const { return *mData; }
    double & operator[](int i) { return *mData[i]; }
    double operator[](int i) const { return *mData[i]; }


    QString toQStr() const{
        QString tmp = "(%1,%2,%3)";
        return tmp.arg(x).arg(y).arg(z);
    }
private:

    ptrarray_xyz mData = {&this->x,&this->y,&this->z};

};

//Отрезок 2D
class lS2D : public lObj
{
public:
    lP2D p1,p2;
    lS2D(lP2D _p1, lP2D _p2): lObj(dim2),p1(_p1),p2(_p2){}

    double len() const{
        double sum2 = 0;
        for (int i = 0; i < dim2; ++i) {
            sum2 += pow(p1[i]-p2[i],2);
        }
        return sqrt(sum2);
    }
};

//Отрезок 3D
class lS3D : public lObj
{
public:
    lP3D p1,p2;
    lS3D(lP3D _p1, lP3D _p2): lObj(dim3),p1(_p1),p2(_p2){}

    double len() const{
        double sum2 = 0;
        for (int i = 0; i < dim3; ++i) {
            sum2 += pow(p1[i]-p2[i],2);
        }
        return sqrt(sum2);
    }
};


//Вектор 2D
class lV2D : public lObj
{
    bool fixed = false;

public:
    double x = 0.0;
    double y = 0.0;
    lP2D p = lP2D(0.0,0.0);

    lV2D(double _x, double _y): lObj(dim2),fixed(false),x(_x),y(_y){}
    lV2D(mVector mVec): lObj(dim2),fixed(false),x(mVec[x_ax]),y(mVec[y_ax]){}

    lV2D(double _x, double _y, lP2D _p): lObj(dim2),fixed(true),x(_x),y(_y),p(_p){}
    lV2D(mVector mVec, lP2D _p): lObj(dim2),fixed(true),x(mVec[x_ax]),y(mVec[y_ax]),p(_p){}

    lV2D(lP2D p1, lP2D p2, bool isToFix = true): lObj(dim2),fixed(isToFix){
        setP1P2(p1,p2,isToFix);
    }

    lV2D(): lV2D(0.0,0.0){}
    lV2D(const lV2D & P):lV2D(){
        // Выполняем копирование значений
        x     = P.x    ;
        y     = P.y    ;
        p     = P.p    ;
        fixed = P.fixed;
    }
    virtual ~lV2D() override{}

    lV2D& operator= (const lV2D &P)
    {
        // Проверка на самоприсваивание
        if (this == &P)
            return *this;

        // Выполняем копирование значений
        lObj::operator = (P);
        x     = P.x    ;
        y     = P.y    ;
        p     = P.p    ;
        fixed = P.fixed;
        // Возвращаем текущий объект
        return *this;
    }

    mVector vec() const{
        return {x,y};
    }

    friend lV2D operator+(const lV2D &V1, const lV2D &V2){
        return lV2D (V1.x+V2.x,V1.y+V2.y);
    }

    friend lV2D operator-(const lV2D &V1, const lV2D &V2){
        return V1+(-1.0*V2);
    }

    friend lV2D operator*(const lV2D &V1, const double &num){
        return lV2D (V1.x*num,V1.y*num);
    }

    friend lV2D operator*(const double &num, const lV2D &V1){
        return lV2D (V1.x*num,V1.y*num);
    }

    friend lV2D operator*=(const lV2D &V1, const double &num){
        return lV2D (V1.x*num,V1.y*num);
    }

    //Скаляроное умножение
    static double dot(const lV2D &v1, const lV2D &v2){
        return v1.x*v2.x + v1.y*v2.y;
    }

    double dot(const lV2D &v2) const{
        return dot(*this,v2) ;
    }

    static double angle(const lV2D &v1, const lV2D &v2){
        return acos(dot(v1,v2)/(v1.len()*v2.len()));
    }

    double angle(const lV2D &v2) const{
        return angle(*this,v2) ;
    }

    // Проекция вектора v2 на вектор v1
    static double proj(const lV2D &v1, const lV2D &v2){
        return dot(v1,v2)/(v1.len());
    }

    double proj(const lV2D &v2) const{
        return proj(*this,v2) ;//cos(a)*v2.len()
    }

    static lV2D projV(const lV2D &v1, const lV2D &v2){
        return dot(v1,v2)/dot(v1,v1)*v1;
    }

    lV2D projV(const lV2D &v2) const{
        return projV(*this,v2) ;//cos(a)*v2.len()
    }

    void setP1P2(lP2D p1, lP2D p2, bool isToFix = true){
        x = p2.x - p1.x;
        y = p2.y - p1.y;
        fixed = isToFix;
        if (isToFix) {
            p = p1;
        }
    }

    void fix(lP2D p1){
        p = p1;
        fixed = true;
    }

    void unfix(){
        p = lP2D(0.0,0.0);
        fixed = false;
    }

    static bool isCollinear(const lV2D &v1, const lV2D &v2, double tol = 1e-6){
        return fabs(v1.x/v2.x-v1.y/v2.y)<tol?true:false;
    }

    bool isCollinear(const lV2D &v2, double tol = 1e-6) const{
        return isCollinear(*this,v2,tol);
    }

    static bool isOrt(const lV2D &v1, const lV2D &v2, double tol = 1e-6){
        return fabs(dot(v1,v2))<tol?true:false;
    }

    bool isOrt(const lV2D &v2, double tol = 1e-6) const{
        return isOrt(*this,v2,tol);
    }

    double len() const{
        double sum2 = 0;
        for (int i = 0; i < dim2; ++i) {
            sum2 += pow(*mData[i],2);
        }
        return sqrt(sum2);
    }

    bool isFixed(){return fixed;}

    // Направляющий косинус вектор
    lV2D dirVector(bool toFix = false) const{
        if (!toFix) {
            return lV2D(x/len(),y/len());
        } else {
            return lV2D(x/len(),y/len(),p);
        }
    }

    lV2D dirVector(lP2D newPoint) const{
        return lV2D(x/len(),y/len(),newPoint);
    }

    lV2D ort ()const{
        return lV2D(-y,x);
    }

    lV2D turnV (double ang)const{
        mMatrix A({{cos(ang),-sin(ang)},
                   {sin(ang), cos(ang)}});

        return mVector(A*vec());
    }

    double * data() { return *mData;}
    const double * data() const { return *mData; }
    double & operator[](int i) { return *mData[i]; }
    double operator[](int i) const { return *mData[i]; }


    QString toQStr(bool addLen = false) const{
        QString tmp = "{%1,%2}%3%4";
        return tmp.arg(x).arg(y).
                arg((fixed)?QString(" - F%1").arg(p.toQStr()):"").
                arg(addLen?QString(" len = %1").arg(len()):"");
    }
private:
    ptrarray_xy mData = {&this->x,&this->y};

};

//Вектор 3D
class lV3D : public lObj
{
    bool fixed = false;

public:
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    lP3D p = lP3D(0.0,0.0,0.0);

    lV3D(double _x, double _y, double _z): lObj(dim3),fixed(false),x(_x),y(_y),z(_z){}
    lV3D(mVector mVec): lObj(dim3),fixed(false),x(mVec[x_ax]),y(mVec[y_ax]),z(mVec[z_ax]){}

    lV3D(double _x, double _y, double _z, lP3D _p): lObj(dim3),fixed(true),x(_x),y(_y),z(_z),p(_p){}
    lV3D(mVector mVec, lP3D _p): lObj(dim3),fixed(true),x(mVec[x_ax]),y(mVec[y_ax]),z(mVec[z_ax]),p(_p){}

    lV3D(lP3D p1, lP3D p2, bool isToFix = true): lObj(dim3),fixed(isToFix){
        setP1P2(p1,p2,isToFix);
    }

    lV3D(): lV3D(0.0,0.0,0.0){}
    lV3D(const lV3D & P):lV3D(){
        // Выполняем копирование значений
        x     = P.x    ;
        y     = P.y    ;
        z     = P.z    ;
        p     = P.p    ;
        fixed = P.fixed;
    }
    virtual ~lV3D() override{}

    lV3D& operator= (const lV3D &P)
    {
        // Проверка на самоприсваивание
        if (this == &P)
            return *this;

        // Выполняем копирование значений
        lObj::operator = (P);
        x     = P.x    ;
        y     = P.y    ;
        z     = P.z    ;
        p     = P.p    ;
        fixed = P.fixed;
        // Возвращаем текущий объект
        return *this;
    }

    mVector vec() const{
        return {x,y,z};
    }

    friend lV3D operator+(const lV3D &V1, const lV3D &V2){
        return lV3D (V1.x+V2.x,V1.y+V2.y,V1.z+V2.z);
    }

    friend lV3D operator-(const lV3D &V1, const lV3D &V2){
        return V1+(-1.0*V2);
    }

    friend lV3D operator*(const lV3D &V1, const double &num){
        return lV3D (V1.x*num,V1.y*num,V1.z*num);
    }

    friend lV3D operator*(const lV3D &V1, const lV3D &V2){
        mMatrix X ({{V1.y,V1.z},
                    {V2.y,V2.z}});
        mMatrix Y ({{V1.x,V1.z},
                    {V2.x,V2.z}});
        mMatrix Z ({{V1.x,V1.y},
                    {V2.x,V2.y}});

        return {X.det(),-Y.det(),Z.det()};
    }

    friend lV3D operator*(const double &num, const lV3D &V1){
        return lV3D (V1.x*num,V1.y*num,V1.z*num);
    }

    friend lV3D operator*=(const lV3D &V1, const double &num){
        return lV3D (V1.x*num,V1.y*num,V1.z*num);
    }

    //Скаляроное умножение
    static double dot(lV3D v1, lV3D v2){
        return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z ;
    }

    double dot(const lV3D &v2) const{
        return dot(*this,v2) ;
    }

    static double angle(const lV3D &v1, const lV3D &v2){
        return acos(dot(v1,v2)/(v1.len()*v2.len()));
    }

    double angle(const lV3D &v2) const{
        return angle(*this,v2) ;
    }

    // Проекция вектора v2 на вектор v1
    static double proj(const lV3D &v1, const lV3D &v2){
        return dot(v1,v2)/(v1.len());
    }

    double proj(const lV3D &v2) const{
        return proj(*this,v2) ;//cos(a)*v2.len()
    }

    static lV3D projV(const lV3D &v1, const lV3D &v2){
        return dot(v1,v2)/dot(v1,v1)*v1;
    }

    lV3D projV(const lV3D &v2) const{
        return projV(*this,v2) ;//cos(a)*v2.len()
    }

    lV2D projOnXY() const{
        return {x,y};
    }

    lV2D projOnYZ() const{
        return {y,z};
    }

    lV2D projOnXZ() const{
        return {x,z};
    }

    void setP1P2(lP3D p1, lP3D p2, bool isToFix = true){
        x = p2.x - p1.x;
        y = p2.y - p1.y;
        z = p2.z - p1.z;
        fixed = isToFix;
        if (isToFix) {
            p = p1;
        }
    }

    void fix(lP3D p1){
        p = p1;
        fixed = true;
    }

    void unfix(){
        p = lP3D(0.0,0.0,0.0);
        fixed = false;
    }

    static bool isCollinear(const lV3D &v1, const lV3D &v2, double tol = 1e-6){
        double  o_x = v1.x/v2.x,
                o_y = v1.y/v2.y,
                o_z = v1.z/v2.z;
        return fabs(o_x-o_y)<tol && fabs(o_y-o_z)<tol && fabs(o_z-o_x)<tol?true:false;
    }

    bool isCollinear(const lV3D &v2, double tol = 1e-6) const{
        return isCollinear(*this,v2,tol);
    }

    static bool isOrt(const lV3D &v1, const lV3D &v2, double tol = 1e-6){
        return fabs(dot(v1,v2))<tol?true:false;
    }

    bool isOrt(const lV3D &v2, double tol = 1e-6) const{
        return isOrt(*this,v2,tol);
    }

    double len()const{
        double sum2 = 0;
        for (int i = 0; i < dim3; ++i) {
            sum2 += pow(*mData[i],2);
        }
        return sqrt(sum2);
    }

    bool isFixed(){return fixed;}

    // Направляющий косинус вектор
    lV3D dirVector(bool toFix = false) const{
        if (!toFix) {
            return lV3D(x/len(),y/len(),z/len());
        } else {
            return lV3D(x/len(),y/len(),z/len(),p);
        }
    }

    lV3D dirVector(lP3D newPoint) const{
        return lV3D(x/len(),y/len(),z/len(),newPoint);
    }

    lV3D turnV (double a1,double a2,double a3)const{
        mMatrix Axy({{cos(a1),-sin(a1), 0.0},
                     {sin(a1), cos(a1), 0.0},
                     {0.0    , 0.0    , 1.0}});
        //? zx
        mMatrix Axz({{1.0, 0.0    , 0.0    },
                     {0.0, cos(a2),-sin(a2)},
                     {0.0, sin(a2), cos(a2)}});

        mMatrix Ayz({{cos(a3), 0.0,-sin(a3)},
                     {0.0    , 1.0, 0.0    },
                     {sin(a3), 0.0, cos(a3)}});


        return mVector(Axy*Axz*Ayz*vec());
    }

    double * data() { return *mData;}
    const double * data() const { return *mData; }
    double & operator[](int i) { return *mData[i]; }
    double operator[](int i) const { return *mData[i]; }


    QString toQStr(bool addLen = false) const{
        QString tmp = "{%1,%2,%3}%4%5";
        return tmp.arg(x).arg(y).arg(z).
                arg((fixed)?QString(" - F%1").arg(p.toQStr()):"").
                arg(addLen?QString(" len = %1").arg(len()):"");
    }
private:
    ptrarray_xyz mData = {&this->x,&this->y,&this->z};
};

//Прямая 2D
class lL2D : public lObj
{

    enum orientation{
        Oxy,
        Ox,
        Oy
    };

    orientation O = Oxy;
public:
    double A = 0.0;
    double B = 0.0;
    double C = 0.0;
    lL2D(double _A, double _B, double _C): lObj(dim2),A(_A),B(_B),C(_C){}
    lL2D(lV2D vec, lP2D point): lObj(dim2){
        setWithVP(vec,point);
    }
    lL2D(lV2D vec): lObj(dim2){
        setWithFixedV(vec);
    }
    lL2D(lP2D p1, lP2D p2): lObj(dim2){
        setWithFixedV(lV2D(p1,p2));
    }

    lL2D(): lL2D(0.0,0.0,0.0){}
    lL2D(const lL2D & L):lL2D(){
        // Выполняем копирование значений
        A     = L.A    ;
        B     = L.B    ;
        C     = L.C    ;
    }
    virtual ~lL2D() override{}

    lL2D& operator= (const lL2D &L)
    {
        // Проверка на самоприсваивание
        if (this == &L)
            return *this;

        // Выполняем копирование значений
        lObj::operator = (L);
        A     = L.A    ;
        B     = L.B    ;
        C     = L.C    ;
        // Возвращаем текущий объект
        return *this;
    }

    void setWithVP(lV2D vec, lP2D point){
        double mn = (vec.y>0)?1:-1;
        A = mn*vec.y;
        B = mn*-vec.x;
        assert(A != 0.0);
        assert(B != 0.0);
        if (A==0.0) {
            O = Ox;
        } else if (B==0.0){
            O = Oy;
        } else {
            O = Oxy;
        }
        C = mn*(vec.x*point.y-vec.y*point.x);
    }

    void setWithFixedV(lV2D vec){
        assert(vec.isFixed());
        double mn = (vec.y>0)?1:-1;
        A = mn*vec.y;
        B = mn*-vec.x;
        assert(A != 0.0);
        assert(B != 0.0);

        if (A==0.0) {
            O = Ox;
        } else if (B==0.0){
            O = Oy;
        } else {
            O = Oxy;
        }
        C = mn*(vec.x*vec.p.y-vec.y*vec.p.x);
    }

    double y(double x)const{
        switch (O) {
        case Ox:{return -C/B;}break;
        case Oy:{return rand()-rand();}break;
        case Oxy:{return -A/B*x-C/B;}break;
        }

    }
    double x(double y)const{
        switch (O) {
        case Ox:{return rand()-rand();}break;
        case Oy:{return -C/A;}break;
        case Oxy:{return -B/A*y-C/A;}break;
        }

    }

    QVdouble xy(double t)const{
        switch (O) {
        case Ox:{return {-C/B,t};}break;
        case Oy:{return {t,-C/A};}break;
        case Oxy:{return {-B*t,A*t+y(0)};}break;
        }

    }

    lV2D vec ()const{ return lV2D(-B,A); }

    lV2D norm ()const{ return lV2D(A,B); }

    lP2D Mx ()const{return lP2D(-C/A,0);}
    lP2D My ()const{return lP2D(0,-C/B);}

    bool isPoint(lP2D p, double tol = 1e-6){
        return (fabs(A*p.x+B*p.y+C)<tol)?true:false;
    }

    QString toQStr() const{
        QString tmp = "line %1x + %2y + %3 = 0";
        return tmp.arg(A).arg(B).arg(C);
    }
};

////Плоскость 3D
//class lPlain : public lObj
//{
//    //Не обязательно конкретная плоскость связанная с СК, просто параллельная
//    enum PlainType{
//        Oxyz,
//        Oxy,
//        Oyz,
//        Oxz
//    };

//    enum CollinearType{
//        Cxyz,
//        Cx,
//        Cy,
//        Cz,
//        Cxy,
//        Cyz,
//        Cxz
//    };


//    PlainType O = Oxyz;
//    CollinearType CT = Cxyz;

//public:
//    double A = 0.0;
//    double B = 0.0;
//    double C = 0.0;
//    double D = 0.0;
//    lPlain(double _A, double _B, double _C, double _D): lObj(dim3),A(_A),B(_B),C(_C),D(_D){checkType();}
//    lPlain(lV3D normVector, lP3D point): lObj(dim3){
//        setWithNVP(normVector,point);
//        checkType();
//    }
//    lPlain(lV3D normFixedVector): lObj(dim3){
//        setWithNFixedV(normFixedVector);
//        checkType();
//    }
//    lPlain(lP3D p1, lP3D p2): lObj(dim3){
//        setWithNFixedV(lV3D(p1,p2));
//        checkType();
//    }
//    lPlain(lP3D p1, lP3D p2, lP3D p3): lObj(dim3){
//        setWithNFixedV(lV3D(p1,p2));
//        checkType();
//    }

//    lPlain(): lPlain(0.0,0.0,0.0,0.0){}
//    lPlain(const lPlain & Pl):lPlain(){
//        // Выполняем копирование значений
//        A     = Pl.A    ;
//        B     = Pl.B    ;
//        C     = Pl.C    ;
//    }
//    virtual ~lPlain() override{}

//    lPlain& operator= (const lPlain &Pl)
//    {
//        // Проверка на самоприсваивание
//        if (this == &Pl)
//            return *this;

//        // Выполняем копирование значений
//        lObj::operator = (Pl);
//        A     = Pl.A    ;
//        B     = Pl.B    ;
//        C     = Pl.C    ;
//        // Возвращаем текущий объект
//        return *this;
//    }

//    void checkType(){
//        if (fabs(A)<glTol) CT = Cx;
//        if (fabs(B)<glTol) CT = Cy;
//        if (fabs(C)<glTol) CT = Cz;
//        if (fabs(A)<glTol  && fabs(B)<glTol ) {
//            O = Oxy;
//            CT = Cxy;
//        }
//        if (fabs(B)<glTol  && fabs(C)<glTol ) {
//            O = Oyz;
//            CT = Cyz;
//        }
//        if (fabs(C)<glTol  && fabs(A)<glTol ) {
//            O = Oxz;
//            CT = Cxz;
//        }
//    }

//    void setWithNVP(lV3D vec, lP3D point){
//        double mn = (vec.y>0)?1:-1;
//        A = mn*vec.y;
//        B = mn*-vec.x;
//        assert(A != 0.0);
//        assert(B != 0.0);
//        if (A==0.0) {
//            O = Ox;
//        } else if (B==0.0){
//            O = Oy;
//        } else {
//            O = Oxy;
//        }
//        C = mn*(vec.x*point.y-vec.y*point.x);
//    }

//    void setWithNFixedV(lV3D vec){
//        assert(vec.isFixed());
//        double mn = (vec.y>0)?1:-1;
//        A = mn*vec.y;
//        B = mn*-vec.x;
//        assert(A != 0.0);
//        assert(B != 0.0);

//        if (A==0.0) {
//            O = Ox;
//        } else if (B==0.0){
//            O = Oy;
//        } else {
//            O = Oxy;
//        }
//        C = mn*(vec.x*vec.p.y-vec.y*vec.p.x);
//    }

//    void setWithVectors(lV3D V1, lV3D V2){
//        assert(vec.isFixed());
//        double mn = (vec.y>0)?1:-1;
//        A = mn*vec.y;
//        B = mn*-vec.x;
//        assert(A != 0.0);
//        assert(B != 0.0);

//        if (A==0.0) {
//            O = Ox;
//        } else if (B==0.0){
//            O = Oy;
//        } else {
//            O = Oxy;
//        }
//        C = mn*(vec.x*vec.p.y-vec.y*vec.p.x);
//    }

//    double y(double x)const{
//        switch (O) {
//        case Ox:{return -C/B;}break;
//        case Oy:{return rand()-rand();}break;
//        case Oxy:{return -A/B*x-C/B;}break;
//        }

//    }
//    double x(double y)const{
//        switch (O) {
//        case Ox:{return rand()-rand();}break;
//        case Oy:{return -C/A;}break;
//        case Oxy:{return -B/A*y-C/A;}break;
//        }

//    }

//    QVdouble xy(double t)const{
//        switch (O) {
//        case Ox:{return {-C/B,t};}break;
//        case Oy:{return {t,-C/A};}break;
//        case Oxy:{return {-B*t,A*t+y(0)};}break;
//        }

//    }

//    lV2D vec ()const{ return lV2D(-B,A); }

//    lV2D norm ()const{ return lV2D(A,B); }

//    lP2D Mx ()const{return lP2D(-C/A,0);}
//    lP2D My ()const{return lP2D(0,-C/B);}

//    bool isPoint(lP2D p, double tol = 1e-6){
//        return (fabs(A*p.x+B*p.y+C)<tol)?true:false;
//    }

//    QString toQStr() const{
//        QString tmp = "line %1x + %2y + %3 = 0";
//        return tmp.arg(A).arg(B).arg(C);
//    }
//};


#endif // LINEAR_OBJ_H
