#ifndef LABORATORY_H
#define LABORATORY_H

#include <QtWidgets/QDialog>
#include "ui_Laboratory.h" //plik obiektu interfejsu,przechowuj¹cy wszystkie proste widgety
#include <QStackedWidget> // widget pozwalaj¹cy stackowaæ inne widgety oraz okna
#include "EX2W.h" //plik nag³ówkowy interfejsu do drugiego æwiczenia

class Laboratoria : public QDialog{
	Q_OBJECT
public:
	Laboratoria(QWidget* parent = Q_NULLPTR);
private:
	QStackedWidget* exercisesWidget; // obiekty 
	Ui::LaboratoriaClass* ui_Global; //obiekt interfejsu,przechowuj¹cy wszystkie proste widgety,istnieje tylko jedna instancja tego obiektu
	EX2W* secondExercise;
private: //obiekty widgetów dla odpowiednich æwiczeñ

};

#endif // LABORATORY_H


