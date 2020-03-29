#ifndef EX2W_H
#define EX2W_H

#include <QWidget>
#include <QVector>
#include "ui_EX2W.h"
#include "Exercise2.h"
#include <QtCharts/qchart.h>
#include <QtCharts/qsplineseries.h>
#include <QtCharts/qchartview.h>
#include <QMessageBox.h>
#include <DebugDialog.h>

QT_CHARTS_USE_NAMESPACE

enum class ViewMethod{Chart,Trapez,Simpson};

struct DataBase {
	int index = 0; //<0;5>
	bool isComputed = false;
	long double analiticIntegral = 0.0;
	long double simpsonIntegral = 0.0;
	long double trapezIntegral = 0.0;
};

class EX2W : public QWidget{
	Q_OBJECT
public:
	// w polach za pomoc¹ sygna³ów uniemo¿liwiæ wpisywanie znaków ,tylko liczby
	EX2W(QWidget* parent = Q_NULLPTR);
	~EX2W();
private:
	QObject* grabberChannel = Q_NULLPTR;
	Ui::EX2W ui;
	DebugDialog* debugDialog;
private:
	ViewMethod viewMethod = ViewMethod::Chart;
	INT currentChart = 0;
	std::vector<QChart*> charts;
	std::vector<QChart*> trapezAttempts;
	std::vector<QChart*> simpsonAttempts;
	std::vector<QChartView*> chartsView;
	std::vector<QChartView*> trapezAttemptsView;
	std::vector<QChartView*> simpsonAttemptsView;
	std::vector<DataBase> dataBase;
	QChartView* chartViewptr = nullptr;
public slots:
	void computeChart();
	void changeChart(int);
	void changeMethod(int); // prze³¹cza miêdzy wykresami a dok³adnoœciami
private:
	void changeResults();
	void drawCharts(std::vector<Point>&, std::vector<attempt>&, std::vector<attempt>&);
signals:
	void methodChanged(ViewMethod);
	void indexChanged(int);
};

#endif //EX2W_H


