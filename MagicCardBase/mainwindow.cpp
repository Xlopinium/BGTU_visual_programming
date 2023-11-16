#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonArray>
#include <QRegularExpression>
#include <QHeaderView>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    model(new QStandardItemModel(0, 8, this)), // Initialize the model
    proxyModel(new QSortFilterProxyModel(this)), // Initialize the proxyModel
    tableView(new QTableView(this)), // Initialize the tableView
    loadButton(new QPushButton("Download", this)),
    saveButton(new QPushButton("Save", this)),
    addButton(new QPushButton("Add a card", this)),
    removeButton(new QPushButton("Delete a card", this)),
    filterEdit(new QLineEdit(this)) {

    // Set up the model
    model->setHorizontalHeaderLabels({"Name", "Type", "Price", "Color", "Strength", "Endurance", "Features", "Text"});

    // Set up the proxy model
    proxyModel->setSourceModel(model);
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    // Set up the table view
    tableView->setModel(proxyModel);
    tableView->setSortingEnabled(true); // if you want sortable columns
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Set up the layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(loadButton);
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(removeButton);

    mainLayout->addWidget(filterEdit);
    mainLayout->addWidget(tableView);
    mainLayout->addLayout(buttonLayout);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // Set up the connections
    connect(filterEdit, &QLineEdit::textChanged, this, &MainWindow::filterChanged);
    connect(loadButton, &QPushButton::clicked, this, &MainWindow::loadCards);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::saveCards);
    connect(addButton, &QPushButton::clicked, this, &MainWindow::addCard);
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::removeCard);
}

MainWindow::~MainWindow() {
    // Очистка ресурсов???
}

void MainWindow::loadCards() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("JSON Files (*.json)"));
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("Error"), tr("Could not open the file"));
        return;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(data));
    QJsonArray array = doc.array();

    model->setRowCount(0);
    for (const QJsonValue &value : array) {
        QJsonObject obj = value.toObject();
        MagicCard card;
        card.readFromJsonObject(obj);

        QList<QStandardItem *> items;
        items << new QStandardItem(card.name)
              << new QStandardItem(card.type)
              << new QStandardItem(QString::number(card.price))
              << new QStandardItem(card.color)
              << new QStandardItem(card.power)
              << new QStandardItem(card.toughness)
              << new QStandardItem(card.features)
              << new QStandardItem(card.text);

        model->appendRow(items);
    }
}

void MainWindow::saveCards() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("JSON Files (*.json)"));
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, tr("Error"), tr("Failed to save file"));
        return;
    }

    QJsonArray array;
    for (int i = 0; i < model->rowCount(); ++i) {
        MagicCard card;
        card.name = model->item(i, 0)->text();
        card.type = model->item(i, 1)->text();
        card.price = model->item(i, 2)->text().toDouble();
        card.color = model->item(i, 3)->text();
        card.power = model->item(i, 4)->text();
        card.toughness = model->item(i, 5)->text();
        card.features = model->item(i, 6)->text();
        card.text = model->item(i, 7)->text();

        QJsonObject obj;
        card.writeToJsonObject(obj);
        array.append(obj);
    }

    QJsonDocument doc(array);
    file.write(doc.toJson());
}

void MainWindow::addCard() {
    MagicCard newCard;

    newCard.name = QInputDialog::getText(this, tr("Enter a name"), tr("Name:"));
    if (newCard.name.isEmpty()) return;

    newCard.type = QInputDialog::getText(this, tr("Enter the type"), tr("Type:"));
    if (newCard.type.isEmpty()) return;

    bool ok;
    QString price = QInputDialog::getText(this, tr("Enter the price"), tr("Price:"), QLineEdit::Normal, QString(), &ok);
    if (ok && !price.isEmpty()) {
        newCard.price = price.toDouble();
    } else {
        return;
    }

    newCard.color = QInputDialog::getText(this, tr("Enter the color"), tr("Color:"));
    if (newCard.color.isEmpty()) return;

    newCard.power = QInputDialog::getText(this, tr("Enter the power"), tr("Power:"));
    // Power can be empty, indicating that it may not be applicable for all card types.

    newCard.toughness = QInputDialog::getText(this, tr("Enter the toughness"), tr("Toughness:"));
    // Toughness can also be empty.

    newCard.features = QInputDialog::getText(this, tr("Enter the features"), tr("Features:"));
    // Features can be empty as well.

    newCard.text = QInputDialog::getText(this, tr("Enter the text"), tr("Text:"));
    // Text can be empty.

    QList<QStandardItem *> items;
    items << new QStandardItem(newCard.name)
          << new QStandardItem(newCard.type)
          << new QStandardItem(QString::number(newCard.price))
          << new QStandardItem(newCard.color)
          << new QStandardItem(newCard.power)
          << new QStandardItem(newCard.toughness)
          << new QStandardItem(newCard.features)
          << new QStandardItem(newCard.text);

    model->appendRow(items);
}

void MainWindow::removeCard() {
    QModelIndexList selection = tableView->selectionModel()->selectedRows();
    if (!selection.empty()) {
        int row = selection.first().row();
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr("Delete Card"), tr("Are you sure you want to delete this card?"),
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            model->removeRow(row);
        }
    } else {
        QMessageBox::information(this, tr("Select Card"), tr("Please select a card to delete."));
    }
}



void MainWindow::filterChanged(const QString &text) {
    proxyModel->setFilterKeyColumn(0); // Фильтрация по имени
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxyModel->setFilterRegularExpression(QRegularExpression(text, QRegularExpression::CaseInsensitiveOption));
}


