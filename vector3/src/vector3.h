//============================================================================
// Name        : vector3.h
// Author      : BADR EL HAFIDI badr@gatech.edu GTID:903243763
// Version     : 1
// Copyright   : GATECH ECE GRAD
// Description : Header for Vector3 struct
//============================================================================

struct Vector3 {
    float x;
    float y;
    float z;

    Vector3() = default;
    Vector3(float xyz);                     //set x, y, and z to xyz
    Vector3(float x, float y, float z);     //default constructor

    Vector3 operator+ (const Vector3& rhs) const;  //component-wise add
    Vector3 operator- (const Vector3& rhs) const;  //component-wise subtract
    Vector3 operator* (const Vector3& rhs) const;  //component-wise multiplication
    Vector3 operator/ (const Vector3& rhs) const;  //component-wise division

    Vector3 operator+ (float rhs) const;           //add rhs to each component
    Vector3 operator- (float rhs) const;           //subtract rhs from each component 
    Vector3 operator* (float rhs) const;           //multiply each component by rhs
    Vector3 operator/ (float rhs) const;           //divide each component by rhs

    float operator| (const Vector3& rhs) const;    // dot product
    Vector3 operator^ (const Vector3& rhs) const;  // cross product

    Vector3& operator+=(const Vector3& rhs);       //component-wise add
    Vector3& operator-=(const Vector3& rhs);       //component-wise subtract
    Vector3& operator*=(const Vector3& rhs);       //component-wise multiplication
    Vector3& operator/=(const Vector3& rhs);       //component-wise division
    
    Vector3& operator++();                         //rotate xyz to the right - Prefix increment operator
    Vector3 operator++(int __unused);              //rotate xyz to the right - Postfix increment operator
    Vector3& operator--();                         //rotate xyz to the left - Prefix decrement operator
    Vector3 operator--(int __unused);              //rotate xyz to the left - Postfix decrement operator

    bool operator==(const Vector3& rhs) const;           //component-wise equality
    bool operator!=(const Vector3& rhs) const;           //component-wise inequality

};
