#include "tesseractpropertywidget.h"

TesseractPropertyWidget::TesseractPropertyWidget(GameOption &option, QWidget *parent) :
    PropertyWidget(":/Pictures/tesseract.png", parent),
    _option(option),
    _rb3D(0),
    _rb2D(0)
{
    QLabel * lblDisplay = new QLabel("Affichage : ", this);
    _rb3D = new QRadioButton("3D", this);
    _rb2D = new QRadioButton("2D", this);
    _rb2D->setChecked(true);

    QHBoxLayout * lytDisplay = new QHBoxLayout();
    lytDisplay->addStretch();
    lytDisplay->addWidget(lblDisplay);
    lytDisplay->addWidget(_rb3D);
    lytDisplay->addWidget(_rb2D);
    lytDisplay->addStretch();

    QBoxLayout * layout = (QBoxLayout *)this->layout();
    layout->addLayout(lytDisplay);

    QObject::connect(_rb2D, SIGNAL(clicked()), this, SLOT(updateOption()));
    QObject::connect(_rb3D, SIGNAL(clicked()), this, SLOT(updateOption()));
}

void TesseractPropertyWidget::updateIHM()
{
    switch( _option.getDisplay() )
    {
    case TesseractDisplay::IN_2D:
        _rb2D->setChecked(true);
        break;
    case TesseractDisplay::IN_3D:
        _rb3D->setChecked(true);
        break;
    }
}

void TesseractPropertyWidget::updateOption()
{
    if( _rb2D->isChecked() )
    {
        _option.setDisplay(TesseractDisplay::IN_2D);
    }
    else if ( _rb3D->isChecked() )
    {
        _option.setDisplay(TesseractDisplay::IN_3D);
    }
}
