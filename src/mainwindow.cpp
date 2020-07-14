#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_rectangle.setPosition(alVec2(200, 400));
    m_circle.setPosition(alVec2(200, 200));
    m_circle.setRadius(60);
    m_circle.setAngle(360);
    m_circle.setAngularVelocity(20);
    m_circle.setAngularAcceleration(-2);
    m_rectangle.setAngle(-360);
    m_rectangle.setWidth(255);
    m_rectangle.setHeight(136);
    m_rectangle.setAngularVelocity(18);
    m_rectangle.setAngularAcceleration(-2);
    m_timer.setInterval(alTimerInterval);
    m_circle.setSleep(false);
    m_rectangle.setSleep(false);
    m_polygon.setSleep(false);
    alVec2 v1(2, 2);
    alVec2 a1 = v1.getNormalizedVector() * -3;
    m_circle.velocity() += v1;
    m_circle.acceleration() += a1;
    m_rectangle.velocity() += v1;
    m_rectangle.acceleration() += a1;
    connect(&m_timer,&QTimer::timeout,this,&MainWindow::processObjectMovement);

    m_timer.start();
    m_circleRenderer.setCircle(&m_circle);
    m_rectangleRenderer.setRectangle(&m_rectangle);
    m_measurer.bodyList().append(&m_circle);
    m_measurer.bodyList().append(&m_rectangle);
    m_circleRenderer.setThickness(3);


    m_circleRenderer.setAngleLineThickness(2);
    m_rectangleRenderer.setThickness(3);
    m_rectangleRenderer.setAngleLineThickness(2);

    QColor bc2(Qt::blue);
    bc2.setAlphaF(0.12);
    m_rectangleRenderer.fillBrush().setColor(bc2);

    m_rectangleRenderer.strokePen().setColor(Qt::darkBlue);
    m_measurer.setVelocityColor(Qt::darkMagenta);
    m_measurer.setAccelerationColor(Qt::darkCyan);

    m_wallRenderer.wallList().append(&w1);
    m_wallRenderer.wallList().append(&w2);
    m_wallRenderer.wallList().append(&w3);
    m_wallRenderer.wallList().append(&w4);

    m_polygon.vertices().push_back(alVec2(3, 4) * 20);
    m_polygon.vertices().push_back(alVec2(1, 8) * 20);
    m_polygon.vertices().push_back(alVec2(-1, 5) * 20);
    m_polygon.vertices().push_back(alVec2(-8, 1) * 20);
    m_polygon.vertices().push_back(alVec2(-3, -4) * 20);
    m_polygon.vertices().push_back(alVec2(-1, -8) * 20);
    m_polygon.vertices().push_back(alVec2(3, -4) * 20);
    m_polygon.vertices().push_back(alVec2(9, -2) * 20);
    m_polygon.vertices().push_back(alVec2(3, 4) * 20);
    m_polygon.velocity() += v1;
    m_polygon.acceleration() += a1;
    m_polygon.setAngle(-136);
    m_polygon.setAngularVelocity(10);
    m_polygon.setAngularAcceleration(-2);
    m_polygon.setPosition(alVec2(200, 200));
    m_polygonRenderer.setThickness(2);
    m_polygonRenderer.setAngleLineThickness(2);
    m_polygonRenderer.setPolygon(&m_polygon);
    this->resize(1440, 900);
}
void MainWindow::processObjectMovement()
{
    if(m_mousePress && m_drag)
    {
            alVec2 dp(m_mousePos.x() - m_circle.position().x(), m_mousePos.y() - m_circle.position().y());
            m_circle.velocity() += dp * alForceLengthRatio;
    }
    if(m_mousePress && m_drag2)
    {
            alVec2 dp(m_mousePos.x() - m_rectangle.position().x(), m_mousePos.y() - m_rectangle.position().y());
            m_rectangle.velocity() += dp * alForceLengthRatio;
    }
    alVec2 v = m_circle.velocity();

    alVec2 v2 = m_rectangle.velocity();

    alVec2 v3 = m_polygon.velocity();
    alVec2 a1, a2, a3;
    //friction & static judgement
    if(v.length() - alStopThreshold < 0.0101)
    {
        a1 += alVec2(0, 0);
        m_circle.velocity().set(0, 0);
    }
    else{
        a1 += v.getNormalizedVector() * -1;
    }
    if(v2.length() - alStopThreshold < 0.0101)
    {
        a2 += alVec2(0, 0);
        m_rectangle.velocity().set(0, 0);
    }
    else{
        a2 += v2.getNormalizedVector() * -1;
    }
    if(v3.length() - alStopThreshold < 0.0101)
    {
        a3 += alVec2(0, 0);
        m_polygon.velocity().set(0, 0);
    }
    else{
        a3 += v3.getNormalizedVector() * -1;
    }
    float an = m_rectangle.angularVelocity();
    if(an * (an + m_rectangle.angularAcceleration() * alDeltaTime) < 0)
    {
        m_rectangle.setAngularVelocity(0);
        m_rectangle.setAngularAcceleration(0);
    }
    float bn = m_circle.angularVelocity();
    if(bn * (bn + m_circle.angularAcceleration() * alDeltaTime) < 0)
    {
        m_circle.setAngularVelocity(0);
        m_circle.setAngularAcceleration(0);
    }
    float cn = m_polygon.angularVelocity();
    if(cn * (cn + m_polygon.angularAcceleration() * alDeltaTime) < 0)
    {
        m_polygon.setAngularVelocity(0);
        m_polygon.setAngularAcceleration(0);
    }
    m_circle.acceleration() = a1;
    m_rectangle.acceleration() = a2;
    m_polygon.acceleration() = a3;
    m_circle.update();
    m_rectangle.update();
    m_polygon.update();
    repaint();
}
void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    m_circleRenderer.render(&painter);
    m_rectangleRenderer.render(&painter);
    m_measurer.render(&painter);
    m_wallRenderer.render(&painter);
    m_polygonRenderer.render(&painter);
}
void MainWindow::mousePressEvent(QMouseEvent * e)
{
    m_circleRenderer.handleMousePressEvent(e);
    m_mousePress = true;
    m_drag = m_circleRenderer.isInArea(e->pos());
    m_drag2 = m_rectangleRenderer.isInArea(e->pos());
    qDebug() << "press";

}
void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    m_circleRenderer.handleMouseReleaseEvent(e);
    m_mousePress = false;
    qDebug() << "release";
}
void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    m_circleRenderer.handleMouseMoveEvent(e);
    if(m_mousePress)
    {
        m_mousePos = e->pos();
    }
    else
    {
        m_mousePos = QPointF(0, 0);
    }
}
void MainWindow::resizeEvent(QResizeEvent *e)
{
    m_circle.position().set(this->width() / 2, this->height() / 2);
    w1.setPosition(alVec2(0, this->height() / 2));
    w2.setPosition(alVec2(this->width() / 2, this->height()));
    w3.setPosition(alVec2(this->width(), this->height() / 2));
    w4.setPosition(alVec2(this->width() / 2, 0));

    w1.setHeight(this->height());
    w3.setHeight(this->height());

    w2.setWidth(this->width());
    w4.setWidth(this->width());
    this->resize(e->size());
}
MainWindow::~MainWindow()
{
    delete ui;
}

