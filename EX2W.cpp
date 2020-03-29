#include "EX2W.h"
#include <iostream>
#include <qtextcodec.h>
#include <qstackedwidget.h>

EX2W::EX2W(QWidget* parent) : QWidget(parent), grabberChannel{ new QObject{this} }, 
debugDialog{ new DebugDialog{this} }, charts{ std::vector<QChart*>{} }, trapezAttempts{ std::vector<QChart*>{} },
simpsonAttempts{ std::vector<QChart*>{} }, chartsView{ std::vector<QChartView*>{} }, 
trapezAttemptsView{ std::vector<QChartView*>{} },simpsonAttemptsView{ std::vector<QChartView*>{} },
dataBase{ std::vector<DataBase>{} }{
	ui.setupUi(this);
	charts.insert(charts.begin(), 6, new QChart{});
	dataBase.insert(dataBase.begin(), 6, DataBase{});
	trapezAttempts.insert(trapezAttempts.begin(), 6 ,new QChart{});
	simpsonAttempts.insert(simpsonAttempts.begin(), 6, new QChart{});

	this->chartsView.insert(this->chartsView.begin(), 6, new QChartView{ this });
	this->trapezAttemptsView.insert(this->trapezAttemptsView.begin(), 6, new QChartView{ this });
	this->simpsonAttemptsView.insert(this->simpsonAttemptsView.begin(), 6, new QChartView{ this });
	for (int i = 0; i < 6; ++i) {
		this->chartsView[i]->setRenderHint(QPainter::Antialiasing);
		this->trapezAttemptsView[i]->setRenderHint(QPainter::Antialiasing);
		this->simpsonAttemptsView[i]->setRenderHint(QPainter::Antialiasing);
	}
	//this->ui.chartLayout->addWidget(this->chartsView[0]);
	this->chartsView[0]->setChart(this->charts[0]);
	this->chartViewptr = this->chartsView[0];
	//this->ui.chartLayout->removeWidget() przyda siê 
	//QStackedWidget stack{};
	//stack.addWidget(this->chartView); DZIA£A O KURWA!!
	connect(this->ui.computeAndWriteButton, &QPushButton::pressed, this, &EX2W::computeChart);
	connect(this->ui.chartsComboBox, QOverload<int>::of(&QComboBox::activated), this, &EX2W::changeChart);
	connect(this->ui.chartsComboBox_2, QOverload<int>::of(&QComboBox::activated), this, &EX2W::changeMethod);
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
	debugDialog->show();
}

EX2W::~EX2W(){
	for (auto& chart : this->charts)
		chart->deleteLater();
}

void EX2W::changeChart(int idx){
	this->currentChart = idx;
	this->debugDialog->debugWrite(std::to_string(this->currentChart).c_str());
	this->chartViewptr->hide();
	this->ui.chartLayout->removeWidget(chartViewptr);
	this->chartViewptr = this->chartsView[this->currentChart];
	this->ui.chartLayout->addWidget(chartViewptr);
	this->chartViewptr->show();
	if (this->dataBase[this->currentChart].isComputed)
		this->changeResults();//zapisz jeszcze granice ca³kowania itd...
}

void EX2W::changeMethod(int method1){
	/*int method = this->ui.chartsComboBox_2->currentIndex();
	switch (method) {
	case 0:
		this->chartView->setChart(this->charts[this->currentChart]);
		break;
	case 1:
		this->chartView->setChart(this->trapezAttempts[this->currentChart]);
		break;
	case 2:
		this->chartView->setChart(this->simpsonAttempts[this->currentChart]);
		break;
	default:
		QMessageBox::warning(this, tr("B³¹d dzia³ania aplikacji").toUtf8(),
			tr("B³¹d krytyczny funkcji changeMethod(),\nproszê powiadom autora"
				"o b³êdzie").toUtf8(),
			QMessageBox::StandardButton::Ok);
		break;
	}*/
}

void EX2W::changeResults(){ //tutaj skoñczy³em ,pamiêtaj ,¿e ta funkcja zmienia wartoœci za ka¿dym prze³¹czeniem wykresu 1...6
	this->ui.analiticTextBrowser->setText(std::to_string(this->dataBase[this->currentChart].analiticIntegral).c_str());
	this->ui.trapezTextBrowser->setText(std::to_string(this->dataBase[this->currentChart].trapezIntegral).c_str());
	this->ui.simpsonTextBrowser->setText(std::to_string(this->dataBase[this->currentChart].simpsonIntegral).c_str());
}

void EX2W::drawCharts(std::vector<Point>& chartPoints, std::vector<attempt>& trapezPoints,
	std::vector<attempt>& simpsonPoints){
	QSplineSeries* series = new QSplineSeries{ grabberChannel };
	for (auto& point : chartPoints)
		series->append(point.x, point.y);
	this->charts[this->currentChart]->addSeries(series);
	this->charts[this->currentChart]->createDefaultAxes();
	this->chartsView[this->currentChart]->setChart(this->charts[this->currentChart]);

	QSplineSeries* trapezSeries = new QSplineSeries{ grabberChannel };
	for(auto& attempt : trapezPoints)
		trapezSeries->append(attempt.nodeNmbr, attempt.msrError);
	this->trapezAttempts[this->currentChart]->addSeries(trapezSeries);
	this->trapezAttempts[this->currentChart]->createDefaultAxes();
	this->trapezAttemptsView[this->currentChart]->setChart(this->trapezAttempts[this->currentChart]);

	QSplineSeries* simpsonSeries = new QSplineSeries{ grabberChannel };
	for (auto& attempt : simpsonPoints)
		simpsonSeries->append(attempt.nodeNmbr, attempt.msrError);
	this->simpsonAttempts[this->currentChart]->addSeries(simpsonSeries);
	this->simpsonAttempts[this->currentChart]->createDefaultAxes();
	this->simpsonAttemptsView[this->currentChart]->setChart(this->simpsonAttempts[this->currentChart]);
}

void EX2W::computeChart() {

	if (this->ui.nodeNmbrTextEdit->toPlainText() == "" ||
		this->ui.fromTextEdit->toPlainText() == "" ||
		this->ui.toTextEdit->toPlainText() == "")
		QMessageBox::warning(this, tr("B³¹d").toUtf8(), tr("Nie uzupe³niono wszystkich pól").toUtf8(),
			QMessageBox::StandardButton::Ok);
	else {
		long double n = std::stold(this->ui.nodeNmbrTextEdit->toPlainText().toStdString());
		long double from = std::stold(this->ui.fromTextEdit->toPlainText().toStdString());
		long double to = std::stold(this->ui.toTextEdit->toPlainText().toStdString());
		std::vector<Point> chartPoints{};
		std::vector<attempt> trapezPoints{};
		std::vector<attempt> simpsonPoints{};
		switch (this->currentChart) {
		case 0:
			chartPoints =  std::move(computeFunctionValues(from,to,function_1));
			trapezPoints = std::move(rtrnTrapezAttempts(from, to, n, function_1, function_1_INTEGRAL));
			simpsonPoints = std::move(rtrnSimpsonAttempts(from, to, n, function_1, function_1_INTEGRAL));
			this->dataBase[this->currentChart].analiticIntegral = function_1_INTEGRAL(to, from);
			this->dataBase[this->currentChart].trapezIntegral = trapez(from, to, function_1, sqrt(n));
			this->dataBase[this->currentChart].simpsonIntegral = simpson(from, to, function_1, sqrt(n));
			break;
		case 1:
			chartPoints = std::move(computeFunctionValues(from, to, function_2));
			trapezPoints = std::move(rtrnTrapezAttempts(from, to, n, function_2, function_2_INTEGRAL));
			simpsonPoints = std::move(rtrnSimpsonAttempts(from, to, n, function_2, function_2_INTEGRAL));
			this->dataBase[this->currentChart].analiticIntegral = function_2_INTEGRAL(from, to);
			this->dataBase[this->currentChart].trapezIntegral = trapez(from, to, function_2, sqrt(n));
			this->dataBase[this->currentChart].simpsonIntegral = simpson(from, to, function_2, sqrt(n));
			break;
		case 2:
			chartPoints = std::move(computeFunctionValues(from, to, function_3));
			trapezPoints = std::move(rtrnTrapezAttempts(from, to, n, function_3, function_3_INTEGRAL));
			simpsonPoints = std::move(rtrnSimpsonAttempts(from, to, n, function_3, function_3_INTEGRAL));
			this->dataBase[this->currentChart].analiticIntegral = function_3_INTEGRAL(from, to);
			this->dataBase[this->currentChart].trapezIntegral = trapez(from, to, function_3, sqrt(n));
			this->dataBase[this->currentChart].simpsonIntegral = simpson(from, to, function_3, sqrt(n));
			break;
		case 3:
			chartPoints = std::move(computeFunctionValues(from, to, function_4));
			trapezPoints = std::move(rtrnTrapezAttempts(from, to, n, function_4, function_4_INTEGRAL));
			simpsonPoints = std::move(rtrnSimpsonAttempts(from, to, n, function_4, function_4_INTEGRAL));
			this->dataBase[this->currentChart].analiticIntegral = function_4_INTEGRAL(from, to);
			this->dataBase[this->currentChart].trapezIntegral = trapez(from, to, function_4, sqrt(n));
			this->dataBase[this->currentChart].simpsonIntegral = simpson(from, to, function_4, sqrt(n));
			break;
		case 4:
			chartPoints = std::move(computeFunctionValues(from, to, function_5));
			trapezPoints = std::move(rtrnTrapezAttempts(from, to, n, function_5, function_5_INTEGRAL));
			simpsonPoints = std::move(rtrnSimpsonAttempts(from, to, n, function_5, function_5_INTEGRAL));
			this->dataBase[this->currentChart].analiticIntegral = function_5_INTEGRAL(from, to);
			this->dataBase[this->currentChart].trapezIntegral = trapez(from, to, function_5, sqrt(n));
			this->dataBase[this->currentChart].simpsonIntegral = simpson(from, to, function_5, sqrt(n));
			break;
		case 5:
			chartPoints = std::move(computeFunctionValues(from, to, function_6));
			trapezPoints = std::move(rtrnTrapezAttempts(from, to, n, function_6, function_6_INTEGRAL));
			simpsonPoints = std::move(rtrnSimpsonAttempts(from, to, n, function_6, function_6_INTEGRAL));
			this->dataBase[this->currentChart].analiticIntegral = function_6_INTEGRAL(from, to);
			this->dataBase[this->currentChart].trapezIntegral = trapez(from, to, function_6, sqrt(n));
			this->dataBase[this->currentChart].simpsonIntegral = simpson(from, to, function_6, sqrt(n));
			break;
		default:
			QMessageBox::warning(this, tr("B³¹d dzia³ania aplikacji").toUtf8(),
				tr("B³¹d krytyczny funkcji computeChart(),\nproszê powiadom autora"
					"o b³êdzie").toUtf8(),
				QMessageBox::StandardButton::Ok);
			break;
		}
		this->dataBase[this->currentChart].index = this->currentChart;
		this->dataBase[this->currentChart].isComputed = true;
		this->drawCharts(chartPoints,trapezPoints,simpsonPoints);
		this->changeResults();
	}
}
