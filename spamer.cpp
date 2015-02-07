#include "spamer.h"

Spamer::Spamer(QObject *parent) : QObject(parent){}
Spamer::~Spamer(){}

bool Spamer::readFile(const QString &filePath)
{
    m_spamerThread = new SpamerThreadedProcessing(NULL);
    if(!m_spamerThread->initSpaming(filePath))
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
    connect(m_spamerThread,      SIGNAL(logOutputSignal(QString)),  this,                SIGNAL(logOutputSignal(QString)));

    threadForProcessing->start();
    return true;
}


void SpamerThreadedProcessing::m_spamingStart()
{
    QString buffer;
    QFile sourceFile(m_filePath);
    QTextDecoder decoder(QTextCodec::codecForName("UTF-8"));

    sourceFile.open(QIODevice::ReadOnly|QIODevice::Text);
    if((!sourceFile.isOpen())||(!sourceFile.isReadable()))
    {
        sourceFile.close();
        return;
    }

    while(!sourceFile.atEnd())
    {
        buffer.clear();
        buffer = decoder.toUnicode(sourceFile.readLine());
        if(buffer.contains("\n"))
        {
            buffer.remove("\n");
        }
        if(buffer.contains("\r"))
        {
            buffer.remove("\r");
        }
        logOutputSignal(buffer);
    }
    sourceFile.close();
    return;
}

SpamerThreadedProcessing::SpamerThreadedProcessing(QObject *parent) : QObject(parent){}
SpamerThreadedProcessing::~SpamerThreadedProcessing(){}

bool SpamerThreadedProcessing::initSpaming(const QString &filePath)
{
    if(filePath.isEmpty()){
        return false;
    }
    m_filePath = filePath;
    return true;
}
