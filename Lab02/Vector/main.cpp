﻿#include <iostream>

#include "../Vector_Container/Vector/Vector.hpp"

using namespace std;

int main()
{
    Vector<double> initializing = { 5, 2, 15 };
    const Vector<int> constVect = { 0, 1, 2, 3, 4 };
    Vector<float> lenExample(3);
    Vector<double> lenFillExample(3, 6.66, 7.5, 8.6);
    Vector<double> emptyVector(0);

    cout << "---------------Vectors Construction-------------" << endl;
    cout << "  Vector with initialization: " << initializing << endl;
    cout << "  Vector with a given length " << lenExample << endl;
    cout << "  Vector of a given length with initialization: " << lenFillExample << std::endl;

    cout << "Empty vector: " << emptyVector << endl;

    Vector<double> operVecF = { 4, 2, 4 };
    Vector<double> operVecS = { 3, 1, 5 };

    cout << "---------------Vectors checks-------------" << endl;
    cout << "   Normalization of the vector: " << operVecS << "=>" << operVecS.getSingle() << endl;
    cout << "   Size vector: " << initializing << " => " << initializing.getSize() << endl;
    cout << "   Vector length: " << initializing << " => " << initializing.getLength() << endl;
    cout << "   Is the vector zero: " << initializing << " => " << initializing.isZero() << endl;
    cout << "   Is a single vector: " << initializing << " => " << initializing.isSingle() << endl;

    cout << "---------------Vectors gets and sets-------------" << endl;
    cout << "   Setting the second element to 10: " << initializing.setItem(1, 10) << endl;
    cout << "   The second element of the vector: " << initializing.getItem(1) << endl;
    cout << "   The second element of the constant vector: " << constVect.getItem(1) << endl;

    cout << "---------------Vectors operation-------------" << endl;
    cout << "1. Sum Vectors:" << endl;
    cout << "   Vectors +: " << operVecF << " + " << operVecS << " = " << operVecF + operVecS << endl;
    cout << "   Vectors +: " << operVecF << ".sum(" << operVecS << ") = " << operVecF.sum(operVecS) << endl;
    cout << "   Vectors +=: " << operVecF << " += " << operVecS << " => " << (operVecF += operVecS) << endl;
    cout << "   Vectors +=: " << operVecF << ".sumEqual(" << operVecS << ") => " << operVecF.sumEqual(operVecS) << endl;

    operVecF = { 4, 2, 4 };

    cout << "   Sum vector and number:" << endl;
    int sumNumber = 10;
    cout << "   Vectors +: " << operVecF << " + " << sumNumber << " = " << operVecF + sumNumber << endl;
    cout << "   Vectors +: " << operVecF << ".sumNum(" << sumNumber << ") = " << operVecF.sumNum(sumNumber) << endl;
    cout << "   Vectors +=: " << operVecF << " += " << sumNumber << " => " << (operVecF += sumNumber) << endl;
    cout << "   Vectors +=: " << operVecF << ".sumNumEqual(" << sumNumber << ") => " << operVecF.sumNumEqual(sumNumber) << endl;

    operVecF = { 4, 2, 4 };

    cout << "2. Sub Vectors:" << endl;
    cout << "   Vectors -: " << operVecF << " - " << operVecS << " = " << operVecF - operVecS << endl;
    cout << "   Vectors -: " << operVecF << ".sub(" << operVecS << ") = " << operVecF.sub(operVecS) << endl;
    cout << "   Vectors -=: " << operVecF << " -= " << operVecS << " => " << (operVecF -= operVecS) << endl;
    cout << "   Vectors -=: " << operVecF << ".subEqual(" << operVecS << ") => " << operVecF.subEqual(operVecS) << endl;

    cout << "   Sub vector and number:" << endl;
    cout << "   Vectors -: " << operVecF << " - " << sumNumber << " = " << operVecF - sumNumber << endl;
    cout << "   Vectors -: " << operVecF << ".subNum(" << sumNumber << ") = " << operVecF.subNum(sumNumber) << endl;
    cout << "   Vectors -=: " << operVecF << " -= " << sumNumber << " => " << (operVecF -= sumNumber) << endl;
    cout << "   Vectors -=: " << operVecF << ".subNumEqual(" << sumNumber << ") => " << operVecF.sumNumEqual(sumNumber) << endl;

    operVecF = { 4, 2, 4 };

    cout << "3. Scalar Multy:" << endl;
    cout << "   Vectors * : " << operVecF << " * " << operVecS << " = " << operVecF * operVecS << endl;
    cout << "   Vectors * : " << operVecF << ".scalarMul(" << operVecS << ") = " << operVecF.scalarMul(operVecS) << endl;
    cout << "   Vectors *=: " << operVecF << " *= " << operVecS << " => " << (operVecF *= operVecS) << endl;
    cout << "   Vectors *=: " << operVecF << ".scalarMulEqual(" << operVecS << ") => " << operVecF.scalarMulEqual(operVecS) << endl;

    operVecF = { 4, 2, 4 };

    cout << "4. Multy vector and number:" << endl;
    int multyNumber = 2;
    cout << "   Vectors *: " << operVecF << " * " << multyNumber << " = " << operVecF * multyNumber << endl;
    cout << "   Vectors *: " << operVecF << ".mulNum(" << multyNumber << ") = " << operVecF.mulNum(multyNumber) << endl;
    cout << "   Vectors *=: " << operVecF << " *= " << multyNumber << " => " << (operVecF *= multyNumber) << endl;
    cout << "   Vectors *=: " << operVecF << ".mulNumEqual(" << multyNumber << ") => " << operVecF.mulNumEqual(multyNumber) << endl;

    operVecF = { 4, 2, 4 };

    cout << "5. Vector Multy:" << endl;
    cout << "   Vectors &: " << operVecF << " & " << operVecS << " = " << (operVecF & operVecS) << endl;
    cout << "   Vectors &: " << operVecF << ".vectorMul(" << operVecS << ") = " << operVecF.vectorMul(operVecS) << endl;
    cout << "   Vectors &=: " << operVecF << " &= " << operVecS << " => " << (operVecF &= operVecS) << endl;
    cout << "   Vectors &=: " << operVecF << ".vectorMulEqual(" << operVecS << ") => " << operVecF.vectorMulEqual(operVecS) << endl;

    operVecF = { 4, 2, 4 };

    cout << "6. Multy Elements Vectors:" << endl;
    cout << "   Vectors ^: " << operVecF << " ^ " << operVecS << " = " << (operVecF ^ operVecS) << endl;
    cout << "   Vectors ^: " << operVecF << ".mulElems(" << operVecS << ") = " << operVecF.mulElems(operVecS) << endl;
    cout << "   Vectors ^=: " << operVecF << " ^= " << operVecS << " => " << (operVecF ^= operVecS) << endl;
    cout << "   Vectors ^=: " << operVecF << ".mulElemsEqual(" << operVecS << ") => " << operVecF.mulElemsEqual(operVecS) << endl;

    operVecF = { 4, 2, 4 };

    cout << "7. Div vector and number:" << endl;
    int divNum = 2;
    cout << "   Vectors /: " << operVecF << " / " << divNum << " = " << operVecF / divNum << endl;
    cout << "   Vectors /: " << operVecF << ".divNum(" << divNum << ") = " << operVecF.divNum(divNum) << endl;
    cout << "   Vectors /=: " << operVecF << " /= " << divNum << " => " << (operVecF /= divNum) << endl;
    cout << "   Vectors /=: " << operVecF << ".divNumEqual(" << divNum << ") => " << operVecF.divNumEqual(divNum) << endl;

    operVecF = { 4, 2, 4 };

    cout << "8. Div vectorsr:" << endl;

    cout << "   Vectors /: " << operVecF << " / " << operVecS << " = " << operVecF / operVecS << endl;
    cout << "   Vectors /: " << operVecF << ".div(" << operVecS << ") = " << operVecF.div(operVecS) << endl;
    cout << "   Vectors /=: " << operVecF << " /= " << operVecS << " => " << (operVecF /= operVecS) << endl;
    cout << "   Vectors /=: " << operVecF << ".divEqual(" << operVecS << ") => " << operVecF.divEqual(operVecS) << endl;

    cout << "---------------Vectors checks-------------" << endl;
    Vector<float> orthVecF = { 1, 0, 0 };

    cout << "---------------Vectors Errors-------------" << endl;
    try
    {
        orthVecF.getItem(-1);
    }
    catch (IndexVectorError& er) 
    {
        cout << "Find error:" << er.what() << endl;
    }

    return 0;
}