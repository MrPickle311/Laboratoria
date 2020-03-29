#pragma once

#include <QDialog>
#include <qwidget.h>
#include <qgridlayout.h>
#include <qtextedit.h>

class DebugDialog : public QDialog{
	Q_OBJECT
public:
	QGridLayout* debugLayout;
	QTextEdit* debugTextEdit;
	QString debugText;
	void debugWrite(QString);
	DebugDialog(QWidget *parent);
	~DebugDialog();
};
