#include "Zoom.h"
#include <QFileDialog>
#include <QVBoxLayout>

Zoom::Zoom(QWidget* parent) : QWidget(parent) {
    // Initializing the widget and its components
    imageView = new QGraphicsView(this);
    QGraphicsScene* scene = new QGraphicsScene(this);
    imageView->setScene(scene);

    pixmapItem = new QGraphicsPixmapItem();
    scene->addItem(pixmapItem);

    openButton = new QPushButton(tr("Open"), this);
    saveButton = new QPushButton(tr("Save As"), this);
    zoomSlider = new QSlider(Qt::Horizontal, this);
    zoomSlider->setRange(1, 300);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(openButton);
    layout->addWidget(saveButton);
    layout->addWidget(zoomSlider);
    layout->addWidget(imageView);

    connect(openButton, &QPushButton::clicked, this, &Zoom::openImage);
    connect(saveButton, &QPushButton::clicked, this, &Zoom::saveImage);
    connect(zoomSlider, &QSlider::valueChanged, this, &Zoom::zoomImage);
}

void Zoom::openImage() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
    if (!fileName.isEmpty()) {
        QImage image(fileName);
        pixmapItem->setPixmap(QPixmap::fromImage(image));
        imageView->fitInView(pixmapItem, Qt::KeepAspectRatio);
    }
}

void Zoom::saveImage() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"), "", tr("PNG (*.png);;JPEG (*.jpg *.jpeg);;All Files (*)"));
    if (!fileName.isEmpty()) {
        const QPixmap pixmap = pixmapItem->pixmap();
        pixmap.save(fileName);
    }
}

void Zoom::zoomImage(int value) {
    qreal scaleFactor = value / 100.0;
    QTransform transform;
    transform.scale(scaleFactor, scaleFactor);
    imageView->setTransform(transform);
}
