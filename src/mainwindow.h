#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QMouseEvent>
#include <albody.h>
#include <alrenderer.h>
#include <alcollisiondetector.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void processObjectMovement();
protected:
    void paintEvent(QPaintEvent *) override;
    void resizeEvent(QResizeEvent *e) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;

private:
    Ui::MainWindow *ui;

//    alCircle m_circle;
//    alCircle m_circle2;
//    alRectangle m_rectangle;
//    alRectangle m_rectangle2;
//    alRectangleRenderer m_rectangleRenderer;
//    alCircleRenderer m_circleRenderer;
//    alPolygonCircleCollisionDetector m_polygonCircleCD;
//    alPolygonPolygonCollisionDetector m_polygonPolygonCD;
//    alCircleCircleCollisionDetector m_circleCircleCD;
//    alMeasurer m_measurer;

    QTimer m_timer;
    QPointF m_mousePos;
    bool m_drag = false;
    bool m_drag2 = false;
    bool m_mousePress = false;

    alPolygon m_polygon;
    alPolygon m_polygon2;
    alPolygonRenderer m_polygonRenderer;
    alWall w1,w2,w3,w4;
    alWallRenderer m_wallRenderer;
};
#endif // MAINWINDOW_H
