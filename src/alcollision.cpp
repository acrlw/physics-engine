#include "alcollision.h"



std::pair<bool, alVector2> alCircleCollisionDetector::detect(alBody *body1, alBody *body2)
{
    bool result = false;
    if(body1 == nullptr || body2 == nullptr)
        return std::pair<bool, alVector2>(result, alVector2());
    alCircle * circle1 = static_cast<alCircle*>(body1);
    alCircle * circle2 = static_cast<alCircle*>(body2);

    alVector2 dp = circle1->position() - circle2->position();
    float dps = dp.length();
    float distance = circle1->radius() + circle2->radius();
    if(dps > distance * 1.2)
        result = false;
    if(dps <= distance)
    {
        dp.normalize();
        dp *= dps - distance;
        m_penetrateLength = dp.length();
        m_minimumPenetration = dp;
        result = true;
    }
    return std::pair<bool, alVector2>(result, alVector2());
}

std::pair<bool, alVector2> alSATCollisionDetector::detect(alBody *body1, alBody *body2)
{
    bool result = false;
    m_penetrateLength = 0;
    m_minimumPenetration.set(0, 0);

    if(body1 == nullptr || body2 == nullptr)
        return std::pair<bool, alVector2>(result, alVector2());


    if(body1->type() == BodyType::Circle)
        result = circleSATDetection(static_cast<alCircle*>(body1), static_cast<alPolygon*>(body2));

    else if(body2->type() == BodyType::Circle)
        result = circleSATDetection(static_cast<alCircle*>(body2), static_cast<alPolygon*>(body1));
    else
    {
        alPolygon * polygon1 = static_cast<alPolygon*>(body1);
        alPolygon * polygon2 = static_cast<alPolygon*>(body2);
        int contact1 = polygonSATDetection(polygon1, polygon2);
        int contact2 = polygonSATDetection(polygon2, polygon1);
        if(contact1 == polygon1->vertices().size() - 1 && contact2 == polygon2->vertices().size() - 1)
        {
            alVector2 positionDirection = polygon2->position() - polygon1->position();
            if(m_minimumPenetration * positionDirection / abs(m_minimumPenetration * positionDirection) == 1)
                m_minimumPenetration *= -1;
            result = true;
        }
    }
    return std::pair<bool, alVector2>(result, m_minimumPenetration);
}


int alSATCollisionDetector::polygonSATDetection(alPolygon *p1, alPolygon *p2)
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
        minVector1 += p1->position();
        maxVector1 += p1->position();
        minVector2 += p1->position();
        maxVector2 += p1->position();
        float dt1 = b1_max - b2_min;
        float dt2 = b2_max - b1_min;
        float min = abs(dt1) > abs(dt2) ? dt2 : dt1;

        if((b2_min > b1_min && b2_min < b1_max) || (b2_max > b1_min && b2_max < b1_max) ||
                (b1_min > b2_min && b1_max < b2_max) || (b2_min > b1_min && b1_max > b2_max))
            contactAxis++;


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
    return contactAxis;
}

bool alSATCollisionDetector::circleSATDetection(alCircle *body1, alPolygon *body2)
{
    if(body1 == nullptr || body2 == nullptr)
        return false;
    ///Attention the body order!
    alPolygon polygon = *body2;
    alCircle circle = *body1;
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


        if((b2_min > b1_min && b2_min < b1_max) || (b2_max > b1_min && b2_max < b1_max) ||
                (b1_min > b2_min && b1_max < b2_max) || (b2_min > b1_min && b1_max > b2_max))
            contactAxis++;
        float dt1 = b1_max - b2_min;
        float dt2 = b2_max - b1_min;
        float min = abs(dt1) > abs(dt2) ? dt2 : dt1;


        minVector1 += body2->position();
        maxVector1 += body2->position();
        minVector2 += body2->position();
        maxVector2 += body2->position();
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

    minVector1 += body2->position();
    maxVector1 += body2->position();
    minVector2 += body2->position();
    maxVector2 += body2->position();

    float dt1 = b1_max - b2_min;
    float dt2 = b2_max - b1_min;
    float min = abs(dt1) > abs(dt2) ? dt2 : dt1;
    if((b2_min > b1_min && b2_min < b1_max) || (b2_max > b1_min && b2_max < b1_max))
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
        alVector2 positionDirection = body1->position() - body2->position();
        if(m_minimumPenetration * positionDirection / abs(m_minimumPenetration * positionDirection) == 1)
            m_minimumPenetration *= -1;
        m_penetrateLength = m_minimumPenetration.length();
        return true;
    }
    return false;
}

std::pair<bool, alVector2> alGJKCollisionDetector::detect(alBody *body1, alBody *body2)
{
    bool result = false;
    m_penetrateLength = 0;
    m_minimumPenetration.set(0, 0);

    if(body1 == nullptr || body2 == nullptr)
        return std::pair<bool, alVector2>(result, alVector2());

    result = doGJKDetection(body2, body1);

    return std::pair<bool, alVector2>(result, m_minimumPenetration);

}

alVector2 alGJKCollisionDetector::findFarthestPoint(alBody *body, const alVector2 &direction)
{
    alVector2 maxVector;
    if(body->type() == BodyType::Polygon)
    {
        std::vector<alVector2> vertices = static_cast<alPolygon*>(body)->getRotatedVertices();
        float max = 0.0f;
        foreach(alVector2 vertex, vertices)
        {
            if(max == 0.0f)
            {
                max = vertex * direction;
                maxVector = vertex;
            }
            else
            {
                if(max < vertex * direction){
                    max = vertex * direction;
                    maxVector = vertex;
                }
            }
        }
    }
    else if(body->type() == BodyType::Circle)
    {
        alCircle * circle = static_cast<alCircle*>(body);
        alVector2 d = direction;
        maxVector = d.getNormalizedVector() * circle->radius();
    }
    return maxVector;
}

alVector2 alGJKCollisionDetector::support(alBody *body1, alBody *body2, const alVector2 &direction)
{
    alVector2 p1 = findFarthestPoint(body1, direction) + body1->position();
    alVector2 p2 = findFarthestPoint(body2, direction * -1) + body2->position();
    return p1 - p2;
}


bool alGJKCollisionDetector::doGJKDetection(alBody *body1, alBody *body2)
{
    alSimplex simplex;

    alBody rigidBody1 = *body1;
    alBody rigidBody2 = *body2;
    alVector2 direction = rigidBody2.position() - rigidBody1.position();
    rigidBody1.position().set(0, 0);
    rigidBody2.position() = direction;

    //start gjk
    //scale vertices in order to optimize the epa iteration result
    scaleBody(&rigidBody1);
    scaleBody(&rigidBody2);

    int iteration = 0; 
    simplex.vertices().push_back(support(&rigidBody1, &rigidBody2, direction));
    direction.negate();
    //iteration start
    while(iteration <= alGJKIteration)
    {
        simplex.vertices().push_back(support(&rigidBody1, &rigidBody2, direction));
        if (simplex.getLastVertex() * direction <= 0) {
            return false;
        } else {
            if(simplex.containOrigin())
            {
                doEPA(&rigidBody1, &rigidBody2, simplex);
                return true;
            }
            else
            {
                direction = getDirection(simplex, true);
            }
        }
        iteration++;
    }
    return false;
}

void alGJKCollisionDetector::doEPA(alBody *body1, alBody *body2, alSimplex &simplex)
{
    if(simplex.vertices().size() == 3)
    {
        //epa iteration start
        int iteration = 0;
        while(iteration <= alEPAIteration)
        {
            alSimplex edge = findClosestEdge(simplex);

            alVector2 normal = getDirection(edge, false).getNormalizedVector();

            float originToEdge = abs(normal * edge.vertices()[0]);

            alVector2 p = support(body1, body2, normal);

            float d = p * normal;

            float difference = d - originToEdge;

            //optimization
            float even = sqrt(d * originToEdge);
            if (abs(difference) < alEPAEpsilon) {
                m_minimumPenetration = normal * even;
            } else {
                //check if we have already saved the same Minkowski Difference
                bool isExisted = false;
                foreach(alVector2 v, simplex.vertices())
                {
                    if(v == p)
                    {
                        isExisted = true;
                        break;
                    }
                }
                if(isExisted)
                {
                    m_minimumPenetration = normal * even;
                    return;
                }
                else
                    simplex.insertVertex(edge, p);
            }
            iteration++;
        }
    }
}



alVector2 alGJKCollisionDetector::getDirection(alSimplex &simplex, bool towardsOrigin = true)
{
    alVector2 result;
    int count = simplex.vertices().size();
    if(count == 3)
    {
        //planning the area, filtering area that the origin must not exist
        //using dot product, for example, if AO * AB >= 0, it means that the origin lay in this area
        //if the origin is found, remaining the two point of line, removing the third point
        //return the normal vector of this line vector
        //
        simplex = findClosestEdge(simplex);
    }
    //count = 2
    //make the vector always point to origin
    //generate perpendicular vector of line, making it point to the origin
    //qDebug() << "simplex 2!";
    alVector2 ao = simplex.vertices()[0] * -1;
    alVector2 ab = simplex.vertices()[1] - simplex.vertices()[0];
    alVector2 perpendicularOfAB = ab.perpendicularVector();
    result = perpendicularOfAB;
    if(ao * perpendicularOfAB < 0 && towardsOrigin)
        result.negate();
    else if(ao * perpendicularOfAB > 0 && !towardsOrigin)
        result.negate();
    return result;
}
alSimplex alGJKCollisionDetector::findClosestEdge(alSimplex simplex)
{
    int minimumDistance = INT_MAX;
    int minimumIndex1 = 0;
    int minimumIndex2 = 0;
    for(int i = 0;i < simplex.vertices().size(); i++)
    {
        int j = i == simplex.vertices().size() - 1 ? 0 : i + 1;
        alVector2 a = simplex.vertices()[i];
        alVector2 b = simplex.vertices()[j];
        alVector2 ab = b - a; // a -> b
        alVector2 ao = a * -1;
        alVector2 perpendicularOfAB = ab.perpendicularVector();
        alVector2 e = perpendicularOfAB;
        if(ao * perpendicularOfAB < 0)//perpendicular vector point to origin
            e = e * -1;
        alVector2 projection = e.getNormalizedVector() * (ao * e);

        if(minimumDistance > projection.length())
        {
            minimumIndex1 = i;
            minimumIndex2 = j;
            minimumDistance = projection.length();
        }
    }
    alSimplex result;
    result.vertices().push_back(simplex.vertices()[minimumIndex1]);
    result.vertices().push_back(simplex.vertices()[minimumIndex2]);
    return result;
}

void alGJKCollisionDetector::scaleBody(alBody *body)
{
    if(body->type() == BodyType::Circle)
    {
        alCircle * circle = static_cast<alCircle*>(body);
        circle->setRadius(circle->radius() * alEPAScale);
    }
    else if(body->type() == BodyType::Polygon)
    {
        alPolygon * polygon = static_cast<alPolygon*>(body);
        foreach(alVector2 v, polygon->vertices())
            v *= alEPAScale;
    }
}
bool alSimplex::containOrigin(){
    if(m_vertices.size() == 3)
    {
        float a = 0, b = 0, c = 0;
        alVector2 origin;
        alVector2 oa = origin - m_vertices[0];
        alVector2 ob = origin - m_vertices[1];
        alVector2 oc = origin - m_vertices[2];

        a = alCross2(oa, ob);
        b = alCross2(ob, oc);
        c = alCross2(oc, oa);

        if((a <= 0 && b <= 0 && c <= 0)||
                (a >= 0 && b >= 0 && c >= 0))
            return true;
        return false;
    }
    else if(m_vertices.size() == 2)
    {
        alVector2 origin;
        alVector2 oa = origin - m_vertices[0];
        alVector2 ob = origin - m_vertices[1];
        return alCross2(oa, ob) == 0;
    }
    else
        return false;

}

void alSimplex::insertVertex(alSimplex &edge, const alVector2 &vertex)
{
    //insert into vertices list before the index
    int targetIndex = 0;
    for(int i = 0;i < m_vertices.size();i++)
        if((m_vertices[i] == edge.vertices()[0] || m_vertices[i] == edge.vertices()[1]) && targetIndex < i)
            targetIndex = i;
	targetIndex = targetIndex == m_vertices.size() - 1 ? targetIndex + 1 : targetIndex;
    m_vertices.insert(m_vertices.begin() + targetIndex, vertex);
}
