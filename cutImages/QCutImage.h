#pragma once

#include <QtWidgets/QWidget>
#include <QDebug>
#include <QEvent>
#include <QMenu>
#include <QAction>
#include <QSystemTrayIcon>
#include <QMouseEvent>
#include <QMessageBox>
#include <QPainter>
#include "ui_QCutImage.h"
#include "diaoLogs.h"
class QCutImage : public QWidget
{
    Q_OBJECT

public:
    QCutImage(QWidget *parent = nullptr);
    ~QCutImage();
    void keyPressEvent(QKeyEvent* event);//键盘响应事件
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void closeEvent(QCloseEvent* event);
    void paintEvent(QPaintEvent* event);

    void drawRects(QPainter* painter);

private:
    //obj
    QMenu* menu;
    QAction* mexit;
    QAction* mshow;
    QPainter *painter;
    HWND pointNd;
    QSystemTrayIcon* tray;
    bool leftButtonClicked=false;
    bool painted = false;
    bool cursorMoved = false;//鼠标是否移动了
    QPoint startPoint;
    QPoint endPoint;
    QPixmap map;
    QPixmap cutMap;
    QRect rectMap;
    diaoLogs diaL;
    Ui::QCutImageClass ui;
    //fun
    //void setLabelImage(HWND windowND);
    void setLabelImage();
    void showWin();
    void exitWin();
    void setMenu();
    void saveMap();
};
