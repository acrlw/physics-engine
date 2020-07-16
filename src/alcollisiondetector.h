#ifndef ALCOLLISIONDETECTOR_H
#define ALCOLLISIONDETECTOR_H

#include <albody.h>
#include <QPainter>
class alCollisionDetector
{
public:
    alCollisionDetector();

    alBody *body1() const
    {
        return m_body1;
    }

    void setBody1(alBody *body1)
    {
        m_body1 = body1;
    }

    alBody *body2() const
    {
        return m_body2;
    }

    void setBody2(alBody *body2)
    {
        m_body2 = body2;
    }

    virtual bool detect() = 0;

    alVecter2 minimunTranslationVector() const
    {
        return m_minimunTranslationVector;
    }

    void setMinimunTranslationVector(const alVecter2 &minimunTranslationVector)
    {
        m_minimunTranslationVector = minimunTranslationVector;
    }
protected:
    void setContactStatus(const bool status){
        m_body1->setIsTouched(status);
        m_body2->setIsTouched(status);
    }
    alVecter2 m_minimunTranslationVector;
    alBody *m_body1;
    alBody *m_body2;
};
class alPolygonCircleCollisionDetector : public alCollisionDetector
{
public:
    alPolygonCircleCollisionDetector() {}

    bool detect() override;
protected:
};
class alCircleCircleCollisionDetector : public alCollisionDetector
{
public:
    alCircleCircleCollisionDetector() {}
    bool detect() override;
protected:

};
class alPolygonPolygonCollisionDetector : public alCollisionDetector
{
public:
    alPolygonPolygonCollisionDetector() {}
    bool detect() override;
protected:
};
#endif // ALCOLLISIONDETECTOR_H
