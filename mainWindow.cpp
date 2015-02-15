#include "mainWindow.h"
#include "ui_mainWindow.h"

mainWindow::mainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::mainWindow)
{
    ui->setupUi(this);

    m_spamer = new Spamer;
    connect(m_spamer, SIGNAL(logOutputSignal(QString)), ui->textEdit, SLOT(append(QString)));
    connect(ui->spinBox_refreshInterval, SIGNAL(valueChanged(int)), ui->textEdit, SLOT(setRefreshInterval(int)));
    ui->textEdit->setRefreshInterval(ui->spinBox_refreshInterval->value());
}

mainWindow::~mainWindow()
{
    delete m_spamer;
    delete ui;
}

void mainWindow::on_pushButton_start_clicked()
{
    m_spamer->readFile("./text.txt");
}
