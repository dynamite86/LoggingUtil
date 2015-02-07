#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QtWidgets>
#include <QtGui>
#include "loggingUtil.h"
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
    void m_slotLog(QString message);
    void on_pushButton_start_clicked();


private:
    Ui::mainWindow *ui;
    loggingUtil    *m_loggingUtil;
    Spamer         *m_spamer;

};

#endif // MAINWINDOW_H
