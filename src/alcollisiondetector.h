#ifndef ALCOLLISIONDETECTOR_H
#define ALCOLLISIONDETECTOR_H

#include <albody.h>
#include <QPainter>
#include <alrenderer.h>
class alCollisionDetector
{
public:
    alCollisionDetector();



    alVector2 minimumPenetration() const;

    float penetrateLength() const;

protected:
    float m_penetrateLength = 0;
    alVector2 m_minimumPenetration;
};
class alPolygonCircleCollisionDetector : public alCollisionDetector
{
public:
    alPolygonCircleCollisionDetector() {}
    ~alPolygonCircleCollisionDetector();

    bool detect() ;
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

    alVector2 contactPoint() const;

protected:
private:
    alCircle *m_circle;
    alPolygon *m_polygon;
    alVector2 m_contactPoint;
};
class alCircleCircleCollisionDetector : public alCollisionDetector
{
public:
    alCircleCircleCollisionDetector() {}
    ~alCircleCircleCollisionDetector();
    bool detect() ;
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

    bool detect(QPainter *painter) ;
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


    alVector2 contactPoint() const;

protected:
private:
    bool satDetection(QPainter *painter, alPolygon *p1, alPolygon *p2);

    alPolygon *m_polygon1;
    alPolygon *m_polygon2;
    alVector2 m_contactPoint;
    alVector2 m_st;
    alVector2 m_ed;
};
#endif // ALCOLLISIONDETECTOR_H
