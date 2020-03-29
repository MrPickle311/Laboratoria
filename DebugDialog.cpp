#include "DebugDialog.h"

DebugDialog::DebugDialog(QWidget* parent) : QDialog(parent),debugLayout { new QGridLayout{} },
debugTextEdit{ new QTextEdit{this} }{
	this->setLayout(debugLayout);
	debugLayout->addWidget(debugTextEdit);
}

void DebugDialog::debugWrite(QString text){
	QString oldText{ this->debugTextEdit->toPlainText() };
	oldText += text + "\n";
	this->debugTextEdit->setText(oldText);
}

DebugDialog::~DebugDialog(){
}
