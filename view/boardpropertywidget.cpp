#include "boardpropertywidget.h"

BoardPropertyWidget::BoardPropertyWidget(QWidget *parent) :
    PropertyWidget(":/Pictures/board.png", parent)
{
    QLabel * lblDimension = new QLabel("Dimension : ", this);
    QLineEdit * txtHeight = new QLineEdit("8", this);
    QLabel * lblMultiplication = new QLabel("X", this);
    QLineEdit * txtWidth = new QLineEdit("8", this);

    QHBoxLayout * lytDimension = new QHBoxLayout();
    lytDimension->addStretch();
    lytDimension->addWidget(lblDimension);
    lytDimension->addWidget(txtHeight);
    lytDimension->addWidget(lblMultiplication);
    lytDimension->addWidget(txtWidth);
    lytDimension->addStretch();

    QBoxLayout * layout = (QBoxLayout *)this->layout();
    layout->addLayout(lytDimension);

}
