#include "propertywidget.h"

PropertyWidget::PropertyWidget(QWidget *parent) :
    QWidget(parent)
{

    QLabel * preview = new QLabel();
    preview->setPixmap(QPixmap(":/Pictures/board.png"));

    QVBoxLayout * layout = new QVBoxLayout();
    //layout->addLayout(lytLegend);
    layout->addWidget(preview);

    this->setLayout(layout);
}
