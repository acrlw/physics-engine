#ifndef ALRENDERER_H
#define ALRENDERER_H

#include <QObject>
#include <QPainter>
#include <QMouseEvent>
#include <QVector>
#include <QDebug>
#include <QPainterPath>
#include <albody.h>
class alRenderer : public QObject
{
    Q_OBJECT
public:
    alRenderer(const bool visible = true , const QColor &centerColor = Qt::darkBlue);
    enum RenderType{
        Measurer,
        Circle,
        Polygon,
        Wall,
        World
    };


    bool visible() const
    {
        return m_visible;
    }

    void setVisible(bool visible)
    {
        m_visible = visible;
    }
    qreal angleLineThickness() const
    {
        return m_angleLineThickness;
    }

    void setAngleLineThickness(const qreal &angleLineThickness)
    {
        m_angleLineThickness = angleLineThickness;
    }

    void renderMassCenter(QPainter * e, alBody *body, const QColor &color);

    RenderType type() const
    {
        return m_type;
    }

    void setType(const RenderType &type)
    {
        m_type = type;
    }

    QPen& strokePen()
    {
        return m_strokePen;
    }

    void setStrokePen(const QPen &strokePen)
    {
        m_strokePen = strokePen;
    }


    QBrush& fillBrush()
    {
        return m_fillBrush;
    }

    void setFillBrush(const QBrush &fillBrush)
    {
        m_fillBrush = fillBrush;
    }

    qreal thickness() const
    {
        return m_thickness;
    }

    void setThickness(const qreal &thickness)
    {
        m_thickness = thickness;
    }



public slots:
    void handleMousePressEvent(QMouseEvent *e);
    void handleMouseMoveEvent(QMouseEvent *e);
    void handleMouseReleaseEvent(QMouseEvent *e);
    void handlePaintEvent(QPainter *e);
protected:
    bool m_visible;
    qreal m_angleLineThickness;
    QColor m_centerColor;
    QBrush m_fillBrush;
    QPen m_strokePen;
    QPen b;
    qreal m_thickness;
    RenderType m_type;
};

class alMeasurer : public alRenderer{
    Q_OBJECT

public:
    alMeasurer(const qreal arrowSize = 8, const qreal fontSize = 10, const qreal distance = 20, const qreal thickness = 2, const QColor &accelerationColor = Qt::darkRed, const QColor &velocityColor = Qt::darkCyan);
    inline QVector<alBody *>& bodyList()
    {
        return m_bodyList;
    }
    inline void setBodyList(const QVector<alBody *> &bodyList)
    {
        m_bodyList = bodyList;
    }
    inline bool visible() const
    {
        return m_visible;
    }
    inline void setVisible(bool visible)
    {
        m_visible = visible;
    }

    qreal arrowSize() const
    {
        return m_arrowSize;
    }

    void setArrowSize(qreal arrowSize)
    {
        m_arrowSize = arrowSize;
    }
    qreal textDistance() const
    {
        return m_textDistance;
    }

    void setTextDistance(const qreal &textDistance)
    {
        m_textDistance = textDistance;
    }

    qreal fontSize() const
    {
        return m_fontSize;
    }

    void setFontSize(const qreal &fontSize)
    {
        m_fontSize = fontSize;
    }
    QColor velocityColor() const
    {
        return m_velocityColor;
    }

    void setVelocityColor(const QColor &velocityColor)
    {
        m_velocityColor = velocityColor;
    }

    QColor accelerationColor() const
    {
        return m_accelerationColor;
    }

    void setAccelerationColor(const QColor &accelerationColor)
    {
        m_accelerationColor = accelerationColor;
    }

    void renderArrow(QPainter *painter, const QPointF &start, const QPointF &end, const QString &text, const QColor& color);

public slots:

    void render(QPainter *e) ;
private:
    QColor m_accelerationColor;
    QColor m_velocityColor;
    QPainter * m_painter;
    QVector<alBody *> m_bodyList;
    bool m_visible = true;
    qreal m_arrowSize;
    qreal m_fontSize;
    qreal m_textDistance;
};

class alCircleRenderer : public alRenderer{
    Q_OBJECT

public:
    alCircleRenderer(alCircle * circlePtr = nullptr,const qreal angleLineThickness = 1);

    inline alCircle *circle() const
    {
        return m_circle;
    }

    inline void setCircle(alCircle *circle)
    {
        m_circle = circle;
    }
    inline bool isInArea(const QPointF& pos)
    {
        return alVec2(pos.x() - m_circle->position().x(), pos.y() - m_circle->position().y()).lengthSquare() <= m_circle->radius() * m_circle->radius();
    }


public slots:
    void render(QPainter *e) ;

private:
    alCircle *m_circle;
};
class alPolygonRenderer : public alRenderer
{
    Q_OBJECT
public:
    alPolygonRenderer(){

    }
    alPolygon *polygon() const
    {
        return m_polygon;
    }

    void setPolygon(alPolygon *polygon)
    {
        m_polygon = polygon;
    }

    static QPolygonF updateVertices(alPolygon *polygon);
public slots:
    void render(QPainter *e);
private:
    alPolygon *m_polygon;
};
class alRectangleRenderer : public alRenderer
{
    Q_OBJECT
public:
    alRectangleRenderer(alRectangle * rectPtr = nullptr, const qreal borderThickness = 1);

    alRectangle *rectangle() const
    {
        return m_rectangle;
    }

    void setRectangle(alRectangle *rectangle)
    {
        m_rectangle = rectangle;
        m_rectVertex = alPolygonRenderer::updateVertices(m_rectangle);
    }

    inline bool isInArea(const QPointF& pos)
    {
        return (abs(pos.x() - m_rectangle->position().x()) < m_rectangle->width() / 2) &&
                (abs(pos.y() - m_rectangle->position().y()) < m_rectangle->height() / 2);
    }
public slots:
    void render(QPainter *e) ;
protected:
    QPolygonF m_rectVertex;
    alRectangle *m_rectangle;
};

class alWallRenderer: public alRenderer{
    Q_OBJECT
public:
    alWallRenderer(){
        m_type = RenderType::Wall;
    }
    QVector<alWall*> &wallList()
    {
        return m_wallList;
    }
    void setWallList(const QVector<alWall*> &wallList)
    {
        m_wallList = wallList;
    }

public slots:
    void render(QPainter * e);
private:
    QVector<alWall*> m_wallList;
};

class alWorldRenderer: public alRenderer
{
public:
    alWorldRenderer() {
        m_type = RenderType::World;
    }
};
#endif // ALRENDERER_H
