#ifndef ALWORLD_H
#define ALWORLD_H
#include <QVector>
#include <QObject>
#include <alsettings.h>
#include <albody.h>
class alWorld
{
public:
    alWorld();
    void update();
private:
    QVector<alBody*> m_bodyList;
    alVec2 m_gravity;

};

#endif // ALWORLD_H