#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    alVecter2 v1(2, 2);
    alVecter2 a1 = v1.getNormalizedVector() * -3;


    //    m_measurer.setVisible(false);
    //    m_measurer.bodyList().append(&m_circle);
    //    m_measurer.bodyList().append(&m_rectangle);
    //    m_measurer.bodyList().append(&m_polygon);
    //    m_measurer.bodyList().append(&m_circle2);
    //    m_measurer.bodyList().append(&m_rectangle2);
    //    m_measurer.bodyList().append(&m_polygon2);
    //    m_measurer.setVelocityColor(Qt::darkMagenta);
    //    m_measurer.setAccelerationColor(Qt::darkCyan);

    //    m_circle.setPosition(alVecter2(200, 200));
    //    m_circle.setRadius(50);
    //    m_circle.setAngle(360);
    //    m_circle.setAngularVelocity(20);
    //    m_circle.setAngularAcceleration(-2);
    //    m_circle.setSleep(false);
    //    m_circle.velocity() += v1;
    //    m_circle.acceleration() += a1;

    //    m_circle2.setPosition(alVecter2(450, 500));
    //    m_circle2.setRadius(135);
    //    m_circle2.setAngle(360);
    //    m_circle2.setAngularVelocity(20);
    //    m_circle2.setAngularAcceleration(-2);
    //    m_circle2.setSleep(false);
    //    m_circle2.velocity() += v1;
    //    m_circle2.acceleration() += a1;

    //    m_circleRenderer.setThickness(3);
    //    m_circleRenderer.setAngleLineThickness(3);
    //    m_circleRenderer.circleList().append(&m_circle);
    //    m_circleRenderer.circleList().append(&m_circle2);

    //    m_rectangle.setPosition(alVecter2(300, 150));
    //    m_rectangle.setAngle(-360);
    //    m_rectangle.setWidth(80);
    //    m_rectangle.setHeight(100);
    //    m_rectangle.setAngularVelocity(18);
    //    m_rectangle.setAngularAcceleration(-2);
    //    m_rectangle.setSleep(false);
    //    m_rectangle.velocity() += v1;
    //    m_rectangle.acceleration() += a1;

    //    m_rectangle2.setPosition(alVecter2(200, 400));
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



    m_polygon.addVertex(alVecter2(4, 2) * 25);
    m_polygon.addVertex(alVecter2(2, 4) * 25);
    m_polygon.addVertex(alVecter2(-2, 4) * 25);
    m_polygon.addVertex(alVecter2(-4, 2) * 25);
    m_polygon.addVertex(alVecter2(-4, -2) * 25);
    m_polygon.addVertex(alVecter2(-2, -4) * 25);
    m_polygon.addVertex(alVecter2(2, -4) * 25);
    m_polygon.addVertex(alVecter2(4, -2) * 25);
    m_polygon.addVertex(alVecter2(4, 2) * 25);
    m_polygon.setPosition(alVecter2(300, 460));
    m_polygon.setSleep(false);

    m_polygon2.addVertex(alVecter2(4, 4) * 15);
    m_polygon2.addVertex(alVecter2(0, 6) * 15);
    m_polygon2.addVertex(alVecter2(-4, 4) * 15);
    m_polygon2.addVertex(alVecter2(-4, -4) * 15);
    m_polygon2.addVertex(alVecter2(0, -6) * 15);
    m_polygon2.addVertex(alVecter2(4, -4) * 15);
    m_polygon2.addVertex(alVecter2(4, 4) * 15);
    m_polygon2.setPosition(alVecter2(480, 680));
    m_polygon2.setSleep(false);

    m_polygonRenderer.setThickness(3);
    m_polygonRenderer.setAngleLineThickness(3);
    m_polygonRenderer.polygonList().append(&m_polygon);
    m_polygonRenderer.polygonList().append(&m_polygon2);

    //    m_circleCircleCD.setBody1(&m_circle);
    //    m_circleCircleCD.setBody2(&m_circle2);

    //    m_polygonCircleCD.setBody1(&m_rectangle);
    //    m_polygonCircleCD.setBody2(&m_circle);

    //    m_polygonPolygonCD.setBody1(&m_polygon);
    //    m_polygonPolygonCD.setBody2(&m_polygon2);

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

    //    if(m_mousePress && m_drag)
    //    {
    //            alVecter2 dp(m_mousePos.x() - m_circle.position().x(), m_mousePos.y() - m_circle.position().y());
    //            m_circle.velocity() += dp * alForceLengthRatio;
    //    }
    //    if(m_mousePress && m_drag2)
    //    {
    //            alVecter2 dp(m_mousePos.x() - m_rectangle.position().x(), m_mousePos.y() - m_rectangle.position().y());
    //            m_rectangle.velocity() += dp * alForceLengthRatio;
    //    }
    //    alVecter2 v = m_circle.velocity();
    //    alVecter2 v1 = m_circle2.velocity();

    //    alVecter2 v2 = m_rectangle.velocity();

    //    alVecter2 v3 = m_polygon.velocity();
    //    alVecter2 a1, a2, a3, a4;
    //    //friction & static judgement
    //    if(v.length() - alStopThreshold < 0.0101)
    //    {
    //        a1 += alVecter2(0, 0);
    //        m_circle.velocity().set(0, 0);
    //    }
    //    else{
    //        a1 += v.getNormalizedVector() * -1;
    //    }
    //    if(v1.length() - alStopThreshold < 0.0101)
    //    {
    //        a4 += alVecter2(0, 0);
    //        m_circle2.velocity().set(0, 0);
    //    }
    //    else{
    //        a4 += v1.getNormalizedVector() * -1;
    //    }
    //    if(v2.length() - alStopThreshold < 0.0101)
    //    {
    //        a2 += alVecter2(0, 0);
    //        m_rectangle.velocity().set(0, 0);
    //    }
    //    else{
    //        a2 += v2.getNormalizedVector() * -1;
    //    }
    //    if(v3.length() - alStopThreshold < 0.0101)
    //    {
    //        a3 += alVecter2(0, 0);
    //        m_polygon.velocity().set(0, 0);
    //    }
    //    else{
    //        a3 += v3.getNormalizedVector() * -1;
    //    }
    //    float an = m_rectangle.angularVelocity();
    //    if(an * (an + m_rectangle.angularAcceleration() * alDeltaTime) < 0)
    //    {
    //        m_rectangle.setAngularVelocity(0);
    //        m_rectangle.setAngularAcceleration(0);
    //    }
    //    float bn = m_circle.angularVelocity();
    //    if(bn * (bn + m_circle.angularAcceleration() * alDeltaTime) < 0)
    //    {
    //        m_circle.setAngularVelocity(0);
    //        m_circle.setAngularAcceleration(0);
    //    }
    //    float bn2 = m_circle2.angularVelocity();
    //    if(bn2 * (bn2 + m_circle2.angularAcceleration() * alDeltaTime) < 0)
    //    {
    //        m_circle2.setAngularVelocity(0);
    //        m_circle2.setAngularAcceleration(0);
    //    }
    //    float cn = m_polygon.angularVelocity();
    //    if(cn * (cn + m_polygon.angularAcceleration() * alDeltaTime) < 0)
    //    {
    //        m_polygon.setAngularVelocity(0);
    //        m_polygon.setAngularAcceleration(0);
    //    }
    //    bool rr = m_circleCircleCD.detect();
    //    if(rr)
    //    {
    //        m_circle.position() -= m_circleCircleCD.minimunTranslationVector();
    //        alVecter2 temp = m_circle2.velocity();
    //        m_circle2.velocity() = m_circle.velocity();
    //        m_circle.velocity() = temp;
    //    }
    //    m_circle.acceleration() = a1;
    //    m_circle2.acceleration() = a4;
    //    m_circle.update();
    //    m_circle2.update();




    //    m_rectangle.acceleration() = a2;
    //    m_rectangle2.acceleration() = a2;
    //    m_rectangle.update();
    //    m_rectangle2.update();

    //    bool pr = m_polygonCircleCD.detect();
    //    m_circle.setIsTouched(pr);
    //    m_rectangle.setIsTouched(pr);
    //    if(pr)
    //    {
    //        m_circle.position() -= m_polygonCircleCD.minimunTranslationVector();
    //        alVecter2 temp = m_rectangle.velocity();
    //        m_rectangle.velocity() = m_circle.velocity();
    //        m_circle.velocity() = temp;
    //    }
    //    m_polygon.acceleration() = a3;
    //    m_polygon2.acceleration() = a3;
    //    m_polygon.update();
    //    m_polygon2.update();

    //    bool pp = m_polygonPolygonCD.detect();
    //    m_polygon.setIsTouched(pp);
    //    m_polygon2.setIsTouched(pp);
    //    if(pp)
    //    {
    //        m_polygon.position() -= m_polygonPolygonCD.minimunTranslationVector();
    //        alVecter2 temp = m_polygon2.velocity();
    //        m_polygon2.velocity() = m_polygon.velocity();
    //        m_polygon.velocity() = temp;
    //    }
    //    if((m_rectangle.position() - m_rectangle2.position()).length() < 20)
    //    {
    //        m_rectangle.setIsTouched(true);
    //        m_rectangle2.setIsTouched(true);
    //    }
    //    else
    //    {
    //        m_rectangle.setIsTouched(false);
    //        m_rectangle2.setIsTouched(false);
    //    }
    if(m_mousePress)
    {
        alVecter2 mousePos(m_mousePos.x(), m_mousePos.y());
        alVecter2 dp1 = mousePos - m_polygon.position();
        alVecter2 dp2 = mousePos - m_polygon2.position();
        if(dp1.length() < 20)
        {
            m_polygon.position() = mousePos;
        }
        if(dp2.length() < 20)
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
    //    m_circleRenderer.render(&painter);
    //    m_rectangleRenderer.render(&painter);
    //    m_measurer.render(&painter);

    //sat collision detection
    int offset = 680;
    QPen line(Qt::darkBlue, 1, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
    QPen dot1(Qt::darkYellow, 8, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen dot2(Qt::darkGreen, 8, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen dotmax(Qt::red, 8, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen dotmin(Qt::blue, 8, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    bool contact = false;
    alVecter2 minimumTranslationDirectionVector;
    alVecter2 relativeP = m_polygon2.position() - m_polygon.position();
    //qDebug () << "relative : ( " << relativeP.x() << "," << relativeP.y() << " )";
    alPolygon body1 = m_polygon;
    alPolygon body2 = m_polygon2;
    //m_polygon.setAngularVelocity(2);
    //m_polygon.update();
    body1.position().set(0, 0);
    body2.position() = body1.position() + relativeP;
    std::vector<alVecter2> b1vertices = body1.getRotatedVertices();
    std::vector<alVecter2> b2vertices = body2.getRotatedVertices();
    int contactAxis = 0;
    alVecter2 minimumTranslationVector;
    float minimumTranslationVectorLength;
    for(int i = 0; i < b1vertices.size() - 1; i++)
    {
        alVecter2 edge = b1vertices[i + 1] - b1vertices[i];

        alVecter2 perpendicular = alVecter2(edge.y(), -edge.x()).getNormalizedVector();

        //assistant perpendicular line drawing
        alVecter2 mid = (b1vertices[i + 1] + b1vertices[i]) * 0.5;
        alVecter2 s = perpendicular * offset + mid;

        alVecter2 st = m_polygon.position() + mid;
        alVecter2 ed = m_polygon.position() + s;

        painter.setPen(line);
        painter.drawLine(st.x(), st.y(), ed.x(), ed.y());
        //assistant end draw


        float b1_min = (b1vertices[0]) * (perpendicular), b1_max = (b1vertices[0]) * (perpendicular);
        for(int j = 0;j < b1vertices.size(); j++)
        {
            float temp = (b1vertices[j]) * (perpendicular);
            alVecter2 tempVector = perpendicular * temp;
            tempVector += m_polygon.position();
            alVecter2 tempP = b1vertices[j] + m_polygon.position();
            painter.setPen(dot1);
            painter.drawPoint(tempP.x(), tempP.y());
            painter.drawPoint(tempVector.x(), tempVector.y());

            painter.setPen(line);
            painter.drawLine(tempVector.x(), tempVector.y(), tempP.x(), tempP.y());

            if(b1_min > temp)
                b1_min = temp;
            if(b1_max < temp)
                b1_max = temp;
        }

        alVecter2 minVector1 = perpendicular * b1_min;
        alVecter2 maxVector1 = perpendicular * b1_max;
        minVector1 += m_polygon.position();
        maxVector1 += m_polygon.position();
        painter.setPen(dotmin);
        painter.drawPoint(minVector1.x(), minVector1.y());
        painter.setPen(dotmax);
        painter.drawPoint(maxVector1.x(), maxVector1.y());

        float b2_min = (b2vertices[0] + relativeP) * (perpendicular), b2_max = (b2vertices[0] + relativeP) * (perpendicular);
        for(int j = 0;j < b2vertices.size(); j++)
        {
            alVecter2 tempP = b2vertices[j] + m_polygon2.position();
            painter.setPen(dot1);
            painter.drawPoint(tempP.x(), tempP.y());

            float temp = (b2vertices[j] + relativeP) * (perpendicular);
            alVecter2 tempVector = perpendicular * temp;
            tempVector += m_polygon.position();

            painter.drawPoint(tempVector.x(), tempVector.y());

            painter.setPen(line);
            painter.drawLine(tempVector.x(), tempVector.y(), tempP.x(), tempP.y());

            if(b2_min > temp)
                b2_min = temp;
            if(b2_max < temp)
                b2_max = temp;
        }


        alVecter2 minVector2 = perpendicular * b2_min;
        alVecter2 maxVector2 = perpendicular * b2_max;
        minVector2 += m_polygon.position();
        maxVector2 += m_polygon.position();
        painter.setPen(dotmin);
        painter.drawPoint(minVector2.x(), minVector2.y());
        painter.setPen(dotmax);
        painter.drawPoint(maxVector2.x(), maxVector2.y());

        if(b1_max >= b2_min || b2_max <= b1_min)
        {
            contactAxis++;
        }

    }
    //qDebug() << "contact axis count: " << contactAxis;
    if(contactAxis == b1vertices.size() - 1)
        contact = true;
    m_polygon.setIsTouched(contact);
    m_polygon2.setIsTouched(contact);
    m_wallRenderer.render(&painter);
    m_polygonRenderer.render(&painter);
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

