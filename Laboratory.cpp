#include "Laboratory.h"

Laboratoria::Laboratoria(QWidget* parent) : QDialog(parent), exercisesWidget{ new QStackedWidget{this} }, 
ui_Global{ new Ui::LaboratoriaClass{} }, secondExercise{ new EX2W{this} }{
	ui_Global->setupUi(this);
	ui_Global->mainLayout->addWidget(exercisesWidget);
	exercisesWidget->addWidget(this->secondExercise);
}
