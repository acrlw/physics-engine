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

bool alPolygonCircleCollisionDetector::detect(QPainter *painter)
{
    int offset = 680;
    QPen line(Qt::darkBlue, 1, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
    QPen linemin(Qt::darkGray, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen linepenetrate(Qt::red, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen dot1(Qt::darkYellow, 8, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen dot2(Qt::darkGreen, 8, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen dotmax(Qt::red, 8, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen dotmin(Qt::blue, 8, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen dotmax2(Qt::green, 8, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen dotmin2(Qt::magenta, 8, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
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
    alVector2 penetrateDirection;
    float shortestLength = 0;
    alVector2 shortestST;
    alVector2 shortestED;
    for(int i = 0; i < b1vertices.size() - 1; i++)
    {
        alVector2 edge = b1vertices[i + 1] - b1vertices[i];

        alVector2 perpendicular = alVector2(edge.y(), -edge.x()).getNormalizedVector();

        //        //assistant perpendicular line drawing
        //        alVector2 mid = (b1vertices[i + 1] + b1vertices[i]) * 0.5;
        //        alVector2 s = perpendicular * offset + mid;

        //        alVector2 st = m_polygon->position() + mid;
        //        alVector2 ed = m_polygon->position() + s;

        //        painter->setPen(line);
        //        painter->drawLine(st.x(), st.y(), ed.x(), ed.y());
        //        //assistant end draw


        float b1_min = (b1vertices[0]) * (perpendicular), b1_max = (b1vertices[0]) * (perpendicular);
        for(int j = 0;j < b1vertices.size(); j++)
        {
            float temp = (b1vertices[j]) * (perpendicular);

            //            //emphasize vertices
            //            alVector2 tempVector = perpendicular * temp;
            //            tempVector += m_polygon->position();
            //            alVector2 tempP = b1vertices[j] + m_polygon->position();
            //            painter->setPen(dot1);
            //            painter->drawPoint(tempP.x(), tempP.y());
            //            painter->drawPoint(tempVector.x(), tempVector.y());

            //            painter->setPen(line);
            //            painter->drawLine(tempVector.x(), tempVector.y(), tempP.x(), tempP.y());
            //            //emphasize end

            if(b1_min > temp)
                b1_min = temp;
            if(b1_max < temp)
                b1_max = temp;
        }

        //draw min max point
        alVector2 minVector1 = perpendicular * b1_min;
        alVector2 maxVector1 = perpendicular * b1_max;
        minVector1 += m_polygon->position();
        maxVector1 += m_polygon->position();
        //        painter->setPen(dotmin);
        //        painter->drawPoint(minVector1.x(), minVector1.y());
        //        painter->setPen(dotmax);
        //        painter->drawPoint(maxVector1.x(), maxVector1.y());
        //draw end

        float project = perpendicular * circle.position();
        float b2_min = project - circle.radius();
        float b2_max = project + circle.radius();

        //draw min max point of circle projection
        alVector2 minVector2 = perpendicular * b2_min;
        alVector2 maxVector2 = perpendicular * b2_max;
        minVector2 += m_polygon->position();
        maxVector2 += m_polygon->position();
        //        painter->setPen(dotmin2);
        //        painter->drawPoint(minVector2.x(), minVector2.y());
        //        painter->setPen(dotmax2);
        //        painter->drawPoint(maxVector2.x(), maxVector2.y());
        //draw end

        if(b1_max >= b2_min || b2_max <= b1_min){
            contactAxis++;
        }
        float dt1 = b1_max - b2_min;
        float dt2 = b2_max - b1_min;
        float min = abs(dt1) > abs(dt2) ? dt2 : dt1;
        //        painter->setPen(linemin);
        //        if(abs(dt1) > abs(dt2))
        //        {
        //            painter->drawLine(maxVector2.x(), maxVector2.y(), minVector1.x(), minVector1.y());
        //        }
        //        else
        //        {
        //            painter->drawLine(maxVector1.x(), maxVector1.y(), minVector2.x(), minVector2.y());
        //        }

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

    alVector2 st = b1vertices[minimumIndex] + m_polygon->position();
    alVector2 ed = m_circle->position();
    //    painter->setPen(line);
    //    painter->drawLine(st.x(), st.y(), ed.x(), ed.y());

    float b1_min = (b1vertices[0]) * (edge), b1_max = (b1vertices[0]) * (edge);
    for(int j = 0;j < b1vertices.size(); j++)
    {
        float temp = (b1vertices[j]) * (edge);

        //emphasize vertices
        //        alVector2 tempVector = edge * temp;
        //        tempVector += m_polygon->position();
        //        alVector2 tempP = b1vertices[j] + m_polygon->position();
        //        painter->setPen(dot1);
        //        painter->drawPoint(tempP.x(), tempP.y());
        //        painter->drawPoint(tempVector.x(), tempVector.y());

        //        painter->setPen(line);
        //        painter->drawLine(tempVector.x(), tempVector.y(), tempP.x(), tempP.y());
        //emphasize end

        if(b1_min > temp)
            b1_min = temp;
        if(b1_max < temp)
            b1_max = temp;
    }

    //draw min max point
    alVector2 minVector1 = edge * b1_min;
    alVector2 maxVector1 = edge * b1_max;
    minVector1 += m_polygon->position();
    maxVector1 += m_polygon->position();
    //    painter->setPen(dotmin);
    //    painter->drawPoint(minVector1.x(), minVector1.y());
    //    painter->setPen(dotmax);
    //    painter->drawPoint(maxVector1.x(), maxVector1.y());
    //draw end

    float project = edge * circle.position();
    float b2_min = project - circle.radius();
    float b2_max = project + circle.radius();

    //draw min max point of circle projection
    alVector2 minVector2 = edge * b2_min;
    alVector2 maxVector2 = edge * b2_max;
    minVector2 += m_polygon->position();
    maxVector2 += m_polygon->position();
    //    painter->setPen(dotmin2);
    //    painter->drawPoint(minVector2.x(), minVector2.y());
    //    painter->setPen(dotmax2);
    //    painter->drawPoint(maxVector2.x(), maxVector2.y());
    //draw end




    float dt1 = b1_max - b2_min;
    float dt2 = b2_max - b1_min;
    float min = abs(dt1) > abs(dt2) ? dt2 : dt1;
    if(b2_max >= b1_min || b1_max <= b2_min)
        contactAxis++;
    //    painter->setPen(linemin);
    //    if(abs(dt1) > abs(dt2))
    //    {
    //        painter->drawLine(maxVector2.x(), maxVector2.y(), minVector1.x(), minVector1.y());
    //    }
    //    else
    //    {
    //        painter->drawLine(maxVector1.x(), maxVector1.y(), minVector2.x(), minVector2.y());
    //    }

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
        painter->setPen(linepenetrate);
        painter->drawLine(shortestST.x(), shortestST.y(), shortestED.x(), shortestED.y());
        return true;
    }
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

bool alPolygonPolygonCollisionDetector::detect(QPainter *painter)
{
    m_minimunTranslationVector.set(0 ,0);
    if(m_polygon1 == nullptr || m_polygon1 == nullptr)
        return false;
    penetrateLine = QLineF();
    penetrateLength = 0;
    bool contact1 = satDetection(painter,m_polygon1, m_polygon2);
    bool contact2 = satDetection(painter,m_polygon2, m_polygon1);
    QPen linepenetrate(Qt::red, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    if(contact1 && contact2)
    {
        painter->setPen(linepenetrate);
        painter->drawLine(penetrateLine);
        return true;
    }
    return false;
}

bool alPolygonPolygonCollisionDetector::satDetection(QPainter *painter,alPolygon *p1, alPolygon *p2)
{

    int offset = 680;
    QPen line(Qt::darkBlue, 1, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
    QPen linemin(Qt::darkGray, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen linepenetrate(Qt::red, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen dot1(Qt::darkYellow, 8, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen dot2(Qt::darkGreen, 8, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen dotmax(Qt::red, 8, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen dotmin(Qt::blue, 8, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen dotmax2(Qt::green, 8, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen dotmin2(Qt::magenta, 8, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
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

//                alVector2 mid = (b1vertices[i + 1] + b1vertices[i]) * 0.5;
//                alVector2 s = perpendicular * offset + mid;

//                alVector2 st = p1->position() + mid;
//                alVector2 ed = p1->position() + s;

//                painter->setPen(line);
//                painter->drawLine(st.x(), st.y(), ed.x(), ed.y());


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

        //draw min max point
        alVector2 minVector1 = perpendicular * b1_min;
        alVector2 maxVector1 = perpendicular * b1_max;
        minVector1 += p1->position();
        maxVector1 += p1->position();
//        painter->setPen(dotmin);
//        painter->drawPoint(minVector1.x(), minVector1.y());
//        painter->setPen(dotmax);
//        painter->drawPoint(maxVector1.x(), maxVector1.y());
        //draw end


        //draw min max point of circle projection
        alVector2 minVector2 = perpendicular * b2_min;
        alVector2 maxVector2 = perpendicular * b2_max;
        minVector2 += p1->position();
        maxVector2 += p1->position();
//        painter->setPen(dotmin2);
//        painter->drawPoint(minVector2.x(), minVector2.y());
//        painter->setPen(dotmax2);
//        painter->drawPoint(maxVector2.x(), maxVector2.y());
        //draw end


        float dt1 = b1_max - b2_min;
        float dt2 = b2_max - b1_min;
        float min = abs(dt1) > abs(dt2) ? dt2 : dt1;
//        if(min == 0)
//            qDebug () << "minimum = 0";
        if(b1_max > b2_min || b2_max < b1_min)
        {
            contactAxis++;
        }
//        painter->setPen(linemin);
//        if(abs(dt1) > abs(dt2))
//        {
//            painter->drawLine(maxVector2.x(), maxVector2.y(), minVector1.x(), minVector1.y());
//        }
//        else
//        {
//            painter->drawLine(maxVector1.x(), maxVector1.y(), minVector2.x(), minVector2.y());
//        }

        //draw min max point of circle projection

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
    if(contactAxis == p1->vertices().size() - 1)
    {
        if(penetrateLine.length() == 0)
        {
            penetrateLength = shortestLength;
            penetrateLine.setLine(shortestST.x(), shortestST.y(), shortestED.x(), shortestED.y());
        }
        else
        {
            if(penetrateLength > shortestLength)
            {
                penetrateLength = shortestLength;
                penetrateLine.setLine(shortestST.x(), shortestST.y(), shortestED.x(), shortestED.y());
            }
        }
        return true;
    }
    else
        return false;
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
