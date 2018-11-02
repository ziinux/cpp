//============================================================================
// Name        : main.cc
// Author      : BADR EL HAFIDI badr@gatech.edu GTID:903243763
// Version     : 1
// Copyright   : GATECH ECE GRAD
// Description : main file to test Vector3 struct
//============================================================================

#include "src/vector3.h"
#include <iostream>

using namespace std;

int main()
{   
    float Ax=10.9, Ay=5.2, Az=2.7;
    float Bx=3.5, By=2.3, Bz=7.9;
    float Ex=0, Ey=2.3, Ez=7.9;
    float rhs=19871.31;
    
    Vector3 A(Ax,Ay,Az);
    Vector3 B(Bx,By,Bz);
    Vector3 E(Ex,Ey,Ez);
    Vector3 C;

    int counter=0;

    // Test operator+ Vector3 
    cout << "Testing operator+ Vector3 .." << endl;
    C = A + B;
    if((C.x==(Ax+Bx))&&(C.y==(Ay+By))&&(C.z==(Az+Bz))) 
    {
        cout << "\tTEST PASSED" << endl;
        counter++;
    } 
    else 
    {
        cout << "\tTEST FAILED" << endl;
    }   

    // Test operator- Vector3 
    cout << "Testing operator- Vector3 .." << endl;
    C = A - B;
    if((C.x==(Ax-Bx))&&(C.y==(Ay-By))&&(C.z==(Az-Bz))) 
    {
        cout << "\tTEST PASSED" << endl;
        counter++;
    } 
    else 
    {
        cout << "\tTEST FAILED" << endl;
    }   

    // Test operator* Vector3 
    cout << "Testing operator* Vector3 .." << endl;
    C = A * B;
    if((C.x==(Ax*Bx))&&(C.y==(Ay*By))&&(C.z==(Az*Bz))) 
    {
        cout << "\tTEST PASSED" << endl;
        counter++;
    } 
    else 
    {
        cout << "\tTEST FAILED" << endl;
    }   

    // Test operator/ Vector3
    cout << "Testing operator/ Vector3 .." << endl;
    C = A / B;
    if((C.x==(Ax/Bx))&&(C.y==(Ay/By))&&(C.z==(Az/Bz))) 
    {
        cout << "\tTEST PASSED" << endl;
        counter++;
    } 
    else 
    {
        cout << "\tTEST FAILED" << endl;
    }   

    // Test exception of operator/ Vector3
    try{
        cout << "Testing exception of operator/ Vector3 .." << endl;
        C = A / E;
        cout << "\tFAILED" << endl;
    } catch(const char* err) {
        cerr << "\tException catched: " << err << endl;
        cout << "\tTEST PASSED" << endl;
        counter++;
    }

    // Test operator+ float 
    cout << "Testing operator+ float .." << endl;
    C = A + rhs;
    if((C.x==(Ax+rhs))&&(C.y==(Ay+rhs))&&(C.z==(Az+rhs))) 
    {
        cout << "\tTEST PASSED" << endl;
        counter++;
    } 
    else 
    {
        cout << "\tTEST FAILED" << endl;
    }   


    // Test operator- float 
    cout << "Testing operator- float .." << endl;
    C = A - rhs;
    if((C.x==(Ax-rhs))&&(C.y==(Ay-rhs))&&(C.z==(Az-rhs))) 
    {
        cout << "\tTEST PASSED" << endl;
        counter++;
    } 
    else 
    {
        cout << "\tTEST FAILED" << endl;
    }   

    // Test operator* float 
    cout << "Testing operator* float .." << endl;
    C = A * rhs;
    if((C.x==(Ax*rhs))&&(C.y==(Ay*rhs))&&(C.z==(Az*rhs))) 
    {
        cout << "\tTEST PASSED" << endl;
        counter++;
    } 
    else 
    {
        cout << "\tTEST FAILED" << endl;
    }   

    // Test operator/ float
    cout << "Testing operator/ float .." << endl;
    C = A / rhs;
    if((C.x==(Ax/rhs))&&(C.y==(Ay/rhs))&&(C.z==(Az/rhs))) 
    {
        cout << "\tTEST PASSED" << endl;
        counter++;
    } 
    else 
    {
        cout << "\tTEST FAILED" << endl;
    }   

    // Test exception of operator/ float
    try{
        cout << "Testing exception of operator/ float .." << endl;
        C = A / 0.0;
        cout << "\tFAILED" << endl;
    } catch(const char* err) {
        cerr << "\tException catched: " << err << endl;
        cout << "\tTEST PASSED" << endl;
        counter++;
    }

    // Test operator| 
    cout << "Testing operator|  .." << endl;
    float dot = A | B;
    if( dot == (Ax*Bx + Ay*By + Az*Bz) ) 
    {
        cout << "\tTEST PASSED" << endl;
        counter++;
    } 
    else 
    {
        cout << "\tTEST FAILED" << endl;
    }   

    // Test operator^ 
    cout << "Testing operator^ .." << endl;
    C = A ^ B;
    if( (C.x==(Ay*Bz-By*Az)) && (C.y==(Az*Bx-Bz*Ax)) && (C.z==(Ax*By-Bx*Ay)) ) 
    {
        cout << "\tTEST PASSED" << endl;
        counter++;
    } 
    else 
    {
        cout << "\tTEST FAILED" << endl;
    }   

    // Test operator+= 
    cout << "Testing operator+= .." << endl;
    A += B;
    if( (A.x==(Ax+Bx)) && (A.y==(Ay+By)) && (A.z==(Az+Bz)) ) 
    {
        cout << "\tTEST PASSED" << endl;
        counter++;
    } 
    else 
    {
        cout << "\tTEST FAILED" << endl;
    }
    A = Vector3(Ax,Ay,Az);

    // Test operator-= 
    cout << "Testing operator-= .." << endl;
    A -= B;
    if( (A.x==(Ax-Bx)) && (A.y==(Ay-By)) && (A.z==(Az-Bz)) ) 
    {
        cout << "\tTEST PASSED" << endl;
        counter++;
    } 
    else 
    {
        cout << "\tTEST FAILED" << endl;
    }
    A = Vector3(Ax,Ay,Az);

    // Test operator*= 
    cout << "Testing operator*= .." << endl;
    A *= B;
    if( (A.x==(Ax*Bx)) && (A.y==(Ay*By)) && (A.z==(Az*Bz)) ) 
    {
        cout << "\tTEST PASSED" << endl;
        counter++;
    } 
    else 
    {
        cout << "\tTEST FAILED" << endl;
    }
    A = Vector3(Ax,Ay,Az);

    // Test operator/= 
    cout << "Testing operator/= .." << endl;
    A /= B;
    if( (A.x==(Ax/Bx)) && (A.y==(Ay/By)) && (A.z==(Az/Bz)) ) 
    {
        cout << "\tTEST PASSED" << endl;
        counter++;
    } 
    else 
    {
        cout << "\tTEST FAILED" << endl;
    }   
    A = Vector3(Ax,Ay,Az);

    // Test exception of operator/=
    try{
        cout << "Testing exception of operator/= .." << endl;
        A /= E;
        cout << "\tFAILED" << endl;
    } catch(const char* err) {
        cerr << "\tException catched: " << err << endl;
        cout << "\tTEST PASSED" << endl;
        counter++;
    }
    A = Vector3(Ax,Ay,Az);

    // Test operator++ 
    cout << "Testing Postfix operator++ .." << endl;
    C = A++;

    if( (A.x==Az) && (A.y==Ax) && (A.z==Ay) && (C.x==Ax) && (C.y==Ay)  && (C.z==Az)) 
    {
        cout << "\tTEST PASSED" << endl;
        counter++;
    } 
    else 
    {
        cout << "\tTEST FAILED" << endl;
    }   
    A = Vector3(Ax,Ay,Az);

    // Test ++operator 
    cout << "Testing Prefix operator++ .." << endl;
    C = ++A;

    if( (A.x==Az) && (A.y==Ax) && (A.z==Ay) && (C.x==Az) && (C.y==Ax)  && (C.z==Ay)) 
    {
        cout << "\tTEST PASSED" << endl;
        counter++;
    } 
    else 
    {
        cout << "\tTEST FAILED" << endl;
    }   
    A = Vector3(Ax,Ay,Az);

    // Test operator-- 
    cout << "Testing Postfix operator-- .." << endl;
    C = A--;

    if( (A.x==Ay) && (A.y==Az) && (A.z==Ax) && (C.x==Ax) && (C.y==Ay)  && (C.z==Az)) 
    {
        cout << "\tTEST PASSED" << endl;
        counter++;
    } 
    else 
    {
        cout << "\tTEST FAILED" << endl;
    }   
    A = Vector3(Ax,Ay,Az);

    // Test --operator 
    cout << "Testing Prefix operator-- .." << endl;
    C = --A;

    if( (A.x==Ay) && (A.y==Az) && (A.z==Ax) && (C.x==Ay) && (C.y==Az)  && (C.z==Ax)) 
    {
        cout << "\tTEST PASSED" << endl;
        counter++;
    } 
    else 
    {
        cout << "\tTEST FAILED" << endl;
    }   
    A = Vector3(Ax,Ay,Az);

    // Test operator== 
    cout << "Testing operator== .." << endl;
    C = Vector3(Ax,Ay,Az);

    if( (A==C) && !(A==B) ) 
    {
        cout << "\tTEST PASSED" << endl;
        counter++;
    } 
    else 
    {
        cout << "\tTEST FAILED" << endl;
    }   
    A = Vector3(Ax,Ay,Az);

    // Test operator!= 
    cout << "Testing operator!= .." << endl;
    C = Vector3(Ax,Ay,Az);

    if( (A!=B) && !(A!=C) ) 
    {
        cout << "\tTEST PASSED" << endl;
        counter++;
    } 
    else 
    {
        cout << "\tTEST FAILED" << endl;
    }   
    A = Vector3(Ax,Ay,Az);

    cout << "------------------------------------------------------" << endl;
    cout << "TEST PASSED: " << counter << "/23" << endl;
    return 0;
}
