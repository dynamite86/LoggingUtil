#include "mainWindow.h"
#include "ui_mainWindow.h"

mainWindow::mainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::mainWindow)
{
    ui->setupUi(this);

    m_loggingUtil = new loggingUtil;
    m_spamer      = new Spamer;
    connect(m_spamer,                      SIGNAL(logOutputSignal(QString)), m_loggingUtil,    SLOT(inputMessage(QString)));
    connect(m_loggingUtil,                 SIGNAL(outputMessage(QString)),   this,             SLOT(m_slotLog(QString)));
    connect(ui->spinBox_messageBufferSize, SIGNAL(valueChanged(int)),        m_loggingUtil,    SLOT(setBufferSize(int)));
    connect(ui->pushButton_clear,          SIGNAL(clicked()),                ui->textEdit_log, SLOT(clear()));

    ui->textEdit_log->hide();
    m_loggingUtil->setBufferSize(10);
}

mainWindow::~mainWindow()
{
    delete m_spamer;
    delete m_loggingUtil;
    delete ui;
}

void mainWindow::m_slotLog(QString message)
{
    ui->textEdit_log->append(message);
}

void mainWindow::on_pushButton_start_clicked()
{
    m_spamer->readFile("./L.N. Tolstoy - Voyna I Mir.txt");
}
