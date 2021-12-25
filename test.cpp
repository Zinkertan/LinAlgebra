#include "test.h"

QString test::test_mAlg()
{
    mMatrix A1_({{-1,-2,1},{5,9,-8}});
    mMatrix B1_({{10,-25,98},{3,0,-14}});
    QString out = A1_.toQStr()+ "\n+\n"+
            B1_.toQStr()+ "\n=\n" +
            (A1_+B1_).toQStr() + "\n\n";
    mMatrix A2_({{-1,-2,7},{4,9,0}});
    out += " 3*\n"+A2_.toQStr()+ "\n=\n"+( 3*A2_).toQStr()+ "\n\n";
    out += "-5*\n"+A2_.toQStr()+ "\n=\n"+(-5*A2_).toQStr()+ "\n\n";

    mMatrix A3_({{-1, 2, -3, 0},
                 { 5, 4, -2, 1},
                 {-8,11,-10,-5}});
    mMatrix B3_({{-9, 3},
                 { 6,20},
                 { 7, 0},
                 {12,-4}});

    out +=  A3_.toQStr()+ "\n*\n"+
            B3_.toQStr()+ "\n=\n" +
            (A3_*B3_).toQStr()+ "\n\n";

    mMatrix A4_({{5,8,-4},
                 {6,9,-5},
                 {4,7,-3}});

    out +=  A4_.toQStr()+ " T\n=\n"+
            (A4_.T()).toQStr()+ "\n\n";

    mMatrix A5_({{2,5,7},{6,3,4},{5,-2,-3}});

    out +=  A5_.toQStr()+ " det = "+
            QString::number(A5_.det())+ "\n\n";


    out +=  A5_.toQStr()+ "\n MinorMatr = \n"+
            A5_.MMatr().toQStr()+ "\n\n";

    out +=  A5_.toQStr()+ "\n AlgDopMatr = \n"+
            A5_.adMatr().toQStr()+ "\n\n";


    out +=  A5_.toQStr()+ "\n AlgDopMatr T = \n"+
            A5_.adMatr().T().toQStr()+ "\n\n";


    out +=  A5_.toQStr()+ "\n ^-1 = \n"+
            (A5_.adMatr().T()*(1.0/A5_.det())).toQStr()+ "\n\n";

    out +=  A5_.toQStr()+ "\n*\n"+
            (A5_.adMatr().T()*(1.0/A5_.det())).toQStr()+ "\n=\n" +
            (A5_*(A5_.adMatr().T()*(1.0/A5_.det()))).toQStr()+ "\n\n";

//    mVector v({2,-3,1},mvtCol);
//    auto m00 = c.Minor(0,0);
//    double det = c.det();
//    double detB = B.det();
//    mMatrix min = c.MMatr();
//    mMatrix ad  = c.adMatr();
//    mMatrix obr = c.inv();
//    auto res = obr*c;
//    bool us = res.isE();

    mMatrix A6_({{3,2,1},{2,3,1},{2,1,3}});

    out +=  A6_.toQStr()+ " det = "+
            QString::number(A5_.det())+ "\n\n";


    out +=  A6_.toQStr()+ "\n MinorMatr = \n"+
            A6_.MMatr().toQStr()+ "\n\n";

    out +=  A6_.toQStr()+ "\n AlgDopMatr = \n"+
            A6_.adMatr().toQStr()+ "\n\n";


    out +=  A6_.toQStr()+ "\n AlgDopMatr T = \n"+
            A6_.adMatr().T().toQStr()+ "\n\n";


    out +=  A6_.toQStr()+ "\n ^-1 = \n"+
            (A6_.inv()).toQStr()+ "\n\n";


    mVector V6_({5,-1,4},mvtCol);
    auto X = mMatrix::solve(A6_,V6_);
//    mMatrix A2({{4,8},{6,2}});
    out +=  QString("AX=B\n A=\n%1\nB=\n%2\nX=\n%3\n\n").
            arg(A6_.toQStr()).
            arg(V6_.toQStr()).
            arg(X.toQStr());

//    auto X = A1.solve(A1,A2);

    return out;
}

QString test::test_anGeom()
{
    QString out = "";
    lP2D A (2.0,1.0);
    lP2D B (-2.0,3.0);
    out += QString("A(%1,%2)\n")
            .arg(A.x)
            .arg(A.y);
    out += QString("B(%1,%2)\n")
            .arg(B.x)
            .arg(B.y);

    lV2D a (A,B);

    out += QString("AB(a)(%1,%2), len = %3\n")
            .arg(a.x)
            .arg(a.y)
            .arg(a.len());

    return out;


}
