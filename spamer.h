#ifndef SPAMER_H
#define SPAMER_H

#include <QtCore>

class SpamerThreadedProcessing : public QObject
{
    Q_OBJECT

private:
    QString m_filePath;

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
