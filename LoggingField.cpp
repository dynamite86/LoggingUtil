/*************************************************************************
File encoding: UTF-8.
*************************************************************************/

#include "LoggingField.h"

void LoggingField::paintEvent(QPaintEvent *event)
{
    if(m_needRefreshFlag)
    {
        event->accept();
        m_needRefreshFlag = false;
    }
}

void LoggingField::m_timerShot()
{
    m_needRefreshFlag = true;
    this->update();
}

LoggingField::LoggingField(QWidget *parent) : QTextEdit(parent)
{
    m_refreshInterval = 10;
    m_needRefreshFlag = false;

    m_refreshTimer = new QTimer;
    connect(m_refreshTimer, SIGNAL(timeout()), this, SLOT(m_timerShot()));

    m_refreshTimer->setInterval(1000*m_refreshInterval);
    m_refreshTimer->start();
}

LoggingField::~LoggingField()
{
    if(m_refreshTimer->isActive())
    {
        m_refreshTimer->stop();
    }
    delete m_refreshTimer;
}

int LoggingField::refreshInterval() const
{
    return m_refreshInterval;
}

void LoggingField::setRefreshInterval(const int interval)
{
    if((interval > 0)&&(interval != m_refreshInterval))
    {
        m_refreshInterval = interval;
        m_refreshTimer->setInterval(1000*m_refreshInterval);
        if(m_refreshTimer->isActive())
        {
            m_refreshTimer->stop();
        }
        m_refreshTimer->start();
    }
}
