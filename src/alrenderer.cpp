#include "alrenderer.h"



alRenderer::alRenderer(const bool visible, const qreal thickness, const QColor strikeColor, const QColor fillcolor, const QColor &centerColor)
    : QObject(), m_visible(visible), m_angleLineThickness(1), m_thickness(thickness), m_strokeColor(strikeColor), m_fillColor(fillcolor), m_centerColor(centerColor)
{

}

void alRenderer::renderMassCenter(QPainter * e, alBody *body, const QColor &color)
{
    e->setPen(QPen(color, 4, Qt::SolidLine, Qt::RoundCap));
    e->drawPoint(QPointF(body->position().x(), body->position().y()));
}

void alRenderer::handleMousePressEvent(QMouseEvent *e)
{

}

void alRenderer::handleMouseMoveEvent(QMouseEvent *e)
{

}

void alRenderer::handleMouseReleaseEvent(QMouseEvent *e)
{

}

void alRenderer::handlePaintEvent(QPainter *e)
{

}



alMeasurer::alMeasurer(const qreal arrowSize, const qreal fontSize, const qreal distance, const QColor& accelerationColor, const QColor& velocityColor):
    alRenderer(), m_accelerationColor(accelerationColor), m_velocityColor(velocityColor), m_arrowSize(arrowSize), m_fontSize(fontSize), m_textDistance(distance)
{

}

void alMeasurer::renderArrow(QPainter * painter,const QPointF& start, const QPointF& end, const QString& text, const QColor& color)
{
    painter->setPen(QPen(color, m_thickness, Qt::SolidLine, Qt::RoundCap));
    QLineF arrowLine(start, end);
    qreal dist = arrowLine.length();
    painter->drawLine(arrowLine);
    //draw arrow head
    QPolygonF head;

    double angle = std::atan2(-arrowLine.dy(), arrowLine.dx());

    QPointF arrowP1 = arrowLine.p2() - QPointF(sin(angle + M_PI / 3) * m_arrowSize,
                                               cos(angle + M_PI / 3) * m_arrowSize);
    QPointF arrowP2 = arrowLine.p2() - QPointF(sin(angle + M_PI - M_PI / 3) * m_arrowSize,
                                               cos(angle + M_PI - M_PI / 3) * m_arrowSize);

    head.clear();
    head << arrowLine.p2() << arrowP1 << arrowP2;

    QPainterPath path;
    path.addPolygon(head);
    painter->fillPath(path,QBrush(color));
    //draw text

    qreal angleDegree = -angle * 180 / M_PI;
    double textRadiusAngle = M_PI/2 - angle;
    painter->setFont(QFont("Consolas", m_fontSize));
    if(angleDegree >= 90 || angleDegree <= -90)//2 and 3 quadrant
    {
        QPointF ph1 = (arrowLine.p2() + QPointF(cos(textRadiusAngle),sin(textRadiusAngle)) * m_textDistance);
        QPointF ph2 = (arrowLine.p1() + QPointF(cos(textRadiusAngle),sin(textRadiusAngle)) * m_textDistance);
        QLineF lf1(ph1, ph2);
        painter->translate(ph1);
        qreal arc = std::atan2(-lf1.dy(),lf1.dx());
        qreal degree = arc * 180 / M_PI;
        painter->rotate(-degree);
        painter->drawText(QPointF(-m_textDistance + dist / 2, 3 * m_textDistance),text);
        painter->rotate(degree);
        painter->translate(-ph1);
    }
    else
    {
        QPointF f(arrowLine.p1() + QPointF(cos(textRadiusAngle),sin(textRadiusAngle)) * m_textDistance);
        painter->translate(f);
        painter->rotate(angleDegree);
        painter->drawText(QPointF(dist / 2 - m_textDistance, - 2 *m_textDistance),text);
        painter->rotate(-angleDegree);
        painter->translate(-f);
    }
}

void alMeasurer::render(QPainter *e)
{
    if(m_visible)
    {
        foreach (alBody * m, m_bodyList) {
            QPointF mass(m->position().x(),m->position().y());
            QPointF velocity = mass + QPointF(m->velocity().x(),m->velocity().y()) * alLengthForceRatio;
            QPointF acceleration = mass + QPointF(m->acceleration().x(),m->acceleration().y()) * alLengthForceRatio * alLengthForceRatio;
            if(m->velocity().lengthSquare() > 0)
                renderArrow(e, mass, velocity, "v = " + QString::number(static_cast<int>(m->velocity().length())) + " m/s", m_velocityColor);
            if(m->acceleration().lengthSquare() > 0)
                renderArrow(e, mass, acceleration, "a = " + QString::number(static_cast<int>(m->acceleration().length())) + " m/s2", m_accelerationColor);
        }
    }
}

alCircleRenderer::alCircleRenderer(alCircle *circlePtr, const qreal angleLineThickness):
    alRenderer(), m_circle(circlePtr)
{
    m_angleLineThickness = angleLineThickness;
}
void alCircleRenderer::render(QPainter *e)
{
    if(m_visible)
    {
        renderMassCenter(e, m_circle, m_strokeColor);
        //draw circle body
        e->setPen(QPen(m_strokeColor, m_thickness, Qt::SolidLine, Qt::RoundCap));
        QRectF r(m_circle->position().x() - m_circle->radius(),m_circle->position().y() - m_circle->radius(),m_circle->radius() * 2,m_circle->radius() * 2);

        e->drawEllipse(r);
        //draw angle line
        alVec2 v = alRot(m_circle->angle()) * alVec2(m_circle->radius(), 0);
        QLineF l = QLineF(m_circle->position().x(), m_circle->position().y(),m_circle->position().x() + v.x(), m_circle->position().y() + v.y());
        e->setPen(QPen(m_strokeColor, m_angleLineThickness, Qt::SolidLine, Qt::RoundCap));
        e->drawLine(l);
        //fill circle
        m_fillColor.setAlphaF(0.12);
        QPainterPath p;
        p.addEllipse(r);
        e->fillPath(p,QBrush(m_fillColor));
    }
}


alRectangleRenderer::alRectangleRenderer(alRectangle *rectPtr, const qreal borderThickness):
    alRenderer(), m_rectangle(rectPtr)
{
    m_thickness = borderThickness;
}

void alRectangleRenderer::render(QPainter *e)
{
    if(m_visible)
    {
        m_rectVertex = updateRectangle(m_rectangle);
        renderMassCenter(e, m_rectangle, m_strokeColor);
        //render angle line
        alVec2 v = alRot(m_rectangle->angle()) * alVec2(m_rectangle->width() / 2, 0);
        QLineF l = QLineF(m_rectangle->position().x(), m_rectangle->position().y(),m_rectangle->position().x() + v.x(), m_rectangle->position().y() + v.y());
        e->setPen(QPen(m_strokeColor, m_angleLineThickness, Qt::SolidLine, Qt::RoundCap));
        e->drawLine(l);
        e->setPen(QPen(m_strokeColor, m_thickness, Qt::SolidLine, Qt::RoundCap));
        e->drawPolygon(m_rectVertex);
        m_fillColor.setAlphaF(0.1);
        QPainterPath p;
        p.addPolygon(m_rectVertex);
        e->fillPath(p,QBrush(m_fillColor));
    }
}

QPolygonF alRectangleRenderer::updateRectangle(alRectangle* rectangle)
{
    QPolygonF vertex;
    foreach (alVec2 v, rectangle->getActualVertices()) {
        vertex.append(QPointF(v.x(), v.y()));
    }
    return vertex;
}


void alWallRenderer::render(QPainter *e)
{
    if(m_visible)
    {
        foreach (alWall* w, m_wallList) {
            QPolygonF pw = alRectangleRenderer::updateRectangle(w);
            e->setPen(QPen(m_strokeColor, m_thickness, Qt::SolidLine, Qt::RoundCap));
            e->drawPolygon(pw);
            m_fillColor.setAlphaF(0.1);
            QPainterPath p;
            p.addPolygon(pw);
            e->fillPath(p,QBrush(m_fillColor));
        }
    }
}
