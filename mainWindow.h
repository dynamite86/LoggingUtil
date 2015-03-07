#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QtWidgets>
#include <QtGui>
#include "LoggingField.h"
#include "spamer.h"

namespace Ui {
class mainWindow;
}

class mainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainWindow(QWidget *parent = 0);
    ~mainWindow();

private slots:
    void on_pushButton_start_clicked();
    void on_dial_msgBufferSize_valueChanged(int value);

private:
    Ui::mainWindow *ui;
    Spamer         *m_spamer;

};

#endif // MAINWINDOW_H
