#pragma once
#if _MSC_VER >= 1600 //VS2015>VS>VS2010, MSVC VER= 10.0 -14.0
#pragma execution_character_set("utf-8")
#endif
#include <QtWidgets/QWidget>
#include <qfiledialog.h>
#include <qregularexpression.h>
#include <QClipboard>
#include <QSettings>
#include <QDesktopServices>
#include "ui_foxText.h"

class foxText : public QWidget
{
    Q_OBJECT

public:
    foxText(QWidget *parent = nullptr);
    ~foxText();
    void getHtml();
    void setImg();
    void resetText(QString html);
    void setTextCenter();
    void reHTML();
    void reP();
    void reSpan();
    void copyText();
    void getSettings();
    void setClasses();
    void replaceClasses(QString key,QString value);
    void deleteSpan();
    void openTextEditor();
    void getBody(QString &body);
    void onComboChanged(QString text);

    QString html;
    QString confP;

private:
    Ui::foxTextClass ui;
};
