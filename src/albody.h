#ifndef ALBODY_H
#define ALBODY_H

#include <almath.h>
#include <alsettings.h>
#include <vector>
#include <QDebug>


class alBody
{
public:
    alBody(const float m = 1): m_sleep(true), m_isTouched(false), m_mass(m), m_angle(0) , m_angularAcceleration(0), m_angularVelocity(0)
    {

    }
    enum BodyType{
        Circle,
        Polygon
    };
    inline alVecter2& velocity()
    {
        return m_velocity;
    }
    inline void setVelocity(const alVecter2 &velocity)
    {
        m_velocity = velocity;
    }
    inline alVecter2& acceleration()
    {
        return m_acceleration;
    }
    inline void setAcceleration(const alVecter2 &acceleration)
    {
        m_acceleration = acceleration;
    }
    inline alVecter2& position()
    {
        return m_position;
    }
    inline void setPosition(const alVecter2 &position)
    {
        m_position = position;
    }
    inline float mass() const
    {
        return m_mass;
    }
    inline void setMass(float mass)
    {
        m_mass = mass;
    }
    float angle() const
    {
        return m_angle;
    }
    void setAngle(float angle)
    {
        m_angle = angle;
    }
    float angularAcceleration() const
    {
        return m_angularAcceleration;
    }
    void setAngularAcceleration(float angularAcceleration)
    {
        m_angularAcceleration = angularAcceleration;
    }

    bool sleep() const
    {
        return m_sleep;
    }
    void setSleep(bool sleep)
    {
        m_sleep = sleep;
    }
    float angularVelocity() const
    {
        return m_angularVelocity;
    }
    void setAngularVelocity(float angularVelocity)
    {
        m_angularVelocity = angularVelocity;
    }
    void update(){
        if(!m_sleep)
        {
            m_position += m_velocity;
            m_angle += m_angularVelocity;
            m_velocity += m_acceleration * alDeltaTime;
            m_angularVelocity += m_angularAcceleration * alDeltaTime;

            if(m_velocity.lengthSquare() < alStopThreshold)// if it did reach the deadline
                m_velocity.set(0., 0.);

            if(m_angularVelocity * m_angularVelocity < alStopThreshold)
                m_angularVelocity = 0;
        }

    }

    BodyType type() const
    {
        return m_type;
    }

    void setType(const BodyType &type)
    {
        m_type = type;
    }

    bool isTouched() const
    {
        return m_isTouched;
    }

    void setIsTouched(bool isTouched)
    {
        m_isTouched = isTouched;
    }

    float inertia() const
    {
        return m_inertia;
    }
    void setInertia(float inertia)
    {
        m_inertia = inertia;
    }

    float density() const
    {
        return m_density;
    }
    void setDensity(float density)
    {
        m_density = density;
    }
protected:
    bool m_sleep;
    bool m_isTouched;
    float m_mass;
    float m_density;
    float m_inertia;
    float m_angle;
    float m_angularAcceleration;
    float m_angularVelocity;
    alVecter2 m_massPosition;
    alVecter2 m_velocity;
    alVecter2 m_acceleration;
    alVecter2 m_position;
    BodyType m_type;
};
class alCircle: public alBody{

public:
    alCircle(const float radius = 120, const float angle = 0, const float m = 1):
        alBody(), m_radius(radius)
    {
        m_angle = angle;
        m_mass = m;
        m_type = BodyType::Circle;
        m_massPosition = m_position;
    }


    float radius() const
    {
        return m_radius;
    }

    void setRadius(float radius)
    {
        m_radius = radius;
    }

private:
    float m_radius;
};
class alPolygon : public alBody{
public:
    alPolygon(){
        m_type = BodyType::Polygon;
        m_isConvex = true;
    }
    std::vector<alVecter2> &vertices()
    {
        return m_vertices;
    }

    void setVertices(const std::vector<alVecter2> &vertices)
    {
        m_vertices = vertices;
    }
    /// \brief getRotatedVertices
    /// return the rotated vertices of polygon
    /// \return
    std::vector<alVecter2> getRotatedVertices()const
    {
        std::vector<alVecter2> actual;
        foreach (alVecter2 v, m_vertices) {
            alVecter2 va = alRotation(m_angle) * v;
            actual.push_back(va);
        }
        return actual;
    }
    void addVertex(const alVecter2& v){
        m_vertices.push_back(v);
        updateMassPosition();
    }
    inline alVecter2 triangleGravityPoint(const alVecter2& a1, const alVecter2& a2, const alVecter2& a3)const
    {
        return alVecter2(a1 + a2 + a3) * (1 / 3);
    }
    inline float triangleArea(const alVecter2& a1, const alVecter2& a2, const alVecter2& a3)const
    {
        return 0.5 * (alCross2(a1, a2) + alCross2(a2, a3) + alCross2(a1, a3));
    }
protected:
    ///
    /// \brief updateMassPosition
    /// update the mass position
    void updateMassPosition(){
        if(m_vertices.size() >= 3)
        {

        }
    }
    ///
    /// \brief m_vertices
    /// the vertices come from when body stay the origin static status, which means this vertices will not participate the transformation
    std::vector<alVecter2> m_vertices;
    bool m_isConvex;
private:
};

class alRectangle : public alPolygon
{
public:
    alRectangle(const float width = 50, const float height = 50):
        alPolygon(), m_width(width), m_height(height)
    {
        updateVertices();
    }

    float width() const
    {
        return m_width;
    }

    void setWidth(float width)
    {
        m_width = width;
        updateVertices();
    }

    float height() const
    {
        return m_height;
    }

    void setHeight(float height)
    {
        m_height = height;
        updateVertices();
    }
    void updateVertices()
    {
        m_vertices.clear();
        addVertex(alVecter2(-m_width / 2, m_height / 2));
        addVertex(alVecter2(-m_width / 2, -m_height / 2));
        addVertex(alVecter2(m_width / 2, -m_height / 2));
        addVertex(alVecter2(m_width / 2, m_height / 2));
        addVertex(alVecter2(-m_width / 2, m_height / 2));
        m_massPosition = m_position;
    }
protected:
    float m_width;
    float m_height;
private:

};
class alWall : public alRectangle
{
public:
    alWall(const float elasticCoefficient = 0.8, const float width = 40): alRectangle(), m_elasticCoefficient(elasticCoefficient) {
        m_width = width;
        m_height = width;
    }

    float elasticCoefficient() const
    {
        return m_elasticCoefficient;
    }
    void setElasticCoefficient(float elasticCoefficient)
    {
        m_elasticCoefficient = elasticCoefficient;
    }
private:
    float m_elasticCoefficient;
};
#endif // ALBODY_H
