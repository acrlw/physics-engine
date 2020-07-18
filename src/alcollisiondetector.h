#ifndef ALCOLLISIONDETECTOR_H
#define ALCOLLISIONDETECTOR_H

#include <albody.h>
#include <QPainter>
class alCollisionDetector
{
public:
    alCollisionDetector();


    alVector2 minimunTranslationVector()const
    {
        return m_minimunTranslationVector;
    }

    void setMinimunTranslationVector(const alVector2 &minimunTranslationVector)
    {
        m_minimunTranslationVector = minimunTranslationVector;
    }
protected:
    alVector2 m_minimunTranslationVector;
};
class alPolygonCircleCollisionDetector : public alCollisionDetector
{
public:
    alPolygonCircleCollisionDetector() {}
    ~alPolygonCircleCollisionDetector();

    bool detect(QPainter *painter) ;
    alCircle *circle() const;
    void setCircle(alCircle *circle);

    alPolygon *polygon() const;
    void setPolygon(alPolygon *polygon);

    alVector2 penetrate;
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
    bool detect() ;
    alCircle *circle1() const;
    void setCircle1(alCircle *circle1);

    alCircle *circle2() const;
    void setCircle2(alCircle *circle2);

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
    bool satDetection(QPainter *painter, alPolygon * p1, alPolygon * p2);
    int contact = 1;
    QLineF penetrateLine;
    float penetrateLength = 0;
    alPolygon *polygon1() const;
    void setPolygon1(alPolygon *polygon1);

    alPolygon *polygon2() const;
    void setPolygon2(alPolygon *polygon2);

protected:
private:
    alPolygon *m_polygon1;
    alPolygon *m_polygon2;
};
#endif // ALCOLLISIONDETECTOR_H
