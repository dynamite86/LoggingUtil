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
    int m_minDelay;
    int m_maxDelay;

private slots:
    void m_spamingStart();

public:
    explicit SpamerThreadedProcessing(QObject *parent = 0);
    ~SpamerThreadedProcessing();

    bool initSpaming(const QString &filePath, int minDelay, int maxDelay);

signals:
    void signalSpamingIsComplete();
    void logOutputSignal(const bool errorMsg = false, const QString msg = QString());
};

class Spamer : public QObject
{
    Q_OBJECT

private:
    SpamerThreadedProcessing *m_spamerThread;

public:
    explicit Spamer(QObject *parent = 0);
    ~Spamer();

public slots:
    bool start(const QString &filePath, const int minDelay, const int maxDelay);

signals:
    void logOutputSignal(const bool errorMsg = false, const QString msg = QString());
};

#endif // SPAMER_H
