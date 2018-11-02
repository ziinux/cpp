//============================================================================
// Name        : vector3.cc
// Author      : BADR EL HAFIDI badr@gatech.edu GTID:903243763
// Version     : 1
// Copyright   : GATECH ECE GRAD
// Description : Implementation for Vector3 struct
//============================================================================

#include "vector3.h"

Vector3::Vector3(float xyz){
    x = xyz;
    y = xyz;
    z = xyz;
}

Vector3::Vector3(float x_, float y_, float z_){
    x = x_;
    y = y_;
    z = z_;
}

Vector3 Vector3::operator+ (const Vector3& rhs) const 
{
    return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
}

Vector3 Vector3::operator- (const Vector3& rhs) const
{
    return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
}

Vector3 Vector3::operator* (const Vector3& rhs) const
{
    return Vector3(x * rhs.x, y * rhs.y, z * rhs.z);
}

Vector3 Vector3::operator/ (const Vector3& rhs) const
{
    if((rhs.x == 0.0) || (rhs.y == 0.0) || (rhs.z == 0.0))
    {
        throw "Division by zero condition!";        
    }
    return Vector3(x / rhs.x, y / rhs.y, z / rhs.z);
}

Vector3 Vector3::operator+ (float rhs) const
{
    return Vector3(x + rhs, y + rhs, z + rhs);
}

Vector3 Vector3::operator- (float rhs) const
{
    return Vector3(x - rhs, y - rhs, z - rhs);
}

Vector3 Vector3::operator* (float rhs) const
{
    return Vector3(x * rhs, y * rhs, z * rhs);
}

Vector3 Vector3::operator/ (float rhs) const
{
    if(rhs == 0.0)
    {
        throw "Division by zero condition!";        
    }
    return Vector3(x / rhs, y / rhs, z / rhs);
}

float Vector3::operator| (const Vector3& rhs) const
{
    return (x*rhs.x + y*rhs.y + z*rhs.z);
}

Vector3 Vector3::operator^ (const Vector3& rhs) const 
{
    return Vector3(y*rhs.z - z*rhs.y, z*rhs.x - x*rhs.z, x*rhs.y - y*rhs.x);
}

Vector3& Vector3::operator+= (const Vector3& rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;

    return *this;
}

Vector3& Vector3::operator-= (const Vector3& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;

    return *this;
}

Vector3& Vector3::operator*= (const Vector3& rhs)
{
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;

    return *this;
}

Vector3& Vector3::operator/= (const Vector3& rhs)
{
    if((rhs.x == 0.0) || (rhs.y == 0.0) || (rhs.z == 0.0))
    {
        throw "Division by zero condition!";        
    }

    x /= rhs.x;
    y /= rhs.y;
    z /= rhs.z;

    return *this;
}

Vector3& Vector3::operator++()
{
    float zOld = z;
    z=y;
    y=x;
    x=zOld;
    return *this;
}

Vector3 Vector3::operator++(int __unused)
{
   Vector3 tmp = *this;  
   ++*this;  
   return tmp;
}

Vector3& Vector3::operator--() 
{
    float xOld = x;
    x=y;  
    y=z;
    z=xOld;
    return *this;
}

Vector3 Vector3::operator--(int __unused) 
{
   Vector3 tmp = *this;  
   --*this;  
   return tmp;
}

bool Vector3::operator==(const Vector3& rhs) const
{
    if((x==rhs.x)&&(y==rhs.y)&&(z==rhs.z))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Vector3::operator!=(const Vector3& rhs) const
{
    if((x!=rhs.x)&&(y!=rhs.y)&&(z!=rhs.z))
    {
        return true;
    }
    else
    {
        return false;
    }
}




