#ifndef EXERCISE_2_WIDGET
#define EXERCISE_2_WIDGET

#include <QObject>

class Exercise2Widget : public QObject{
	Q_OBJECT
public:
	Exercise2Widget(QObject *parent);
	~Exercise2Widget();
};
#endif //EXERCISE_2_WIDGET