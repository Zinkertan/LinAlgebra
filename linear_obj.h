#ifndef LINEAR_OBJ_H
#define LINEAR_OBJ_H

#include "math.h"


typedef double array_xy[2];
typedef double* ptrarray_xy[2];
typedef double array_xyz[3];
typedef double* ptrarray_xyz[3];

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
    lP2D p = lP2D(0.0,0.0);
    double x = 0.0;
    double y = 0.0;
    lV2D(double _x, double _y): lObj(dim2),fixed(false),x(_x),y(_y){}

    lV2D(double _x, double _y, lP2D _p): lObj(dim2),fixed(false),x(_x),y(_y),p(_p){}

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

    void setP1P2(lP2D p1, lP2D p2, bool isToFix = true){
        x = p2.x - p1.x;
        y = p2.y - p1.y;
        fixed = isToFix;
        if (isToFix) {
            p = p1;
        }
    }

    void setPoint(lP2D p1){
        p = p1;
    }

    static bool isСollinear(const lV2D &v1, const lV2D &v2, double tol = 1e-6){
        return fabs(v1.x/v2.x-v1.y/v2.y)<tol?true:false;
    }

    bool isСollinear(const lV2D &v2, double tol = 1e-6) const{
        return isСollinear(*this,v2,tol);
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


    double * data() { return *mData;}
    const double * data() const { return *mData; }
    double & operator[](int i) { return *mData[i]; }
    double operator[](int i) const { return *mData[i]; }

private:
    ptrarray_xy mData = {&this->x,&this->y};

};

//Вектор 3D
class lV3D : public lObj
{
    bool fixed = false;

public:
    lP3D p = lP3D(0.0,0.0,0.0);
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    lV3D(double _x, double _y, double _z): lObj(dim3),fixed(false),x(_x),y(_y),z(_z){}

    lV3D(double _x, double _y, double _z, lP3D _p): lObj(dim3),fixed(true),x(_x),y(_y),z(_z),p(_p){}

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


    friend lV3D operator+(const lV3D &V1, const lV3D &V2){
        return lV3D (V1.x+V2.x,V1.y+V2.y,V1.z+V2.z);
    }

    friend lV3D operator-(const lV3D &V1, const lV3D &V2){
        return V1+(-1.0*V2);
    }

    friend lV3D operator*(const lV3D &V1, const double &num){
        return lV3D (V1.x*num,V1.y*num,V1.z*num);
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

    void setP1P2(lP3D p1, lP3D p2, bool isToFix = true){
        x = p2.x - p1.x;
        y = p2.y - p1.y;
        z = p2.z - p1.z;
        fixed = isToFix;
        if (isToFix) {
            p = p1;
        }
    }

    void setPoint(lP3D p1){
        p = p1;
    }

    static bool isСollinear(const lV3D &v1, const lV3D &v2, double tol = 1e-6){
        double  o_x = v1.x/v2.x,
                o_y = v1.y/v2.y,
                o_z = v1.z/v2.z;
        return fabs(o_x-o_y)<tol && fabs(o_y-o_z)<tol && fabs(o_z-o_x)<tol?true:false;
    }

    bool isСollinear(const lV3D &v2, double tol = 1e-6) const{
        return isСollinear(*this,v2,tol);
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

    double * data() { return *mData;}
    const double * data() const { return *mData; }
    double & operator[](int i) { return *mData[i]; }
    double operator[](int i) const { return *mData[i]; }

private:
    ptrarray_xyz mData = {&this->x,&this->y,&this->z};

};



//___Отрезок выходящий из базовой точки в некоторую т. Pe
//class l_BLine : public  lObj
//{
//public:
//    l_BLine () {}
//    l_BLine (lP3d Pb) : l_P_array (Pb) {}
//    l_BLine (lP3d Pb,lP3d P_external) : l_BLine(Pb) {
//        this->Pe = P_external;
//    }

//    virtual ~l_BLine() override{}

//    virtual double len() override{
//        double sum2 = 0;
//        for (int i = 0; i < lObj::LAST_ax; ++i) {
//            sum2 += pow(Pe[i],2);
//        }
//        return sqrt(sum2);
//    }
//    virtual void resize(double ratio) override{
//         Pe *= ratio; //Почему-то работает просто присвоение!!!

//    }
//    void turn(int ax_type, double angle)override{

//    }

//protected:
//    lP3d Pe; // хранит координату дополнительной точки
//private:




//};

//class l_Line : public  l_P_array
//{
//public:
//    l_Line () {}
//    l_Line (lP3d Pb) : l_P_array (Pb) {}


//    virtual ~l_Line() override{}

//    void resize(double size);
//    void turn(int ax_type, double angle);
//protected:
//    lP3d P1,P2;
//private:




//};

//class l_Vector : public  l_line
//{
//public:
//    l_Vector () {}
//    l_Vector (double lx,double ly,double lz): P1(), P2(lx,ly,lz){

//    }

//    void move_on(double on_x, double on_y, double on_z)   override {

//    }
//    void move_to(double nx, double ny, double nz)override {

//    }
//    void resize(double size) override {}
//    void turn(int ax_type, double angle) override {}

//protected:



//private:

//};



class linear_obj
{
public:
    linear_obj();
};

#endif // LINEAR_OBJ_H
