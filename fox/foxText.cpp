#if _MSC_VER >= 1600 //VS2015>VS>VS2010, MSVC VER= 10.0 -14.0
#pragma execution_character_set("utf-8")
#endif
#include "foxText.h"
#include <QAction>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qmessagebox.h>

foxText::foxText(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    getSettings();
    //QAction *ac = new QAction("s");
    //ui.toolButton->addAction(ac);
    ui.comboBox->addItem("text");
    ui.comboBox->addItem("html");
    ui.comboBox->setCurrentIndex(0);

    
    ui.comboBox_2->setPlaceholderText("css");
    ui.comboBox_2->setCurrentIndex(-1);
    ui.comboBox_2->addItem("p");
    ui.comboBox_2->addItem("h1");
    //QStringList items("p", "h1");
    //ui.comboBox_2->addItems(items);
    //connect(ui.pushButton, &QPushButton::clicked, this, &foxText::getHtml);
    connect(ui.pushButton_2, &QPushButton::clicked, this, &foxText::openTextEditor);
    connect(ui.comboBox, &QComboBox::currentTextChanged, this, &foxText::onComboChanged);
    connect(ui.pushButton_4, &QPushButton::clicked, this, &foxText::copyText);
    //connect(ui.pushButton_3, &QPushButton::clicked, this, &foxText::setTextCenter);
}

foxText::~foxText()
{}

void foxText::getHtml()
{
    QString html = ui.textEdit->toHtml();
    this->html = html;
    //html = html.replace("text-indent:0px", "text-indent:2em");
    ui.textEdit->setPlainText(html);
}

void foxText::setImg()
{
    QString imgPath = QFileDialog::getOpenFileName(this);
    ui.textEdit->textCursor().insertImage(imgPath);
}

void foxText::resetText(QString html)
{
    ui.textEdit->setHtml(html);
}

void foxText::setTextCenter()
{
    ui.textEdit->setAlignment(Qt::AlignCenter);
}

void foxText::reHTML()
{
    if (html.isEmpty()) { this->html = ui.textEdit->toHtml();}
    //reP();
    //reSpan();
    setClasses();
    if (ui.comboBox->currentIndex() == 1){ ui.textEdit->setPlainText(html); }
    
}

void foxText::reP()
{
    if (ui.comboBox->currentIndex() != 1) { return; }
    QString P = "<p class='" + confP +"'>";
    QRegularExpression re("<p.*>(.*)</p>");
    re.setPatternOptions(QRegularExpression::InvertedGreedinessOption);
    this->html.replace(re, P + "\\1< / p>");
    //ui.textEdit->setPlainText(this->html);
}

void foxText::reSpan()
{
    if (ui.comboBox->currentIndex() != 1) { return; }
    QRegularExpression re("<span.*>(.*)</span>");
    re.setPatternOptions(QRegularExpression::InvertedGreedinessOption);
    this->html.replace(re, "<span>\\1</span>");
    //ui.textEdit->setPlainText(this->html);
}

void foxText::copyText()
{
    QClipboard *clip= QApplication::clipboard();
    if(ui.comboBox->currentIndex()==0){ this->html = ui.textEdit->toHtml();}
    
    deleteSpan();
    reHTML();
    QString copyHt = this->html;
    getBody(copyHt);
    clip->setText(copyHt);
}

void foxText::getSettings()
{
    QFileInfo fileInfo("conf.ini");
    if (!fileInfo.isFile())
    {
        QMessageBox::critical(NULL, QString::fromLocal8Bit("错误"),
        QString::fromLocal8Bit("缺少configIO.ini文件！"));
        return;
    }
    QSettings classSetting("conf.ini", QSettings::IniFormat);
    //classSetting.setIniCodec
    confP = classSetting.value("class/p").toString();
}

void foxText::setClasses()
{
    QFileInfo fileInfo("conf.ini");
    if (!fileInfo.isFile())
    {
        QMessageBox::critical(NULL, QString::fromLocal8Bit("错误"),
            QString::fromLocal8Bit("缺少configIO.ini文件！"));
        return;
    }
    QSettings classSetting("conf.ini", QSettings::IniFormat);
    classSetting.beginGroup("class");
    QStringList classes = classSetting.allKeys();
    for (QString clas : classes) {
        replaceClasses(clas,classSetting.value(clas).toString());
    }

}

void foxText::replaceClasses(QString key, QString value)
{
    
    QString re = "<" + key + ".*>";
    QString reb = "<" + key + " class='"+value+"'>";
    QRegularExpression reg(re);
    reg.setPatternOptions(QRegularExpression::InvertedGreedinessOption);
    this->html.replace(reg, reb);
}

void foxText::deleteSpan()
{
    QString re = "<span.*>(.*)</span>";
    QString reb = "\\1";
    QRegularExpression reg(re);
    reg.setPatternOptions(QRegularExpression::InvertedGreedinessOption);
    this->html.replace(reg, reb);
}

void foxText::openTextEditor()
{
    QDesktopServices::openUrl(QUrl("conf.ini"));
}

void foxText::getBody(QString& body)
{

    body.remove(0, body.indexOf("<body"));
    body.remove(body.indexOf("</body"), body.length() - 1);
    QString re1 = ".*<body.*>(.*)";
    QString re2 = "(.*)<body.*";
    QString reb = "\\1";
    QRegularExpression reg1(re1);
    //reg1.setPatternOptions(QRegularExpression::InvertedGreedinessOption);
    QRegularExpression reg2(re2);
    //reg2.setPatternOptions(QRegularExpression::InvertedGreedinessOption);
    body.replace(reg1, reb);
    body.replace(reg2, reb);
}



void foxText::onComboChanged(QString text)
{
    if (text == "text") {
        resetText(html);
    }
    else {
        this->html = ui.textEdit->toHtml();
        deleteSpan();
        reHTML();
       // getHtml();
    }

}

