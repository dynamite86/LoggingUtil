/*************************************************************************
File encoding: UTF-8.

Модуль для генерации и отправки сигналов с текстовыми сообщениями с интервалом 10...500мс.
Автор: dynamite, 2015.
*************************************************************************/

#ifndef SPAMER_H
#define SPAMER_H

#include <QtCore>
#include <windows.h>

class SpamerThreadedProcessing : public QObject
{
    Q_OBJECT

private:
    QFile m_file;

private slots:
    void m_spamingStart();

public:
    explicit SpamerThreadedProcessing(QObject *parent = 0);
    ~SpamerThreadedProcessing();

    bool initSpaming(const QString &filePath);

signals:
    void signalSpamingIsComplete();
    void logOutputSignal(QString msg);
};

class Spamer : public QObject
{
    Q_OBJECT

private:
    SpamerThreadedProcessing *m_spamerThread;

public:
    explicit Spamer(QObject *parent = 0);
    ~Spamer();

    bool readFile(const QString &filePath);

signals:
    void logOutputSignal(QString msg);
};

#endif // SPAMER_H
