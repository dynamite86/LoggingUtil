#include "mainWindow.h"
#include "ui_mainWindow.h"

mainWindow::mainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::mainWindow)
{
    ui->setupUi(this);

    m_spamer = new Spamer;
    connect(m_spamer,               SIGNAL(logOutputSignal(bool,QString)), ui->textEdit, SLOT(addMessage(bool,QString)));
    connect(ui->dial_msgBufferSize, SIGNAL(valueChanged(int)),             ui->textEdit, SLOT(setMsgBufferSize(int)));

    ui->label_msgBufferSize->setText(QString("%1 msg").arg(ui->dial_msgBufferSize->value()));
    ui->textEdit->setMsgBufferSize(ui->dial_msgBufferSize->value());
}

mainWindow::~mainWindow()
{
    delete m_spamer;
    delete ui;
}

void mainWindow::on_pushButton_start_clicked()
{
    ui->textEdit->clear();
    m_spamer->start("./text.txt", ui->spinBox_minimumDelay->value(), ui->spinBox_maximumDelay->value());
}

void mainWindow::on_dial_msgBufferSize_valueChanged(int value)
{
    ui->label_msgBufferSize->setText(QString("%1 msg").arg(value));
    ui->textEdit->setMsgBufferSize(ui->dial_msgBufferSize->value());
}
