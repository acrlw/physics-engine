#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    alVector2 v1(8, 2);

    //    std::vector<int> v;
    //    v.push_back(1);
    //    v.push_back(2);
    //    v.push_back(3);
    //    v.erase(v.begin());
    //    qDebug() << v[0];
    //    qDebug() << v[1];
    //    v.push_back(4);
    //    qDebug() << v[0];
    //    qDebug() << v[1];
    //    qDebug() << v[2];
    //    v.erase(v.begin() + 1);
    //    qDebug() << v[0];
    //    qDebug() << v[1];

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
    //        m_circle.velocity() += v1;
    //        m_circle.acceleration() += alVector2(0, 8);
    //        m_circle.setAngularVelocity(20);
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

//        m_polygon.addVertex(alVector2(4, 3) * 25);
//        m_polygon.addVertex(alVector2(3, 4) * 25);
//        m_polygon.addVertex(alVector2(0, 5) * 25);
//        m_polygon.addVertex(alVector2(-3, 4) * 25);
//        m_polygon.addVertex(alVector2(-4, 3) * 25);
//        m_polygon.addVertex(alVector2(-4, -3) * 25);
//        m_polygon.addVertex(alVector2(-3, -4) * 25);
//        m_polygon.addVertex(alVector2(0, -6) * 25);
//        m_polygon.addVertex(alVector2(3, -4) * 25);
//        m_polygon.addVertex(alVector2(4, -3) * 25);
//        m_polygon.addVertex(alVector2(4, 3) * 25);
    m_polygon.addVertex(alVector2(1, 4) * 15);
    m_polygon.addVertex(alVector2(-1, 4) * 15);
    m_polygon.addVertex(alVector2(-3, 0) * 15);
    m_polygon.addVertex(alVector2(-2, -6) * 15);
    m_polygon.addVertex(alVector2(0, -8) * 15);
    m_polygon.addVertex(alVector2(3, -6) * 15);
    m_polygon.addVertex(alVector2(4, 4) * 15);
    m_polygon.addVertex(alVector2(1, 4) * 15);

        //m_polygon.addVertex(alVector2(0, 3) * 15);
        //m_polygon.addVertex(alVector2(-3, -2) * 15);
        //m_polygon.addVertex(alVector2(4, -3) * 15);
        //m_polygon.addVertex(alVector2(0, 3) * 15);
    m_polygon.setPosition(alVector2(250, 650));
    m_polygon.setAngle(36);
    m_polygon.setSleep(false);

//        m_polygon2.addVertex(alVector2(3, 4) * 25);
//        m_polygon2.addVertex(alVector2(-3, 4) * 25);
//        m_polygon2.addVertex(alVector2(-3, -5) * 25);
//        m_polygon2.addVertex(alVector2(3, -5) * 25);
//        m_polygon2.addVertex(alVector2(3, 4) * 25);

    m_polygon2.addVertex(alVector2(0, 5) * 15);
    m_polygon2.addVertex(alVector2(-2, 3) * 15);
    m_polygon2.addVertex(alVector2(0, -8) * 15);
    m_polygon2.addVertex(alVector2(2, 3) * 15);
    m_polygon2.addVertex(alVector2(0, 5) * 15);

        //m_polygon2.addVertex(alVector2(2, 0) * 15);
        //m_polygon2.addVertex(alVector2(0, 2) * 15);
        //m_polygon2.addVertex(alVector2(-2, -2) * 15);
        //m_polygon2.addVertex(alVector2(2, 0) * 15);
    m_polygon2.setPosition(alVector2(360, 680));
    m_polygon2.setAngle(-39);
    m_polygon2.setSleep(false);

    m_polygonRenderer.setThickness(2);
    m_polygonRenderer.setAngleLineThickness(2);
    m_polygonRenderer.polygonList().append(&m_polygon);
    m_polygonRenderer.polygonList().append(&m_polygon2);

    //    pccd1.setCircle(&m_circle);
    //        pccd1.setPolygon(&w1);

    //        pccd2.setCircle(&m_circle);
    //        pccd2.setPolygon(&w2);

    //        pccd3.setCircle(&m_circle);
    //        pccd3.setPolygon(&w3);

    //        pccd4.setCircle(&m_circle);
    //        pccd4.setPolygon(&w4);

    //        ppcd1.setPolygon1(&m_polygon);
    //        ppcd1.setPolygon2(&w1);

    //        ppcd2.setPolygon1(&m_polygon);
    //        ppcd2.setPolygon2(&w2);

    //        ppcd3.setPolygon1(&m_polygon);
    //        ppcd3.setPolygon2(&w3);

    //        ppcd4.setPolygon1(&m_polygon);
    //        ppcd4.setPolygon2(&w4);

    //    ppcdObject.setPolygon1(&m_polygon);
    //    ppcdObject.setPolygon2(&m_polygon2);

    //    pccdObject.setCircle(&m_circle);
    //    pccdObject.setPolygon(&m_polygon);


    m_wallRenderer.wallList().append(&w1);
    m_wallRenderer.wallList().append(&w2);
    m_wallRenderer.wallList().append(&w3);
    m_wallRenderer.wallList().append(&w4);

    connect(&m_timer,&QTimer::timeout,this,&MainWindow::processObjectMovement);
    m_timer.setInterval(alTimerInterval);
    m_timer.start();
    this->resize(1920, 1080);
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


    m_polygon.update();
    m_polygon2.update();
    m_circle.update();
    repaint();
}
void MainWindow::paintEvent(QPaintEvent *e)
{

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    //    m_rectangleRenderer.render(&painter);
    //    m_measurer.render(&painter);
    int circleTouch = 0;
    if(m_mousePress)
    {
        QPen st(Qt::blue, 6, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        painter.setPen(st);
        painter.drawPoint(m_mouseStart);
        QPen ed(Qt::blue, 6, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        painter.setPen(ed);
        painter.drawPoint(m_mousePos);
        QPen line(Qt::darkCyan, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        painter.setPen(line);
        painter.drawLine(m_mouseStart, m_mousePos);
    }

    alSATCollisionDetector sat;
    std::pair<bool, alVector2> result = sat.detect(&m_polygon, &m_circle);

    m_polygon.setIsTouched(result.first);
	m_circle.setIsTouched(result.first);
        if(result.first)
        {
            m_polygon.position() += result.second;
            qDebug () << "penetration: " << result.second.x() << ", " << result.second.y();
        }


    m_wallRenderer.render(&painter);
    m_polygonRenderer.render(&painter);
    m_circleRenderer.render(&painter);
}
void MainWindow::mousePressEvent(QMouseEvent * e)
{
    m_mousePress = true;
    m_mouseStart = e->pos();
    qDebug() << "press";

}
void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    m_mousePress = false;
    m_mousePos = e->pos();
    QPointF dp(m_mousePos - m_mouseStart);
    alVector2 f1(dp.x(), dp.y());
    alVector2 massPos = m_polygon.massPosition() + m_polygon.position();
    alVector2 mousePos(m_mousePos.x(), m_mousePos.y());
    qDebug () << "torque: " << alCross2(mousePos - massPos, f1);
    m_polygon.setTorque(alCross2(mousePos - massPos, f1) * 10);
    m_polygon.setForces(f1);
    m_circle.setTorque(alCross2(mousePos - massPos, f1) * 10);
    m_circle.setForces(f1);
    qDebug() << "release";
}
void MainWindow::mouseMoveEvent(QMouseEvent *e)
{

    m_mousePos = e->pos();
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

