#ifndef ALCOLLISIONDETECTOR_H
#define ALCOLLISIONDETECTOR_H

#include <albody.h>
#include <QPainter>
class alCollisionDetector
{
public:
    alCollisionDetector();



    alVector2 minimumPenetration() const;

    float penetrateLength() const;

    virtual bool detect() = 0;
protected:
    float m_penetrateLength = 0;
    alVector2 m_minimumPenetration;
};
class alPolygonCircleCollisionDetector : public alCollisionDetector
{
public:
    alPolygonCircleCollisionDetector() {}
    ~alPolygonCircleCollisionDetector();

    bool detect() override;
    alCircle *circle() const
    {
        return m_circle;
    }
    void setCircle(alCircle *circle)
    {
        m_circle = circle;
    }

    alPolygon *polygon() const
    {
        return m_polygon;
    }
    void setPolygon(alPolygon *polygon)
    {
        m_polygon = polygon;
    }

protected:
private:
    alCircle *m_circle;
    alPolygon *m_polygon;
};
class alCircleCircleCollisionDetector : public alCollisionDetector
{
public:
    alCircleCircleCollisionDetector() {}
    ~alCircleCircleCollisionDetector();
    bool detect() override;
    alCircle *circle1() const
    {
        return m_circle1;
    }
    void setCircle1(alCircle *circle1)
    {
        m_circle1 = circle1;
    }

    alCircle *circle2() const
    {
        return m_circle2;
    }
    void setCircle2(alCircle *circle2)
    {
        m_circle2 = circle2;
    }

protected:
private:
    alCircle *m_circle1;
    alCircle *m_circle2;

};
class alPolygonPolygonCollisionDetector : public alCollisionDetector
{
public:
    alPolygonPolygonCollisionDetector() {}
    ~alPolygonPolygonCollisionDetector();

    bool detect() override;
    ///
    /// \brief satDetection
    /// \param p1
    /// \param p2
    /// separating axis theorem colision detection

    alPolygon *polygon1() const
    {
        return m_polygon1;
    }
    void setPolygon1(alPolygon *polygon1)
    {
        m_polygon1 = polygon1;
    }

    alPolygon *polygon2() const
    {
        return m_polygon2;
    }
    void setPolygon2(alPolygon *polygon2)
    {
        m_polygon2 = polygon2;
    }


protected:
private:
    bool satDetection(alPolygon * p1, alPolygon * p2);

    alPolygon *m_polygon1;
    alPolygon *m_polygon2;

};
#endif // ALCOLLISIONDETECTOR_H
