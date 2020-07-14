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
    alCircle m_circle;
    alRectangle m_rectangle;
    alPolygon m_polygon;
    QTimer m_timer;
    alCircleRenderer m_circleRenderer;
    alRectangleRenderer m_rectangleRenderer;
    alPolygonRenderer m_polygonRenderer;
    alMeasurer m_measurer;
    bool m_mousePress = false;
    QPointF m_mousePos;
    bool m_drag = false;
    bool m_drag2 = false;

    alWall w1,w2,w3,w4;
    alWallRenderer m_wallRenderer;
};
#endif // MAINWINDOW_H
