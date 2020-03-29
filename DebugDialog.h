#pragma once

#include <QDialog>
#include <qwidget.h>
#include <qgridlayout.h>
#include <qtextedit.h>
#include <qgridlayout.h>
#include <qchart.h>
#include <qchartview.h>

class DebugDialog : public QDialog{
	Q_OBJECT
public:
	QChartView* view = nullptr;
	QGridLayout* layout = nullptr;
	QPushButton* button = nullptr;
	QChart* chart1 = nullptr;
	QChart* chart2 = nullptr;
	QGridLayout* debugLayout;
	QTextEdit* debugTextEdit;
	QString debugText;
	void debugWrite(QString);
	DebugDialog(QWidget *parent);
	~DebugDialog();
};
