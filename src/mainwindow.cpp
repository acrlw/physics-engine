#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_rectangle.setPosition(alVecter2(200, 400));
    m_circle.setPosition(alVecter2(200, 200));
    m_circle.setRadius(50);
    m_circle.setAngle(360);
    m_circle.setAngularVelocity(20);
    m_circle.setAngularAcceleration(-2);
    m_rectangle.setAngle(-360);
    m_rectangle.setWidth(80);
    m_rectangle.setHeight(100);
    m_rectangle.setAngularVelocity(18);
    m_rectangle.setAngularAcceleration(-2);
    m_timer.setInterval(alTimerInterval);
    m_circle.setSleep(false);
    m_rectangle.setSleep(false);
    m_polygon.setSleep(false);
    alVecter2 v1(2, 2);
    alVecter2 a1 = v1.getNormalizedVector() * -3;
    m_circle.velocity() += v1;
    m_circle.acceleration() += a1;
    m_rectangle.velocity() += v1;
    m_rectangle.acceleration() += a1;
    connect(&m_timer,&QTimer::timeout,this,&MainWindow::processObjectMovement);

    m_timer.start();
    m_circleRenderer.circleList().append(&m_circle);
    m_rectangleRenderer.rectangleList().append(&m_rectangle);
    m_polygonRenderer.polygonList().append(&m_polygon);
    m_measurer.bodyList().append(&m_circle);
    m_measurer.bodyList().append(&m_rectangle);
    m_measurer.bodyList().append(&m_polygon);

    m_circleRenderer.setThickness(3);
    m_rectangleRenderer.setThickness(3);
    m_polygonRenderer.setThickness(3);
    m_circleRenderer.setAngleLineThickness(3);
    m_rectangleRenderer.setAngleLineThickness(3);
    m_polygonRenderer.setAngleLineThickness(3);

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

    m_polygon.vertices().push_back(alVecter2(4, 4) * 15);
    m_polygon.vertices().push_back(alVecter2(-4, 4) * 15);
    m_polygon.vertices().push_back(alVecter2(0, -6) * 15);
    m_polygon.vertices().push_back(alVecter2(4, 4) * 15);
    m_polygon.velocity() += v1;
    m_polygon.acceleration() += a1;
    m_polygon.setAngle(300);
    m_polygon.setAngularVelocity(30);
    m_polygon.setAngularAcceleration(-2);
    m_polygon.setPosition(alVecter2(200, 200));
    this->resize(1440, 900);
}
void MainWindow::processObjectMovement()
{
    if(m_mousePress && m_drag)
    {
            alVecter2 dp(m_mousePos.x() - m_circle.position().x(), m_mousePos.y() - m_circle.position().y());
            m_circle.velocity() += dp * alForceLengthRatio;
    }
    if(m_mousePress && m_drag2)
    {
            alVecter2 dp(m_mousePos.x() - m_rectangle.position().x(), m_mousePos.y() - m_rectangle.position().y());
            m_rectangle.velocity() += dp * alForceLengthRatio;
    }
    alVecter2 v = m_circle.velocity();

    alVecter2 v2 = m_rectangle.velocity();

    alVecter2 v3 = m_polygon.velocity();
    alVecter2 a1, a2, a3;
    //friction & static judgement
    if(v.length() - alStopThreshold < 0.0101)
    {
        a1 += alVecter2(0, 0);
        m_circle.velocity().set(0, 0);
    }
    else{
        a1 += v.getNormalizedVector() * -1;
    }
    if(v2.length() - alStopThreshold < 0.0101)
    {
        a2 += alVecter2(0, 0);
        m_rectangle.velocity().set(0, 0);
    }
    else{
        a2 += v2.getNormalizedVector() * -1;
    }
    if(v3.length() - alStopThreshold < 0.0101)
    {
        a3 += alVecter2(0, 0);
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
    m_drag = m_circleRenderer.isInArea(&m_circle,e->pos());
    m_drag2 = m_rectangleRenderer.isInArea(&m_rectangle, e->pos());
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
    w1.setPosition(alVecter2(0, this->height() / 2));
    w2.setPosition(alVecter2(this->width() / 2, this->height()));
    w3.setPosition(alVecter2(this->width(), this->height() / 2));
    w4.setPosition(alVecter2(this->width() / 2, 0));

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

