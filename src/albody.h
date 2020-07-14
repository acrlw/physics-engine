#ifndef ALBODY_H
#define ALBODY_H

#include <almath.h>
#include <alsettings.h>
#include <vector>
#include <QDebug>
///deprecated
enum Force{
    Fricion,
    Constant,
    Elastic
};

class alBody
{
public:
    alBody(const float m = 1): m_sleep(true), m_mass(m), m_angle(0) , m_angularAcceleration(0), m_angularVelocity(0)
    {

    }
    inline alVec2& velocity()
    {
        return m_velocity;
    }
    inline void setVelocity(const alVec2 &velocity)
    {
        m_velocity = velocity;
    }
    inline alVec2& acceleration()
    {
        return m_acceleration;
    }
    inline void setAcceleration(const alVec2 &acceleration)
    {
        m_acceleration = acceleration;
    }
    inline alVec2& position()
    {
        return m_position;
    }
    inline void setPosition(const alVec2 &position)
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
protected:
    bool m_sleep;
    float m_mass;
    float m_angle;
    float m_angularAcceleration;
    float m_angularVelocity;
    alVec2 m_velocity;
    alVec2 m_acceleration;
    alVec2 m_position;
};
class alCircle: public alBody{

public:
    alCircle(const float radius = 120, const float angle = 0, const float m = 1):
        alBody(), m_radius(radius)
    {
        m_angle = angle;
        m_mass = m;
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
    std::vector<alVec2> &vertices()
    {
        return m_vertices;
    }

    void setVertices(const std::vector<alVec2> &vertices)
    {
        m_vertices = vertices;
    }
    std::vector<alVec2> getActualVertices()const
    {
        std::vector<alVec2> actual;
        foreach (alVec2 v, m_vertices) {
            v = alRot(m_angle) * v;
            v += m_position;
            actual.push_back(v);
        }
        return actual;
    }
protected:
    std::vector<alVec2> m_vertices;
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

protected:
    float m_width;
    float m_height;
private:
    void updateVertices()
    {
        m_vertices.clear();
        m_vertices.push_back(alVec2(-m_width / 2, m_height / 2));
        m_vertices.push_back(alVec2(-m_width / 2, -m_height / 2));
        m_vertices.push_back(alVec2(m_width / 2, -m_height / 2));
        m_vertices.push_back(alVec2(m_width / 2, m_height / 2));
        m_vertices.push_back(alVec2(-m_width / 2, m_height / 2));
    }
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
