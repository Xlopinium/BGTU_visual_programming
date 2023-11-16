#ifndef ZOOM_H
#define ZOOM_H

#include "zoom_global.h"
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QPushButton>
#include <QSlider>

class ZOOM_EXPORT Zoom : public QWidget {
    Q_OBJECT

public:
    Zoom(QWidget* parent = nullptr);

public slots:
    void openImage();
    void saveImage();
    void zoomImage(int value);

private:
    QGraphicsView* imageView;
    QGraphicsPixmapItem* pixmapItem;
    QPushButton* openButton;
    QPushButton* saveButton;
    QSlider* zoomSlider;
};

#endif // ZOOM_H
