#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QStandardItemModel>
#include <QPushButton>
#include <QLineEdit>
#include <QSortFilterProxyModel>
#include <QInputDialog>
#include "magiccard.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void loadCards();
    void saveCards();
    void addCard();
    void removeCard();
    void filterChanged(const QString &text);

private:
    QTableView *tableView;
    QStandardItemModel *model;
    QSortFilterProxyModel *proxyModel;
    QPushButton *loadButton;
    QPushButton *saveButton;
    QPushButton *addButton;
    QPushButton *removeButton;
    QLineEdit *filterEdit;


    // Другие члены класса...
};

#endif // MAINWINDOW_H
