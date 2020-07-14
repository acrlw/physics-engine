#ifndef ALMATH_H
#define ALMATH_H

#include <math.h>
#include <qmath.h>
#include <stddef.h>
#include <assert.h>
#include <float.h>


///Fast Inverse Square Root Algorithm From Quake III
static inline float alFastInvSqrt(float x)
{
    float xhalf = 0.5f*x;
    int i = *(int*)&x; // get bits for floating VALUE
    i = 0x5f375a86- (i>>1); // gives initial guess y0
    x = *(float*)&i; // convert bits BACK to float
    x = x*(1.5f-xhalf*x*x); // Newton step, repeating increases accuracy
    x = x*(1.5f-xhalf*x*x); // Newton step, repeating increases accuracy
    x = x*(1.5f-xhalf*x*x); // Newton step, repeating increases accuracy
    return x;
}

class alVec2{

public:
    alVec2(): m_x(0), m_y(0), m_length(0){

    }
    alVec2(const float& x, const float& y)
    {
        m_x = x;
        m_y = y;
    }
    alVec2(const alVec2& v)
    {
        m_x = v.x();
        m_y = v.y();
    }

    inline void operator = (const alVec2& v)
    {
        m_x = v.x();
        m_y = v.y();
    }
    inline alVec2 operator + (const alVec2& v) const
    {
        return alVec2(m_x + v.x(), m_y + v.y());
    }
    inline alVec2 operator - (const alVec2& v) const
    {
        return alVec2(m_x - v.x(), m_y - v.y());
    }
    inline alVec2 operator * (const float f) const {
        return alVec2(m_x * f, m_y * f);
    }
    inline float operator * (const alVec2& v) const {
        return m_x * v.x() + m_y * v.y();
    }
    inline void operator += (const alVec2& v) {
        m_x += v.x();
        m_y += v.y();
    }
    inline void operator -= (const alVec2& v) {
        m_x -= v.x();
        m_y -= v.y();
    }
    inline void operator *= (const float f) {
        m_x *= f;
        m_y *= f;
    }

    inline float length()
    {
        m_length = sqrt(m_x * m_x + m_y * m_y);
        return m_length;
    }
    inline float lengthSquare()
    {
        return m_x * m_x + m_y * m_y;
    }
    inline float x() const
    {
        return m_x;
    }
    inline void setX(float x)
    {
        m_x = x;
    }
    inline float y() const
    {
        return m_y;
    }
    inline void setY(float y)
    {
        m_y = y;
    }
    inline void normalize() {
        float r = alFastInvSqrt(m_x * m_x + m_y * m_y);
        length();
        m_x *= r;
        m_y *= r;
    }
    inline const alVec2 getNormalizedVector()
    {
        float r = alFastInvSqrt(m_x * m_x + m_y * m_y);
        return alVec2(m_x, m_y) * r;
    }
    inline void set(const float x, const float y)
    {
        m_x = x;
        m_y = y;
    }
private:
    float m_x;
    float m_y;
    float m_length;
};
class alVec3{

public:
    alVec3(): m_x(0), m_y(0), m_z(0), m_length(0){

    }
    alVec3(const float& x, const float& y, const float& z)
    {
        m_x = x;
        m_y = y;
        m_z = z;
    }
    alVec3(const alVec3& v)
    {
        m_x = v.x();
        m_y = v.y();
        m_z = v.z();
    }

    inline void operator= (const alVec3& v)
    {
        m_x = v.x();
        m_y = v.y();
        m_z = v.z();
    }
    inline alVec3 operator+ (const alVec3& v) const
    {
        return alVec3(m_x + v.x(), m_y + v.y(), m_z + v.z());
    }

    inline alVec3 operator- (const alVec3& v) const
    {
        return alVec3(m_x - v.x(), m_y - v.y(), m_z - v.z());
    }
    inline alVec3 operator* (const float f) const
    {
        return alVec3(m_x * f, m_y * f, m_z * f);
    }
    inline float operator* (const alVec3& v) const
    {
        return m_x * v.x() + m_y * v.y() + m_z * v.z();
    }
    inline void operator+= (const alVec3& v)
    {
        m_x += v.x();
        m_y += v.y();
        m_z += v.z();
    }
    inline void operator-= (const alVec3& v)
    {
        m_x -= v.x();
        m_y -= v.y();
        m_z -= v.z();
    }
    inline void operator*= (const float f)
    {
        m_x *= f;
        m_y *= f;
        m_z *= f;
    }
    inline float lengthSquare()
    {
        return m_x * m_x + m_y * m_y + m_z * m_z;
    }
    inline float length()
    {
        m_length = sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
        return m_length;
    }
    inline float x() const
    {
        return m_x;
    }
    inline void setX(float x)
    {
        m_x = x;
    }
    inline float y() const{
        return m_y;
    }
    inline void setY(float y)
    {
        m_y = y;
    }
    inline float z() const
    {
        return m_z;
    }
    inline void setZ(float z)
    {
        m_z = z;
    }
    inline void normalize()
    {
        float r = alFastInvSqrt(m_x * m_x + m_y * m_y + m_z * m_z);
        m_x *= r;
        m_y *= r;
        m_z *= r;
    }
    inline void set(const float x, const float y, const float z)
    {
        m_x = x;
        m_y = y;
        m_z = z;
    }
    inline alVec3 getNormalizedVector() const
    {
        float r = alFastInvSqrt(m_x * m_x + m_y * m_y + m_z * m_z);
        return alVec3(m_x, m_y, m_z) * r;
    }
private:
    float m_x;
    float m_y;
    float m_z;
    float m_length;
};
class alMat2{

public:
    alMat2(){}
    alMat2(const alVec2& col1, const alVec2& col2)
    {
        m_c1 = col1;
        m_c2 = col2;
    }
    alMat2(const float& a11,const float& a12,const float& a21,const float& a22)
    {
        m_c1 = alVec2(a11, a12);
        m_c2 = alVec2(a21, a22);
    }

    inline void operator= (const alMat2& m)
    {
        m_c1 = m.c1();
        m_c2 = m.c2();
    }
    inline alMat2 operator+ (const alMat2& v) const
    {
        return alMat2(m_c1 + v.c1() , m_c2 + v.c2());
    }
    inline alMat2 operator- (const alMat2& v) const
    {
        return alMat2(m_c1 - v.c1() , m_c2 - v.c2());
    }
    inline alVec2 operator* (const alVec2& v) const
    {
        return alVec2(v.x() * m_c1.x() + v.y() * m_c2.x(), v.x() * m_c1.y() + v.y() * m_c2.y());
    }
    inline alMat2 operator* (const alMat2& v) const
    {
        alMat2 m(m_c1, m_c2);
        return alMat2(m * v.c1(), m * v.c2());
    }
    inline alMat2 operator* (const float f) const
    {
        return alMat2(m_c1 * f, m_c2 * f);
    }
    inline void operator*= (const float f)
    {
        m_c1 *= f;
        m_c2 *= f;
    }

    inline alVec2 c1() const{
        return m_c1;
    }
    inline void setC1(const alVec2 &c1){
        m_c1 = c1;
    }
    inline alVec2 c2() const{
        return m_c2;
    }
    inline void setC2(const alVec2 &c2){
        m_c2 = c2;
    }
    inline alMat2 transpose(){
        alVec2 c1(m_c1.x() , m_c2.x());
        alVec2 c2(m_c1.y() , m_c2.y());
        m_c1 = c1;
        m_c2 = c2;
        return alMat2(c1, c2);
    }
private:
    alVec2 m_c1;
    alVec2 m_c2;
};
class alMat3{

public:

    alMat3(){}
    alMat3(const alVec3& col1, const alVec3& col2, const alVec3& col3)
    {
        m_c1 = col1;
        m_c2 = col2;
        m_c3 = col3;
    }
    alMat3(const float& a11,const float& a12,const float& a13,const float& a21,const float& a22,const float& a23,const float& a31,const float& a32,const float& a33)
    {
        m_c1 = alVec3(a11, a12, a13);
        m_c2 = alVec3(a21, a22, a23);
        m_c3 = alVec3(a31, a32, a33);
    }

    inline void operator= (const alMat3& m)
    {
        m_c1 = m.c1();
        m_c2 = m.c2();
        m_c3 = m.c3();
    }
    inline alMat3 operator+ (const alMat3& v) const
    {
        return alMat3(m_c1 + v.c1() , m_c2 + v.c2(), m_c3 + v.c3());
    }

    inline alMat3 operator- (const alMat3& v) const
    {
        return alMat3(m_c1 - v.c1() , m_c2 - v.c2(), m_c3 - v.c3());
    }
    inline alVec3 operator* (const alVec3& v) const
    {
        return alVec3(v.x() * m_c1.x() + v.y() * m_c2.x() + v.z() * m_c3.x()
                      , v.x() * m_c1.y() + v.y() * m_c2.y() + v.z() * m_c3.y()
                      , v.x() * m_c1.z() + v.y() * m_c2.z() + v.z() * m_c3.z());
    }
    inline alMat3 operator* (const alMat3& v) const
    {
        alMat3 m(m_c1, m_c2, m_c3);
        return alMat3(m * v.c1(), m * v.c2(), m * v.c3());
    }
    inline void operator*= (const float f)
    {
        m_c1 *= f;
        m_c2 *= f;
        m_c3 *= f;
    }

    inline alVec3 c1() const
    {
        return m_c1;
    }
    inline void setC1(const alVec3 &c1){
        m_c1 = c1;
    }

    inline alVec3 c2() const{
        return m_c2;
    }
    inline void setC2(const alVec3 &c2){
        m_c2 = c2;
    }
    inline alVec3 c3() const{
        return m_c3;
    }

    inline void setC3(const alVec3 &c3){
        m_c3 = c3;
    }
    inline void transpose(){
        m_c1 = alVec3(m_c1.x() , m_c2.x(), m_c3.x());
        m_c2 = alVec3(m_c1.y() , m_c2.y(), m_c3.y());
        m_c3 = alVec3(m_c1.z() , m_c2.z(), m_c3.z());
    }
private:
    alVec3 m_c1;
    alVec3 m_c2;
    alVec3 m_c3;
};
class alRot
{
public:

    alRot(const float angle){
        m_angle = angle;
        m_arc = m_angle * M_PI / 180;
        update();
    }

    inline alVec2 operator* (const alVec2& v) const
    {
        return m_rotMat * v;
    }
    inline alMat2 operator* (const float f) const
    {
        return m_rotMat * f;
    }
    inline float angle() const{
        return m_angle;
    }
    inline void setAngle(float angle){
        m_angle = angle;
        m_arc = m_angle * M_PI / 180;
        update();
    }
    inline float arc() const{
        return m_arc;
    }
    inline void setArc(float arc){
        m_arc = arc;
        m_angle = m_angle * 180 / M_PI;
        update();
    }
private:
    inline void update()
    {
        m_rotMat = alMat2(cos(m_arc), sin(m_arc), -sin(m_arc), cos(m_arc));
    }
    float m_angle;
    float m_arc;
    alMat2 m_rotMat;
};
///3d vector cross product
///
static inline alVec3 alCross(const alVec3& l, const alVec3& r){
    return alVec3(l.y() * r.z() - l.z() * r.y(), l.z() * r.x() - l.x() * r.z(), l.x() * r.y() - l.y() * r.x());
}
static inline alVec2 alPolarToCartesian(const float arc, const float length)
{
    return alVec2(cos(arc), sin(arc)) * length;
}
#endif // ALMATH_H
