#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    alVector2 v1(2, 2);
    alVector2 a1 = v1.getNormalizedVector() * -3;


    //    m_measurer.setVisible(false);
    //    m_measurer.bodyList().append(&m_circle);
    //    m_measurer.bodyList().append(&m_rectangle);
    //    m_measurer.bodyList().append(&m_polygon);
    //    m_measurer.bodyList().append(&m_circle2);
    //    m_measurer.bodyList().append(&m_rectangle2);
    //    m_measurer.bodyList().append(&m_polygon2);
    //    m_measurer.setVelocityColor(Qt::darkMagenta);
    //    m_measurer.setAccelerationColor(Qt::darkCyan);

        m_circle.setPosition(alVector2(200, 200));
        m_circle.setRadius(80);
        m_circle.setAngle(0);
        m_circle.setSleep(false);

//        m_circle2.setPosition(alVector2(450, 500));
//        m_circle2.setRadius(35);
//        m_circle2.setAngle(360);
//    //    m_circle2.setAngularVelocity(20);
//    //    m_circle2.setAngularAcceleration(-2);
//        m_circle2.setSleep(false);
    //    m_circle2.velocity() += v1;
    //    m_circle2.acceleration() += a1;

        m_circleRenderer.setThickness(2);
        m_circleRenderer.setAngleLineThickness(2);
        m_circleRenderer.circleList().append(&m_circle);
        //m_circleRenderer.circleList().append(&m_circle2);

    //    m_rectangle.setPosition(alVector2(300, 150));
    //    m_rectangle.setAngle(-360);
    //    m_rectangle.setWidth(80);
    //    m_rectangle.setHeight(100);
    //    m_rectangle.setAngularVelocity(18);
    //    m_rectangle.setAngularAcceleration(-2);
    //    m_rectangle.setSleep(false);
    //    m_rectangle.velocity() += v1;
    //    m_rectangle.acceleration() += a1;

    //    m_rectangle2.setPosition(alVector2(200, 400));
    //    m_rectangle2.setAngle(-360);
    //    m_rectangle2.setWidth(90);
    //    m_rectangle2.setHeight(40);
    //    m_rectangle2.setAngularVelocity(25);
    //    m_rectangle2.setAngularAcceleration(-2);
    //    m_rectangle2.setSleep(false);
    //    m_rectangle2.velocity() += v1;
    //    m_rectangle2.acceleration() += a1;
    //    m_rectangleRenderer.rectangleList().append(&m_rectangle);
    //    m_rectangleRenderer.rectangleList().append(&m_rectangle2);

    //    m_rectangleRenderer.setThickness(3);
    //    m_rectangleRenderer.setAngleLineThickness(3);

    //    QColor bc2(Qt::blue);
    //    bc2.setAlphaF(0.12);
    //    m_rectangleRenderer.fillBrush().setColor(bc2);
    //    m_rectangleRenderer.strokePen().setColor(Qt::darkBlue);



    m_polygon.addVertex(alVector2(4, 3) * 30);
    m_polygon.addVertex(alVector2(-2, 8) * 30);
    m_polygon.addVertex(alVector2(-6, 2) * 30);
    m_polygon.addVertex(alVector2(-4, -5) * 30);
    m_polygon.addVertex(alVector2(-2, -6) * 30);
    m_polygon.addVertex(alVector2(7, -4) * 30);
    m_polygon.addVertex(alVector2(4, 3) * 30);
    m_polygon.setPosition(alVector2(300, 460));
    m_polygon.setSleep(false);
    m_polygon.setAngle(36);

    m_polygon2.addVertex(alVector2(4, -4) * 20);
    m_polygon2.addVertex(alVector2(-4, -4) * 20);
    m_polygon2.addVertex(alVector2(0, 8) * 20);
    m_polygon2.addVertex(alVector2(4, -4) * 20);
    m_polygon2.setPosition(alVector2(480, 680));
    m_polygon2.setSleep(false);
    m_polygon2.setAngle(78);

    m_polygonRenderer.setThickness(2);
    m_polygonRenderer.setAngleLineThickness(2);
    m_polygonRenderer.polygonList().append(&m_polygon);
    m_polygonRenderer.polygonList().append(&m_polygon2);

    pccd1.setPolygon(&m_polygon);
    pccd1.setCircle(&m_circle);


    pccd2.setPolygon(&m_polygon2);
    pccd2.setCircle(&m_circle);

    ppcd1.setPolygon1(&m_polygon);
    ppcd1.setPolygon2(&m_polygon2);

    m_wallRenderer.wallList().append(&w1);
    m_wallRenderer.wallList().append(&w2);
    m_wallRenderer.wallList().append(&w3);
    m_wallRenderer.wallList().append(&w4);

    connect(&m_timer,&QTimer::timeout,this,&MainWindow::processObjectMovement);
    m_timer.setInterval(alTimerInterval);
    m_timer.start();
    this->resize(1440, 900);
}
void MainWindow::processObjectMovement()
{
    if(m_mousePress)
    {
        alVector2 mousePos(m_mousePos.x(), m_mousePos.y());
        alVector2 dp1 = mousePos - m_polygon.position();
        alVector2 dp2 = mousePos - m_circle.position();
        alVector2 dp3 = mousePos - m_polygon2.position();
        if(dp1.length() < 20)
        {
            m_polygon.position() = mousePos;
        }
        if(dp2.length() < 20)
        {
            m_circle.position() = mousePos;
        }
        if(dp3.length() < 20)
        {
            m_polygon2.position() = mousePos;
        }
    }

    repaint();
}
void MainWindow::paintEvent(QPaintEvent *e)
{

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    //    m_rectangleRenderer.render(&painter);
    //    m_measurer.render(&painter);
    QPen line(Qt::darkBlue, 1, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
    bool contact1 = pccd1.detect();
    bool contact3 = pccd2.detect();
    bool contact2 = ppcd1.detect();
    int circleTouch = 0;
    int polygonTouch = 0;
    int polygonTouch2 = 0;
    if(contact1){
        circleTouch++;
        polygonTouch++;
    }
    if(contact2){
        polygonTouch++;
        polygonTouch2++;
    }
    if(contact3)
    {
        polygonTouch2++;
        circleTouch++;
    }
    m_circle.setIsTouched(circleTouch);
    m_polygon.setIsTouched(polygonTouch);
    m_polygon2.setIsTouched(polygonTouch2);
    if(contact2)
    {
        m_polygon.position() += ppcd1.minimumPenetration();
        m_polygon2.position() -= ppcd1.minimumPenetration();
    }
    if(contact1)
    {
        m_polygon.position() += pccd1.minimumPenetration();
        m_circle.position() -= pccd1.minimumPenetration();
    }
    if(contact3)
    {
        m_polygon2.position() += pccd2.minimumPenetration();
        m_circle.position() -= pccd2.minimumPenetration();
    }
    m_wallRenderer.render(&painter);
    m_polygonRenderer.render(&painter);
    m_circleRenderer.render(&painter);
}
void MainWindow::mousePressEvent(QMouseEvent * e)
{
    m_mousePress = true;
    qDebug() << "press";

}
void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    m_mousePress = false;
    qDebug() << "release";
}
void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
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
    w1.setPosition(alVector2(0, this->height() / 2));
    w2.setPosition(alVector2(this->width() / 2, this->height()));
    w3.setPosition(alVector2(this->width(), this->height() / 2));
    w4.setPosition(alVector2(this->width() / 2, 0));

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

