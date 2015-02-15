/*************************************************************************
File encoding: UTF-8.
*************************************************************************/

#ifndef LOGGINGFIELD_H
#define LOGGINGFIELD_H

#include <QtCore>
#include <QtWidgets>
#include <QtGui>

class LoggingField : public QTextEdit
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *event);

private:
    bool m_needRefreshFlag;
    QTimer *m_refreshTimer;
    int m_refreshInterval;
    Q_PROPERTY(int refreshInterval READ refreshInterval WRITE setRefreshInterval MEMBER m_refreshInterval)

private slots:
    void m_timerShot();

public slots:
    int refreshInterval() const;
    void setRefreshInterval(const int interval);

public:
    explicit LoggingField(QWidget *parent = 0);
    ~LoggingField();
};

#endif // LOGGINGFIELD_H
