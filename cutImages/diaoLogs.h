#pragma once

#include <QDialog>
#include "ui_diaoLogs.h"

class diaoLogs : public QDialog
{
	Q_OBJECT

public:
	diaoLogs(QWidget *parent = nullptr);
	~diaoLogs();
	Ui::diaoLogsClass ui;
private:
	
};
