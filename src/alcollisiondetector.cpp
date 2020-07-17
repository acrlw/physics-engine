#include "alcollisiondetector.h"

alCollisionDetector::alCollisionDetector()
{

}


///
/// \brief alPolygonPolygonCollisionDetector::detect
/// using separating axis theorem to judge polygon and circle collision status
/// \return
///
alPolygonCircleCollisionDetector::~alPolygonCircleCollisionDetector()
{
    m_circle = nullptr;
    m_polygon = nullptr;
}

bool alPolygonCircleCollisionDetector::detect()
{
    m_minimunTranslationVector.set(0 ,0);
    if(m_polygon == nullptr || m_circle == nullptr)
        return false;
    ///Attention the body order!
    alPolygon polygon = *m_polygon;
    alCircle circle = *m_circle;
    alVector2 relativePosition = circle.position() - polygon.position();
    std::vector<alVector2> b1vertices = polygon.getRotatedVertices();
    int contactAxis = 0;
    float minimumDistance = 0;
    int minimumIndex = 0;
    polygon.position().set(0, 0);
    circle.position() = polygon.position() + relativePosition;
    for(int i = 0; i < b1vertices.size() - 1; i++)
    {
        alVector2 edge = b1vertices[i + 1] - b1vertices[i];

        alVector2 perpendicular = alVector2(edge.y(), -edge.x()).getNormalizedVector();


        float b1_min = (b1vertices[0]) * (perpendicular), b1_max = (b1vertices[0]) * (perpendicular);
        for(int j = 0;j < b1vertices.size(); j++)
        {
            float temp = (b1vertices[j]) * (perpendicular);
            if(b1_min > temp)
                b1_min = temp;
            if(b1_max < temp)
                b1_max = temp;
        }
        float project = perpendicular * circle.position();
        float b2_min = project - circle.radius();
        float b2_max = project + circle.radius();
        if(b1_max >= b2_min || b2_max <= b1_min)
            contactAxis++;
    }
    //circle projection
    for(int i = 0; i < b1vertices.size(); i++)
    {
        float temp = (b1vertices[i] - circle.position()).length();
        if(minimumDistance == 0)
        {
            minimumDistance = temp;
            minimumIndex = 0;
            continue;
        }
        if(minimumDistance > temp)
        {
            minimumIndex = i;
            minimumDistance = temp;
        }
    }

    alVector2 edge = b1vertices[minimumIndex] - circle.position();
    edge.normalize();

    float b1_min = (b1vertices[0]) * (edge), b1_max = (b1vertices[0]) * (edge);
    for(int j = 0;j < b1vertices.size(); j++)
    {
        float temp = (b1vertices[j]) * (edge);
        if(b1_min > temp)
            b1_min = temp;
        if(b1_max < temp)
            b1_max = temp;
    }

    float project = edge * circle.position();
    float b2_min = project - circle.radius();
    float b2_max = project + circle.radius();
    if(b2_max >= b1_min || b1_max <= b2_min)
        contactAxis++;

    if(contactAxis == polygon.vertices().size())
        return true;
    return false;
}

alCircle *alPolygonCircleCollisionDetector::circle() const
{
    return m_circle;
}

void alPolygonCircleCollisionDetector::setCircle(alCircle *circle)
{
    m_circle = circle;
}

alPolygon *alPolygonCircleCollisionDetector::polygon() const
{
    return m_polygon;
}

void alPolygonCircleCollisionDetector::setPolygon(alPolygon *polygon)
{
    m_polygon = polygon;
}

alCircleCircleCollisionDetector::~alCircleCircleCollisionDetector()
{
    m_circle1 = nullptr;
    m_circle2 = nullptr;
}

bool alCircleCircleCollisionDetector::detect()
{
    m_minimunTranslationVector.set(0 ,0);
    if(m_circle1 == nullptr || m_circle2 == nullptr)
        return false;
    alVector2 dp = m_circle1->position() - m_circle2->position();
    float dps = dp.length();
    float distance = m_circle1->radius() + m_circle2->radius();
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

alCircle *alCircleCircleCollisionDetector::circle1() const
{
    return m_circle1;
}

void alCircleCircleCollisionDetector::setCircle1(alCircle *circle1)
{
    m_circle1 = circle1;
}

alCircle *alCircleCircleCollisionDetector::circle2() const
{
    return m_circle2;
}

void alCircleCircleCollisionDetector::setCircle2(alCircle *circle2)
{
    m_circle2 = circle2;
}
///
/// \brief alPolygonPolygonCollisionDetector::detect
/// using different methods to judge two polygon collision status
/// \return
///
alPolygonPolygonCollisionDetector::~alPolygonPolygonCollisionDetector()
{
    m_polygon1 = nullptr;
    m_polygon2 = nullptr;
}

bool alPolygonPolygonCollisionDetector::detect()
{
    m_minimunTranslationVector.set(0 ,0);
    if(m_polygon1 == nullptr || m_polygon1 == nullptr)
        return false;
    alVector2 contact1 = satDetection(m_polygon1, m_polygon2);
    alVector2 contact2 = satDetection(m_polygon2, m_polygon1);
    float length1 = contact1.length();
    float length2 = contact2.length();
    if(length1 > 0 && length2 > 0)
    {
        m_minimunTranslationVector = length1 > length2 ? contact2 : contact1;
        return true;
    }
    return false;
}

alVector2 alPolygonPolygonCollisionDetector::satDetection(alPolygon *p1, alPolygon *p2)
{
    std::vector<alVector2> b1vertices = p1->getRotatedVertices();
    std::vector<alVector2> b2vertices = p2->getRotatedVertices();
    alVector2 relativePosition = p2->position() - p1->position();
    int contactAxis = 0;
    float minimumPenetration = 0;
    alVector2 minimumPenetrationVector;
    for(int i = 0; i < b1vertices.size() - 1; i++)
    {
        alVector2 edge = b1vertices[i + 1] - b1vertices[i];
        alVector2 perpendicular = alVector2(edge.y(), -edge.x()).getNormalizedVector();
        float b1_min = (b1vertices[0]) * (perpendicular), b1_max = (b1vertices[0]) * (perpendicular);
        for(int j = 0;j < b1vertices.size(); j++)
        {
            float temp = (b1vertices[j]) * (perpendicular);
            if(b1_min > temp)
                b1_min = temp;
            if(b1_max < temp)
                b1_max = temp;
        }
        float b2_min = (b2vertices[0] + relativePosition) * (perpendicular), b2_max = (b2vertices[0] + relativePosition) * (perpendicular);
        for(int j = 0;j < b2vertices.size(); j++)
        {
            float temp = (b2vertices[j] + relativePosition) * (perpendicular);
            if(b2_min > temp)
                b2_min = temp;
            if(b2_max < temp)
                b2_max = temp;
        }
        float d1 = b1_max - b2_min;
        float d2 = b2_max - b1_min;
        if(b1_max >= b2_min || b2_max <= b1_min)
        {
            contactAxis++;
            if(minimumPenetration == 0)
            {
                minimumPenetrationVector = perpendicular;
                minimumPenetration = d1 > d2 ? d1 : d2;
            }
            else
            {
                if(minimumPenetration > d1)
                {
                    minimumPenetrationVector = perpendicular;
                    minimumPenetration = d1;
                }
                if(minimumPenetration > d2)
                {
                    minimumPenetrationVector = perpendicular;
                    minimumPenetration = d2;
                }
            }
        }
    }
    if(contactAxis == p1->vertices().size() - 1)
    {
        return minimumPenetrationVector * minimumPenetration;
    }
    else
        return alVector2();
}

alPolygon *alPolygonPolygonCollisionDetector::polygon1() const
{
    return m_polygon1;
}

void alPolygonPolygonCollisionDetector::setPolygon1(alPolygon *polygon1)
{
    m_polygon1 = polygon1;
}

alPolygon *alPolygonPolygonCollisionDetector::polygon2() const
{
    return m_polygon2;
}

void alPolygonPolygonCollisionDetector::setPolygon2(alPolygon *polygon2)
{
    m_polygon2 = polygon2;
}
