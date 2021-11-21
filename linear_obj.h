#ifndef LINEAR_OBJ_H
#define LINEAR_OBJ_H

#include "math.h"


typedef double array_xy[2];
typedef double* ptrarray_xy[2];
typedef double array_xyz[3];
typedef double* ptrarray_xyz[3];


class lObj
{
public:
    lObj() {}

    enum Axes_type{
        x_ax = 0,
        y_ax,
        z_ax,
        LAST_ax,
    };

    virtual void move_on(double on_x, double on_y, double on_z) = 0;
    virtual void move_to(double nx, double ny, double nz) = 0;

    virtual ~lObj(){}
};

class lP2d : public lObj
{
public:
    lP2d(double _x, double _y) { sP(_x, _y); }
    lP2d(double C) : lP2d(C,C) {}
    lP2d() : lP2d(0.0){}

    lP2d(const lP2d & P){
        // Выполняем копирование значений
        *(this->mData) = *(P.mData);
    }

    lP2d& operator= (const lP2d &P)
    {
        // Проверка на самоприсваивание
        if (this == &P)
            return *this;

        // Выполняем копирование значений
        *(this->mData) = *(P.mData);
        // Возвращаем текущий объект
        return *this;
    }

    friend lP2d operator-(const lP2d &P1, const lP2d &P2){
        return lP2d (P1.x-P2.x,P1.y-P2.y);
    }

    friend lP2d operator+(const lP2d &P1, const lP2d &P2){
        return lP2d (P1.x+P2.x,P1.y+P2.y);
    }

    friend lP2d operator*(const lP2d &P1, const double &num){
        return lP2d (P1.x*num,P1.y*num);
    }

    friend lP2d operator*=(const lP2d &P1, const double &num){
        return lP2d (P1.x*num,P1.y*num);
    }

    virtual ~lP2d() override{}

    double * data() { return *mData;}
    const double * data() const { return *mData; }
    double & operator[](int i) { return *mData[i]; }
    double operator[](int i) const { return *mData[i]; }

//    template<typename T>
    void move_on(double on_x, double on_y, double on_z)   override {
        _CRT_UNUSED(on_z);
        sP(this->x+on_x,this->y+on_y);
    }
    void move_to(double _x, double _y, double _z)override {
        _CRT_UNUSED(_z);
        sP(_x,_y);
    }

    double x = 0.0;
    double y = 0.0;

protected:
    void sP(double nx, double ny){
        this->x = nx;
        this->y = ny;
    }

private:

    ptrarray_xy mData = {&this->x,&this->y};

};

class lP3d : public lObj
{
public:
    lP3d(double _x, double _y, double _z) { sP(_x, _y, _z); }
    lP3d(double C) : lP3d(C,C,C){}
    lP3d() : lP3d(0.0) {}

    lP3d(const lP3d & P){
        // Выполняем копирование значений
        *(this->mData) = *(P.mData);
    }

    lP3d& operator= (const lP3d &P)
    {
        // Проверка на самоприсваивание
        if (this == &P)
            return *this;

        // Выполняем копирование значений
        *(this->mData) = *(P.mData);
        // Возвращаем текущий объект
        return *this;
    }

    friend lP3d operator-(const lP3d &P1, const lP3d &P2){
        return lP3d (P1.x-P2.x,P1.y-P2.y,P1.z-P2.z);
    }

    friend lP3d operator+(const lP3d &P1, const lP3d &P2){
        return lP3d (P1.x+P2.x,P1.y+P2.y,P1.z+P2.z);
    }

    friend lP3d operator*(const lP3d &P1, const double &num){
        return lP3d (P1.x*num,P1.y*num,P1.z*num);
    }

    friend lP3d operator*=(const lP3d &P1, const double &num){
        return lP3d (P1.x*num,P1.y*num,P1.z*num);
    }

    virtual ~lP3d() override{}

    double * data() { return *mData;}
    const double * data() const { return *mData; }
    double & operator[](int i) { return *mData[i]; }
    double operator[](int i) const { return *mData[i]; }

//    template<typename T>
    void move_on(double on_x, double on_y, double on_z)   override {
        sP(this->x+on_x,this->y+on_y,this->z+on_z);
    }
    void move_to(double _x, double _y, double _z) override {
        sP(_x,_y,_z);
    }

    double x = 0.0;
    double y = 0.0;
    double z = 0.0;

protected:
    void sP(double nx, double ny, double nz){
        this->x = nx;
        this->y = ny;
        this->z = nz;
    }



private:

    ptrarray_xyz mData = {&this->x,&this->y,&this->z};

};

class l_P_array : public lObj
{
public:
    l_P_array () : lObj() {}
    l_P_array (double nx, double ny, double nz) : lObj(),Pb(nx,ny,nz){}
    l_P_array (lP3d P) : lObj(),Pb(P){}



    l_P_array(const l_P_array & P_a){
        // Выполняем копирование значений
        this->Pb = P_a.Pb;
    }

    l_P_array& operator= (const l_P_array &P_a)
    {
        // Проверка на самоприсваивание
        if (this == &P_a)
            return *this;

        // Выполняем копирование значений
        this->Pb = P_a.Pb;
        // Возвращаем текущий объект
        return *this;
    }

    virtual void move_on(double on_x, double on_y, double on_z) override {
        Pb.move_on(on_x,on_y,on_z);
    }
    virtual void move_to(double nx, double ny, double nz)override {
        Pb.move_to(nx,ny,nz);
    }

    virtual ~l_P_array() override{}

    virtual double len() = 0;
    virtual void resize(double ratio) = 0;
    virtual void turn(int ax_type, double angle) = 0;
    void sPb(lP3d P){this->Pb = P;}
    lP3d gPb(){return this->Pb;}
protected:
private:
    lP3d Pb = lP3d(0.0); // Хранит положение объекта относительно начальной точки

};

//___Отрезок выходящий из базовой точки в некоторую т. Pe
class l_BLine : public  l_P_array
{
public:
    l_BLine () {}
    l_BLine (lP3d Pb) : l_P_array (Pb) {}
    l_BLine (lP3d Pb,lP3d P_external) : l_BLine(Pb) {
        this->Pe = P_external;
    }

    virtual ~l_BLine() override{}

    virtual double len() override{
        double sum2 = 0;
        for (int i = 0; i < lObj::LAST_ax; ++i) {
            sum2 += pow(Pe[i],2);
        }
        return sqrt(sum2);
    }
    virtual void resize(double ratio) override{
         Pe *= ratio; //Почему-то работает просто присвоение!!!

    }
    void turn(int ax_type, double angle)override{

    }

protected:
    lP3d Pe; // хранит координату дополнительной точки
private:




};

class l_Line : public  l_P_array
{
public:
    l_Line () {}
    l_Line (lP3d Pb) : l_P_array (Pb) {}


    virtual ~l_Line() override{}

    void resize(double size);
    void turn(int ax_type, double angle);
protected:
    lP3d P1,P2;
private:




};

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
