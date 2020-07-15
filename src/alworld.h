#ifndef ALWORLD_H
#define ALWORLD_H
#include <vector>
#include <alsettings.h>
#include <albody.h>
class alWorld
{
    enum WorldType{
        Vertical,
        Horizontal
    };

public:
    alWorld(){
        m_gravity = alVecter2(0, alGravity);
        m_airFrictionCoefficient = alAirFrictionCoefficient;
        m_planeFrictionCoefficient = alFrictionCoefficient;
    }

    std::vector<alBody *>& bodyList()
    {
        return m_bodyList;
    }

    void setBodyList(const std::vector<alBody *> &bodyList)
    {
        m_bodyList = bodyList;
    }

    std::vector<alWall *>& wallList()
    {
        return m_wallList;
    }

    void setWallList(const std::vector<alWall *> &wallList)
    {
        m_wallList = wallList;
    }


    void update();

    void addBody(alBody * body){
        m_bodyList.push_back(body);
    }
    void addWall(alWall * wall)
    {
        m_wallList.push_back(wall);
    }


    alVecter2 gravity() const
    {
        return m_gravity;
    }

    void setGravity(const alVecter2 &gravity)
    {
        m_gravity = gravity;
    }

    float airFrictionCoefficient() const
    {
        return m_airFrictionCoefficient;
    }

    void setAirFrictionCoefficient(float airFrictionCoefficient)
    {
        m_airFrictionCoefficient = airFrictionCoefficient;
    }

    float planeFrictionCoefficient() const
    {
        return m_planeFrictionCoefficient;
    }

    void setPlaneFrictionCoefficient(float planeFrictionCoefficient)
    {
        m_planeFrictionCoefficient = planeFrictionCoefficient;
    }


private:
    std::vector<alBody *> m_bodyList;
    std::vector<alWall *> m_wallList;
    alVecter2 m_gravity;
    float m_airFrictionCoefficient;
    float m_planeFrictionCoefficient;


};

#endif // ALWORLD_H
