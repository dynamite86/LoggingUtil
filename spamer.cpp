/*************************************************************************
File encoding: UTF-8.

Модуль для генерации и отправки сигналов с текстовыми сообщениями.
Автор: dynamite, 2015.
*************************************************************************/

#include "spamer.h"

Spamer::Spamer(QObject *parent) : QObject(parent){}
Spamer::~Spamer(){}

bool Spamer::start(const QString &filePath, const int minDelay, const int maxDelay)
{
    m_spamerThread = new SpamerThreadedProcessing(NULL);
    if(!m_spamerThread->initSpaming(filePath, minDelay, maxDelay))
    {
        delete m_spamerThread;
        return false;
    }
    QThread *threadForProcessing = new QThread;
    m_spamerThread->moveToThread(threadForProcessing);

    connect(threadForProcessing, SIGNAL(started()),                 m_spamerThread,      SLOT(m_spamingStart()));
    connect(threadForProcessing, SIGNAL(finished()),                threadForProcessing, SLOT(deleteLater()));
    connect(m_spamerThread,      SIGNAL(signalSpamingIsComplete()), m_spamerThread,      SLOT(deleteLater()));
    connect(m_spamerThread,      SIGNAL(signalSpamingIsComplete()), threadForProcessing, SLOT(quit()));

    connect(m_spamerThread, SIGNAL(logOutputSignal(bool,QString)), this, SIGNAL(logOutputSignal(bool,QString)));

    threadForProcessing->start();
    return true;
}

void SpamerThreadedProcessing::m_spamingStart()
{
    srand(QTime().msecsTo(QTime::currentTime()));
    m_file.open(QIODevice::ReadOnly|QIODevice::Text);
    while(!m_file.atEnd())
    {
        QString buffer = QTextDecoder(QTextCodec::codecForName("UTF-8")).toUnicode(m_file.readLine());
        if(buffer.contains("\n"))
        {
            buffer.remove("\n");
        }
        if(buffer.contains("\r"))
        {
            buffer.remove("\r");
        }
        logOutputSignal(false, buffer);
        Sleep((rand()%m_maxDelay + m_minDelay));
    }
    m_file.close();
    signalSpamingIsComplete();
    return;
}

SpamerThreadedProcessing::SpamerThreadedProcessing(QObject *parent) : QObject(parent){}

SpamerThreadedProcessing::~SpamerThreadedProcessing(){}

bool SpamerThreadedProcessing::initSpaming(const QString &filePath, int minDelay, int maxDelay)
{
    if(filePath.isEmpty())
    {
        return false;
    }
    m_file.setFileName(filePath);
    m_minDelay = minDelay;
    m_maxDelay = maxDelay;
    return true;
}

