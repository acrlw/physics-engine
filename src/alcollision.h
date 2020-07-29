#ifndef ALCOLLISION_H
#define ALCOLLISION_H

#include <albody.h>
///
/// \brief
/// This is the collision detection base class
class alCollision
{
public:
    alCollision(): m_penetrateLength(0){}
    virtual std::pair<bool, alVector2> detect(alBody *body1, alBody *body2) = 0;

protected:
    alVector2 m_minimumPenetration;
    float m_penetrateLength;
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
class alCircleCollisionDetector: public alCollision
{
public:
    alCircleCollisionDetector() {}
    std::pair<bool, alVector2> detect(alBody *body1, alBody *body2) override;
};

class alGJKCollisionDetector : public alCollision
{
public:
    alGJKCollisionDetector() {}
    std::pair<bool, alVector2> detect(alBody *body1, alBody *body2) override;

private:

    alVector2 findFarthestPoint(alBody *body, const alVector2& direction);
    alVector2 support(alBody *body1, alBody *body2, const alVector2& direction);
    void doEPA(alBody *body1, alBody *body2, alSimplex &simplex);

    alVector2 getDirection(alSimplex &simplex, bool towardsOrigin);
    bool doGJKDetection(alBody *body1, alBody *body2);
    alSimplex findClosestEdge(alSimplex simplex);
    void scaleBody(alBody *body);
};
class alSATCollisionDetector : public alCollision
{
public:
    alSATCollisionDetector() {}
    std::pair<bool, alVector2> detect(alBody *body1, alBody *body2) override;

private:
    int polygonSATDetection(alPolygon *p1, alPolygon *p2);
    bool circleSATDetection(alCircle *body1, alPolygon *body2);
};

#endif // ALCOLLISION_H
