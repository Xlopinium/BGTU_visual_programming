#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Zoom.h"
#include <QVBoxLayout> // Убедитесь, что QVBoxLayout включен

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Создаем виджет Zoom и добавляем его в layout
    Zoom *zoomWidget = new Zoom(this);
    QVBoxLayout *layout = new QVBoxLayout; // Объявляем layout
    layout->addWidget(zoomWidget);
    this->setCentralWidget(zoomWidget); // Устанавливаем zoomWidget как центральный виджет
}

MainWindow::~MainWindow() {
    delete ui;
}
