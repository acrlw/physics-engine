#include "alcollisiondetector.h"

alCollisionDetector::alCollisionDetector()
{

}

alVector2 alCollisionDetector::minimumPenetration() const
{
    return m_minimumPenetration;
}

float alCollisionDetector::penetrateLength() const
{
    return m_penetrateLength;
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
    float shortestLength = 0;
    alVector2 shortestST;
    alVector2 shortestED;
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
        //draw min max point
        alVector2 minVector1 = perpendicular * b1_min;
        alVector2 maxVector1 = perpendicular * b1_max;
        //draw end

        float project = perpendicular * circle.position();
        float b2_min = project - circle.radius();
        float b2_max = project + circle.radius();

        //draw min max point of circle projection
        alVector2 minVector2 = perpendicular * b2_min;
        alVector2 maxVector2 = perpendicular * b2_max;

        if(b1_max > b2_min || b2_max < b1_min){
            contactAxis++;
        }
        float dt1 = b1_max - b2_min;
        float dt2 = b2_max - b1_min;
        float min = abs(dt1) > abs(dt2) ? dt2 : dt1;


        if(i == 0)
        {
            shortestLength = abs(min);
            if(abs(dt1) > abs(dt2))
            {
                shortestST = alVector2(maxVector2.x(), maxVector2.y());
                shortestED = alVector2(minVector1.x(), minVector1.y());
            }
            else
            {
                shortestST = alVector2(maxVector1.x(), maxVector1.y());
                shortestED = alVector2(minVector2.x(), minVector2.y());
            }
        }
        else
        {
            if(shortestLength > abs(dt2))
            {
                shortestLength = abs(dt2);
                shortestST = alVector2(maxVector2.x(), maxVector2.y());
                shortestED = alVector2(minVector1.x(), minVector1.y());
            }
            if(shortestLength > abs(dt1))
            {
                shortestLength = abs(dt1);
                shortestST = alVector2(maxVector1.x(), maxVector1.y());
                shortestED = alVector2(minVector2.x(), minVector2.y());
            }
        }
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
    //projection axis of circle
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

    alVector2 minVector1 = edge * b1_min;
    alVector2 maxVector1 = edge * b1_max;

    float project = edge * circle.position();
    float b2_min = project - circle.radius();
    float b2_max = project + circle.radius();

    alVector2 minVector2 = edge * b2_min;
    alVector2 maxVector2 = edge * b2_max;




    float dt1 = b1_max - b2_min;
    float dt2 = b2_max - b1_min;
    float min = abs(dt1) > abs(dt2) ? dt2 : dt1;
    if(b2_max > b1_min || b1_max < b2_min)
        contactAxis++;


    if(shortestLength == 0)
    {
        shortestLength = abs(min);
        if(abs(dt1) > abs(dt2))
        {
            shortestST = alVector2(maxVector2.x(), maxVector2.y());
            shortestED = alVector2(minVector1.x(), minVector1.y());
        }
        else
        {
            shortestST = alVector2(maxVector1.x(), maxVector1.y());
            shortestED = alVector2(minVector2.x(), minVector2.y());
        }
    }
    else
    {
        if(shortestLength > abs(dt2))
        {
            shortestLength = abs(dt2);
            shortestST = alVector2(maxVector2.x(), maxVector2.y());
            shortestED = alVector2(minVector1.x(), minVector1.y());
        }
        if(shortestLength > abs(dt1))
        {
            shortestLength = abs(dt1);
            shortestST = alVector2(maxVector1.x(), maxVector1.y());
            shortestED = alVector2(minVector2.x(), minVector2.y());
        }
    }

    if(contactAxis == polygon.vertices().size()){
        m_minimumPenetration = shortestED - shortestST;
        alVector2 positionDirection = m_circle->position() - m_polygon->position();
        if(m_minimumPenetration * positionDirection / abs(m_minimumPenetration * positionDirection) == 1)
            m_minimumPenetration *= -1;
        m_penetrateLength = m_minimumPenetration.length();
        return true;
    }
    return false;
}

alCircleCircleCollisionDetector::~alCircleCircleCollisionDetector()
{
    m_circle1 = nullptr;
    m_circle2 = nullptr;
}

bool alCircleCircleCollisionDetector::detect()
{
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
        m_penetrateLength = dp.length();
        m_minimumPenetration = dp;
        return true;
    }
    return false;
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
    if(m_polygon1 == nullptr || m_polygon1 == nullptr)
        return false;
    m_penetrateLength = 0;
    m_minimumPenetration.set(0, 0);
    bool contact1 = satDetection(m_polygon1, m_polygon2);
    bool contact2 = satDetection(m_polygon2, m_polygon1);

    if(contact1 && contact2)
    {
        alVector2 positionDirection = m_polygon2->position() - m_polygon1->position();
        if(m_minimumPenetration * positionDirection / abs(m_minimumPenetration * positionDirection) == 1)
            m_minimumPenetration *= -1;
        return true;
    }
    return false;
}

bool alPolygonPolygonCollisionDetector::satDetection(alPolygon *p1, alPolygon *p2)
{
    std::vector<alVector2> b1vertices = p1->getRotatedVertices();
    std::vector<alVector2> b2vertices = p2->getRotatedVertices();
    alVector2 relativePosition = p2->position() - p1->position();
    int contactAxis = 0;
    float shortestLength = 0;
    alVector2 shortestST;
    alVector2 shortestED;
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

        alVector2 minVector1 = perpendicular * b1_min;
        alVector2 maxVector1 = perpendicular * b1_max;
        alVector2 minVector2 = perpendicular * b2_min;
        alVector2 maxVector2 = perpendicular * b2_max;

        float dt1 = b1_max - b2_min;
        float dt2 = b2_max - b1_min;
        float min = abs(dt1) > abs(dt2) ? dt2 : dt1;

        if(b1_max > b2_min || b2_max < b1_min)
            contactAxis++;
        if(i == 0)
        {
            shortestLength = min;
            if(abs(dt1) > abs(dt2))
            {
                shortestST = alVector2(maxVector2.x(), maxVector2.y());
                shortestED = alVector2(minVector1.x(), minVector1.y());
            }
            else
            {
                shortestST = alVector2(maxVector1.x(), maxVector1.y());
                shortestED = alVector2(minVector2.x(), minVector2.y());
            }
        }
        else
        {
            if(shortestLength > abs(dt2))
            {
                shortestLength = dt2;
                shortestST = alVector2(maxVector2.x(), maxVector2.y());
                shortestED = alVector2(minVector1.x(), minVector1.y());
            }
            if(shortestLength > abs(dt1))
            {
                shortestLength = dt1;
                shortestST = alVector2(maxVector1.x(), maxVector1.y());
                shortestED = alVector2(minVector2.x(), minVector2.y());
            }
        }
    }
    if(contactAxis == p1->vertices().size() - 1)
    {
        if(m_penetrateLength == 0)
        {
            m_minimumPenetration = shortestED - shortestST;
            m_penetrateLength = shortestLength;
        }
        else
        {
            if(m_penetrateLength > shortestLength)
            {
                m_minimumPenetration = shortestED - shortestST;
                m_penetrateLength = shortestLength;
            }
        }
        return true;
    }
    else
        return false;
}










