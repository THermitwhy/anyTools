#include "QCutImage.h"
#include <QtWinExtras>
#include "getWinImage.h"
QCutImage::QCutImage(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    //setMaximumSize(1920, 1080);
    showFullScreen();
    
    //showMaximized();
    ////showFullScreen();
    //QWidget::setWindowFlags(Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint);
    //setWindowFlags(Qt::FramelessWindowHint);
    
    setMouseTracking(true);
    this->grabKeyboard();
    this->setMenu();
    
    if (!QSystemTrayIcon::isSystemTrayAvailable())
    {
        QMessageBox::information(this, QStringLiteral("托盘提示"), QStringLiteral("不支持托盘"));
    }
    else
    {
        tray = new QSystemTrayIcon(this);
        QIcon icon = QIcon(":/QCutImage/pic.ico");
        tray->setIcon(icon);
        tray->setToolTip(QStringLiteral("测试成功"));
        tray->setContextMenu(menu);//关联菜单
    }
    diaL.hide();
    connect(this->diaL.ui.pushButton, &QPushButton::clicked, this, &QCutImage::saveMap);
    //diaL.show();

}

QCutImage::~QCutImage()
{}

void QCutImage::keyPressEvent(QKeyEvent * event)
{
    switch (event->key()) {
    case Qt::Key_1:
        pointNd = getCursorND();
        if (pointNd != NULL) {
            //setLabelImage(pointNd);
        }
        break;
    }
}

void QCutImage::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        leftButtonClicked = true;
        startPoint = event->pos();
        diaL.hide();
    }
}

void QCutImage::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton&&leftButtonClicked==true) {
        //
        leftButtonClicked = false;
        endPoint = event->pos();
        diaL.show();
        this->update();
    }
}

void QCutImage::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() && Qt::LeftButton) {
        endPoint = event->pos();
        this->update();
    }
}

void QCutImage::closeEvent(QCloseEvent* event)
{
    if (QMessageBox::information(this, QStringLiteral("关闭提示"), QStringLiteral("是否退出"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
        event->accept();
    else
    {
        
        event->ignore();
        this->hide();
        tray->show();
    }
}

void QCutImage::paintEvent(QPaintEvent* event)
{

        QPainter p(this);
        if (!painted) {
            map = QtWin::fromHBITMAP(cutFullWindow(), QtWin::HBitmapFormat::HBitmapNoAlpha);
            painted = true;
        }
        p.drawPixmap(0, 0, map);
        QColor shadowColor = QColor(0, 0, 0, 20);
        p.fillRect(map.rect(), shadowColor);
        //QRect rect;
        //p.drawPixmap(rect(), map);
        if (leftButtonClicked) {  
            rectMap.setX(startPoint.x());
            rectMap.setY(startPoint.y());
            rectMap.setWidth(endPoint.x() - startPoint.x());
            rectMap.setHeight(endPoint.y() - startPoint.y());
        }
        p.drawRect(rectMap);
        cutMap = map.copy(rectMap);
        p.drawPixmap(rectMap.topLeft(), cutMap);
        p.drawRect(rectMap );
    
    
}



void QCutImage::drawRects(QPainter* painter)
{
    painter->setPen(Qt::blue);
    QRect rect;
    rect.setX(startPoint.x());
    rect.setY(startPoint.y());
    rect.setWidth(endPoint.x() - startPoint.x());
    rect.setHeight(endPoint.y() - startPoint.y());
    painter->drawRect(rect);
}



//void QCutImage::setLabelImage(HWND windowND)
//{
//    QPixmap map1 = QtWin::fromHBITMAP(cutWindow(windowND), QtWin::HBitmapFormat::HBitmapNoAlpha);
//    //QPixmap map1 = QtWin::fromHBITMAP(cutFullWindow(), QtWin::HBitmapFormat::HBitmapNoAlpha);
//    QSize size1 = map1.size();
//    ui.label->resize(size1);
//    ui.label->setPixmap(map1);
//}

//void QCutImage::setLabelImage()
//{
//    QPixmap map1 = QtWin::fromHBITMAP(cutFullWindow(), QtWin::HBitmapFormat::HBitmapNoAlpha);
//    QSize size1 = map1.size();
//    ui.label->resize(size1);
//    ui.label->setPixmap(map1);
//}

void QCutImage::showWin()
{
    if (this->isHidden()) {
        this->show();
    }
}

void QCutImage::exitWin()
{
    this->close();
}

void QCutImage::setMenu()
{
    menu = new QMenu(this);
    mexit = new QAction(QStringLiteral("退出"), this);
    mshow = new QAction(QStringLiteral("显示"), this);
    connect(mexit, &QAction::triggered, this, &QCutImage::exitWin);
    connect(mshow, &QAction::triggered, this, &QCutImage::showWin);
    menu->addAction(mexit);
    menu->addAction(mshow);

}

void QCutImage::saveMap()
{
    cutMap.save("1.jpg","JPG");
}


