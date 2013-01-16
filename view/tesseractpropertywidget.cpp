#include "tesseractpropertywidget.h"

TesseractPropertyWidget::TesseractPropertyWidget(QWidget *parent) :
    PropertyWidget(":/Pictures/tesseract.png", parent)
{
    QLabel * lblDisplay = new QLabel("Affichage : ", this);
    QRadioButton * rb3D = new QRadioButton("3D", this);
    QRadioButton * rb2D = new QRadioButton("2D", this);
    rb2D->setChecked(true);

    QHBoxLayout * lytDisplay = new QHBoxLayout();
    lytDisplay->addStretch();
    lytDisplay->addWidget(lblDisplay);
    lytDisplay->addWidget(rb3D);
    lytDisplay->addWidget(rb2D);
    lytDisplay->addStretch();

    QBoxLayout * layout = (QBoxLayout *)this->layout();
    layout->addLayout(lytDisplay);
}
