#include "alcollisiondetector.h"

alCollisionDetector::alCollisionDetector()
{

}


///
/// \brief alPolygonPolygonCollisionDetector::detect
/// using separating axis theorem to judge polygon and circle collision status
/// \return
///
bool alPolygonCircleCollisionDetector::detect()
{
    return false;
}

bool alCircleCircleCollisionDetector::detect()
{
    m_minimunTranslationVector.set(0 ,0);
    if(m_body1 == nullptr || m_body2 == nullptr)
        return false;
    alVecter2 dp = m_body1->position() - m_body2->position();
    float dps = dp.length();
    float distance = static_cast<alCircle*>(m_body1)->radius() + static_cast<alCircle*>(m_body2)->radius();
    if(dps > distance * 1.2)
        return false;
    if(dps <= distance)
    {
        dp.normalize();
        dp *= dps - distance;
        m_minimunTranslationVector = dp;
        return true;
    }
    return false;
}
///
/// \brief alPolygonPolygonCollisionDetector::detect
/// using separating axis theorem to judge two polygon collision status
/// \return
///
bool alPolygonPolygonCollisionDetector::detect()
{
    m_minimunTranslationVector.set(0 ,0);
    if(m_body1 == nullptr || m_body2 == nullptr)
        return false;
    alPolygon * p1 = static_cast<alPolygon*>(m_body1);
    alPolygon * p2 = static_cast<alPolygon*>(m_body1);
    std::vector<float> penetration;
    for(int i = 0;i < p1->vertices().size(); i++)
    {
        for(int j = i + 1;j < p1->vertices().size(); j++)
        {
            alVecter2 da = p1->vertices()[i] - p1->vertices()[j];
            alVecter2 n = alRotation(-90) * da;
            n.normalize();
            for(int k = 0; k < p2->vertices().size(); k++)
            {
                alVecter2 v = p2->vertices()[k];
                float s = (v - p1->vertices()[i]) * n;
                qDebug () << "penetration: " << s;
                if(s > 0)
                    penetration.push_back(s);
            }
        }
    }

    return false;
}
