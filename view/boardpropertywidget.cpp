#include "boardpropertywidget.h"

BoardPropertyWidget::BoardPropertyWidget(GameOption &option, QWidget *parent) :
    PropertyWidget(":/Pictures/board.png", parent),
    _option(option),
    _txtHeight(0),
    _txtWidth(0)
{

    QIntValidator * intValidator = new QIntValidator(2,10000,this);
    QLabel * lblDimension = new QLabel("Dimension : ", this);
    _txtHeight = new QLineEdit("8", this);
    _txtHeight->setValidator(intValidator);
    QLabel * lblMultiplication = new QLabel("X", this);
    _txtWidth = new QLineEdit("8", this);
    _txtWidth->setValidator(intValidator);

    QHBoxLayout * lytDimension = new QHBoxLayout();
    lytDimension->addStretch();
    lytDimension->addWidget(lblDimension);
    lytDimension->addWidget(_txtHeight);
    lytDimension->addWidget(lblMultiplication);
    lytDimension->addWidget(_txtWidth);
    lytDimension->addStretch();

    QBoxLayout * layout = (QBoxLayout *)this->layout();
    layout->addLayout(lytDimension);

    QObject::connect(_txtHeight, SIGNAL(editingFinished()), this, SLOT(updateOption()));
    QObject::connect(_txtWidth, SIGNAL(editingFinished()), this, SLOT(updateOption()));
}

void BoardPropertyWidget::updateIHM()
{
    _txtHeight->setText(QString::number(_option.getHeight()));
    _txtWidth->setText(QString::number(_option.getWidth()));
}

void BoardPropertyWidget::updateOption()
{
    _option.setHeight(_txtHeight->text().toInt());
    _option.setWidth(_txtWidth->text().toInt());
}
