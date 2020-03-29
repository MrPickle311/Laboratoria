#ifndef LABORATORY_H
#define LABORATORY_H

#include <QtWidgets/QDialog>
#include "ui_Laboratory.h" //plik obiektu interfejsu,przechowuj�cy wszystkie proste widgety
#include <QStackedWidget> // widget pozwalaj�cy stackowa� inne widgety oraz okna
#include "EX2W.h" //plik nag��wkowy interfejsu do drugiego �wiczenia

class Laboratoria : public QDialog{
	Q_OBJECT
public:
	Laboratoria(QWidget* parent = Q_NULLPTR);
private:
	QStackedWidget* exercisesWidget; // obiekty 
	Ui::LaboratoriaClass* ui_Global; //obiekt interfejsu,przechowuj�cy wszystkie proste widgety,istnieje tylko jedna instancja tego obiektu
	EX2W* secondExercise;
private: //obiekty widget�w dla odpowiednich �wicze�

};

#endif // LABORATORY_H


