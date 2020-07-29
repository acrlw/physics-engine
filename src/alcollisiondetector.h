#ifndef ALCOLLISIONDETECTOR_H
#define ALCOLLISIONDETECTOR_H

#include <albody.h>
#include <QPainter>
class alCollisionDetector
{
public:
    alCollisionDetector();



    alVector2 minimumPenetration() const;
    virtual bool detect() = 0;
    float penetrateLength() const;

protected:
    float m_penetrateLength = 0;
    alVector2 m_minimumPenetration;
};
///
/// \brief
/// This class is used for Minkowski sum calculation
class alSimplex{
public:

    std::vector<alVector2>& vertices()
    {
        return m_vertices;
    }

    bool containOrigin();
    alVector2 getLastVertex()const{
        return m_vertices[m_vertices.size() - 1];
    }
    void insertVertex(alSimplex &edge, const alVector2& vertex);
private:
    std::vector<alVector2> m_vertices;
};

///
/// \brief
/// Use Gilbert–Johnson–Keerthi distance algorithm to detect the collision status of two bodies
class alGJKCollisionDetector : public alCollisionDetector
{

public:
    alGJKCollisionDetector(alPolygon *body1 = nullptr, alPolygon *body2 = nullptr): alCollisionDetector(), m_body1(body1), m_body2(body2){};

    alPolygon *body1() const
    {
        return m_body1;
    }

    void setBody1(alPolygon *body1)
    {
        m_body1 = body1;
    }

    alPolygon *body2() const
    {
        return m_body2;
    }

    void setBody2(alPolygon *body2)
    {
        m_body2 = body2;
    }

    bool detectCollision(QPainter * painter);

    std::pair<alVector2, alVector2> contactPair() const
    {
        return m_contactPair;
    }

    alVector2 penetration() const
    {
        return m_penetration;
    }

    alVector2 findFarthestPoint(alPolygon *body1, const alVector2& direction);
    alVector2 support(alPolygon *body1, alPolygon *body2, const alVector2& direction);
    void doEPA(alPolygon *body1, alPolygon *body2, alSimplex &simplex);

    bool detect()override;
    alVector2 getDirection(alSimplex &simplex, bool towardsOrigin);
    bool doGJKDetection(alPolygon *body1, alPolygon *body2);
    alSimplex findClosestEdge(alSimplex simplex);
private:
    alPolygon *m_body1;
    alPolygon *m_body2;
    std::pair<alVector2, alVector2> m_contactPair;
    alVector2 m_penetration;
    alSimplex m_simplex;
};
///
/// \brief
/// Use Separating Axis Theorm algorithm to detect the collision status of two bodies
class alPolygonCircleCollisionDetector : public alCollisionDetector
{
public:
    alPolygonCircleCollisionDetector() {}
    ~alPolygonCircleCollisionDetector();

    bool detect()override;
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
    bool detect()override;
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

    bool detect()override;

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


    ///
    /// \brief
    /// separating axis theorem colision detection
    int satDetection(alPolygon *p1, alPolygon *p2);
protected:
private:

    alPolygon *m_polygon1;
    alPolygon *m_polygon2;

};
#endif // ALCOLLISIONDETECTOR_H
