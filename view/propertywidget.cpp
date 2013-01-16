#include "propertywidget.h"

PropertyWidget::PropertyWidget(QString picture, QWidget *parent) :
    QWidget(parent)
{

    QLabel * preview = new QLabel();
    QPixmap pixmap(picture);
    preview->setPixmap(pixmap.scaled(QSize(480,480), Qt::KeepAspectRatio));

    QVBoxLayout * layout = new QVBoxLayout();
    layout->addWidget(preview);
    layout->setAlignment(preview, Qt::AlignHCenter);

    this->setLayout(layout);
}
